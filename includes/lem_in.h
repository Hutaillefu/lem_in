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
	int			index;
	int			num_ant;
}				t_room;

typedef struct	s_world
{
	int				nb_ants;
	int				nb_rooms;
	t_room			*start_room;
	t_room			*end_room;
	t_list			*rooms;
	unsigned char	**links;
	int				*ants;
	char			*print;
	int				nb_paths;
	t_list			**paths;
}				t_world;

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
t_world			*create_world();
int				add_room(t_world *world, t_room *room);
int				init_links(t_world *world);
int				init_ants(t_world *world);
int				init_paths(t_world *world);

/*
	** Free func
*/
void			free_world(t_world **world);
void			free_room(t_room **room);
void			free_links(unsigned char **links, int len);
void			free_room_maillon(void *content, int content_size);
void			free_list(t_list **lst, void (*del)(void *, int));

/*
	** Parser func
*/
int				parse_num_ants(t_world *world);
t_room			*parse_room(t_world *world, const char *line);
int				parse_active_commentary(t_world *world, const char *pre_line);
int				parse_commentary(t_world *world, const char *line);
int				parse_link(const char *line, t_world *world);
void			parse_map(t_world *world);
int				setup_room(t_world **world, char *line, int index);
int				process_room(const char *line, t_world *world);
int				parse_links(t_world *world);
int				parse_rooms(t_world *world);

/*
   ** Getter func
*/
int				get_room_index(t_world *world, const char *name);
t_room			*get_room_by_index(t_world *world, int index);
t_list			*get_room_where_ant(t_world *world, int ant_num);

/*
	** Pathfinding func
*/
void			get_all_moves(t_world *world, t_room *room);
void			get_all_moves_rec(t_world *world, t_room *room,
int path_index, int val[2]);
void			pathfinding(t_world *world);
int				is_joinable(t_world *world, t_room *from, t_room *to);
int				can_join(t_world *world, t_room *from, t_room *to);
t_room			*get_best_move(t_world *world);
int				bfs(t_world *world, t_room *start);

/*
	** Bit func
*/
int				is_link_exist(unsigned char data);
int				is_link_free(unsigned char data);
void			set_link_exist(unsigned char *data, unsigned char is_exist);
void			set_link_free(unsigned char *data, unsigned char is_free);
int				is_ant_reach(t_world *world, int ant_num);
void			set_ant_reach(t_world *world, int ant_num);

/*
   ** Links tools func
*/
int				add_link(t_world *world, int start_index, int end_index);
void			reinit_links(t_world *world);

void			add_print(char **str, char *add, int back);
void			add_move_print(char **str, int ant_num, char *room_name);

#endif
