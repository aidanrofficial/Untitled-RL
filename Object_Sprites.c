#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Sprite.h"

extern const unsigned char Tiles_Clear;

extern const unsigned char Tiles_HiroBLK0; 
extern const unsigned char Tiles_HiroBLK1;
extern const unsigned char Tiles_HiroBLK2;
extern const unsigned char Tiles_HiroBLK3;
extern const unsigned char Tiles_HiroBLK4;
extern const unsigned char Tiles_HiroBLK5;
extern const unsigned char Tiles_HiroBLK6;
extern const unsigned char Tiles_HiroBLK7;

extern const unsigned char Tiles_Hiro_AttackBLK0;
extern const unsigned char Tiles_Hiro_AttackBLK1;
extern const unsigned char Tiles_Hiro_AttackBLK2;
extern const unsigned char Tiles_Hiro_AttackBLK3;
extern const unsigned char Tiles_Hiro_AttackBLK4;
extern const unsigned char Tiles_Hiro_AttackBLK5;
extern const unsigned char Tiles_Hiro_AttackBLK6;
extern const unsigned char Tiles_Hiro_AttackBLK7;

extern const unsigned char Tiles_BatBLK0;
extern const unsigned char Tiles_BatBLK1;
extern const unsigned char Tiles_BatBLK2;
extern const unsigned char Tiles_BatBLK4;

extern const unsigned char Tiles_WormBLK0;
extern const unsigned char Tiles_WormBLK1;

extern const unsigned char Tiles_Item_Sword;

extern const unsigned char Tiles_Drop_Heart;

extern const unsigned char Tiles_ChestBLK0;
extern const unsigned char Tiles_ChestBLK1;

/*  Game Sprites  */
const GameSprite sprite_clear = {&Tiles_Clear, bank4};

const GameSprite sprite_hiro_up_0 = {&Tiles_HiroBLK0, bank4};
const GameSprite sprite_hiro_up_1 = {&Tiles_HiroBLK1, bank4};
const GameSprite sprite_hiro_down_0 = {&Tiles_HiroBLK2, bank4};
const GameSprite sprite_hiro_down_1 = {&Tiles_HiroBLK3, bank4};
const GameSprite sprite_hiro_left_0 = {&Tiles_HiroBLK4, bank4};
const GameSprite sprite_hiro_left_1 = {&Tiles_HiroBLK5, bank4};
const GameSprite sprite_hiro_right_0 = {&Tiles_HiroBLK6, bank4};
const GameSprite sprite_hiro_right_1 = {&Tiles_HiroBLK7, bank4};

const GameSprite sprite_hiro_attack_up_0 = {&Tiles_Hiro_AttackBLK0, bank4};
const GameSprite sprite_hiro_attack_up_1 = {&Tiles_Hiro_AttackBLK1, bank4};
const GameSprite sprite_hiro_attack_down_0 = {&Tiles_Hiro_AttackBLK2, bank4};
const GameSprite sprite_hiro_attack_down_1 = {&Tiles_Hiro_AttackBLK3, bank4};
const GameSprite sprite_hiro_attack_left_0 = {&Tiles_Hiro_AttackBLK4, bank4};
const GameSprite sprite_hiro_attack_left_1 = {&Tiles_Hiro_AttackBLK5, bank4};
const GameSprite sprite_hiro_attack_right_0 = {&Tiles_Hiro_AttackBLK6, bank4};
const GameSprite sprite_hiro_attack_right_1 = {&Tiles_Hiro_AttackBLK7, bank4};

const GameSprite sprite_bat_down_0 = {&Tiles_BatBLK2, bank4};
const GameSprite sprite_bat_down_hurt = {&Tiles_BatBLK4, bank4};

const GameSprite sprite_worm_head_up_0 = {&Tiles_WormBLK0, bank4};

const GameSprite sprite_item_sword = {&Tiles_Item_Sword, bank4};

const GameSprite sprite_drop_heart = {&Tiles_Drop_Heart, bank4};

const GameSprite sprite_chest_closed = {&Tiles_ChestBLK0, bank4};
const GameSprite sprite_chest_open = {&Tiles_ChestBLK1, bank4};

/*  Game Animations  */
const GameAnimation anim_hiro_up = {{&sprite_hiro_up_0, &sprite_hiro_up_1}, 2, 7};
const GameAnimation anim_hiro_down = {{&sprite_hiro_down_0, &sprite_hiro_down_1}, 2, 7};
const GameAnimation anim_hiro_left = {{&sprite_hiro_left_0, &sprite_hiro_left_1}, 2, 7};
const GameAnimation anim_hiro_right = {{&sprite_hiro_right_0, &sprite_hiro_right_1}, 2, 7};

const GameAnimation anim_hiro_attack_up = {{&sprite_hiro_attack_up_0, &sprite_hiro_attack_up_1, &sprite_hiro_up_0}, 3, 7};
const GameAnimation anim_hiro_attack_down = {{&sprite_hiro_attack_down_0, &sprite_hiro_attack_down_1, &sprite_hiro_down_0}, 3, 7};
const GameAnimation anim_hiro_attack_left = {{&sprite_hiro_attack_left_0, &sprite_hiro_attack_left_1, &sprite_hiro_left_0}, 3, 7};
const GameAnimation anim_hiro_attack_right = {{&sprite_hiro_attack_right_0, &sprite_hiro_attack_right_1, &sprite_hiro_right_0}, 3, 7};

const GameAnimation anim_bat_down = {{&sprite_bat_down_0, &sprite_bat_down_0}, 2, 7};
const GameAnimation anim_bat_down_hurt = {{&sprite_bat_down_hurt, &sprite_bat_down_0}, 2, 7};

const GameAnimation anim_worm_head_up = {{&sprite_worm_head_up_0}, 1, 7};

/*  Game Anim Packages  */
const GameAnimPackage anim_hiro = {&anim_hiro_up, &anim_hiro_down, &anim_hiro_left, &anim_hiro_right};

const GameAnimPackage anim_hiro_face_up = {&anim_hiro_up, &anim_hiro_up, &anim_hiro_up, &anim_hiro_up};
const GameAnimPackage anim_hiro_face_down = {&anim_hiro_down, &anim_hiro_down, &anim_hiro_down, &anim_hiro_down};
const GameAnimPackage anim_hiro_face_left = {&anim_hiro_left, &anim_hiro_left, &anim_hiro_left, &anim_hiro_left};
const GameAnimPackage anim_hiro_face_right = {&anim_hiro_right, &anim_hiro_right, &anim_hiro_right, &anim_hiro_right};

const GameAnimPackage anim_bat = {&anim_bat_down, &anim_bat_down, &anim_bat_down, &anim_bat_down};

const GameAnimPackage anim_worm_head = {&anim_worm_head_up, &anim_worm_head_up, &anim_worm_head_up, &anim_worm_head_up};