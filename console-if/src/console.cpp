#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

#include "console.hpp"

static const char* main_menu[] =
{
    "##### AMU CONTROL MENU #####",
    "# [1] Select speed         #",
    "# [2] Select lighting      #",
    "# [3] Select signal        #",
    "############################",
    "> "
};

static const char* speed_menu[] =
{
    "###### AMU SPEED MENU ######",
    "# [1] Read speed           #",
    "# [2] Set speed            #",
    "#                          #",
    "# [0] Return to main menu  #",
    "############################",
    "> "
};

void clear_screen(void)
{
    system("clear");
}

int8_t show_menu(int id, bool &changed, ipcData &data)
{
    static int speed = 0;
    int sel = (-1);
    unsigned int i = 0;

    changed = false;

    clear_screen();
    if(id == 1) {
        size_t menu_size = sizeof(speed_menu)/sizeof(speed_menu[0]);

        for(i = 0; i < (menu_size-1); i++) {
            std::cout<<speed_menu[i]<<std::endl;
        }
        std::cout<<speed_menu[i];
        std::cout.flush();

        std::cin>>sel;
        std::cin.ignore(100, '\n');

        if(sel == 1) {
            sel = 4;
        }
        else if(sel == 2) {
            sel = 5;
        }
        else if(sel != 0){
            sel = 1;
        }
        else {
            //return to main menu
        }
    }
    else if(id == 4) {
        std::cout<<"Current speed: "<<speed;
        getchar();
        sel = 1;
    }
    else  if(id == 5) {
        std::cout<<"Enter speed: ";
        std::cin>>speed;
        data.type = IPC_DATA_SPEED;
        data.speed.value = speed;
        changed = true;
        sel = 1;
    }
    else {
        sel = 0;
    }

    return sel;
}

void serveConsoleThread(ipcDataStream<ipcData> &ipc_data_stream)
{
    int sel = (-1);
    unsigned int i = 0;
    size_t menu_size = sizeof(main_menu)/sizeof(main_menu[0]);
    ipcData ipc_data;
    bool new_data = false;

    while(1) {
        clear_screen();
        for(i = 0; i < (menu_size-1); i++) {
            std::cout<<main_menu[i]<<std::endl;
        }
        std::cout<<main_menu[i];
        std::cout.flush();

        std::cin>>sel;

        if(sel > 0 && sel < 4) {
            while(sel) {
                sel = show_menu(sel, new_data, ipc_data);
                if(new_data == true) {
                    ipc_data_stream.put(ipc_data);
                }
            }
        }
        else {
            std::cout<<"Selection not supported, try again!"<<std::endl;
            sleep(3);
        }
    }
}
