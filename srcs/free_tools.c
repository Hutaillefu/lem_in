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



void	free_ant(t_ant **ant)
{
	if (!ant || !(*ant))
		return ;	
	free(*ant);
	ant = NULL;
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

void	free_list(t_list **lst, void (*del)(void *, int))
{
	t_list	*it;
	t_list	*next;

	if (!lst || !(*lst) || !del)
		return ;
	it = *lst;
	while (it)
	{
		next = it->next;
		del(&(it->content), it->content_size);
		free(it);
		it = next;
	}
	lst = NULL;
}

void	free_world(t_world **world)
{
	if (!world || !(*world))
		return ;
	free_room(&((*world)->start_room));
	free_room(&((*world)->end_room));
	free_list(&((*world)->rooms), free_room_maillon);
	free_list(&((*world)->ants), free_ant_maillon);
	free_links((*world)->links, (*world)->nb_rooms);
	free(*world);
	world = NULL;
}
