#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Character.h"

/*  Game Characters  */
GameCharacter char_player = {"", true, 0, 0, 0, down, 0, 0, &sprite_hiro};

GameCharacter char_enemy_1 = {"", false, 0, 0, 4, down, 0, 0, &sprite_hiro};
GameCharacter char_enemy_2 = {"", false, 0, 0, 8, down, 0, 0, &sprite_hiro};
GameCharacter char_enemy_3 = {"", false, 0, 0, 12, down, 0, 0, &sprite_hiro};
GameCharacter char_enemy_4 = {"", false, 0, 0, 16, down, 0, 0, &sprite_hiro};