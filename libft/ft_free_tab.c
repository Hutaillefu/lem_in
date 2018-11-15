#include "libft.h"

void	ft_free_tab(void **tab)
{
	int i;

	if (!tab)
		return ;
	i=0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(*tab);
	tab = NULL;
}
