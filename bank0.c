#include <gb/gb.h>
#include <rand.h>
#include <string.h>

#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Map.h"
#include "Game_Character.h"
#include "Game_Sprite.h"
#include "Game_Enemy.h"
#include "Game_Item.h"
#include "Game_Projectile.h"

#include "Object_Tilesets.c"
#include "Object_Maps.c"
#include "Object_Characters.c"
#include "Object_Sprites.c"
#include "Object_Enemies.c"
#include "Object_Items.c"
#include "Object_Projectiles.c"

UBYTE Tileset = 1, Joy = 0;

UBYTE saved_bank = 0;
UBYTE bank_stack[15];
UBYTE bank_counter = 0;
UBYTE temp_bank;

const GameMap* current_map;

const GameMap* floor_map[11][11];
Point end_rooms[15];
UBYTE ctr_end_room = 0;
UBYTE room_open[11][11];
Point last_room = {0, 0};
UBYTE doors_open[4] = {false, false, false, false};

const GameItem* current_weapon = &item_sword;
const GameItem* current_use_item = NULL;

const GameItem* items[20];

UBYTE sprite_index = 0;

UBYTE sprite_column = 0, sprite_row = 0;

UBYTE gold = 0;

UBYTE room_x = 5, room_y = 5, room_count = 0, room_amount = 0, load_pos_x = 0, load_pos_y = 0, queue_pos = 0, queue_amount = 0, neighbor_count = 0, neighbors = 0;

UBYTE weapon_direction = up;

UBYTE map_x = 0, map_y = 0, line_x = 0, line_y = 0, map_pos_x = 0, map_pos_y = 0, offset_x = 0, offset_y = 0;

UBYTE collision_tick = 0, weapon_tick = 0;

UBYTE flag_weapon_out = false, flag_halt_movement = false, flag_weapon_hit = false, flag_action_button = false;

INT8 camera_x = 0, camera_y = 0;

INT8 i = 0, j = 0, x = 0, y = 0;

UBYTE u_i = 0, u_j = 0, u_x = 0, u_y = 0;

UINT16 u16_i = 0, u16_j = 0, u16_x = 0, u16_y = 0;

INT16 collision_x = 0, collision_y = 0, distance = 0, direction_x = 0, direction_y = 0, hitbox_1_x = 0, hitbox_1_y = 0, hitbox_2_x = 0, hitbox_2_y = 0, overlap = 0, root = 0, lowerbound = 0, upperbound = 0, temp_root = 0, temp_count = 0;

UBYTE temp_UBYTE = 0;

INT8 temp_INT8 = 0;

UINT16 temp_UINT16 = 0;

GameCharacter* temp_char = NULL;
const GameEnemy* temp_enemy = NULL;
GameProjectile* temp_projectile = NULL;
const GameAnimation* temp_anim = NULL;
GameItemObject* temp_obj_item = NULL;
GameDropObject* temp_obj_drop = NULL;
GameChest* temp_chest = NULL;

UBYTE door_count[4] = {false, false, false, false};

extern UINT16 Seed;
extern UBYTE saved_flag;

extern const unsigned char Font_Menu[];

/*  Engine Functions  */

INT16 sqrt(INT16 x)
{
    if(x < 0){return -1;}
    if(x == 0 || x == 1){return x;}

    lowerbound = 1;
    upperbound = x;
    root = lowerbound + (upperbound - lowerbound) / 2;

    while(root > x / root || root + 1 <= x / (root + 1))
    {
        if(root > x / root)
        {
            upperbound = root;
        }
        else
        {
            lowerbound = root;
        }

        root = lowerbound + (upperbound - lowerbound) / 2;
    }

    return root;
}

INT16 wabs(INT16 x)
{
    return x > 0 ? x : -x;
}

void switch_bank(UBYTE bank)
{
    if(bank_counter == 15){return;}

    bank_stack[bank_counter] = _current_bank;
    bank_counter++;

    SWITCH_ROM_MBC1(bank);
}

void return_bank()
{
    if(bank_counter == 0){return;}

    bank_counter--;
    temp_bank = bank_stack[bank_counter];

    SWITCH_ROM_MBC1(temp_bank);

}

void performant_delay(UBYTE num_loops)
{
    for(u_i = 0; u_i < num_loops; u_i++)
    {
        wait_vbl_done();
    }
}

UBYTE button_up(UBYTE button)
{
    if(joypad() & button){return false;}
    else{return true;}
}

UBYTE compare_string(char* string_1, char* string_2)
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

void set_anim_package(GameCharacter* character, const GameAnimPackage* anims)
{
    character->anims = anims;
}

void load_sprite_tiles(UBYTE target_bank, UBYTE first_tile, UBYTE num_tiles, const unsigned char* tiles)
{
    switch_bank(target_bank);

    set_sprite_data(first_tile, num_tiles, tiles);

    return_bank();
}

void load_bkg_tiles(UBYTE target_bank, UBYTE first_tile, UBYTE num_tiles, const unsigned char* tiles)
{
    saved_bank = _current_bank;

    switch_bank(target_bank);

    set_bkg_data(first_tile, num_tiles, tiles);

    return_bank();
}

void play_animation(GameCharacter* character, const GameAnimation* anim, UBYTE override, UBYTE overlap)
{
    if((character->current_anim != NULL && override == false) || (character->current_anim == anim && character->overlap_anim == false))
    {
        return;
    }

    character->current_anim = anim;
    character->anim_frame = 0;
    character->anim_tick = 0;
    character->overlap_anim = overlap;
}

void stop_animation(GameCharacter* character)
{
    character->current_anim = NULL;
    character->anim_frame = 0;
    character->anim_tick = 0;
}

void load_sprite(GameObject* object, const GameSprite* sprite)
{
    set_sprite_data(object->sprite_index, 4, sprite->tiles);
}

void build_object(GameObject* object)
{
    switch(object->size)
    {
        case size_2x2:
            set_sprite_tile(object->sprite_index, object->sprite_index);
            set_sprite_tile(object->sprite_index + 1, object->sprite_index + 1);
            set_sprite_tile(object->sprite_index + 2, object->sprite_index + 2);
            set_sprite_tile(object->sprite_index + 3, object->sprite_index + 3);
            break;
        case size_1x1:
            set_sprite_tile(object->sprite_index, object->sprite_index);
            break;
    }
}

void move_object(GameObject* object, UBYTE pos_x, UBYTE pos_y)
{
    switch(object->size)
    {
        case size_2x2:
            move_sprite(object->sprite_index, pos_x + 8, pos_y + 16);
            move_sprite(object->sprite_index + 1, pos_x + 8, pos_y + 24);
            move_sprite(object->sprite_index + 2, pos_x + 16, pos_y + 16);
            move_sprite(object->sprite_index + 3, pos_x + 16, pos_y + 24);

            object->width = 16;
            object->height = 16;
            break;
        case size_1x1:
            move_sprite(object->sprite_index, pos_x + 8, pos_y + 16);
            object->width = 8;
            object->height = 8;
            break;
    }

    object->pos_x = pos_x;
    object->pos_y = pos_y;
}

void print_number(UBYTE number, UBYTE pos_x, UBYTE pos_y);

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
    for(u_i = 0; u_i < 15; u_i++)
    {
        bank_stack[u_i] = 0;
    }

    for(u_i = 0; u_i < 11; u_i++)
    {
        for(u_j = 0; u_j < 11; u_j++)
        {
            floor_map[u_i][u_j] = NULL;
        }
    }

    for(u_i = 0; u_i < 11; u_i++)
    {
        for(u_j = 0; u_j < 11; u_j++)
        {
            room_open[u_i][u_j] = false;
        }
    }

    for(u_i = 0; u_i < 20; u_i++)
    {
        items[u_i] = NULL;
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

void Call_Draw_Map(const GameMap* map)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Map20(map); break;
        default: Draw_Map20(map); break;
    }

    return_bank();
}

void Call_Load_Map(const GameMap* map)
{
    switch_bank(bank3);

    Load_Map(map);

    return_bank();
}

void Call_Load_Floor()
{
    switch_bank(bank3);

    Load_Floor();

    return_bank();
}

void Call_Load_Sprite(GameObject* object, const GameSprite* sprite)
{
    switch_bank(sprite->bank);

    load_sprite(object, sprite);

    return_bank();
}

void Call_Load_Room_Enemies(const GameMap* map)
{
    switch_bank(bank3);

    Load_Room_Enemies(map);

    return_bank();
}

void Call_Load_Enemy(const GameEnemy* enemy, UBYTE pos_x, UBYTE pos_y)
{
    switch_bank(bank3);

    Load_Enemy(enemy, pos_x, pos_y);

    return_bank();
}

void Call_Clear_Enemy(GameCharacter* character)
{
    switch_bank(bank3);

    Clear_Enemy(character);

    return_bank();
}

void Call_Draw_Horizontal_Line(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Horizontal_Line20(map, pos_x, pos_y, tile_y); break;
        default: Draw_Horizontal_Line20(map, pos_x, pos_y, tile_y); break;
    }

    return_bank();
}

void Call_Draw_Vertical_Line(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y)
{
    switch_bank(map->map_bank);

    switch(map->map_bank)
    {
        case 20: Draw_Vertical_Line20(map, pos_x, pos_y, tile_y); break;
        default: Draw_Vertical_Line20(map, pos_x, pos_y, tile_y); break;
    }

    return_bank();
}

void Call_Draw_Tile(UINT16 tile_x, UINT16 tile_y, UBYTE tile_num)
{
    switch_bank(current_map->map_bank);

    switch(current_map->map_bank)
    {
        case 20: Draw_Tile20(tile_x, tile_y, tile_num); break;
        default: Draw_Tile20(tile_x, tile_y, tile_num); break;
    }

    return_bank();
}

UBYTE Call_Get_Collision(UBYTE pos_x, UBYTE pos_y, INT8 offset_x, INT8 offset_y, UBYTE type)
{
    switch_bank(current_map->map_bank);

    switch(current_map->map_bank)
    {
        case 20: u_i = Get_Collision20(pos_x, pos_y, offset_x, offset_y, type); break;
        default: u_i = Get_Collision20(pos_x, pos_y, offset_x, offset_y, type); break;
    }

    return_bank();

    return u_i;
}

void Call_Perform_Char_Update(GameCharacter* character)
{
    switch_bank(bank10);

    character->update(character);

    return_bank();
}

void Call_Perform_Item_Action(const GameItem* item)
{
    switch_bank(bank11);

    item->item_action();

    return_bank();
}

void Call_Perform_On_Collision(GameObject* object, UBYTE direction)
{
    switch_bank(bank10);

    object->on_collision(object, direction);

    return_bank();
}

void Call_Perform_Drop_Pickup(const GameDrop* drop)
{
    switch_bank(bank11);

    drop->on_pickup();

    return_bank();
}

void Call_Load_Menu_Font()
{
    switch_bank(bank3);

    set_bkg_data(0, 120, Font_Menu);

    return_bank();
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

    SWITCH_ROM_MBC1(bank2);

    build_object(&char_player.object);
    build_object(&char_enemy_1.object);
    build_object(&char_enemy_2.object);
    build_object(&char_enemy_3.object);

    Call_Load_Sprite(&char_player.object, &sprite_hiro_down_0);

    while(!joypad()){Seed++; if(Seed>=255)Seed=1;}
    
    initrand(Seed);

    Load_HUD();

    Update_Weapon_Icon();

    Call_Load_Floor();

	while(true)
	{
        ENABLE_RAM_MBC5;

        performant_delay(1);

        Update_Joypad();

        DISABLE_RAM_MBC5;
	}
}