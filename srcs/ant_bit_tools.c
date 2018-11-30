#include "lem_in.h"

int is_ant_reach(t_world *world, int ant_num)
{
	int int_index; // index in world->ants
	int index;	 // index of bit in int of 32 bits

	if (!world)
		return (0);
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	return ((world->ants[int_index] >> (31 - index)) & 1);
}

void set_ant_reach(t_world *world, int ant_num)
{
	int int_index; // index in world->ants
	int index;	 // index of bit in int of 32 bits

	if (!world)
		return;
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	world->ants[int_index] |= (1 << (31 - index));
}