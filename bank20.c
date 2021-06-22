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

#include "Maps/Map_Dungeon_Boss_T.c"
#include "Maps/Map_Dungeon_Boss_B.c"
#include "Maps/Map_Dungeon_Boss_L.c"
#include "Maps/Map_Dungeon_Boss_R.c"

#include "Maps/Map_Dungeon_Item_T.c"
#include "Maps/Map_Dungeon_Item_B.c"
#include "Maps/Map_Dungeon_Item_L.c"
#include "Maps/Map_Dungeon_Item_R.c"

extern const UBYTE Tileset_1_Map[60][4];
extern const UBYTE Tileset_1_Collision[60];

void Draw_Tile20(UINT16 tile_x, UINT16 tile_y, UBYTE tile_num)
{
    if(tile_x > 31){tile_x -= 32;}
    if(tile_y > 31){tile_y -= 32;}

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
        map_pos_x = pos_x + u_i * 2;;
        map_pos_y = pos_y;

        if(map_pos_x > 31){map_pos_x -= 32;}
        if(map_pos_y > 31){map_pos_y -= 32;}

        Draw_Tile20(map_pos_x, map_pos_y, map->data[tile_y * 10 + u_i]);
    }
}

void Draw_Vertical_Line20(const GameMap* map, UBYTE pos_x, UBYTE pos_y, UBYTE tile_x)
{
    for(u_i = 0; u_i < 9; u_i++)
    {
        map_pos_x = pos_x;
        map_pos_y = pos_y + u_i * 2;

        if(map_pos_x > 31){map_pos_x -= 32;}
        if(map_pos_y > 31){map_pos_y -= 32;}

        Draw_Tile20(map_pos_x, map_pos_y, map->data[tile_x + u_i * 10]);
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

UBYTE Get_Collision20(UBYTE x1, UBYTE y1, INT8 offset_x, INT8 offset_y, UBYTE type)
{
    map_x = x1;
    map_y = y1;

    if(Get_Collision_Tile20(map_x, map_y) != type && Get_Collision_Tile20(map_x + offset_x, map_y + offset_y) != type)
    {
        return false;
    }

    return true;
}