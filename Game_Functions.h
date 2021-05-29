#include <gb/gb.h>
#include "Game_Map.h"
#include "Game_Character.h"
#include "Game_Sprite.h"

#ifndef FUNCTIONS
#define FUNCTIONS

/*  Engine Functions  */
extern INT16 wabs(INT16 x);
extern INT16 sqrt(INT16 x);

extern void performant_delay(UBYTE num_loops);
extern void switch_bank(UBYTE bank);

extern void set_char_sprite(GameCharacter* character, const GameCharSprite* sprites);
extern void load_sprite(GameCharacter* character, const GameSprite* sprite);
extern void build_char(GameCharacter* character);
extern void move_char(GameCharacter* character, UBYTE pos_x, UBYTE pos_y);

extern UBYTE get_rand(UBYTE min, UBYTE max);

extern void fade_in();
extern void fade_out();

/*  Bank 0  */
extern void Call_Draw_Map(UBYTE bank, const GameMap* map);
extern void Call_Load_Map(UBYTE bank, const GameMap* map);
extern void Call_Load_Floor(UBYTE bank);
extern void Call_Load_Sprite(UBYTE bank, GameCharacter* character, const GameSprite* sprite);
extern void Call_Load_Room_Enemies(UBYTE bank, const GameMap* map);
extern void Call_Load_Enemy(UBYTE bank, const GameEnemy* enemy, UBYTE pos_x, UBYTE pos_y);
extern void Call_Clear_Enemy(UBYTE bank, GameCharacter* character);
extern void Call_Draw_Horizontal_Line(UBYTE bank, const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern void Call_Draw_Vertical_Line(UBYTE bank, const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern UBYTE Call_Get_Collision(UBYTE bank, UBYTE direction, UBYTE pos_x, UBYTE pos_y);

/*  Bank 2  */
extern void build_char(GameCharacter* character);
extern void move_char(GameCharacter* character, UBYTE pos_x, UBYTE pos_y);

extern void Show_HUD();
extern void Hide_HUD();
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
extern UBYTE Get_Collision20(UBYTE direction, UBYTE pos_x, UBYTE pos_y);
extern void Draw_Horizontal_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y);
extern void Draw_Vertical_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_x);

#endif