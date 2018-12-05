/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/29 17:04:25 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 16:24:34 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int			index_of(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char		*process(char **stock)
{
	int		pos;
	char	*res;
	char	*stock_ret;

	if ((pos = index_of(*stock, '\n')) >= 0)
	{
		stock_ret = *stock;
		if (!(res = ft_strsub(*stock, 0, pos)) ||
				!(*stock = ft_strsub(*stock, pos + 1,
						ft_strlen(*stock) - pos + 1)))
			return (NULL);
		free(stock_ret);
		stock_ret = NULL;
		return (res);
	}
	return (NULL);
}

int			read_line(int fd, char **stock, char **line, char **res)
{
	char			buffer[BUFF_SIZE + 1];
	int				ret;
	char			*stock_ret;

	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		stock_ret = *stock;
		if (ret == -1 || !(*stock = ft_strjoin(*stock, buffer)))
			return (-1);
		ft_strdel(&stock_ret);
		if ((*res = process(stock)))
		{
			*line = *res;
			return (1);
		}
	}
	if (!(*res) && ft_strlen(*stock) > 0)
	{
		if (!(*line = ft_strdup(*stock)))
			return (-1);
		ft_strdel(stock);
		return (1);
	}
	return (0);
}

t_list		*get_lst(t_list **lst, size_t fd)
{
	t_list		*iterator;
	t_list		*new;

	iterator = *lst;
	while (iterator)
	{
		if (iterator->content_size == fd)
		{
			return (iterator);
		}
		iterator = iterator->next;
	}
	new = ft_lstnew(NULL, 0);
	new->content_size = fd;
	ft_lstadd(lst, new);
	return (*lst);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	char			*res;
	t_list			*current;

	res = NULL;
	current = NULL;
	if (fd < 0 || !(line))
		return (-1);
	current = get_lst(&list, (size_t)fd);
	if (!current)
		return (-1);
	if ((char *)current->content)
	{
		if ((res = process((char **)&current->content)))
		{
			*line = res;
			return (1);
		}
	}
	if (!(char *)current->content)
		if (!(char *)(current->content = ft_strdup("")))
			return (-1);
	return (read_line(fd, (char **)&current->content, line, &res));
}
