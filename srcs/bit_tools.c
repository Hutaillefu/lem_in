/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bit_tools.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 10:29:55 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 10:30:09 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
  ** Extract first bit
*/

int		is_link_exist(unsigned char data)
{
	return (data >> 7);
}

/*
 ** Extract last bit
*/

int		is_link_free(unsigned char data)
{
	return (data & 1);
}

/*
  ** Set first bit
*/

void	set_link_exist(unsigned char *data, unsigned char is_exist)
{
	if (!data || (is_exist != 0 && is_exist != 1))
		return ;
	(*data) = ((*data) & 127) | (is_exist << 7);
}

/*
 ** Set last bit
*/

void	set_link_free(unsigned char *data, unsigned char is_free)
{
	if (!data || (is_free != 0 && is_free != 1))
		return ;
	*data = ((*data) & 254) | is_free;
}
