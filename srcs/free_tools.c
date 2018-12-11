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

void	free_room_maillon(void *content, int content_size)
{
	t_room	**room;

	(void)content_size;
	if (!content)
		return ;
	room = (t_room **)content;
	if (!room || !(*room))
		return ;
	free_room(room);
}

/*
   ** Free each maillon and its content using 'del'.
   ** If del is null, free only the maillon.
*/

void	free_list(t_list **lst, void (*del)(void *, int))
{
	t_list	*it;
	t_list	*next;

	if (!lst || !(*lst))
		return ;
	it = *lst;
	while (it)
	{
		next = it->next;
		if (del)
			del(&(it->content), it->content_size);
		free(it);
		it = next;
	}
	lst = NULL;
}
