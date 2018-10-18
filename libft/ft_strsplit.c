/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 18:07:55 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 18:07:57 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	skip_sep(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	skip_word(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	get_nb_words(char const *s, char c)
{
	int nbwords;
	int i;
	int sep;
	int word;
	int index;

	nbwords = 0;
	i = 0;
	index = 0;
	while (s[i])
	{
		sep = skip_sep(&s[index], c);
		index += sep;
		word = skip_word(&s[index], c);
		index += word;
		if (word > 0)
			nbwords++;
		i += sep + word;
	}
	return (nbwords);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		nbwords;
	int		index;
	int		i;

	i = 0;
	index = 0;
	nbwords = get_nb_words(s, c);
	res = (char **)ft_memalloc(sizeof(char *) * nbwords + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < nbwords)
	{
		index += skip_sep(&s[index], c);
		res[i] = ft_strsub(s, index, skip_word(&s[index], c));
		index += skip_word(&s[index], c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
