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
		// else if (is_link(line)
		// 	parse_link(line, world);
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
