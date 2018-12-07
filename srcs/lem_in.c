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
	if (!world || !(world->start_room) || !(world->end_room) || !(world->links))
		return (0);
	return (bfs(world, world->start_room));
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


	t_list	*moves;
	get_all_moves(world, world->start_room, &moves);
	while (moves)
	{
		t_move	*move = (t_move *)moves->content;
		printf("Move : cost=%d, target_index=%d\n", move->cost, move->target_index);
		moves = moves->next;
	}

	// free(world->print);
	// world->print = ft_strdup("");
	// init_ants(world);
	// pathfinding(world);
	// ft_putstr(world->print);
	exit_lemin(&world, 0);
	return (0);
}
