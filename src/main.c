#define SDL_MAIN_HANDLED

#define STB_DS_IMPLEMENTATION

#include "game.h"


int main(int argc, char *argv[]) {
    init();
    loop();

    return 0;
}
