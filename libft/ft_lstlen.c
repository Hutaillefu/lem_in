/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 18:18:55 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 18:18:57 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list **lst)
{
	t_list	*it;
	int		res;

	if (!lst || !(*lst))
		return (0);
	res = 1;
	it = *lst;
	while (it->next)
	{
		it = it->next;
		res++;
	}
	return (res);
}
