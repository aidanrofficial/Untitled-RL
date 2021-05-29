#include <gb/gb.h>
#include <stdlib.h>
#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Character.h"
#include "Maps/Map_HUD.c"
#include "Tiles/Tiles_HUD.c"

const unsigned char temp_char_room[1] = {0x01};
const unsigned char temp_char_current[1] = {0x02};

UBYTE Do_Circles_Overlap(UBYTE x1, UBYTE y1, UBYTE x2, UBYTE y2)
{
    collision_x = x1 - x2;
    collision_y = y1 - y2;

    return wabs((collision_x) * (collision_x) + (collision_y) * (collision_y)) <= 144;
}

void Movement(GameCharacter* character)
{
    if(character->velocity_x > 0)
    {
        if(Call_Get_Collision(bank2, right, character->pos_x + character->velocity_x, character->pos_y) == true)
        {
            if(character == &char_player || character->pos_x + character->velocity_x < 128)
            {
                character->pos_x += character->velocity_x;
            }
        }

        character->velocity_x--;
    }
    else if(character->velocity_x < 0)
    {
        if(Call_Get_Collision(bank2, left, character->pos_x + character->velocity_x, character->pos_y) == true)
        {
            if(character == &char_player || character->pos_x + character->velocity_x > 16)
            {
                character->pos_x += character->velocity_x;
            }
        }

        character->velocity_x++;
    }

    if(character->velocity_y > 0)
    {
        if(Call_Get_Collision(bank2, down, character->pos_x, character->pos_y + character->velocity_y) == true)
        {
            if(character == &char_player || character->pos_y + character->velocity_y < 96)
            {
                character->pos_y += character->velocity_y;
            }
        }

        character->velocity_y--;
    }
    else if(character->velocity_y < 0)
    {
        if(Call_Get_Collision(bank2, up, character->pos_x, character->pos_y + character->velocity_y) == true)
        {
            if(character == &char_player || character->pos_y + character->velocity_y > 15)
            {
                character->pos_y += character->velocity_y;
            }
        }

        character->velocity_y++;
    }
}

GameCharacter* Is_Colliding_Enemy()
{
    if(Do_Circles_Overlap(char_player.pos_x + 8, char_player.pos_y + 8, char_enemy_1.pos_x + 8, char_enemy_1.pos_y + 8))
    {
        return &char_enemy_1;
    }
    
    return NULL;
}

void Damage_Knockback(GameCharacter* character1, GameCharacter* character2)
{
    collision_x = (character1->pos_x + 8) - (character2->pos_x + 8);
    collision_y = (character1->pos_y + 8) - (character2->pos_y + 8);

    distance = sqrt((collision_x * collision_x) + (collision_y * collision_y));

    character1->velocity_x += 8 * collision_x / distance;
    character1->velocity_y += 8 * collision_y / distance;
}

void Push_Character(GameCharacter* character1, GameCharacter* character2)
{
    collision_x = (character1->pos_x + 8) - (character2->pos_x + 8);
    collision_y = (character1->pos_y + 8) - (character2->pos_y + 8);

    distance = sqrt((collision_x * collision_x) + (collision_y * collision_y));

    character1->velocity_x += collision_x / distance;
    character1->velocity_y += collision_y / distance;

    character2->velocity_x -= collision_x / distance;
    character2->velocity_y -= collision_y / distance;
}

void Enemy_Collide()
{
    temp_char = Is_Colliding_Enemy();  
}

void Show_HUD()
{
    move_win(7, 50);

    wait_vbl_done();
    SHOW_WIN;
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

    Call_Clear_Enemy(bank2, &char_enemy_1);
    Call_Clear_Enemy(bank2, &char_enemy_2);
    Call_Clear_Enemy(bank2, &char_enemy_3);
    Call_Clear_Enemy(bank2, &char_enemy_4);

    if(direction == up)
    {
        if(camera_y - 14 < 0){camera_y = 32 - (14 - camera_y);}
        else{camera_y -= 14;}

        line_y = 6;

        for(u_j = 0; u_j < 28; u_j++)
        {
            wait_vbl_done();

            load_pos_y = camera_y + line_y * 2;
            if(load_pos_y > 31){load_pos_y = load_pos_y - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Horizontal_Line(bank2, floor_map[map_y][map_x], camera_x, load_pos_y, line_y);
                line_y--;
            }

            char_player.pos_y += 4;
            move_char(&char_player, char_player.pos_x, char_player.pos_y);
            scroll_bkg(0, -4);
        }

        room_y--;
        current_map = floor_map[map_y][map_x];

        char_player.pos_y--;
        move_char(&char_player, char_player.pos_x, char_player.pos_y);
    }

    else if(direction == down)
    {
        if(camera_y + 14 > 31){camera_y = (camera_y + 14) - 32;}
        else{camera_y += 14;}

        line_y = 1;

        for(u_j = 0; u_j < 28; u_j++)
        {
            wait_vbl_done();

            load_pos_y = camera_y + line_y * 2;
            if(load_pos_y > 31){load_pos_y = load_pos_y - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Horizontal_Line(bank2, floor_map[map_y][map_x], camera_x, load_pos_y, line_y);
                line_y++;
            }

            char_player.pos_y -= 4;
            move_char(&char_player, char_player.pos_x, char_player.pos_y);
            scroll_bkg(0, 4);
        }

        room_y++;
        current_map = floor_map[map_y][map_x];

        char_player.pos_y++;
        move_char(&char_player, char_player.pos_x, char_player.pos_y);
    }

    else if(direction == right)
    {
        if(camera_x + 18 > 31){camera_x = (camera_x + 18) - 32;}
        else{camera_x += 18;}

        line_x = 1;

        for(u_j = 0; u_j < 36; u_j++)
        {
            wait_vbl_done();

            load_pos_x = camera_x + line_x * 2;
            if(load_pos_x > 31){load_pos_x = load_pos_x - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Vertical_Line(bank2, floor_map[map_y][map_x], load_pos_x, camera_y, line_x);
                line_x++;
            }

            char_player.pos_x -= 4;
            move_char(&char_player, char_player.pos_x, char_player.pos_y);
            scroll_bkg(4, 0);
        }

        room_x++;
        current_map = floor_map[map_y][map_x];

        char_player.pos_x++;
        move_char(&char_player, char_player.pos_x, char_player.pos_y);
    }

    else if(direction == left)
    {
        if(camera_x - 18 < 0){camera_x = 32 - (18 - camera_x);}
        else{camera_x -= 18;}

        line_x = 8;

        for(u_j = 0; u_j < 36; u_j++)
        {
            wait_vbl_done();

            load_pos_x = camera_x + line_x * 2;
            if(load_pos_x > 31){load_pos_x = load_pos_x - 32;}

            if(u_j % 4 == 0)
            {
                Call_Draw_Vertical_Line(bank2, floor_map[map_y][map_x], load_pos_x, camera_y, line_x);
                line_x--;
            }

            char_player.pos_x += 4;
            move_char(&char_player, char_player.pos_x, char_player.pos_y);
            scroll_bkg(-4, 0);
        }

        room_x--;
        current_map = floor_map[map_y][map_x];

        char_player.pos_x--;
        move_char(&char_player, char_player.pos_x, char_player.pos_y);
    }

    Call_Load_Room_Enemies(bank2, current_map);

    for(u_i = 0; u_i < 11; u_i++)
    {
        for(u_j = 0; u_j < 11; u_j++)
        {
            if(u_j == room_x && u_i == room_y)
            {
                set_win_tiles(u_j, u_i, 1, 1, temp_char_current);
            }
            else if(floor_map[u_i][u_j] != NULL)
            {
                set_win_tiles(u_j, u_i, 1, 1, temp_char_room);
            }
        }
    }
}

void Transition_Room()
{
    if(char_player.pos_y == 0)
    {
        Move_Room(up);
    }
    else if(char_player.pos_y == 112)
    {
        Move_Room(down);
    }
    else if(char_player.pos_x == 0)
    {
        Move_Room(left);
    }
    else if(char_player.pos_x == 144)
    {
        Move_Room(right);
    }
}

void Update_Joypad()
{
    Joy = joypad();

    Enemy_Collide();
    Movement(&char_player);
    Movement(&char_enemy_1);

    if(collision_tick > 0){collision_tick--;}

    if(Joy & J_UP)
    {
        if(char_player.pos_y > 0 && char_player.velocity_y == 0)
        {
            char_player.facing = up;
            char_player.velocity_y--;
        }
    }

    if(Joy & J_DOWN)
    {
        if(char_player.pos_y < 112 && char_player.velocity_y == 0)
        {
            char_player.facing = down;
            char_player.velocity_y++;
        }
    }

    if(Joy & J_LEFT)
    {
        if(char_player.pos_x > 0 && char_player.velocity_x == 0)
        {
            char_player.facing = left;
            char_player.velocity_x--;
        }
    }

    if(Joy & J_RIGHT)
    {
        if(char_player.pos_x < 144 && char_player.velocity_x == 0)
        {
            char_player.facing = right;
            char_player.velocity_x++;
        }
    }

    if(Joy & J_A)
    {
        Show_HUD();
    }

    if(Joy & J_B)
    {
        Hide_HUD();
    }

    if(Joy & J_START)
    {
        Call_Load_Floor(bank2);
    }

    if(Joy & J_SELECT)
    {
        waitpadup();
    }

    Transition_Room();
}