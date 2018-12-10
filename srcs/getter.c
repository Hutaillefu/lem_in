/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getter.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 15:05:12 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 15:05:14 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Return start_room for 'index' 0, end_room for 'index' 1
  ** other room for 'index' > 1.
*/

t_room		*get_room_by_index(t_world *world, int index)
{
	if (!world || index < 0)
		return (NULL);
	if (index == 0)
		return (world->start_room);
	else if (index == 1)
		return (world->end_room);
	return ((t_room *)(ft_lstgetindex(&(world->rooms), index - 2)->content));
}

/*
  ** Return the index of the room 'name' in 'rooms'.
*/

static int	get_room_index_in_list(t_list *rooms, const char *name)
{
	t_list	*it;
	int		i;

	if (!rooms || !name)
		return (-1);
	it = rooms;
	i = 0;
	while (it)
	{
		if (ft_strcmp(name, ((t_room *)it->content)->name) == 0)
			return (i);
		it = it->next;
		i++;
	}
	return (-1);
}

/*
  ** Return 0 for start_room, 1 for end_room
  ** and index in world's list rooms for others.
*/

int			get_room_index(t_world *world, const char *name)
{
	int index;

	if (!world || !name)
		return (-1);
	if (world->start_room && world->start_room->name &&
	ft_strcmp(name, world->start_room->name) == 0)
		return (0);
	else if (world->end_room && world->end_room->name &&
	ft_strcmp(name, world->end_room->name) == 0)
		return (1);
	if ((index = get_room_index_in_list(world->rooms, name)) != -1)
		return (index + 2);
	return (-1);
}

/*
  ** Return the maillon of path where the 'ant' is or NULL if ant is on start.
*/

t_list		*get_room_where_ant(t_world *world, int ant_num)
{
	t_list	*it;
	int		i;

	if (!world)
		return (NULL);
	i = -1;
	while (++i < world->nb_paths)
	{
		it = world->paths[i];
		while (it)
		{
			if (((t_room *)it->content)->num_ant == ant_num)
				return (it);
			it = it->next;
		}
	}
	return (NULL);
}
