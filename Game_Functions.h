#ifndef FUNCTIONS
#define FUNCTIONS

#include <gb/gb.h>

#include "Game_Map.h"
#include "Game_Object.h"
#include "Game_Character.h"
#include "Game_Sprite.h"
#include "Game_Item.h"

/*  Engine Functions  */
extern INT16 wabs(INT16 x);
extern INT16 sqrt(INT16 x);

extern void switch_bank(UBYTE bank);
extern void performant_delay(UBYTE num_loops);
extern UBYTE button_up(UBYTE button);

extern void set_anim_package(GameCharacter* character, const GameAnimPackage* anims);
extern void load_sprite_tiles(UBYTE target_bank, UBYTE first_tile, UBYTE num_tiles, const unsigned char* tiles);
extern void load_bkg_tiles(UBYTE target_bank, UBYTE first_tile, UBYTE num_tiles, const unsigned char* tiles);
extern void play_animation(GameCharacter* character, const GameAnimation* anim, UBYTE override, UBYTE overlap);
extern void stop_animation(GameCharacter* character);
extern void load_sprite(GameObject* object, const GameSprite* sprite);
extern void build_object(GameObject* object);
extern void move_object(GameObject* object, UBYTE pos_x, UBYTE pos_y);

extern UBYTE get_rand(UBYTE min, UBYTE max);

extern void fade_in();
extern void fade_out();

/*  Bank 0  */
extern void Call_Draw_Map(const GameMap* map);
extern void Call_Load_Map(const GameMap* map);
extern void Call_Load_Floor();
extern void Call_Load_Sprite(GameObject* object, const GameSprite* sprite);
extern void Call_Load_Room_Enemies(const GameMap* map);
extern void Call_Load_Enemy(const GameEnemy* enemy, UBYTE pos_x, UBYTE pos_y);
extern void Call_Clear_Enemy(GameCharacter* character);
extern void Call_Draw_Horizontal_Line(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern void Call_Draw_Vertical_Line(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern void Call_Draw_Tile(UINT16 tile_x, UINT16 tile_y, UBYTE tile_num);
extern UBYTE Call_Get_Collision(UBYTE pos_x, UBYTE pos_y, INT8 offset_x, INT8 offset_y, UBYTE type);
extern void Call_Perform_Char_Update(GameCharacter* character);
extern void Call_Perform_Chest_Update(GameChest* chest);
extern void Call_Perform_Item_Action(const GameItem* item);
extern void Call_Perform_On_Collision(GameObject* object, UBYTE direction);
extern void Call_Perform_Drop_Pickup(const GameDrop* drop);
extern void Call_Load_Menu_Font();

/*  Bank 2  */
extern void Load_HUD();
extern void Hide_HUD();
extern void Update_Weapon_Icon();
extern void Update_Joypad();

/*  Bank 3  */
extern void Load_Enemy(const GameEnemy* enemy, UBYTE pos_x, UBYTE pos_y);
extern void Load_Room_Enemies(const GameMap* map);
extern void Clear_Enemy(GameCharacter* character);
extern void Load_Tileset(UBYTE tileset);
extern void Load_Map(const GameMap* map);
extern void Load_Floor();

/*  Bank 20  */
extern void Draw_Map20(const GameMap* map);
extern void Draw_Tile20(UINT16 tile_x, UINT16 tile_y, UBYTE tile_num);
extern UBYTE Get_Collision20(UBYTE x1, UBYTE y1, INT8 offset_x, INT8 offset_y, UBYTE type);
extern void Draw_Horizontal_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern void Draw_Vertical_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_x);

#endif