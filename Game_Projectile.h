#include <gb/gb.h>

#ifndef PROJECTILES
#define PROJECTILES

typedef struct GameProjectile
{
    UBYTE active;
    UBYTE pos_x;
    UBYTE pos_y;
    INT8 velocity_x;
    INT8 velocity_y;
    UBYTE size_x;
    UBYTE size_y;
    UBYTE damage;
    UBYTE friendly;
    UBYTE sprite_id;
    UBYTE life_cycles;

} GameProjectile;

extern GameProjectile projectile_1;

#endif