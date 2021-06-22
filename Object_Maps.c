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

extern const unsigned char Map_Dungeon_Boss_T;
extern const unsigned char Map_Dungeon_Boss_B;
extern const unsigned char Map_Dungeon_Boss_L;
extern const unsigned char Map_Dungeon_Boss_R;

extern const unsigned char Map_Dungeon_Item_T;
extern const unsigned char Map_Dungeon_Item_B;
extern const unsigned char Map_Dungeon_Item_L;
extern const unsigned char Map_Dungeon_Item_R;

/*  Game Maps  */
const GameMap map_dungeon_1 = {bank20, 1, &Map_Dungeon_1, room_normal, {true, true, true, true}, {{NULL, {0, 0}}, {NULL, {0, 0}}}};

const GameMap map_dungeon_t = {bank20, 1, &Map_Dungeon_T, room_normal, {true, false, false, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_b = {bank20, 1, &Map_Dungeon_B, room_normal, {false, true, false, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_l = {bank20, 1, &Map_Dungeon_L, room_normal, {false, false, true, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_r = {bank20, 1, &Map_Dungeon_R, room_normal, {false, false, false, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tb = {bank20, 1, &Map_Dungeon_TB, room_normal, {true, true, false, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_lr = {bank20, 1, &Map_Dungeon_LR, room_normal, {false, false, true, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tlr = {bank20, 1, &Map_Dungeon_TLR, room_normal, {true, false, true, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_blr = {bank20, 1, &Map_Dungeon_BLR, room_normal, {false, true, true, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tbl = {bank20, 1, &Map_Dungeon_TBL, room_normal, {true, true, true, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tbr = {bank20, 1, &Map_Dungeon_TBR, room_normal, {true, true, false, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tl = {bank20, 1, &Map_Dungeon_TL, room_normal, {true, false, true, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_tr = {bank20, 1, &Map_Dungeon_TR, room_normal, {true, false, false, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_bl = {bank20, 1, &Map_Dungeon_BL, room_normal, {false, true, true, false}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_br = {bank20, 1, &Map_Dungeon_BR, room_normal, {false, true, false, true}, {{&enemy_bat, {48, 48}}, {NULL, {0, 0}}}};

const GameMap map_dungeon_boss_t = {bank20, 1, &Map_Dungeon_Boss_T, room_boss, {true, false, false, false}, {{&boss_worm_head, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_boss_b = {bank20, 1, &Map_Dungeon_Boss_B, room_boss, {false, true, false, false}, {{&boss_worm_head, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_boss_l = {bank20, 1, &Map_Dungeon_Boss_L, room_boss, {false, false, true, false}, {{&boss_worm_head, {48, 48}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_boss_r = {bank20, 1, &Map_Dungeon_Boss_R, room_boss, {false, false, false, true}, {{&boss_worm_head, {48, 48}}, {NULL, {0, 0}}}};

const GameMap map_dungeon_item_t = {bank20, 1, &Map_Dungeon_Item_T, room_item, {true, false, false, false}, {{NULL, {0, 0}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_item_b = {bank20, 1, &Map_Dungeon_Item_B, room_item, {false, true, false, false}, {{NULL, {0, 0}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_item_l = {bank20, 1, &Map_Dungeon_Item_L, room_item, {false, false, true, false}, {{NULL, {0, 0}}, {NULL, {0, 0}}}};
const GameMap map_dungeon_item_r = {bank20, 1, &Map_Dungeon_Item_R, room_item, {false, false, false, true}, {{NULL, {0, 0}}, {NULL, {0, 0}}}};