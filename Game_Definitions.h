#ifndef DEFINITIONS
#define DEFINITIONS

#include "Game_Map.h"
#include "Game_Character.h"
#include "Game_Projectile.h"
#include "Game_Item.h"

extern UBYTE Tileset, Joy;

extern UINT16 Seed;

extern const GameMap* current_map;

extern const GameMap* floor_map[11][11];
extern Point end_rooms[15];
extern UBYTE ctr_end_room;
extern UBYTE room_open[11][11];
extern Point last_room;
extern UBYTE doors_open[4];

extern const GameItem* current_weapon;
extern const GameItem* current_use_item;

extern const GameItem* items[20];

extern UBYTE door_count[4];

extern UBYTE room_x, room_y, room_count, room_amount, load_pos_x, load_pos_y, queue_pos, queue_amount, neighbor_count, neighbors;

extern UBYTE weapon_direction;

extern UBYTE map_x, map_y, line_x, line_y, map_pos_x, map_pos_y, offset_x, offset_y;

extern UBYTE collision_tick, weapon_tick;

extern UBYTE flag_weapon_out, flag_halt_movement, flag_weapon_hit, flag_action_button;

extern INT8 camera_x, camera_y;

extern INT8 i, j, x, y;

extern UBYTE u_i, u_j, u_x, u_y;

extern UINT16 u16_i, u16_j, u16_x, u16_y;

extern INT16 collision_x, collision_y, distance, direction_x, direction_y, hitbox_1_x, hitbox_1_y, hitbox_2_x, hitbox_2_y, overlap;

extern UBYTE temp_UBYTE;

extern INT8 temp_INT8;

extern UINT16 temp_UINT16;

extern GameCharacter* temp_char;
extern const GameEnemy* temp_enemy;
extern GameProjectile* temp_projectile;
extern const GameAnimation* temp_anim;
extern GameItemObject* temp_obj_item;
extern GameDropObject* temp_obj_drop;
extern GameChest* temp_chest;

/*  Condition Definitions  */
#define false 0
#define true 1

/*  Object Size Definitions  */
#define size_2x2 0
#define size_1x1 1
#define size_1x2 2
#define size_3x3 3

/*  Direction Definitions  */
#define up 0
#define down 1
#define left 2
#define right 3
#define idle 4

/*  Collision Definitions  */
#define floor 0
#define wall 1
#define obstruction 2
#define door 3

/*  Map Size Definitions  */
#define MIN_SIZE_X 0
#define MAX_SIZE_X 144
#define MIN_SIZE_Y 0
#define MAX_SIZE_Y 112

/*  Room Type Definitions  */
#define room_normal 0
#define room_boss 1
#define room_item 2

/*  Bank Definitions  */
#define bank0 0
#define bank1 1
#define bank2 2
#define bank3 3
#define bank4 4
#define bank10 10
#define bank11 11
#define bank20 20

#endif