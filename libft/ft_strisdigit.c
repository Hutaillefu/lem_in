/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strisdigit.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 10:24:01 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 10:24:03 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisdigit(const char *str)
{
	int i;

	if (!str || !(*str))
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
