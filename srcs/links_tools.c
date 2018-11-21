/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   links_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 15:35:10 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 15:35:15 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Set each existing links as free.
*/

void	reinit_links(t_world *world)
{
	int i;
	int y;

	i = 0;
	while (i < world->nb_rooms)
	{
		y = 0;
		while (y < world->nb_rooms)
		{
			if (is_link_exist(world->links[i][y]))
				set_link_free(&(world->links[i][y]), 1);
			else if (is_link_exist(world->links[y][i]))
				set_link_free(&(world->links[y][i]), 1);
			y++;
		}
		i++;
	}
}

/*
   ** Create link 'start_index' -> 'end_index' and setup it as free.
*/

int		add_link(t_world *world, int start_index, int end_index)
{
	if (!world || !world->links || start_index < 0 || end_index < 0)
		return (0);
	set_link_exist(&(world->links[start_index][end_index]), 1);
	set_link_free(&(world->links[start_index][end_index]), 1);
	return (1);
}
