#ifndef OBJECT
#define OBJECT

#include <gb/gb.h>

#include "Game_Character.h"

typedef struct GameObject
{
    UBYTE pos_x;
    UBYTE pos_y;
    INT8 velocity_x;
    INT8 velocity_y;
    UBYTE sprite_index;
    UBYTE size;
    UBYTE width;
    UBYTE height;
    UBYTE floating;
    void (*on_collision)(struct GameObject*, UBYTE);

} GameObject;

#endif