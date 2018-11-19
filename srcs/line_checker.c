/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_checker.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 17:10:58 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:10:59 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		is_room(const char *line)
{
	return (line && ft_nb_char_in_str(line, ' ') == 2);
}

int		is_link(const char *line)
{
	return (line && ft_nb_char_in_str(line, '-') == 1);
}

int		is_commentary(const char *line)
{
	return (line && *line == '#');
}

int		is_active_commentary(const char *line)
{
	return (is_commentary(line) && ft_strlen(line) >= 2 && line[1] == '#');
}
