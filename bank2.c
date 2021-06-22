#include <gb/gb.h>
#include <rand.h>
#include <stdlib.h>

#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Character.h"
#include "Game_Projectile.h"
#include "Game_Map.h"

#include "Maps/Map_HUD.c"
#include "Tiles/Tiles_HUD.c"

const unsigned char temp_char_room[1] = {0x01};
const unsigned char temp_char_current[1] = {0x02};

const UBYTE tile_heart_full[1] = {0xF0};
const UBYTE tile_heart_half[1] = {0xF1};
const UBYTE tile_heart_empty[1] = {0xF2};

const UBYTE tile_weapon_icon[4] = {0xEC, 0xEE, 0xED, 0xEF};

GameChest* Find_Free_Chest()
{
    if(!chest_1.active)
    {
        return &chest_1;
    }
    else if(!chest_2.active)
    {
        return &chest_2;
    }
    
    return NULL;
}

GameItemObject* Find_Free_Item_Object()
{
    if(!obj_item_1.active)
    {
        return &obj_item_1;
    }

    return NULL;
}

GameDropObject* Find_Free_Drop_Object()
{
    if(!obj_drop_1.active)
    {
        return &obj_drop_1;
    }
    else if(!obj_drop_2.active)
    {
        return &obj_drop_2;
    }

    return NULL;
}

UBYTE Do_Circles_Overlap(UBYTE x1, UBYTE y1, UBYTE x2, UBYTE y2)
{
    collision_x = x1 - x2;
    collision_y = y1 - y2;

    return wabs((collision_x) * (collision_x) + (collision_y) * (collision_y)) <= 144;
}

UBYTE Do_Rectangles_Overlap(UBYTE x1, UBYTE y1, UBYTE width1, UBYTE height1, UBYTE x2, UBYTE y2, UBYTE width2, UBYTE height2)
{
    return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

UBYTE Do_Hitboxes_Overlap(UBYTE x1, UBYTE y1, UBYTE width1, UBYTE height1, UBYTE x2, UBYTE y2, UBYTE width2, UBYTE height2)
{
    hitbox_1_x = x1 + (width1 / 2);
    hitbox_1_y = y1 + (height1 / 2);

    hitbox_2_x = x2 + (width2 / 2);
    hitbox_2_y = y2 + (height2 / 2);

    distance = hitbox_1_x - hitbox_2_x;
    distance = wabs(distance);

    if(distance < width2)
    {
        distance = hitbox_1_y - hitbox_2_y;
        distance = wabs(distance);

        if(distance < height2)
        {
            return true;
        }
    }

    return false;
}

void Update_Player()
{
    if(char_player.object.velocity_x > 0){char_player.object.velocity_x--;}
    else if(char_player.object.velocity_x < 0){char_player.object.velocity_x++;}

    if(char_player.object.velocity_y > 0){char_player.object.velocity_y--;}
    else if(char_player.object.velocity_y < 0){char_player.object.velocity_y++;}
}

void Update_Chest(GameChest* chest)
{
    if(chest->object.velocity_x > 0){chest->object.velocity_x--;}
    else if(chest->object.velocity_x < 0){chest->object.velocity_x++;}

    if(chest->object.velocity_y > 0){chest->object.velocity_y--;}
    else if(chest->object.velocity_y < 0){chest->object.velocity_y++;}
}

void Object_Movement(GameObject* object)
{
    if(object->velocity_x > 0)
    {
        collision_x = object->pos_x + object->velocity_x + 14;
        collision_y = object->pos_y + 4;

        if((Call_Get_Collision(collision_x, collision_y, 0, 11, obstruction) == false || object->floating) && Call_Get_Collision(collision_x, collision_y, 0, 11, wall) == false)
        {
            if(Call_Get_Collision(collision_x, collision_y, 0, 11, door) == false || room_open[room_y][room_x] == true)
            {
                object->pos_x += object->velocity_x;
                move_object(object, object->pos_x, object->pos_y);
            }
            else if(object->on_collision != NULL){Call_Perform_On_Collision(object, right);}
        }
        else if(object->on_collision != NULL){Call_Perform_On_Collision(object, right);}
    }
    else if(object->velocity_x < 0)
    {
        collision_x = object->pos_x + object->velocity_x + 2;
        collision_y = object->pos_y + 4;

        if((Call_Get_Collision(collision_x, collision_y, 0, 11, obstruction) == false || object->floating) && Call_Get_Collision(collision_x, collision_y, 0, 11, wall) == false)
        {
            if(Call_Get_Collision(collision_x, collision_y, 0, 11, door) == false || room_open[room_y][room_x] == true)
            {
                object->pos_x += object->velocity_x;
                move_object(object, object->pos_x, object->pos_y);
            }
            else if(object->on_collision != NULL){Call_Perform_On_Collision(object, left);}
        }
        else if(object->on_collision != NULL){Call_Perform_On_Collision(object, left);}
    }

    if(object->velocity_y > 0)
    {
        collision_x = object->pos_x + 2;
        collision_y = object->pos_y + object->velocity_y + 15;
        
        if((Call_Get_Collision(collision_x, collision_y, 12, 0, obstruction) == false || object->floating) && Call_Get_Collision(collision_x, collision_y, 12, 0, wall) == false)
        {
            if(Call_Get_Collision(collision_x, collision_y, 12, 0, door) == false || room_open[room_y][room_x] == true)
            {
                object->pos_y += object->velocity_y;
                move_object(object, object->pos_x, object->pos_y);
            }
            else if(object->on_collision != NULL){Call_Perform_On_Collision(object, down);}
        }
        else if(object->on_collision != NULL){Call_Perform_On_Collision(object, down);}
    }
    else if(object->velocity_y < 0)
    {
        collision_x = object->pos_x + 2;
        collision_y = object->pos_y + object->velocity_y + 4;

        if((Call_Get_Collision(collision_x, collision_y, 12, 0, obstruction) == false || object->floating) && Call_Get_Collision(collision_x, collision_y, 12, 0, wall) == false)
        {
            if(Call_Get_Collision(collision_x, collision_y, 12, 0, door) == false || room_open[room_y][room_x] == true)
            {
                object->pos_y += object->velocity_y;
                move_object(object, object->pos_x, object->pos_y);
            }
            else if(object->on_collision != NULL){Call_Perform_On_Collision(object, up);}
        }
        else if(object->on_collision != NULL){Call_Perform_On_Collision(object, up);}    
    }
}

void Clear_Projectile(GameProjectile* projectile)
{
    projectile->active = false;
    projectile->pos_x = 0;
    projectile->pos_y = 0;
    projectile->velocity_x = 0;
    projectile->velocity_y = 0;
    projectile->size_x = 0;
    projectile->size_y = 0;
    projectile->friendly = true;
}

void Projectile_Movement(GameProjectile* projectile)
{
    if(projectile->life_cycles == 0)
    {
        Clear_Projectile(projectile);
    }

    if(projectile->life_cycles > 0){projectile->life_cycles--;}
}

GameCharacter* Is_Colliding_Enemy()
{
    if(Do_Rectangles_Overlap(char_player.object.pos_x, char_player.object.pos_y, 16, 16, char_enemy_1.object.pos_x, char_enemy_1.object.pos_y, 16, 16))
    {
        return &char_enemy_1;
    }
    
    return NULL;
}

GameProjectile* Is_Colliding_Projectile(GameCharacter* character)
{
    if(Do_Hitboxes_Overlap(character->object.pos_x, character->object.pos_y, 16, 16, projectile_1.pos_x, projectile_1.pos_y, projectile_1.size_x, projectile_1.size_y))
    {
        return &projectile_1;
    }

    return NULL;
}

GameChest* Is_Colliding_Chest()
{
    if(Do_Rectangles_Overlap(char_player.object.pos_x + 1, char_player.object.pos_y + 1, 14, 14, chest_1.object.pos_x + 1, chest_1.object.pos_y + 1, 14, 14))
    {
        return &chest_1;
    }
    else if(Do_Rectangles_Overlap(char_player.object.pos_x + 1, char_player.object.pos_y + 1, 14, 14, chest_2.object.pos_x + 1, chest_2.object.pos_y + 1, 14, 14))
    {
        return &chest_2;
    }

    return NULL;
}

GameDropObject* Is_Colliding_Drop()
{
    if(obj_drop_1.active == true && Do_Rectangles_Overlap(char_player.object.pos_x, char_player.object.pos_y, 16, 16, obj_drop_1.object.pos_x, obj_drop_1.object.pos_y, obj_drop_1.object.width, obj_drop_1.object.height))
    {
        return &obj_drop_1;
    }
    else if(obj_drop_2.active == true && Do_Rectangles_Overlap(char_player.object.pos_x, char_player.object.pos_y, 16, 16, obj_drop_2.object.pos_x, obj_drop_2.object.pos_y, obj_drop_2.object.width, obj_drop_2.object.height))
    {
        return &obj_drop_2;
    }

    return NULL;
}

void Check_Chests()
{
    if(chest_1.active && chest_1.room.x == room_x && chest_1.room.y == room_y)
    {
        move_object(&chest_1.object, chest_1.object.pos_x, chest_1.object.pos_y);
        load_sprite_tiles(bank4, chest_1.object.sprite_index, 4, sprite_chest_closed.tiles);
    }

    if(chest_2.active && chest_2.room.x == room_x && chest_2.room.y == room_y)
    {
        move_object(&chest_2.object, chest_2.object.pos_x, chest_2.object.pos_y);
        load_sprite_tiles(bank4, chest_2.object.sprite_index, 4, sprite_chest_closed.tiles);
    }
}

void Hide_Chest(GameChest* chest)
{
    load_sprite_tiles(bank4, chest->object.sprite_index, 4, sprite_clear.tiles);
}

void Load_Chest(UBYTE pos_x, UBYTE pos_y, const GameItem* item)
{
    temp_chest = Find_Free_Chest();

    if(temp_chest == NULL){return;}

    temp_chest->active = true;
    temp_chest->object.pos_x = pos_x;
    temp_chest->object.pos_y = pos_y;
    temp_chest->object.velocity_x = 0;
    temp_chest->object.velocity_y = 0;
    temp_chest->open = false;
    temp_chest->item = item;
    temp_chest->room.x = room_x;
    temp_chest->room.y = room_y;

    build_object(&temp_chest->object);

    move_object(&temp_chest->object, pos_x, pos_y);
    load_sprite_tiles(bank4, temp_chest->object.sprite_index, 4, sprite_chest_closed.tiles);
}

void Clear_Chest(GameChest* chest)
{
    chest->active = false;
    chest->object.pos_x = 0;
    chest->object.pos_y = 0;
    chest->object.velocity_x = 0;
    chest->object.velocity_y = 0;
    chest->open = false;
    chest->item = NULL;
    chest->room.x = 0;
    chest->room.y = 0;

    load_sprite_tiles(bank4, temp_chest->object.sprite_index, 4, sprite_clear.tiles);
}

void Check_Room_Cleared()
{
    if(char_enemy_1.active == false && char_enemy_2.active == false && char_enemy_3.active == false && char_enemy_4.active == false)
    {
        if(room_open[room_y][room_x] == false)
        {
            if(current_map->type == room_boss)
            {
                Load_Chest(80, 48, &item_sword);
            }

            for(u_i = 0; u_i < 4; u_i++)
            {
                if(current_map->doors[u_i] == true)
                {
                    doors_open[u_i] = true;

                    switch(u_i)
                    {
                        case up: Call_Draw_Tile(camera_x + 10, camera_y + 0, 10); break;
                        case down: Call_Draw_Tile(camera_x + 10, camera_y + 14, 11); break;
                        case left: Call_Draw_Tile(camera_x + 0, camera_y + 6, 13); break;
                        case right: Call_Draw_Tile(camera_x + 18, camera_y + 6, 12); break;
                    }
                }
            }

            room_open[room_y][room_x] = true;
        }
    }
}

void Damage_Knockback(GameCharacter* character1, UBYTE x2, UBYTE y2)
{
    collision_x = (character1->object.pos_x + 8) - x2;
    collision_y = (character1->object.pos_y + 8) - y2;

    distance = sqrt((collision_x * collision_x) + (collision_y * collision_y));

    if(collision_x / distance > 0){direction_x = 1;}
    else if(collision_x / distance < 0){direction_x = -1;}
    else{direction_x = 0;}

    if(collision_y / distance > 0){direction_y = 1;}
    else if(collision_y / distance < 0){direction_y = -1;}
    else{direction_y = 0;}

    character1->object.velocity_x += 8 * direction_x;
    character1->object.velocity_y += 8 * direction_y;
}

void Damage_Character(GameCharacter* character, UBYTE damage)
{
    if(character->health - damage < 0){character->health = 0;}
    else{character->health -= damage;}
}

void Push_Object(GameObject* object_1, GameObject* object_2)
{
    //    collision_x = (object_1->pos_x) - (object_2->pos_x);
    //    collision_y = (object_1->pos_y) - (object_2->pos_y);
    //
    //    distance = sqrt((collision_x * collision_x) + (collision_y * collision_y));
    //
    //    object_1->velocity_x += collision_x / distance;
    //    object_1->velocity_y += collision_y / distance;
    //
    //    object_2->velocity_x -= collision_x / distance;
    //    object_2->velocity_y -= collision_y / distance;

    if(object_1->pos_x < object_2->pos_x){object_1->velocity_x--; object_2->velocity_x++;}
    else if(object_1->pos_x > object_2->pos_x){object_1->velocity_x++; object_2->velocity_x--;}

    if(object_1->pos_y < object_2->pos_y){object_1->velocity_y--; object_2->velocity_y++;}
    else if(object_1->pos_y > object_2->pos_y){object_1->velocity_y++; object_2->velocity_y--;}
}

void Update_Player_Health()
{
    for(u_i = 0; u_i < (char_player.max_health / 2); u_i++)
    {
        if(char_player.health >= (u_i + 1) * 2)
        {
            set_win_tiles(15 + u_i, 0, 1, 1, tile_heart_full);
        }
        else if(char_player.health == ((u_i + 1) * 2) - 1)
        {
            set_win_tiles(15 + u_i, 0, 1, 1, tile_heart_half);
        }
        else
        {
            set_win_tiles(15 + u_i, 0, 1, 1, tile_heart_empty);
        }
    }
}

void Load_Drop(const GameDrop* drop, UBYTE pos_x, UBYTE pos_y)
{
    temp_obj_drop = Find_Free_Drop_Object();

    temp_obj_drop->active = true;
    temp_obj_drop->object.pos_x = pos_x;
    temp_obj_drop->object.pos_y = pos_y;
    temp_obj_drop->object.velocity_x = 0;
    temp_obj_drop->object.velocity_y = 0;
    temp_obj_drop->object.size = drop->size;
    temp_obj_drop->drop = drop;

    build_object(&temp_obj_drop->object);

    switch(drop->size)
    {
        case size_1x1:
            load_sprite_tiles(bank4, temp_obj_drop->object.sprite_index, 1, drop->sprite->tiles);
            break;
        case size_1x2:
            load_sprite_tiles(bank4, temp_obj_drop->object.sprite_index, 2, drop->sprite->tiles);
            break;
    }

    move_object(&temp_obj_drop->object, temp_obj_drop->object.pos_x, temp_obj_drop->object.pos_y);
}

void Clear_Drop(GameDropObject* drop_object)
{
    drop_object->active = false;
    drop_object->object.pos_x = 0;
    drop_object->object.pos_y = 0;
    drop_object->object.velocity_x = 0;
    drop_object->object.velocity_y = 0;
    drop_object->object.size = size_1x1;
    drop_object->drop = NULL;

    load_sprite_tiles(bank4, drop_object->object.sprite_index, 2, sprite_clear.tiles);
}

void Object_Collision()
{
    if(char_player.damage_timer > 0){char_player.damage_timer--;}
    if(char_enemy_1.damage_timer > 0){char_enemy_1.damage_timer--;}

    //* Player Collision

    temp_char = Is_Colliding_Enemy();

    if(temp_char != NULL && temp_char->active && char_player.damage_timer == 0)
    {
        char_player.damage_timer = 120;
        
        if(char_player.health > 0)
        {
            char_player.health--;
        }

        Update_Player_Health();

        Damage_Knockback(&char_player, temp_char->object.pos_x + 8, temp_char->object.pos_y + 8);
    }

    temp_chest = Is_Colliding_Chest();

    if(temp_chest != NULL && temp_chest->active)
    {
        Push_Object(&char_player.object, &temp_chest->object);
    }

    if(char_enemy_1.active)
    {
        temp_projectile = Is_Colliding_Projectile(&char_enemy_1);

        if(temp_projectile != NULL && char_enemy_1.damage_timer == 0)
        {
            char_enemy_1.damage_timer = 15;

            play_animation(&char_enemy_1, &anim_bat_down_hurt, true, true);
            Damage_Character(&char_enemy_1, temp_projectile->damage);

            if(char_enemy_1.health == 0)
            {
                switch(rand() % 3)
                {
                    case 0: Load_Drop(&drop_heart, char_enemy_1.object.pos_x + (char_enemy_1.object.width / 2) - 4, char_enemy_1.object.pos_y + (char_enemy_1.object.height / 2) - 4); break;
                }

                Call_Clear_Enemy(&char_enemy_1);
            }
        }
    }

    temp_obj_drop = Is_Colliding_Drop();

    if(temp_obj_drop != NULL)
    {
        Call_Perform_Drop_Pickup(temp_obj_drop->drop);
        Clear_Drop(temp_obj_drop);

        Update_Player_Health();
    }

}

void Load_Item(const GameItem* item, UBYTE pos_x, UBYTE pos_y)
{
    temp_obj_item = Find_Free_Item_Object();

    if(temp_obj_item == NULL){return;}

    temp_obj_item->item = item;
    temp_obj_item->object.pos_x = pos_x;
    temp_obj_item->object.pos_y = pos_y;

    build_object(&temp_obj_item->object);
    load_sprite(&temp_obj_item->object, item->sprite);
}

void Update_Weapon_Icon()
{
    if(current_weapon == NULL){return;}

    load_bkg_tiles(bank4, 236, 4, current_weapon->sprite->tiles);
    set_win_tiles(6, 0, 2, 2, tile_weapon_icon);
}

void Update_Characters()
{
    Update_Player();

    if(char_enemy_1.active){Call_Perform_Char_Update(&char_enemy_1);}
    if(char_enemy_2.active){Call_Perform_Char_Update(&char_enemy_2);}
    if(char_enemy_3.active){Call_Perform_Char_Update(&char_enemy_3);}
    if(char_enemy_4.active){Call_Perform_Char_Update(&char_enemy_4);}
}

void Update_Chests()
{
    if(chest_1.active){Update_Chest(&chest_1);}
    if(chest_2.active){Update_Chest(&chest_2);}
}

void Cycle_Anim(GameCharacter* character)
{
    if(character->active == true)
    {
        temp_anim = character->current_anim;

        if(temp_anim != NULL)
        {
            if(character->anim_frame == temp_anim->frames && character->anim_tick == temp_anim->duration)
            {
                character->current_anim = NULL;
                character->anim_frame = 0;
                character->anim_tick = 0;

                return;
            }
            else if(character->anim_tick == temp_anim->duration)
            {
                character->anim_tick = 0;
            }
            
            if(character->anim_tick == 0)
            {
                Call_Load_Sprite(&character->object, temp_anim->sprites[character->anim_frame]);

                character->anim_frame++;
            }

            character->anim_tick++;
        }
    }
}

void Load_HUD()
{
    set_bkg_data(240, 8, Tiles_HUD);

    set_win_tiles(0, 0, 20, 2, Map_HUD);

    move_win(7, 128);

    Update_Player_Health();

    wait_vbl_done();
    SHOW_WIN;
}

void Show_Menu()
{
    fade_out();

    move_win(7, 0);

    wait_vbl_done();
    SHOW_WIN;

    fade_in();
}

void Hide_HUD()
{
    move_win(7, 128);

    wait_vbl_done();
    SHOW_WIN;
}

void Move_Room(UBYTE direction)
{
    x = 0;
    y = 0;

    switch(direction)
    {
        case up: y = -1; break;
        case down: y = 1; break;
        case left: x = -1; break;
        case right: x = 1; break;
    }

    map_x = room_x + x;
    map_y = room_y + y;

    if(floor_map[map_y][map_x] == NULL)
    {
        return;
    }

    Call_Clear_Enemy(&char_enemy_1);
    Call_Clear_Enemy(&char_enemy_2);
    Call_Clear_Enemy(&char_enemy_3);
    Call_Clear_Enemy(&char_enemy_4);

    Hide_Chest(&chest_1);
    Hide_Chest(&chest_2);

    Clear_Drop(&obj_drop_1);

    flag_weapon_out = false;
    weapon_tick = 0;
    move_sprite(30, 0, 0);
    move_sprite(31, 0, 0);
    move_sprite(32, 0, 0);
    move_sprite(33, 0, 0);

    set_anim_package(&char_player, &anim_hiro);

    if(direction == up)
    {
        if(camera_y - 16 < 0){camera_y = 32 - (16 - camera_y);}
        else{camera_y -= 16;}

        line_y = 7;

        for(u_j = 0; u_j < 32; u_j++)
        {
            wait_vbl_done();

            load_pos_y = camera_y + line_y * 2;
            if(load_pos_y > 31){load_pos_y = load_pos_y - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Horizontal_Line(floor_map[map_y][map_x], camera_x, load_pos_y, line_y);
                line_y--;
            }

            if(u_j % 2 == 0)
            {
                char_player.object.pos_y--;
                move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            }

            char_player.object.pos_y += 4;
            move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            scroll_bkg(0, -4);
        }

        room_y--;
        current_map = floor_map[map_y][map_x];

        char_player.object.pos_y--;
        move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
    }

    else if(direction == down)
    {
        if(camera_y + 16 > 31){camera_y = (camera_y + 16) - 32;}
        else{camera_y += 16;}

        line_y = 0;

        for(u_j = 0; u_j < 32; u_j++)
        {
            wait_vbl_done();

            load_pos_y = camera_y + line_y * 2;
            if(load_pos_y > 31){load_pos_y = load_pos_y - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Horizontal_Line(floor_map[map_y][map_x], camera_x, load_pos_y, line_y);
                line_y++;
            }

            if(u_j % 2 == 0)
            {
                char_player.object.pos_y++;
                move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            }

            char_player.object.pos_y -= 4;
            move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            scroll_bkg(0, 4);
        }

        room_y++;
        current_map = floor_map[map_y][map_x];

        char_player.object.pos_y++;
        move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
    }

    else if(direction == right)
    {
        if(camera_x + 20 > 31){camera_x = (camera_x + 20) - 32;}
        else{camera_x += 20;}

        line_x = 0;

        for(u_j = 0; u_j < 40; u_j++)
        {
            wait_vbl_done();

            load_pos_x = camera_x + line_x * 2;
            if(load_pos_x > 31){load_pos_x = load_pos_x - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Vertical_Line(floor_map[map_y][map_x], load_pos_x, camera_y, line_x);
                line_x++;
            }

            if(u_j % 2 == 0)
            {
                char_player.object.pos_x++;
                move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            }

            char_player.object.pos_x -= 4;
            move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            scroll_bkg(4, 0);
        }

        room_x++;
        current_map = floor_map[map_y][map_x];

        char_player.object.pos_x++;
        move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
    }

    else if(direction == left)
    {
        if(camera_x - 20 < 0){camera_x = 32 - (20 - camera_x);}
        else{camera_x -= 20;}

        line_x = 9;

        for(u_j = 0; u_j < 40; u_j++)
        {
            wait_vbl_done();

            load_pos_x = camera_x + line_x * 2;
            if(load_pos_x > 31){load_pos_x = load_pos_x - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Vertical_Line(floor_map[map_y][map_x], load_pos_x, camera_y, line_x);
                line_x--;
            }

            if(u_j % 2 == 0)
            {
                char_player.object.pos_x--;
                move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            }

            char_player.object.pos_x += 4;
            move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
            scroll_bkg(-4, 0);
        }

        room_x--;
        current_map = floor_map[map_y][map_x];

        char_player.object.pos_x--;
        move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
    }

    if(chest_1.active && chest_1.room.x == map_x && chest_1.room.y == map_y)
    {
        load_sprite_tiles(bank4, chest_1.object.sprite_index, 4, sprite_chest_closed.tiles);
    }

    if(chest_2.active && chest_2.room.x == map_x && chest_2.room.y == map_y)
    {
        load_sprite_tiles(bank4, chest_2.object.sprite_index, 4, sprite_chest_closed.tiles);
    }

    if(room_open[map_y][map_x] == false)
    {
        if(floor_map[map_y][map_x]->type == room_item)
        {
            Load_Chest(80, 48, &item_sword);
        }

        Call_Load_Room_Enemies(current_map);

        for(u_i = 0; u_i < 4; u_i++)
        {
            doors_open[u_i] = false;

            if(current_map->doors[u_i] == true)
            {
                switch(u_i)
                {
                    case up: Call_Draw_Tile(camera_x + 10, camera_y + 0, 21); break;
                    case down: Call_Draw_Tile(camera_x + 10, camera_y + 14, 22); break;
                    case left: Call_Draw_Tile(camera_x + 0, camera_y + 6, 23); break;
                    case right: Call_Draw_Tile(camera_x + 18, camera_y + 6, 24); break;
                }
            }
        }
    }

    for(u_i = 0; u_i < 12; u_i++)
    {
        wait_vbl_done();

        switch(direction)
        {
            case up: char_player.object.pos_y--; break;
            case down: char_player.object.pos_y++; break;
            case left: char_player.object.pos_x--; break;
            case right: char_player.object.pos_x++; break;
        }

        move_object(&char_player.object, char_player.object.pos_x, char_player.object.pos_y);
    }
}

void Transition_Room()
{
    if(char_player.object.pos_y == 0 || char_player.object.pos_y > 200)
    {
        Move_Room(up);
    }
    else if(char_player.object.pos_y > 111 && char_player.object.pos_y < 201)
    {
        Move_Room(down);
    }
    else if(char_player.object.pos_x == 0 || char_player.object.pos_x > 200)
    {
        Move_Room(left);
    }
    else if(char_player.object.pos_x > 143 && char_player.object.pos_y < 201)
    {
        Move_Room(right);
    }
}

void Update_Joypad()
{
    Joy = joypad();

    if(Joy & J_UP && flag_halt_movement == false)
    {
        if(char_player.object.pos_y > 0 && char_player.object.velocity_y == 0)
        {
            char_player.facing = up;
            char_player.object.velocity_y--;

            if(button_up(J_LEFT) && button_up(J_RIGHT))
            {
                play_animation(&char_player, char_player.anims->char_up, true, false);
            }
        }
    }

    if(Joy & J_DOWN && flag_halt_movement == false)
    {
        if(char_player.object.pos_y < 112 && char_player.object.velocity_y == 0)
        {
            char_player.facing = down;
            char_player.object.velocity_y++;

            if(button_up(J_LEFT) && button_up(J_RIGHT))
            {
                play_animation(&char_player, char_player.anims->char_down, true, false);
            }
        }
    }

    if(Joy & J_LEFT && flag_halt_movement == false)
    {
        if(char_player.object.pos_x > 0 && char_player.object.velocity_x == 0)
        {
            char_player.facing = left;
            char_player.object.velocity_x--;

            play_animation(&char_player, char_player.anims->char_left, true, false);
        }
    }

    if(Joy & J_RIGHT && flag_halt_movement == false)
    {
        if(char_player.object.pos_x < 144 && char_player.object.velocity_x == 0)
        {
            char_player.facing = right;
            char_player.object.velocity_x++;

            play_animation(&char_player, char_player.anims->char_right, true, false);
        }
    }

    //if(!(Joy & J_UP) && !(Joy & J_DOWN) && !(Joy & J_LEFT) && !(Joy & J_RIGHT))
    //{
    //    stop_animation(&char_player);
    //}

    if(Joy & J_B)
    {
    }

    if(Joy & J_START)
    {
    }

    if(Joy & J_SELECT)
    {
    }

    Call_Perform_Item_Action(current_weapon);

    Cycle_Anim(&char_player);
    Cycle_Anim(&char_enemy_1);

    Object_Collision();

    Object_Movement(&char_player.object);
    
    if(char_enemy_1.active){Object_Movement(&char_enemy_1.object);}
    
    if(chest_1.active){Object_Movement(&chest_1.object);}
    if(chest_2.active){Object_Movement(&chest_2.object);}
    
    if(projectile_1.active){Projectile_Movement(&projectile_1);}

    Update_Characters();
    Update_Chests();

    Check_Room_Cleared();

    Transition_Room();
}