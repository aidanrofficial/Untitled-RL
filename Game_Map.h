#include <gb/gb.h>
#include "Game_Enemy.h"

#ifndef MAPS
#define MAPS

typedef struct Point
{
    UBYTE pos_x;
    UBYTE pos_y;

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

#endif