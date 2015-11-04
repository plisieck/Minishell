/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 06:49:50 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:52:31 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

char	*replace_str(char *str, char *add, int start, int end)
{
	return (ft_strjoin(ft_strsub(str, 0, start), ft_strjoin(add, ft_strsub
	(str, end, ft_strlen(str) - end))));
}

int		does_not_contain(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (!*str)
		return (1);
	return (0);
}

int		check_if_variable_exist(char **env, char *variable_name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(variable_name, get_variable_name(env[i])))
			return (1);
		i++;
	}
	return (0);
}

int		exec_setenv(t_struc *s)
{
	if (s->argc == 1)
		print_env(s->env);
	else if (s->argc > 3)
	{
		ft_putstr_fd("\033[33;31m-> Error: ", 2);
		ft_putendl_fd("\033[33;0msetenv: Too many arguments.", 2);
		return (-1);
	}
	else
	{
		if (!check_if_variable_exist(s->env, s->argv[1]))
			exec_setenv2(s);
		else
		{
			if (s->argc == 2)
				s->env = replace_existing_variable(s->env, s->argv[1], "");
			else if (s->argc == 3)
				s->env = replace_existing_variable
				(s->env, s->argv[1], s->argv[2]);
		}
	}
	return (0);
}

void	exec_setenv2(t_struc *s)
{
	if (s->argc == 2)
	{
		if (does_not_contain(s->argv[1], '='))
			s->env = add_variable_to_env(s->env, ft_strjoin(s->argv[1], "="));
		else
		{
			ft_putstr_fd("\033[33;31m-> Error: ", 2);
			ft_putendl_fd("\033[33;0msetenv: Syntax error.", 2);
		}
	}
	else if (s->argc == 3)
	{
		if (does_not_contain(s->argv[1], '='))
			s->env = add_variable_to_env(s->env, ft_strjoin(ft_strjoin
						(s->argv[1], "="), s->argv[2]));
		else
		{
			ft_putstr_fd("\033[33;31m-> Error: ", 2);
			ft_putendl_fd("\033[33;0msetenv: Syntax error.", 2);
		}
	}
}
