/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 09:22:34 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:54:24 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	ft_poubelle(int argc, char **argv)
{
	argc += 0;
	argv[0] = argv[0];
}

int		exec_exit(t_struc *s)
{
	if (s->argc > 2)
	{
		ft_putstr_fd("\033[33;31m-> Error: ", 2);
		ft_putendl_fd("\033[33;0mexit: Too many arguments.", 2);
	}
	else if (s->argv[1] && !is_only_digit(s->argv[1]))
		ft_putendl_fd("\033[33;31m-> Error: \033[33;0mexit: Syntax error.", 2);
	else if (s->argv[1])
		exit(ft_atoi(s->argv[1]));
	else
		exit(0);
	return (0);
}

void	gestion_ctrl_c(int i)
{
	i += 0;
	ft_putchar('\n');
	if (!g_ctrl_c)
		ft_putstr("[\033[32mMinishell\033[33;0m] > ");
	g_ctrl_c = 0;
}

int		gestion_ctrl_l(void)
{
	ft_putstr("\033c");
	return (-1);
}

void	gestion_ctrl_backslash(int i)
{
	i += 0;
	write(1, "\b\b", 2);
}
