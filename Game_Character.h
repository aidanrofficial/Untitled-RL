#include <gb/gb.h>
#include "Game_Sprite.h"

#ifndef CHARACTER
#define CHARACTER

typedef struct GameCharacter
{
    unsigned char name[15];
    UBYTE active;
    UBYTE pos_y;
    UBYTE pos_x;
    UBYTE sprite_index;
    UBYTE facing;
    INT8 velocity_x;
    INT8 velocity_y;
    const GameCharSprite* sprites;

} GameCharacter;

extern GameCharacter char_player;

extern GameCharacter char_enemy_1;
extern GameCharacter char_enemy_2;
extern GameCharacter char_enemy_3;
extern GameCharacter char_enemy_4;

#endif