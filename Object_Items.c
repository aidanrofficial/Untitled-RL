#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Item.h"
#include "Game_Sprite.h"

extern void Chest_Ai(GameChest* chest);

extern void Sword_Action();

extern void Heart_Pickup();

/*  Game Items  */
const GameItem item_sword = {true, &sprite_item_sword, &Sword_Action};

/*  Game Drops  */
const GameDrop drop_heart = {&sprite_drop_heart, size_1x1, &Heart_Pickup};

/*  Game Drop Objects */
GameDropObject obj_drop_1 = {false, {0, 0, 0, 0, 20, size_1x1, 8, 8, false, NULL}, NULL};
GameDropObject obj_drop_2 = {false, {0, 0, 0, 0, 22, size_1x1, 8, 8, false, NULL}, NULL};

/*  Game Item Objects  */
GameItemObject obj_item_1 = {false, {0, 0, 0, 0, 24, size_2x2, 16, 16, false, NULL}, NULL};

/*  Game Chests  */
GameChest chest_1 = {false, {0, 0, 0, 0, 4, size_2x2, 16, 16, false, NULL}, false, NULL, {0, 0}};
GameChest chest_2 = {false, {0, 0, 0, 0, 8, size_2x2, 16, 16, false, NULL}, false, NULL, {0, 0}};