/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_list_tools.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 15:24:28 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 15:24:30 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	free_room_maillon(void *content, int content_size)
{
	t_room	**room;

	(void)content_size;
	room = (t_room **)content;
	if (!room || !(*room))
		return ;
	free_room(room);
}

void	free_ant_maillon(void *content, int content_size)
{
	t_ant	**ant;

	(void)content_size;
	ant = (t_ant **)content;
	if (!ant || !(*ant))
		return ;
	free_ant(ant);
}
