#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "logging.hpp"


typedef void (Log::*log_fn_t)(const std::string &, const std::string &);

std::mutex Log::log_mtx;
std::ofstream Log::log_stream;

Log::Log(): Log(true, false, false, false)
{
    if(log_stream.is_open() == false) {
        char tmp_pipe[] = ("/tmp/logfifo_pipe");

        remove(tmp_pipe);
        if (mkfifo(tmp_pipe, 0777) == 0) {
            std::string cmd("gnome-terminal -e \"cat "+ std::string(tmp_pipe) +"\"");

            if(system(cmd.c_str()) == 0) {
                log_stream.open(tmp_pipe, std::ios::out);
            }
        }
    }
}

void Log::log(log_t type, const std::string &source, const std::string &txt)
{
    static log_fn_t log_fn[] =
    {
        [LOG_SIMPLE] = &Log::log_simple,
        [LOG_ERROR]  = &Log::log_error,
        [LOG_INFO]   = &Log::log_info,
        [LOG_DEBUG]  = &Log::log_debug
    };
    static const uint8_t log_fn_size = sizeof(log_fn)/sizeof(*log_fn);

    if(type < log_fn_size && log_fn[type] != NULL) {
        std::unique_lock<std::mutex> lock(log_mtx);
        (this->*log_fn[type])(source, txt);
        lock.unlock();
    }
}

void Log::log_simple(const std::string &source, const std::string &txt)
{
    if(SHOW_SIMPLE_LOGS == true) {
        log_stream<<"[LOG] "<<txt<<std::endl;
    }
}

void Log::log_error(const std::string &source, const std::string &txt)
{
    if(SHOW_ERROR_LOGS == true) {
        log_stream<<"[ERROR]["<<source<<"] "<<txt<<std::endl;
    }
}

void Log::log_info(const std::string &source, const std::string &txt)
{
    if(SHOW_INFO_LOGS == true) {
        log_stream<<"[INFO]["<<source<<"] "<<txt<<std::endl;
    }
}

void Log::log_debug(const std::string &source, const std::string &txt)
{
    if(SHOW_DEBUG_LOGS == true) {
        log_stream<<"[DEBUG]["<<source<<"] "<<txt<<std::endl;
    }
}

