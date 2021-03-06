/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ant_bit_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 13:29:35 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 13:29:36 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
   ** Return 1 if the ant number 'ant_num' is on end_room,
   ** else return 0.
*/

int		is_ant_reach(t_world *world, int ant_num)
{
	int int_index;
	int index;

	if (!world)
		return (0);
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	return ((world->ants[int_index] >> (31 - index)) & 1);
}

/*
   ** Set the ant number 'ant_num' as reached (on end_room).
*/

void	set_ant_reach(t_world *world, int ant_num)
{
	int int_index;
	int index;

	if (!world)
		return ;
	ant_num--;
	int_index = ant_num / 32;
	index = ant_num % 32;
	world->ants[int_index] |= (1 << (31 - index));
}
