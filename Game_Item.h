#ifndef ITEMS
#define ITEMS

#include <gb/gb.h>

#include "Game_Map.h"

typedef struct GameItem
{
    UBYTE equip;
    const GameSprite* sprite;
    void (*item_action)(void);

} GameItem;

typedef struct GameItemObject
{
    UBYTE active;
    GameObject object;
    const GameItem* item;

} GameItemObject;

typedef struct GameDrop
{
    const GameSprite* sprite;
    UBYTE size;
    void (*on_pickup)(void);

} GameDrop;

typedef struct GameDropObject
{
    UBYTE active;
    GameObject object;
    const GameDrop* drop;

} GameDropObject;

typedef struct GameChest
{
    UBYTE active;
    GameObject object;
    UBYTE open;
    const GameItem* item;
    Point room;

} GameChest;

extern const GameItem item_sword;

extern const GameDrop drop_heart;
extern const GameDrop drop_gold;

extern GameDropObject obj_drop_1;
extern GameDropObject obj_drop_2;

extern GameItemObject obj_item_1;

extern GameChest chest_1;
extern GameChest chest_2;

#endif