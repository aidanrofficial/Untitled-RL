#include <gb/gb.h>
#include <rand.h>
#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Map.h"

void Chest_AI(GameChest* chest)
{
    if(chest->object.velocity_x > 0){chest->object.velocity_x--;}
    else if(chest->object.velocity_x < 0){chest->object.velocity_x++;}

    if(chest->object.velocity_y > 0){chest->object.velocity_y--;}
    else if(chest->object.velocity_y < 0){chest->object.velocity_y++;}
}

void Worm_Head_Col(GameObject* object, UBYTE direction)
{
    switch(direction)
    {
        case up: case down: object->velocity_y *= -1; break;
        case left: case right: object->velocity_x *= -1; break;
    }

    return;
}

void Worm_Head_AI(GameCharacter* character)
{
    if(character->object.velocity_x == 0){character->object.velocity_x = 1;}
    if(character->object.velocity_y == 0){character->object.velocity_y = 1;}

    return;
}

void Bat_AI(GameCharacter* character)
{
    if(character->ai_tick > 0){character->ai_tick--;}

    return;
}