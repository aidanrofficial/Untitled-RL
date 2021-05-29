#include <gb/gb.h>
#include "Game_Sprite.h"

#ifndef ENEMYS
#define ENEMYS

typedef struct GameEnemy
{
    UBYTE health;
    const GameCharSprite* sprites;

} GameEnemy;

extern const GameEnemy enemy_bat;

#endif