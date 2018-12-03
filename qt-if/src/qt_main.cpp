#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "gui_init.hpp"
#include "gui.hpp"



int start_gui(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, &deploy_window, NULL);

    return 0;
}



