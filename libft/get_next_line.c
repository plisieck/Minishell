/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 05:16:10 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/09 14:13:18 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*impro_realloc(char **line, int *i)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(*line) + *i + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, *line);
	free(*line);
	return (str);
}

static int	need_place(char **ste, char *sti)
{
	if (*ste == NULL)
		return (0);
	**ste = '\0';
	*ste += 1;
	ft_strcpy(sti, *ste);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char	sti[BUFF_SIZE];
	char		str[BUFF_SIZE + 1];
	char		*ste;
	int			i;

	if (!line || fd == -1)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char *) *
					(BUFF_SIZE + ft_strlen(sti) + 1))))
		return (-1);
	ft_strcpy(*line, sti);
	while (!((ste = ft_strchr(*line, '\n'))) &&
			((i = read(fd, str, BUFF_SIZE)) > 0))
	{
		str[i] = '\0';
		if (!(*line = impro_realloc(line, &i)))
			return (-1);
		ft_strcat(*line, str);
	}
	if (need_place(&ste, sti))
		return (1);
	if (i == 0)
		return (0);
	else
		return (-1);
}
