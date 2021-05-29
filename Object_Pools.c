#include "Game_Map.h"

const GameMap* map_pool_t[10] =
{
    &map_dungeon_t, &map_dungeon_t, &map_dungeon_t, &map_dungeon_t, &map_dungeon_t,
    &map_dungeon_t, &map_dungeon_t, &map_dungeon_t, &map_dungeon_t, &map_dungeon_t
};

const GameMap* map_pool_b[10] =
{
    &map_dungeon_b, &map_dungeon_b, &map_dungeon_b, &map_dungeon_b, &map_dungeon_b,
    &map_dungeon_b, &map_dungeon_b, &map_dungeon_b, &map_dungeon_b, &map_dungeon_b
};

const GameMap* map_pool_l[10] =
{
    &map_dungeon_l, &map_dungeon_l, &map_dungeon_l, &map_dungeon_l, &map_dungeon_l,
    &map_dungeon_l, &map_dungeon_l, &map_dungeon_l, &map_dungeon_l, &map_dungeon_l
};

const GameMap* map_pool_r[10] =
{
    &map_dungeon_r, &map_dungeon_r, &map_dungeon_r, &map_dungeon_r, &map_dungeon_r,
    &map_dungeon_r, &map_dungeon_r, &map_dungeon_r, &map_dungeon_r, &map_dungeon_r
};

const GameMap* map_pool_tb[10] =
{
    &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb,
    &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb, &map_dungeon_tb
};

const GameMap* map_pool_lr[10] =
{
    &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr,
    &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr, &map_dungeon_lr
};

const GameMap* map_pool_tlr[10] =
{
    &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr,
    &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr, &map_dungeon_tlr
};

const GameMap* map_pool_blr[10] =
{
    &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr,
    &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr, &map_dungeon_blr
};

const GameMap* map_pool_tbl[10] =
{
    &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl,
    &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl, &map_dungeon_tbl
};

const GameMap* map_pool_tbr[10] =
{
    &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr,
    &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr, &map_dungeon_tbr
};

const GameMap* map_pool_tl[10] =
{
    &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl,
    &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl, &map_dungeon_tl
};

const GameMap* map_pool_tr[10] =
{
    &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr,
    &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr, &map_dungeon_tr
};

const GameMap* map_pool_bl[10] =
{
    &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl,
    &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl, &map_dungeon_bl
};

const GameMap* map_pool_br[10] =
{
    &map_dungeon_br, &map_dungeon_br, &map_dungeon_br, &map_dungeon_br, &map_dungeon_br,
    &map_dungeon_br, &map_dungeon_br, &map_dungeon_br, &map_dungeon_br, &map_dungeon_br
};