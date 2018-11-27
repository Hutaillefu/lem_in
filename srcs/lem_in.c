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
	t_list	*moves;
	t_list	*indexes;

	if (!world || !(world->start_room) || !(world->end_room) || !(world->links))
		return (0);
	moves = NULL;
	indexes = NULL;
	get_all_moves_rec(world, world->start_room, &moves, 0, -1, &indexes);
	//printf("Can rune : %d paths\n", ft_lstlen(&moves));
	//free_list(&indexes, free_index_maillon);
	if (!moves)
		return (0);
	free_list(&moves, free_move_maillon);
	return (1);
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
	init_ants(world);

	//t_list *indexes = NULL;
	//parcours(world, world->start_room, &indexes);

	//display_transi(world);
	pathfinding(world);
	printf("%s", world->print);
	exit_lemin(&world, 0);
	return (0);
}
