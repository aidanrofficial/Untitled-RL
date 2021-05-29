#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Sprite.h"

extern const unsigned char Tiles_Clear;
extern const unsigned char Tiles_CollisionBLK1;

extern const unsigned char Tiles_HiroBLK0;
extern const unsigned char Tiles_HiroBLK1;
extern const unsigned char Tiles_HiroBLK2;
extern const unsigned char Tiles_HiroBLK3;
extern const unsigned char Tiles_HiroBLK4;
extern const unsigned char Tiles_HiroBLK5;
extern const unsigned char Tiles_HiroBLK6;
extern const unsigned char Tiles_HiroBLK7;
extern const unsigned char Tiles_HiroBLK8;
extern const unsigned char Tiles_HiroBLK9;

extern const unsigned char Tiles_BatBLK0;

/*  Game Sprites  */
const GameSprite sprite_clear = {&Tiles_Clear, bank4};
const GameSprite sprite_collision = {&Tiles_CollisionBLK1, bank4};

const GameSprite sprite_hiro_up_0 = {&Tiles_HiroBLK9, bank4};
const GameSprite sprite_hiro_down_0 = {&Tiles_HiroBLK0, bank4};
const GameSprite sprite_hiro_left_0 = {&Tiles_HiroBLK3, bank4};
const GameSprite sprite_hiro_right_0 = {&Tiles_HiroBLK6, bank4};

const GameSprite sprite_bat_left_0 = {&Tiles_BatBLK0, bank4};

/*  Game Sprite Packages  */
const GameSpritePackage sprite_clear_all = {{&sprite_clear, &sprite_clear}};

const GameSpritePackage sprite_hiro_up = {{&sprite_hiro_up_0, &sprite_clear}};
const GameSpritePackage sprite_hiro_down = {{&sprite_hiro_down_0, &sprite_clear}};
const GameSpritePackage sprite_hiro_left = {{&sprite_hiro_left_0, &sprite_clear}};
const GameSpritePackage sprite_hiro_right = {{&sprite_hiro_right_0, &sprite_clear}};

const GameSpritePackage sprite_bat_left = {{&sprite_bat_left_0, &sprite_clear}};

/*  Game Character Sprites  */
const GameCharSprite sprite_hiro = {&sprite_hiro_up, &sprite_hiro_down, &sprite_hiro_left, &sprite_hiro_right};
const GameCharSprite sprite_bat = {&sprite_bat_left, &sprite_bat_left, &sprite_bat_left, &sprite_bat_left};