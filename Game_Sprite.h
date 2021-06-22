#include <gb/gb.h>

#ifndef GAME_SPRITE
#define GAME_SPRITE

typedef struct GameSprite
{
    const unsigned char* tiles;
    UBYTE bank;

} GameSprite;

typedef struct GameAnimation
{
    const GameSprite* sprites[3];
    UBYTE frames;
    UBYTE duration;

} GameAnimation;

typedef struct GameAnimPackage
{
    const GameAnimation* char_up;
    const GameAnimation* char_down;
    const GameAnimation* char_left;
    const GameAnimation* char_right;

} GameAnimPackage;

extern const GameSprite sprite_clear;

extern const GameSprite sprite_hiro_down_0;

extern const GameSprite sprite_bat_down_0;
extern const GameSprite sprite_bat_down_hurt;

extern const GameSprite sprite_chest_closed;
extern const GameSprite sprite_chest_open;

extern const GameAnimation anim_hiro_up;
extern const GameAnimation anim_hiro_down;
extern const GameAnimation anim_hiro_left;
extern const GameAnimation anim_hiro_right;

extern const GameAnimation anim_hiro_attack_up;
extern const GameAnimation anim_hiro_attack_down;
extern const GameAnimation anim_hiro_attack_left;
extern const GameAnimation anim_hiro_attack_right;

extern const GameAnimation anim_bat_down;
extern const GameAnimation anim_bat_down_hurt;

extern const GameAnimPackage anim_hiro;
extern const GameAnimPackage anim_hiro_face_up;
extern const GameAnimPackage anim_hiro_face_down;
extern const GameAnimPackage anim_hiro_face_left;
extern const GameAnimPackage anim_hiro_face_right;

extern const GameAnimPackage anim_bat;

extern const GameAnimPackage anim_worm_head;

#endif