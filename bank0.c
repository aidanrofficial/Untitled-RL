#include <gb/gb.h>
#include <rand.h>
#include <string.h>
#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Map.h"
#include "Game_Character.h"
#include "Game_Sprite.h"
#include "Game_Enemy.h"
#include "Object_Tilesets.c"
#include "Object_Maps.c"
#include "Object_Characters.c"
#include "Object_Sprites.c"
#include "Object_Enemies.c"

UBYTE Tileset = 1, Joy = 0;

const GameMap* current_map;

const GameMap* floor_map[11][11];

UBYTE room_x = 5, room_y = 5, room_count = 0, room_amount = 0, load_pos_x = 0, load_pos_y = 0, queue_pos = 0, queue_amount = 0, neighbor_count = 0, neighbors = 0;

UBYTE map_x = 0, map_y = 0, line_x = 0, line_y = 0;

UBYTE collision_tick = 0;

INT8 camera_x = 0, camera_y = 0;

INT8 i = 0, j = 0, x = 0, y = 0;

UBYTE u_i = 0, u_j = 0, u_x = 0, u_y = 0;

UINT16 u16_i = 0, u16_j = 0, u16_x = 0, u16_y = 0;

INT16 collision_x = 0, collision_y = 0, distance = 0, overlap = 0, root = 0, temp_root = 0, temp_count = 0;

UBYTE temp_UBYTE = 0;

INT8 temp_INT8 = 0;

UINT16 temp_UINT16 = 0;

GameCharacter* temp_char = NULL;

UBYTE door_count[4] = {false, false, false, false};

extern UINT16 Seed;
extern UBYTE saved_flag;

/*  Engine Functions  */

INT16 sqrt(INT16 x)
{
    root = x / 2;
    temp_root = 0;
    temp_count = 0;

    while(root != temp_root)
    {
        temp_root = root;
        root = (x / temp_root + temp_root) / 2;

        temp_count++;
        if(temp_count > 10)
        {
            return root;
        }
    }

    return root;
}

INT16 wabs(INT16 x)
{
    return x > 0 ? x : -x;
}

void switch_bank(UBYTE bank)
{
    SWITCH_ROM_MBC1(bank);
}

void performant_delay(UBYTE num_loops)
{
    for(u_i = 0; u_i < num_loops; u_i++)
    {
        wait_vbl_done();
    }
}

UBYTE Compare_String(char* string_1, char* string_2)
{
    if(strlen(string_1) == strlen(string_2))
    {
        for(u_i = 0; u_i < strlen(string_1); u_i++)
        {
            if(string_1[u_i] != string_2[u_i])
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

void set_char_sprite(GameCharacter* character, const GameCharSprite* sprites)
{
    character->sprites = sprites;
}

void load_sprite(GameCharacter* character, const GameSprite* sprite)
{
    set_sprite_data(character->sprite_index, 4, sprite->tiles);
}

void build_char(GameCharacter* character)
{
    set_sprite_tile(character->sprite_index, character->sprite_index);
    set_sprite_tile(character->sprite_index + 1, character->sprite_index + 1);
    set_sprite_tile(character->sprite_index + 2, character->sprite_index + 2);
    set_sprite_tile(character->sprite_index + 3, character->sprite_index + 3);
}

void move_char(GameCharacter* character, UBYTE pos_x, UBYTE pos_y)
{
    move_sprite(character->sprite_index, pos_x + 8, pos_y + 16);
    move_sprite(character->sprite_index + 1, pos_x + 8, pos_y + 24);
    move_sprite(character->sprite_index + 2, pos_x + 16, pos_y + 16);
    move_sprite(character->sprite_index + 3, pos_x + 16, pos_y + 24);

    character->pos_x = pos_x;
    character->pos_y = pos_y;
}

UBYTE get_rand(UBYTE min, UBYTE max)
{
    return min + (rand() % (max - min));
}

void set_faded()
{
    BGP_REG = 0xFF;
    OBP0_REG = 0xFF;
}

void set_unfaded()
{
    BGP_REG = 0xE4;
    OBP0_REG = 0xD0;
}

void fade_out()
{
    for(i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0:
                BGP_REG = 0xE4;
                OBP0_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                OBP0_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                OBP0_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;
                OBP0_REG = 0xFF;
                break;
        }

        performant_delay(4);
    }
}

void fade_in()
{
    for(i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0:
                BGP_REG = 0xFF;
                OBP0_REG = 0xFF;
                break;
            case 1:
                BGP_REG = 0xFE;
                OBP0_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xF9;
                OBP0_REG = 0xE4;
                break;
            case 3:
                BGP_REG = 0xE4;
                OBP0_REG = 0xD0;
                break;
        }

        performant_delay(4);
    }
}

void initialize_variables()
{
    for(u_i = 0; u_i < 11; u_i++)
    {
        for(u_j = 0; u_j < 11; u_j++)
        {
            floor_map[u_i][u_j] = NULL;
        }
    }
}

void vbl_seed_isr()
{
    Seed += 1;
    if(Seed >= 1000){Seed = 0;}
}

void interrupt_handler()
{
    disable_interrupts();

    add_VBL(vbl_seed_isr);

    enable_interrupts();

    set_interrupts(VBL_IFLAG);
}

/*  Call Functions  */

void Call_Draw_Map(UBYTE bank, const GameMap* map)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Map20(map); break;
        default: Draw_Map20(map); break;
    }

    switch_bank(bank);
}

void Call_Load_Map(UBYTE bank, const GameMap* map)
{
    switch_bank(bank3);

    Load_Map(map);

    switch_bank(bank);
}

void Call_Load_Floor(UBYTE bank)
{
    switch_bank(bank3);

    Load_Floor();

    switch_bank(bank);
}

void Call_Load_Sprite(UBYTE bank, GameCharacter* character, const GameSprite* sprite)
{
    switch_bank(sprite->bank);

    load_sprite(character, sprite);

    switch_bank(bank);
}

void Call_Load_Room_Enemies(UBYTE bank, const GameMap* map)
{
    switch_bank(bank3);

    Load_Room_Enemies(map);

    switch_bank(bank);
}

void Call_Load_Enemy(UBYTE bank, const GameEnemy* enemy, UBYTE pos_x, UBYTE pos_y)
{
    switch_bank(bank3);

    Load_Enemy(enemy, pos_x, pos_y);

    switch_bank(bank);
}

void Call_Clear_Enemy(UBYTE bank, GameCharacter* character)
{
    switch_bank(bank3);

    Clear_Enemy(character);

    switch_bank(bank);
}

void Call_Draw_Horizontal_Line(UBYTE bank, const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Horizontal_Line20(map, pos_x, pos_y, tile_y); break;
        default: Draw_Horizontal_Line20(map, pos_x, pos_y, tile_y); break;
    }

    switch_bank(bank);
}

void Call_Draw_Vertical_Line(UBYTE bank, const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Vertical_Line20(map, pos_x, pos_y, tile_y); break;
        default: Draw_Vertical_Line20(map, pos_x, pos_y, tile_y); break;
    }

    switch_bank(bank);
}

UBYTE Call_Get_Collision(UBYTE bank, UBYTE direction, UBYTE pos_x, UBYTE pos_y)
{
    switch_bank(current_map->map_bank);

    switch(current_map->map_bank)
    {
        case 20: u_i = Get_Collision20(direction, pos_x, pos_y); break;
        default: u_i = Get_Collision20(direction, pos_x, pos_y); break;
    }

    switch_bank(bank);

    return u_i;
}

void main()
{
    SHOW_BKG;
    HIDE_WIN;

    ENABLE_RAM_MBC5;

    if(saved_flag != 1)
    {
        Seed = 0;
        saved_flag = 1;
    }

    SHOW_SPRITES;

    interrupt_handler();

    switch_bank(bank2);

    build_char(&char_player);

    Call_Load_Sprite(bank2, &char_player, &sprite_hiro_down_0);

    while(!joypad()){Seed++; if(Seed>=255)Seed=1;}
    
    initrand(Seed);

    Hide_HUD();

    Call_Load_Floor(bank2);

	while(true)
	{
        ENABLE_RAM_MBC5;

        performant_delay(1);

        Update_Joypad();
        move_char(&char_player, char_player.pos_x, char_player.pos_y);
        move_char(&char_enemy_1, char_enemy_1.pos_x, char_enemy_1.pos_y);

        DISABLE_RAM_MBC5;
	}
}