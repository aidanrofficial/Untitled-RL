#include <gb/gb.h>

#ifndef GAME_SPRITE
#define GAME_SPRITE

typedef struct GameSprite
{
    unsigned char* tiles;
    UBYTE bank;
} GameSprite;

typedef struct GameSpritePackage
{
    GameSprite* sprites[3];

} GameSpritePackage;

typedef struct GameCharSprite
{
    GameSpritePackage* char_up;
    GameSpritePackage* char_down;
    GameSpritePackage* char_left;
    GameSpritePackage* char_right;

} GameCharSprite;

extern const GameSprite sprite_clear;
extern const GameSprite sprite_collision;

extern const GameSprite sprite_hiro_up_0;
extern const GameSprite sprite_hiro_down_0;
extern const GameSprite sprite_hiro_down_1;
extern const GameSprite sprite_hiro_down_2;
extern const GameSprite sprite_hiro_left_0;
extern const GameSprite sprite_hiro_right_0;

extern const GameSprite sprite_bat_left_0;

extern const GameSpritePackage sprite_clear_all;

extern const GameSpritePackage sprite_hiro_up;
extern const GameSpritePackage sprite_hiro_down;
extern const GameSpritePackage sprite_hiro_left;
extern const GameSpritePackage sprite_hiro_right;

extern const GameSpritePackage sprite_bat_left;

extern const GameCharSprite sprite_hiro;
extern const GameCharSprite sprite_bat;

#endif