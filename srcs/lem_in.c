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

const char *room_name(t_list *maillon)
{
	t_room	*room;

	if (!maillon || !(maillon->content))
		return (NULL);
	if (!(room = (t_room *)maillon->content))
		return (NULL);
	return room->name;	
}

/*
  ** Read one line as int and set the number of ants
*/

int	parse_num_ants(t_world *world)
{
	char	*line;
	int	num;

	line = NULL;
	if (!world)
		return (0);
	line = NULL;
	if (get_next_line(0, &line) == -1 || !line)
		return (0);
	num = ft_atoi(line);
	world->nb_ants = num;
	free(line);
	line = NULL;
	return (1);
}

/*
  ** Active commentary read the next line and process it.
*/

int		parse_active_commentary(t_world *world, const char *pre_line)
{
	char	*line;
	t_room	*room;

	line = NULL;
	room = NULL;
	if (!world)
		return (0);
	if (get_next_line(0, &line) == -1 || !line)
		return (0);
	if (ft_strcmp("start", &(pre_line[2])) == 0)
	{
		if (world->start_room || !(room = parse_room(line)))
		{
			free(line);
			line = NULL;
			return (0);
		}
		world->start_room = room;
	}
	else if (ft_strcmp("end", &(pre_line[2])) == 0)
	{
		if (world->end_room || !(room = parse_room(line)))
		{
			free(line);
			line = NULL;
			return (0);
		}
		world->end_room = room;
	}
	return (1);
	free(line);
	line = NULL;
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
	return (get_room_index_in_list(world->rooms, name));
}

int	is_room_name_exist(t_world *world, const char *name)
{
	if (!world || !name)
		return (0);
	return (get_room_index(world, name) >= 0);
	
}

int	ft_tablen(char **tab)
{
	int i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*
  ** Parse the string data {name, x, y} into room object.
  ** x & y must be int.
*/

t_room	*parse_room(const char *line)
{
	char	**values;
	t_room	*room;

	values = NULL;
	room = NULL;
	if (!(values = ft_strsplit(line, ' ')))
		return (NULL);       
	if (ft_tablen(values) != 3 || !ft_strisdigit(values[1]) || !ft_strisdigit(values[2]))
	{
		ft_free_tab(values);
		return (NULL);
	}
	if (!(room = create_room(values[0], ft_atoi(values[1]), ft_atoi(values[2]))))
	{
		ft_free_tab(values);
		return (NULL);
	}
	ft_free_tab(values);
	return (room);
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
	ft_putstr("Link added\n");
	return (1);
}

int	parse_link(const char *line, t_world *world)
{
	char 	**values;
	int	start_index;
	int	end_index;

	ft_putstr("Starting link parsing\n");
	
	if (!line || !world || world->rooms)
		return (0);
	if (world->links || !init_links(world))
		return (0);
	if (!(values = ft_strsplit(line, '-')))
		return (0);
	ft_putstr("Links values extracted\n");
	if (ft_tablen(values) != 2 ||
		(start_index = get_room_index(world, values[0])) < 0 ||
		(end_index = get_room_index(world, values[1])) < 0 ||
		!is_room_name_exist(world, values[0]) ||
		!is_room_name_exist(world, values[1]) ||
		!add_link(world, start_index, end_index))
	{
		ft_free_tab(values);
	       	return (0);
	}
	ft_free_tab(values);
	return (1);
}

/*
  ** Parse stdin input into world object.
*/

void	parse_map(t_world *world)
{
	char	*line;

	if (!world)
		return ;
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (is_active_commentary(line))
			parse_active_commentary(world, line);
		//else if (is_commentary(line))
			//parse_commentary(line);
		 else if (is_room(line))
		 	process_room(line, world);
		 else if (is_link(line))
		 	parse_link(line, world);
		free(line);
		line = NULL;
	}
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
	ft_putstr("Nb ants : ");
	ft_putnbr(world->nb_ants);
	ft_putstr("\n");
	
	parse_map(world);
	ft_putendl(world->start_room->name);
	ft_putendl(world->end_room->name);
	return (0);
}
