#ifndef __STAS_H__
#define __STAS_H__

#include "types.h"

typedef enum {
    PAUSE,
    PLAYING,
    QUIT,
    MENU,
    SETTINGS,
    GAME_OVER
} game_event_state_t;

typedef struct {
    u8 mouse_b1_pressed;
    u8 mouse_b2_pressed;
    f32 click_sleep;
} mouse_t;


typedef struct {
    mouse_t mouse_state;
    game_event_state_t game_event_state;
} game_states_t;

#endif