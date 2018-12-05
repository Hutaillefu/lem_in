/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 17:54:17 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 17:54:19 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = ft_memalloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->content = (void *)content;
	tmp->content_size = content_size;
	return (tmp);
}
