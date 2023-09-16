#define SDL_MAIN_HANDLED

#include "game.h"


int main(int argc, char *argv[]) {
    init();
    loop();

    return 0;
}
