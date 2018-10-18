/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstgetindex.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 17:53:48 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 17:53:50 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetindex(t_list **lst, int index)
{
	int		i;
	t_list	*iterator;

	if (index < 0 || !lst || !(*lst))
		return (NULL);
	i = 0;
	iterator = *lst;
	while (i != index && iterator->next)
	{
		iterator = iterator->next;
		i++;
	}
	if (i == index)
		return (iterator);
	return (NULL);
}
