/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   index_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 15:54:29 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 15:54:31 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	add_index(t_list **indexes, int index)
{
	int	*value;

	if (!indexes)
		return ;
	value = (int *)malloc(sizeof(int));
	*value = index;
	ft_lstadd(indexes, ft_lstnew(value, sizeof(value)));
}

void	rm_index(t_list **indexes, int index)
{
	t_list	*it;
	t_list	*prev;

	if (!indexes)
		return ;
	if (*(int *)(*indexes)->content == index)
	{
		it = *indexes;
		*indexes = it->next;
		free(it->content);
		free(it);
		return ;
	}
	prev = *indexes;
	it = prev->next;
	while (it)
	{
		if (*(int *)it->content == index)
		{
			prev->next = it->next;
			free(it->content);
			free(it);
			return ;
		}
		prev = it;
		it = it->next;
	}
}

int		indexes_contains(t_list **indexes, int index)
{
	t_list *it;

	if (!indexes)
		return (0);
	it = *indexes;
	while (it)
	{
		if ((*(int *)it->content) == index)
			return (1);
		it = it->next;
	}
	return (0);
}
