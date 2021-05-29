#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Functions.h"
#include "Game_Map.h"
#include "Maps/Map_Dungeon_1.c"
#include "Maps/Map_Dungeon_T.c"
#include "Maps/Map_Dungeon_B.c"
#include "Maps/Map_Dungeon_L.c"
#include "Maps/Map_Dungeon_R.c"
#include "Maps/Map_Dungeon_TB.c"
#include "Maps/Map_Dungeon_LR.c"
#include "Maps/Map_Dungeon_TLR.c"
#include "Maps/Map_Dungeon_BLR.c"
#include "Maps/Map_Dungeon_TBL.c"
#include "Maps/Map_Dungeon_TBR.c"
#include "Maps/Map_Dungeon_TL.c"
#include "Maps/Map_Dungeon_TR.c"
#include "Maps/Map_Dungeon_BL.c"
#include "Maps/Map_Dungeon_BR.c"

extern const UBYTE Tileset_1_Map[60][4];
extern const UBYTE Tileset_1_Collision[60];

void Draw_Tile20(UINT16 tile_x, UINT16 tile_y, UBYTE tile_num)
{
    switch(Tileset)
    {
        case 1:
            set_bkg_tiles(tile_x, tile_y, 2, 2, Tileset_1_Map[tile_num]);
            break;
        default:
            set_bkg_tiles(tile_x, tile_y, 2, 2, Tileset_1_Map[tile_num]);
            break;
    }
}

void Draw_Map20(const GameMap* map)
{
    for(u_j = 0; u_j < 8; u_j++)
    {
        performant_delay(1);
        
        for(u_i = 0; u_i < 10; u_i++)
        {
            Draw_Tile20(u_i * 2, u_j * 2, map->data[u_j * 10 + u_i]);
        }
    }
}

void Draw_Horizontal_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_y)
{
    for(u_i = 0; u_i < 10; u_i++)
    {
        Draw_Tile20(pos_x + u_i * 2, pos_y, map->data[tile_y * 10 + u_i]);
    }
}

void Draw_Vertical_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_x)
{
    for(u_i = 0; u_i < 9; u_i++)
    {
        Draw_Tile20(pos_x, pos_y + u_i * 2, map->data[tile_x + u_i * 10]);
    }
}

UBYTE Get_Collision_Tile20(UBYTE pos_x, UBYTE pos_y)
{
    u_x = pos_x / 16;
    u_y = pos_y / 16;

    u_i = u_y * 10;

    u_j = current_map->data[u_i + u_x];

    if(Tileset == 1)
    {
        return Tileset_1_Collision[u_j];
    }
    else
    {
        return Tileset_1_Collision[u_j];
    }
}

UBYTE Get_Collision20(UBYTE direction, UBYTE pos_x, UBYTE pos_y)
{
    map_x = pos_x;
    map_y = pos_y;

    if(map_x > MAX_SIZE_X || map_y > MAX_SIZE_Y)
    {
        return true;
    }

    if(direction == up)
    {
        if(map_x % 16 != 0 && Get_Collision_Tile20(map_x, map_y) != 1 && Get_Collision_Tile20(map_x + 16, map_y) != 1)
        {
            return true;
        }
        else if(map_x % 16 == 0 && Get_Collision_Tile20(map_x, map_y) != 1)
        {
            return true;
        }
    }
    else if(direction == down)
    {
        if(map_x % 16 != 0 && Get_Collision_Tile20(map_x, map_y + 16 - 1) != 1 && Get_Collision_Tile20(map_x + 16, map_y + 16 - 1) != 1)
        {
            return true;
        }
        else if(map_x % 16 == 0 && Get_Collision_Tile20(map_x, map_y + 16 - 1) != 1)
        {
            return true;
        }
    }
    else if(direction == left)
    {
        if(map_y % 16 != 0 && Get_Collision_Tile20(map_x, map_y) != 1 && Get_Collision_Tile20(map_x, map_y + 16) != 1)
        {
            return true;
        }
        else if(map_y % 16 == 0 && Get_Collision_Tile20(map_x, map_y) != 1)
        {
            return true;
        }
    }
    else if(direction == right)
    {
        if(map_y % 16 != 0 && Get_Collision_Tile20(map_x + 16 - 1, map_y) != 1 && Get_Collision_Tile20(map_x + 16 - 1, map_y + 16) != 1)
        {
            return true;
        }
        else if(map_y % 16 == 0 && Get_Collision_Tile20(map_x + 16 - 1, map_y) != 1)
        {
            return true;
        }
    }

    return false;
}