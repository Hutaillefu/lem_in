/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 19:23:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 19:23:42 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>


void display_transi(t_world *world)
{
	int i;
	int y;

	if (!world)
		return ;
	printf("\t");
	i = 0;
	while (i < world->nb_rooms)
	{
		printf("%s\t", get_room_by_index(world, i)->name);
		i++;
	}
	printf("\n");

	i = 0;
	while (i < world->nb_rooms)
	{
		y = 0;
		printf("%s\t", get_room_by_index(world, i)->name);
		while (y < world->nb_rooms)
		{
			printf("%d\t", (int)world->links[y][i]);
			y++;
		}
		printf("\n");
		i++;
	}
}	

const char *room_name(t_list *maillon)
{
	t_room	*room;

	if (!maillon || !(maillon->content))
		return (NULL);
	if (!(room = (t_room *)maillon->content))
		return (NULL);
	return room->name;	
}

int	get_room_index_in_list(t_list *rooms, const char *name)
{
	t_list *it;
	int	i;

	if (!rooms || !name)
		return (-1);
	it = rooms;
	i = 0;
	while (it)
	{
		if (room_name(it) && ft_strcmp(name, room_name(it)) == 0)
			return (i);
		it = it->next;
		i++;
	}
	return (-1);
}

/*
  ** Return 0 for start_room, 1 for end_room and index in world's list rooms for others.
*/
int	get_room_index(t_world *world, const char *name)
{
	if (!world || !name)
		return (-1);
	if (world->start_room && world->start_room->name && ft_strcmp(name, world->start_room->name) == 0)
		return (0);
	else if (world->end_room && world->end_room->name && ft_strcmp(name, world->end_room->name) == 0)
		return (1);
	return (get_room_index_in_list(world->rooms, name) + 2);
}

t_room	*get_room_by_index(t_world *world, int index)
{
	if (!world || !(world->rooms) || index < 0)
		return (NULL);
	if (index == 0)
		return (world->start_room);
	else if (index == 1)
		return (world->end_room);
	t_room *room = (t_room *)ft_lstgetindex(&(world->rooms), index - 2)->content;
	return (room); 
		
}

int	is_room_name_exist(t_world *world, const char *name)
{
	if (!world || !name)
		return (0);
	return (get_room_index(world, name) >= 0);
	
}

/*
  ** Parse a room from line and add it to the world's room list.
*/

int	process_room(const char *line, t_world *world)
{
	t_room	*room;
	
	if (!line || !world)
		return (0);
	if (!(room = parse_room(line)))
		return (0);
	if (!(add_room(world, room)))
	{
		free_room(&room);
		return (0);
	}
	return (1);
}

int	add_link(t_world *world, int start_index, int end_index)
{
	if (!world || !world->links || start_index < 0 || end_index < 0)
		return (0);
	world->links[start_index][end_index] = 1;
	return (1);
}

int		main(int argc, char **argv)
{
	t_world	*world;

	(void)argc;
	(void)argv;

	if (!(world = create_world()))
		return (0);
	
	//if (!parse_num_ants(world) || !parse_map(world))
	//{
		// free world
	//	return (0);
	//}
	parse_num_ants(world);
	printf("Nb ants : %d\n", world->nb_ants);

	parse_map(world);

	display_transi(world);

	//display_world(world);
	return (0);
}
