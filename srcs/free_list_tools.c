/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_list_tools.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 15:24:28 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 15:24:30 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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

void	free_move_maillon(void *content, int content_size)
{
	t_move	**move;

	(void)content_size;
	if (!content)
		return ;
	move = (t_move **)content;
	if (!move || !(*move))
		return ;
	free_move(move);
}

void	free_index_maillon(void *content, int content_size)
{
	int	*index;

	(void)content_size;
	if (!content)
		return ;
	index = (int *)content;
	if (!index)
		return ;
	free(index);
}

/*
   ** Free each link and its content using 'del'.
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
