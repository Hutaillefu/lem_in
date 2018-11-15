/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nb_char_in_str.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 17:23:35 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:23:36 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
	** Return the number of char c in str.
*/

int		ft_nb_char_in_str(const char *str, unsigned char c)
{
	int i;
	int	len;
	int res;

	if (!str)
		return (0);
	len = ft_strlen(str);
	i = 0;
	res = 0;
	while (i < len)
	{
		if (str[i] == c)
			res++;
		i++;
	}
	return (res);
}
