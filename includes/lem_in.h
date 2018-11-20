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

# include "../libft/libft.h"

typedef struct	s_room{
	const char	*name;
	int			x;
	int			y;
	int			num_ant;
}				t_room;

typedef struct	s_world
{
	int				nb_ants;
	int				nb_rooms;
	t_room			*start_room;
	t_room			*end_room;
	t_list			*rooms;
	t_list			*ants;
	unsigned char	**links;
}				t_world;

typedef	struct	s_move
{
	int	target_index;
	int	cost;
}				t_move;

typedef struct	s_ant
{
	int	num;
	int	is_reach;
}				t_ant;

/*
	** Selector func
*/
int				is_commentary(const char *line);
int				is_active_commentary(const char *line);
int				is_room(const char *line);
int				is_link(const char *line);

/*
	** Memory func
*/
t_room			*create_room(const char *name, int x, int y);
void			free_room(t_room **room);
void			free_ant(t_ant **ant);
void			free_move(t_move **move);
t_world			*create_world();
int				add_room(t_world *world, t_room *room);
int				init_links(t_world *world);
int				init_ants(t_world *world);

/*
	** Free func
*/
void			free_world(t_world **world);
void			free_room_maillon(void *content, int content_size);
void			free_ant_maillon(void *content, int content_size);
void			free_move_maillon(void *content, int content_size);
void			free_list(t_list **lst, void (*del)(void *, int));
void			free_indexes(t_list **indexes);

/*
	** Parser func
*/

int				parse_num_ants(t_world *world);
t_room			*parse_room(const char *line);
int				parse_active_commentary(t_world *world, const char *pre_line);
int				parse_link(const char *line, t_world *world);
void			parse_map(t_world *world);

int				get_room_index(t_world *world, const char *name);
t_room			*get_room_by_index(t_world *world, int index);

void			display_world(t_world *world);

int				add_link(t_world *world, int start_index, int end_index);

int				is_room_name_exist(t_world *world, const char *name);
const char		*room_name(t_list *maillon);

int				process_room(const char *line, t_world *world);

/*
	** Pathfinding func
*/
void			get_all_moves_rec(t_world *world, t_room *room,
t_list **all_moves, int cost, int target_index, t_list **indexes);
void			pathfinding(t_world *world);

void			display_room(t_room *room);
void			display_transi(t_world *world);

/*
	** Bit func
*/

int				is_link_exist(unsigned char data);
int				is_link_free(unsigned char data);
void			set_link_exist(unsigned char *data, unsigned char is_exist);
void			set_link_free(unsigned char *data, unsigned char is_free);

#endif
