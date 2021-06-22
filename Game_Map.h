#ifndef MAPS
#define MAPS

#include <gb/gb.h>

#include "Game_Enemy.h"

typedef struct Point
{
    UBYTE x;
    UBYTE y;

} Point;

typedef struct GameTroop
{
    const GameEnemy* enemy;
    Point pos;

} GameTroop;

typedef struct GameMap
{
    UBYTE map_bank;
    UBYTE tileset;
    unsigned char* data;
    UBYTE type;
    UBYTE doors[4];
    GameTroop troops[5];

} GameMap;

extern const GameMap map_dungeon_1;

extern const GameMap map_dungeon_t;
extern const GameMap map_dungeon_b;
extern const GameMap map_dungeon_l;
extern const GameMap map_dungeon_r;
extern const GameMap map_dungeon_tb;
extern const GameMap map_dungeon_lr;
extern const GameMap map_dungeon_tlr;
extern const GameMap map_dungeon_blr;
extern const GameMap map_dungeon_tbl;
extern const GameMap map_dungeon_tbr;
extern const GameMap map_dungeon_tl;
extern const GameMap map_dungeon_tr;
extern const GameMap map_dungeon_bl;
extern const GameMap map_dungeon_br;

extern const GameMap map_dungeon_boss_t;
extern const GameMap map_dungeon_boss_b;
extern const GameMap map_dungeon_boss_l;
extern const GameMap map_dungeon_boss_r;

extern const GameMap map_dungeon_item_t;
extern const GameMap map_dungeon_item_b;
extern const GameMap map_dungeon_item_l;
extern const GameMap map_dungeon_item_r;

#endif