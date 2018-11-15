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

void	parse_num_ants(t_world *world)
{
	char	*line;
	int		num;

	if (!world)
		return ;
	line = NULL;
	if (get_next_line(0, &line) == -1 || !line)
		return ;
	num = ft_atoi(line);
	world->nb_ants = num;
	free(line);
	line = NULL;
}

int		parse_active_commentary(t_world *world)
{
	char *line;

	if (!world)
		return (0);
	if (get_next_line(0, &line) == -1 || !line)
		return (0);
	
	return (1);
	free(line);
	line = NULL;
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
			parse_active_commentary(world);
		//else if (is_commentary(line))
			//parse_commentary(line);
		// else if (is_room(line))
		// 	parse_room(line, world);
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

	if (!(world = (t_world *)malloc(sizeof(t_world))))
		return (0);

	parse_num_ants(world);
	parse_map(world);
	return (0);
}
