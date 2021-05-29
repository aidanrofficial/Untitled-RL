#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Map.h"

extern const unsigned char Map_Dungeon_1;
extern const unsigned char Map_Dungeon_T;
extern const unsigned char Map_Dungeon_B;
extern const unsigned char Map_Dungeon_L;
extern const unsigned char Map_Dungeon_R;
extern const unsigned char Map_Dungeon_TB;
extern const unsigned char Map_Dungeon_LR;
extern const unsigned char Map_Dungeon_TLR;
extern const unsigned char Map_Dungeon_BLR;
extern const unsigned char Map_Dungeon_TBL;
extern const unsigned char Map_Dungeon_TBR;
extern const unsigned char Map_Dungeon_TL;
extern const unsigned char Map_Dungeon_TR;
extern const unsigned char Map_Dungeon_BL;
extern const unsigned char Map_Dungeon_BR;

/*  Game Maps  */
const GameMap map_dungeon_1 = {bank20, 1, &Map_Dungeon_1, {{NULL, {0, 0}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_t = {bank20, 1, &Map_Dungeon_T, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_b = {bank20, 1, &Map_Dungeon_B, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_l = {bank20, 1, &Map_Dungeon_L, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_r = {bank20, 1, &Map_Dungeon_R, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tb = {bank20, 1, &Map_Dungeon_TB, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_lr = {bank20, 1, &Map_Dungeon_LR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tlr = {bank20, 1, &Map_Dungeon_TLR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_blr = {bank20, 1, &Map_Dungeon_BLR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tbl = {bank20, 1, &Map_Dungeon_TBL, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tbr = {bank20, 1, &Map_Dungeon_TBR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tl = {bank20, 1, &Map_Dungeon_TL, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tr = {bank20, 1, &Map_Dungeon_TR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_bl = {bank20, 1, &Map_Dungeon_BL, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_br = {bank20, 1, &Map_Dungeon_BR, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};