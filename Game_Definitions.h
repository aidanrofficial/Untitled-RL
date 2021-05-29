#ifndef DEFINITIONS
#define DEFINITIONS

#include "Game_Map.h"
#include "Game_Character.h"

extern UBYTE Tileset, Joy;

extern UINT16 Seed;

extern const GameMap* current_map;

extern const GameMap* floor_map[11][11];

extern UBYTE door_count[4];

extern UBYTE room_x, room_y, room_count, room_amount, load_pos_x, load_pos_y, queue_pos, queue_amount, neighbor_count, neighbors;

extern UBYTE map_x, map_y, line_x, line_y;

extern UBYTE collision_tick;

extern INT8 camera_x, camera_y;

extern INT8 i, j, x, y;

extern UBYTE u_i, u_j, u_x, u_y;

extern UINT16 u16_i, u16_j, u16_x, u16_y;

extern INT16 collision_x, collision_y, distance, overlap;

extern UBYTE temp_UBYTE;

extern INT8 temp_INT8;

extern UINT16 temp_UINT16;

extern GameCharacter* temp_char;

/*  Condition Definitions  */
#define false 0
#define true 1

/*  Direction Definitions  */
#define up 0
#define down 1
#define left 2
#define right 3
#define idle 4

/*  Map Size Definitions  */
#define MIN_SIZE_X 0
#define MAX_SIZE_X 144
#define MIN_SIZE_Y 0
#define MAX_SIZE_Y 112

/*  Bank Definitions  */
#define bank0 0
#define bank1 1
#define bank2 2
#define bank3 3
#define bank4 4
#define bank20 20

#endif