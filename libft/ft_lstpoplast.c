/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstpoplast.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 17:54:35 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 17:54:37 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpoplast(t_list **lst)
{
	t_list	*last;
	t_list	*previous;

	if (!lst || !(*lst))
		return (NULL);
	previous = NULL;
	last = *lst;
	while (last->next)
	{
		previous = last;
		last = last->next;
	}
	previous->next = NULL;
	return (last);
}
