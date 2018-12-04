/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 14:16:05 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 14:16:07 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Init ant's tab. One bit per ant.
*/
int		init_ants(t_world *world)
{
	int nb_int;
	int i;

	if (!world)
		return (0);
	nb_int = world->nb_ants / 32;
	if (world->nb_ants % 32 > 0)
		nb_int++;
	if (!(world->ants = (int *)malloc(sizeof(int) * nb_int)))
		return (0);
	i = 0;
	while (i < nb_int)
	{
		world->ants[i] = 0;
		i++;
	}
	return (1);
}

int		init_links(t_world *world)
{
	int i;
	int y;

	if (!world || world->links)
		return (0);
	if (!(world->links = (unsigned char **)malloc(sizeof(unsigned char *)
	* world->nb_rooms)))
		return (0);
	i = 0;
	while (i < world->nb_rooms)
	{
		if (!(world->links[i] = (unsigned char *)malloc(sizeof(unsigned char)
		* world->nb_rooms)))
			return (0);
		y = 0;
		while (y < world->nb_rooms)
		{
			world->links[i][y] = 0;
			y++;
		}
		i++;
	}
	return (1);
}

t_list	*create_move(int cost, int target_index)
{
	t_move *move;

	move = (t_move *)malloc(sizeof(t_move));
	move->cost = cost;
	move->target_index = target_index;
	return (ft_lstnew(move, sizeof(move)));
}