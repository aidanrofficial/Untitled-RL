#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Character.h"
#include "Game_Sprite.h"
#include "Game_Map.h"
#include "Game_Projectile.h"

#include "Tiles/Tiles_Sword.c"
#include "Tiles/Tiles_Collision.c"

extern const unsigned char Tiles_Clear[];

UBYTE temp_counter;

GameProjectile* Find_Free_Projectile()
{
    if(!projectile_1.active)
    {
        return &projectile_1;
    }
    else
    {
        return NULL;
    }
}

GameProjectile* Load_Projectile(UBYTE pos_x, UBYTE pos_y, UBYTE velocity_x, UBYTE velocity_y, UBYTE size_x, UBYTE size_y, UBYTE damage, UBYTE friendly, UBYTE life_cycles)
{
    temp_projectile = Find_Free_Projectile();

    if(temp_projectile == NULL)
    {
        return NULL;
    }

    temp_projectile->active = true;
    temp_projectile->pos_x = pos_x;
    temp_projectile->pos_y = pos_y;
    temp_projectile->velocity_x = velocity_x;
    temp_projectile->velocity_y = velocity_y;
    temp_projectile->size_x = size_x;
    temp_projectile->size_y = size_y;
    temp_projectile->damage = damage;
    temp_projectile->friendly = friendly;
    temp_projectile->life_cycles = life_cycles;

    return temp_projectile;
}

void Heart_Pickup()
{
    if(char_player.health + 2 > char_player.max_health)
    {
        char_player.health = char_player.max_health;
        
        return;
    }

    char_player.health += 2;
}

void Sword_Action()
{
    if(joypad() & J_A)
    {
        if(flag_action_button == false)
        {
            flag_action_button = true;
            flag_halt_movement = true;
            flag_weapon_out = true;
            
            weapon_tick = 0;

            switch(char_player.facing)
            {
                case up: weapon_direction = up; break;
                case down: weapon_direction = down; break;
                case left: weapon_direction = left; break;
                case right: weapon_direction = right; break;
            }
        }
    }
    else if(button_up(J_A))
    {
        flag_action_button = false;
    }

    if(flag_weapon_out == true)
    {
        if(weapon_tick == 0)
        {
            move_sprite(30, 0, 0);
            move_sprite(31, 0, 0);

            if(weapon_direction == up)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 32, char_player.object.pos_y + 16);
                move_sprite(31, char_player.object.pos_x + 24, char_player.object.pos_y + 16);
                
                set_sprite_data(30, 2, Tiles_SwordBLK0);

                play_animation(&char_player, &anim_hiro_attack_up, true, true);
                set_anim_package(&char_player, &anim_hiro_face_up);
            }
            else if(weapon_direction == down)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x - 8, char_player.object.pos_y + 16);
                move_sprite(31, char_player.object.pos_x, char_player.object.pos_y + 16);
                
                set_sprite_data(30, 2, Tiles_SwordBLK4);

                play_animation(&char_player, &anim_hiro_attack_down, true, true);
                set_anim_package(&char_player, &anim_hiro_face_down);
            }
            else if(weapon_direction == left)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 8, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 8, char_player.object.pos_y + 8);
                
                set_sprite_data(30, 2, Tiles_SwordBLK8);

                play_animation(&char_player, &anim_hiro_attack_left, true, true);
                set_anim_package(&char_player, &anim_hiro_face_left);
            }
            else if(weapon_direction == right)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 16, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 16, char_player.object.pos_y + 8);
                
                set_sprite_data(30, 2, Tiles_SwordBLK12);

                play_animation(&char_player, &anim_hiro_attack_right, true, true);
                set_anim_package(&char_player, &anim_hiro_face_right);
            }
        }
        else if(weapon_tick == 4)
        {
            move_sprite(30, 0, 0);
            move_sprite(31, 0, 0);
            move_sprite(32, 0, 0);
            move_sprite(33, 0, 0);

            if(weapon_direction == up)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);
                set_sprite_tile(32, 32);
                set_sprite_tile(33, 33);

                move_sprite(30, char_player.object.pos_x + 24, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 24, char_player.object.pos_y + 8);
                move_sprite(32, char_player.object.pos_x + 32, char_player.object.pos_y);
                move_sprite(33, char_player.object.pos_x + 32, char_player.object.pos_y + 8);
                
                set_sprite_data(30, 2, Tiles_SwordBLK1);
                set_sprite_data(32, 2, Tiles_SwordBLK2);

                Load_Projectile(char_player.object.pos_x + 8, char_player.object.pos_y - 16, 0, 0, 24, 16, 2, true, 1);
            }
            else if(weapon_direction == down)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);
                set_sprite_tile(32, 32);
                set_sprite_tile(33, 33);

                move_sprite(30, char_player.object.pos_x - 8, char_player.object.pos_y + 32);
                move_sprite(31, char_player.object.pos_x - 8, char_player.object.pos_y + 40);
                move_sprite(32, char_player.object.pos_x, char_player.object.pos_y + 32);
                move_sprite(33, char_player.object.pos_x, char_player.object.pos_y + 40);
                
                set_sprite_data(30, 2, Tiles_SwordBLK5);
                set_sprite_data(32, 2, Tiles_SwordBLK6);

                Load_Projectile(char_player.object.pos_x - 16, char_player.object.pos_y + 16, 0, 0, 24, 16, 2, true, 1);
            }
            else if(weapon_direction == left)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);
                set_sprite_tile(32, 32);
                set_sprite_tile(33, 33);

                move_sprite(30, char_player.object.pos_x - 8, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x - 8, char_player.object.pos_y + 8);
                move_sprite(32, char_player.object.pos_x, char_player.object.pos_y);
                move_sprite(33, char_player.object.pos_x, char_player.object.pos_y + 8);

                set_sprite_data(30, 2, Tiles_SwordBLK9);
                set_sprite_data(32, 2, Tiles_SwordBLK10);

                Load_Projectile(char_player.object.pos_x - 16, char_player.object.pos_y - 16, 0, 0, 16, 24, 2, true, 1);
            }
            else if(weapon_direction == right)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);
                set_sprite_tile(32, 32);
                set_sprite_tile(33, 33);

                move_sprite(30, char_player.object.pos_x + 24, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 24, char_player.object.pos_y + 8);
                move_sprite(32, char_player.object.pos_x + 32, char_player.object.pos_y);
                move_sprite(33, char_player.object.pos_x + 32, char_player.object.pos_y + 8);
                
                set_sprite_data(30, 2, Tiles_SwordBLK13);
                set_sprite_data(32, 2, Tiles_SwordBLK14);

                Load_Projectile(char_player.object.pos_x + 16, char_player.object.pos_y - 16, 0, 0, 16, 24, 2, true, 1);
            }
        }
        else if(weapon_tick == 7)
        {
            move_sprite(30, 0, 0);
            move_sprite(31, 0, 0);
            move_sprite(32, 0, 0);
            move_sprite(33, 0, 0);

            if(weapon_direction == up)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 8, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 8, char_player.object.pos_y + 8);
           
                set_sprite_data(30, 2, Tiles_SwordBLK3);

                Load_Projectile(char_player.object.pos_x, char_player.object.pos_y - 16, 0, 0, 8, 16, 2, true, 1);
            }
            else if(weapon_direction == down)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 16, char_player.object.pos_y + 32);
                move_sprite(31, char_player.object.pos_x + 16, char_player.object.pos_y + 40);
               
                set_sprite_data(30, 2, Tiles_SwordBLK7);

                Load_Projectile(char_player.object.pos_x, char_player.object.pos_y + 16, 0, 0, 8, 16, 2, true, 1);
            }
            else if(weapon_direction == left)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x - 8, char_player.object.pos_y + 24);
                move_sprite(31, char_player.object.pos_x, char_player.object.pos_y + 24);
               
                set_sprite_data(30, 2, Tiles_SwordBLK11);

                Load_Projectile(char_player.object.pos_x - 16, char_player.object.pos_y + 8, 0, 0, 16, 8, 2, true, 1);
            }
            else if(weapon_direction == right)
            {
                set_sprite_tile(30, 30);
                set_sprite_tile(31, 31);

                move_sprite(30, char_player.object.pos_x + 24, char_player.object.pos_y + 24);
                move_sprite(31, char_player.object.pos_x + 32, char_player.object.pos_y + 24);
            
                set_sprite_data(30, 2, Tiles_SwordBLK15);

                Load_Projectile(char_player.object.pos_x + 16, char_player.object.pos_y + 8, 0, 0, 16, 8, 2, true, 1);
            }

            flag_halt_movement = false;
        } 
        else if(weapon_tick == 15)
        {
            if(button_up(J_A))
            {
                flag_weapon_out = false;
                flag_action_button = false;
                weapon_tick = 0;

                move_sprite(30, 0, 0);
                move_sprite(31, 0, 0);
                move_sprite(36, 0, 0);

                set_anim_package(&char_player, &anim_hiro);

                return;
            } 

            if(weapon_direction == up)
            {
                move_sprite(30, char_player.object.pos_x + 8, char_player.object.pos_y);
                move_sprite(31, char_player.object.pos_x + 8, char_player.object.pos_y + 8);

                Load_Projectile(char_player.object.pos_x, char_player.object.pos_y - 16, 0, 0, 8, 16, 2, true, 1);
            }
            else if(weapon_direction == down)
            {
                move_sprite(30, char_player.object.pos_x + 16, char_player.object.pos_y + 32);
                move_sprite(31, char_player.object.pos_x + 16, char_player.object.pos_y + 40);

                Load_Projectile(char_player.object.pos_x, char_player.object.pos_y + 16, 0, 0, 8, 16, 2, true, 1);
            }
            else if(weapon_direction == left)
            {
                move_sprite(30, char_player.object.pos_x + - 8, char_player.object.pos_y + 24);
                move_sprite(31, char_player.object.pos_x, char_player.object.pos_y + 24);

                Load_Projectile(char_player.object.pos_x - 16, char_player.object.pos_y + 8, 0, 0, 16, 8, 2, true, 1);
            }
            else if(weapon_direction == right)
            {
                move_sprite(30, char_player.object.pos_x + 24, char_player.object.pos_y + 24);
                move_sprite(31, char_player.object.pos_x + 32, char_player.object.pos_y + 24);

                Load_Projectile(char_player.object.pos_x + 16, char_player.object.pos_y + 8, 0, 0, 16, 8, 2, true, 1);
            }
            
        }

        if(weapon_tick < 15){weapon_tick++;}
    }

    return;
}