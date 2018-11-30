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

	if (!world || !(world->links))
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
			if (is_link_exist(world->links[y][i]))
			{
				if (is_link_free(world->links[y][i]))
					printf("1\t");
				else
					printf("2\t");
			}
			else
				printf("0\t");
			y++;
		}
		printf("\n");
		i++;
	}
}	

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

t_list	*get_start_voisins(t_world *world)
{
	int		i;
	t_list	*voisins;
	t_room	*room;

	voisins = NULL;
	i = 1;
	while (i < world->nb_rooms)
	{
		room = get_room_by_index(world, i);
		if (is_joinable(world, world->start_room, room))
			ft_lstpush(&voisins, ft_lstnew(room, sizeof(room)));
		i++;
	}
	return voisins;
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
	// printf("%s", world->print);
	// free(world->print);
	// world->print = ft_strdup("");
	// //free(world->print);
	init_ants(world);
	//display_transi(world);

	// while (visited)
	// {
	// 	display_room((t_room *)visited->content);
	// 	visited = visited->next;
	// }

	// set_ant_reach(world, 34);
	// printf("Is ant num %d is reached : %d\n", 2, is_ant_reach(world, 34));
	// set_ant_reach(world, 2);
	// set_ant_reach(world, 3);
	// set_ant_reach(world, 4);

	// int start_voisins = nb_voisins(world, world->start_room);
	// int end_voisins = nb_voisins(world, world->end_room);
	// printf("Start has %d voisins\n", start_voisins);
	// printf("End has %d voisins\n", end_voisins);
	// bfs(world, world->start_room, start_voisins < end_voisins ? start_voisins : end_voisins);

	// t_list *start_voisins = NULL;
	// start_voisins = get_start_voisins(world);
	// printf("Start has %d voisins\n", ft_lstlen(&start_voisins));

	// t_list *moves = NULL;
	// get_all_moves_rec(world, world->start_room, &moves, 0, -1);
	// printf("%d possible paths\n", ft_lstlen(&moves));
	// printf("best move cost : %d\n", get_best_move(world, moves)->cost);

	//display_transi(world);
	pathfinding(world);
	//printf("%s", world->print);
	exit_lemin(&world, 0);
	return (0);
}
