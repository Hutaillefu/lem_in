/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 18:08:23 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 18:08:25 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(unsigned char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	y;
	size_t	len;
	size_t	z;

	len = ft_strlen(s);
	i = 0;
	while (s[i] && ft_isblank((unsigned char)s[i]))
		i++;
	if (i == len)
		return (char *)ft_memalloc(0);
	y = len - 1;
	z = 0;
	while (s[y] && ft_isblank((unsigned char)s[y]))
	{
		y--;
		z++;
	}
	return (ft_strsub(s, i, len - i - z));
}
