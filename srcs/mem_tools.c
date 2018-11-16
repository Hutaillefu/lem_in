#include "lem_in.h"

t_room	*create_room(const char *name, int x, int y)
{
	t_room	*room;

	if (!name || !(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->num_ant = 0;
	return (room);
}

t_world	*create_world()
{
	t_world	*world;

	if (!(world = (t_world *)malloc(sizeof(t_world))))
			return (NULL);
	world->nb_ants = 0;
	world->nb_rooms = 0;
	world->start_room = NULL;
	world->end_room = NULL;
	world->rooms = NULL;
	world->links = NULL;
	return (world);
}

int	add_room(t_world *world, t_room *room)
{
	t_list *new_room;

	if (!world || !room)
		return (0);
	if (!(new_room = ft_lstnew(room, sizeof(room))))
		return (0);
	ft_lstpush(&(world->rooms), new_room);
	(world->nb_rooms)++;
	return (1);
}

void	free_room(t_room **room)
{
	if (!room || !(*room))
		return ;
	if ((*room)->name)
		ft_strdel((char **)&((*room)->name));
	free(*room);
	room = NULL;
}

int	init_links(t_world *world)
{
	int nb_rooms;
	int i;

	if (!world || world->links || !(world->rooms))
		return (0);
	nb_rooms = ft_lstlen(&(world->rooms)) + 2;
	if (!(world->links = (unsigned char **)malloc(sizeof(unsigned char *) * nb_rooms)))
		return (0);
	i = 0;
	while (i < nb_rooms)
	{
		if (!(world->links[i] = (unsigned char *)malloc(sizeof(unsigned char) * nb_rooms)))
			return (0);
		i++;
	}
	return (1);
}




