#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Character.h"

/*  Game Characters  */
GameCharacter char_player = {true, {0, 0, 0, 0, 0, size_2x2, 16, 16, false, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};

GameCharacter char_enemy_1 = {true, {0, 0, 0, 0, 4, size_2x2, 16, 16, false, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};
GameCharacter char_enemy_2 = {true, {0, 0, 0, 0, 8, size_2x2, 16, 16, false, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};
GameCharacter char_enemy_3 = {true, {0, 0, 0, 0, 12, size_2x2, 16, 16, false, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};
GameCharacter char_enemy_4 = {true, {0, 0, 0, 0, 16, size_2x2, 16, 16, false, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};

GameCharacter char_add_1 = {true, {0, 0, 0, 0, 16, size_2x2, 16, 16, NULL}, down, 6, 6, 0, &anim_hiro, NULL, 0, 0, 0, 0, NULL};