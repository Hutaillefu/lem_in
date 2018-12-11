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

void	exit_lemin(t_world **world, int is_error)
{
	if (!world || !(*world))
		return ;
	free_world(world);
	if (is_error)
		ft_putstr_fd("Error\n", 2);
	exit(0);
}

int		can_run(t_world *world)
{
	if (!world || !(world->start_room) || !(world->end_room) ||
		!(world->links))
		return (0);
	world->nb_paths = bfs(world, world->start_room);
	return (world->nb_paths && init_ants(world) && init_paths(world));
}

int		main(int argc, char **argv)
{
	t_world	*world;

	(void)argc;
	(void)argv;
	if (!(world = create_world()))
		return (0);
	if (!parse_num_ants(world))
		exit_lemin(&world, 1);
	parse_map(world);
	if (!can_run(world))
		exit_lemin(&world, 1);
	ft_putstr(world->print);
	free(world->print);
	world->print = ft_strdup("");
	get_all_moves(world, world->start_room);
	pathfinding(world);
	ft_putstr(world->print);
	exit_lemin(&world, 0);
	return (0);
}
