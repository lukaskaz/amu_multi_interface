#include <string>
#include <thread>
#include <functional>

#include <unistd.h>
#include <signal.h>

#include "logging.hpp"
#include "support.hpp"
#include "interface.hpp"

#include "gui_init.hpp"

#include "console.hpp"

#include "conversions.hpp"


static bool exit_service = false;

void signal_handler(int sig)
{
    Log trace;

    trace.log("Received signal: " + CONV_NUM_GET_STR(int32_t, hex, sig));
    exit_service = true;
}

void qtGuiThread(void)
{
    Log trace;

    start_gui();
    trace.log("QT Thread started!!");
}

int main(int argc, char* argv[])
{
    Log trace;
    completeData data;
    ipcCommunication &ipc = ipcCommunication::get_instance();

    signal(SIGINT, signal_handler);

    std::thread serverThread(serveHttpThread, std::ref(ipc.get_ipc()));
    serverThread.detach();

    std::thread consoleThread(serveConsoleThread, std::ref(ipc.get_ipc()));
    consoleThread.detach();

    std::thread qtThread(qtGuiThread);
    qtThread.detach();

    int i = 0;
    while(exit_service == false) {
        if(ipc.isIpcPending() == true) {
            data = ipc.getData();
        }

        trace.log("Waiting for http requests, already received " + \
            std::to_string(data.web.request_nb) + " requests");
        if(data.web.name.size() > 0 && data.web.nick.size() > 0) {
            trace.log("Last user name: " + data.web.name + " (nick: " + data.web.nick + ")");
        }

        trace.log("Speed: " + std::to_string(data.speed.value));
        sleep(1);
    }
}

