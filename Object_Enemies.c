#include <gb/gb.h>
#include "Game_Definitions.h"
#include "Game_Enemy.h"
#include "Game_Sprite.h"

extern void Worm_Head_Col(GameObject* object, UBYTE direction);

extern void Worm_Head_AI(GameCharacter* character);
extern void Bat_AI(GameCharacter* character);

/*  Game Enemies  */
const GameEnemy enemy_bat = {3, &anim_bat, true, &Bat_AI, NULL};

/*  Game Bosses  */
const GameEnemy boss_worm_head = {2, &anim_worm_head, false, &Worm_Head_AI, &Worm_Head_Col};