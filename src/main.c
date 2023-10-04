#define SDL_MAIN_HANDLED

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include "game.h"


int main(int argc, char *argv[]) {
    init();
    loop();

    return 0;
}
