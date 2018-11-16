/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 19:19:01 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 19:19:18 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "../libft/libft.h"

typedef struct	s_room{
	const char	*name;
	int			x;
	int			y;
	int			num_ant;
}               t_room;

typedef struct	s_world
{
	int				nb_ants;
	int				nb_rooms;
	t_room			*start_room;
	t_room			*end_room;
	t_list			*rooms;
	unsigned char	**links;
}				t_world;

int		is_commentary(const char *line);
int		is_active_commentary(const char *line);
int		is_room(const char *line);
int		is_link(const char *line);

t_room		*create_room(const char *name, int x, int y);
void		free_room(t_room **room);
t_world		*create_world();
int		add_room(t_world *world, t_room *room);
int		init_links(t_world *world);

t_room		*parse_room(const char *line);

#endif
