#ifndef CHARACTER
#define CHARACTER

#include <gb/gb.h>
#include "Game_Object.h"
#include "Game_Sprite.h"

typedef struct GameCharacter
{
    UBYTE active;
    GameObject object;
    UBYTE facing;
    INT8 health;
    UBYTE max_health;
    UBYTE damage_timer;
    const GameAnimPackage* anims;
    const GameAnimation* current_anim;
    UBYTE anim_frame;
    UBYTE anim_tick;
    UBYTE overlap_anim;
    UBYTE ai_tick;
    void (*update)(struct GameCharacter*);

} GameCharacter;

typedef struct GameAdd
{
    UBYTE active;
    GameObject object;
    UBYTE facing;
    INT8 health;
    UBYTE max_health;
    UBYTE damage_timer;
    const GameAnimPackage* anims;
    const GameAnimation* current_anim;
    UBYTE anim_frame;
    UBYTE anim_tick;
    UBYTE overlap_anim;
    UBYTE ai_tick;
} GameAdd;

extern GameCharacter char_player;

extern GameCharacter char_enemy_1;
extern GameCharacter char_enemy_2;
extern GameCharacter char_enemy_3;
extern GameCharacter char_enemy_4;

#endif