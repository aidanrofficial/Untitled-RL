#ifndef ENEMYS
#define ENEMYS

#include <gb/gb.h>

#include "Game_Sprite.h"
#include "Game_Character.h"

typedef struct GameEnemy
{
    UBYTE health;
    const GameAnimPackage* anims;
    UBYTE floating;
    void (*enemy_ai)(GameCharacter*);
    void (*enemy_col)(GameObject*, UBYTE);

} GameEnemy;

extern const GameEnemy enemy_bat;

extern const GameEnemy boss_worm_head;

#endif