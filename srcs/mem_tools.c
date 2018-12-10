/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mem_tools.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 10:32:47 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 10:32:50 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*create_room(const char *name, int x, int y)
{
	t_room	*room;

	if (!name || !(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->index = -1;
	room->num_ant = 0;
	return (room);
}

t_world	*create_world(void)
{
	t_world	*world;

	if (!(world = (t_world *)malloc(sizeof(t_world))))
		return (NULL);
	world->nb_ants = 0;
	world->nb_rooms = 0;
	world->start_room = NULL;
	world->end_room = NULL;
	world->rooms = NULL;
	world->ants = NULL;
	world->links = NULL;
	world->print = ft_strdup("");
	world->nb_paths = 0;
	world->paths = NULL;
	return (world);
}

/*
   ** Add in print, the readed line of the map.
*/

void	add_print(char **str, char *add, int back)
{
	char *ret;

	if (!str || !add)
		return ;
	ret = *str;
	*str = ft_strjoin(*str, add);
	free(ret);
	if (back)
	{
		ret = *str;
		*str = ft_strjoin(*str, "\n");
		free(ret);
	}
}

void	add_move_print(char **str, int ant_num, char *room_name)
{
	char *line;
	char *ret;
	char *num;

	if (!str || !room_name)
		return ;
	num = ft_itoa(ant_num);
	line = ft_strjoin("L", num);
	free(num);
	ret = *str;
	*str = ft_strjoin(*str, line);
	free(line);
	free(ret);
	ret = *str;
	*str = ft_strjoin(*str, "-");
	free(ret);
	ret = *str;
	*str = ft_strjoin(*str, room_name);
	free(ret);
	ret = *str;
	*str = ft_strjoin(*str, " ");
	free(ret);
}

int		add_room(t_world *world, t_room *room)
{
	t_list *maillon;

	if (!world || !room)
		return (0);
	room->index = ft_lstlen(&(world->rooms)) + 2;	
	if (!(maillon = ft_lstnew(room, sizeof(room))))
		return (0);
	ft_lstpush(&(world->rooms), maillon);
	(world->nb_rooms)++;
	return (1);
}
