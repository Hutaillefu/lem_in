/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinding2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 13:26:20 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 13:26:22 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
   ** Set each room's num_ant as 0.
*/

static void		reset_num_ant(t_world *world)
{
	int i;

	if (!world)
		return ;
	i = 0;
	while (i < world->nb_rooms)
	{
		get_room_by_index(world, i)->num_ant = 0;
		i++;
	}
}

static t_room	*pop_room(t_list **lst)
{
	t_room	*room;
	t_list	*maillon;

	if (!lst)
		return (NULL);
	if (!(maillon = ft_lstpop(lst)))
		return (NULL);
	room = (t_room *)maillon->content;
	free(maillon);
	return (room);
}

void			bfs_2(t_world *w, t_list **rooms, t_room *room, int (*val)[4])
{
	t_room	*target;

	(*val)[2] = room->index;
	while (++((*val)[0]) < w->nb_rooms &&
	(target = get_room_by_index(w, (*val)[0])))
	{
		if (!(is_joinable(w, room, target)) || target->num_ant == 1)
		{
			set_link_exist(&(w->links[(*val)[2]][(*val)[0]]), 0);
			continue ;
		}
		set_link_exist(&(w->links[(*val)[2]][(*val)[0]]), 1);
		set_link_exist(&(w->links[(*val)[0]][(*val)[2]]), 0);
		(*val)[1]++;
		if ((*val)[0] != 1)
			target->num_ant = 1;
		else
		{
			(*val)[3]++;
			break ;
		}
		ft_lstpush(rooms, ft_lstnew(target, sizeof(target)));
	}
}

int				bfs(t_world *world, t_room *start)
{
	t_list	*rooms;
	int		val[4];

	if (!world)
		return (0);
	rooms = NULL;
	val[3] = 0;
	start->num_ant = 1;
	ft_lstpush(&rooms, ft_lstnew(start, sizeof(start)));
	while (ft_lstlen(&rooms) > 0)
	{
		val[0] = 0;
		val[1] = 0;
		bfs_2(world, &rooms, pop_room(&rooms), &val);
	}
	reset_num_ant(world);
	return (val[3]);
}
