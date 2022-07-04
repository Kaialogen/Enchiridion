#include "combat.h"

void doMeleeAttack(Entity *attacker, Entity *target)
{
	int damage, attack;
	Monster *atkMonster, *tarMonster;
	
	dungeon.attackDir.x = (target->x - attacker->x);
	dungeon.attackDir.y = (target->y - attacker->y);
	dungeon.animationTimer = FPS / 3;
	
	dungeon.attackingEntity = attacker;
	
	atkMonster = (Monster*) attacker->data;
	
	tarMonster = (Monster*) target->data;
	
	attack = atkMonster->minAttack + (rand() % ((atkMonster->maxAttack + 1) - atkMonster->minAttack));
	
	damage = attack * attack / (attack + tarMonster->defence);
	
	if (damage != 0)
	{
		tarMonster->hp -= damage;

		if (tarMonster->hp <= 0 && target != dungeon.player)
		{
			target->dead = 1;
		}

		setBloodSplat(target->x, target->y);
	}
}
