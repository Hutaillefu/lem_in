/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 10:44:20 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 10:44:26 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	free_room(t_room **room)
{
	if (!room || !(*room))
		return ;
	if ((*room)->name)
		ft_strdel((char **)&((*room)->name));
	free(*room);
	room = NULL;
}

void	free_links(unsigned char **links, int len)
{
	int i;

	if (!links || !(*links))
		return ;
	i = 0;
	while (i < len)
	{
		free(links[i]);
		links[i] = NULL;
		i++;
	}
	free(links);
	links = NULL;
}

void	free_move(t_move **move)
{
	if (!move || !(*move))
		return ;
	free(*move);
	move = NULL;
}

void	free_world(t_world **world)
{
	int i;

	if (!world || !(*world))
		return ;
	i = -1;
	while (++i < (*world)->nb_paths)
		free_list(&((*world)->paths[i]), NULL);
	free((*world)->paths);
	free_room(&((*world)->start_room));
	free_room(&((*world)->end_room));
	free_list(&((*world)->rooms), free_room_maillon);
	free((*world)->ants);
	free_links((*world)->links, (*world)->nb_rooms);
	if ((*world)->print)
		free((*world)->print);
	free(*world);
	world = NULL;
}
