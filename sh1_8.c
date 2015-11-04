/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 13:42:17 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:48:33 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		get_env_options(t_struc *s, int *i, int *option_i)
{
	while (s->argv[*i] && s->argv[*i][0] == '-')
	{
		s->argv[*i]++;
		while (*s->argv[*i])
		{
			if (*s->argv[*i] == 'i')
				*option_i = 1;
			else
			{
				ft_putstr_fd("\033[33;31m-> Error: ", 2);
				ft_putstr_fd("\033[33;0menv: Illegal option -- ", 2);
				ft_putchar_fd(*s->argv[*i], 2);
				ft_putchar_fd('\n', 2);
				ft_putstr_fd("\033[33;32m-> Usage: \033[33;0menv [-i] ", 2);
				ft_putendl_fd("[name=value ...] [utility [argument...]]", 2);
				return (-1);
			}
			s->argv[*i]++;
		}
		(*i)++;
	}
	return (0);
}

char	**exec_env2(t_struc *s, int i, int j, char **new_env)
{
	while (s->argv[i])
	{
		if (!does_not_contain(s->argv[i], '='))
		{
			if (check_if_variable_exist(new_env, get_variable_name(s->argv[i])))
			{
				new_env = replace_existing_variable(new_env,
				get_variable_name(s->argv[i]), get_variable_value(s->argv[i]));
			}
			else
				new_env = add_variable_to_env(new_env, s->argv[i]);
		}
		else
		{
			s->cmd = s->argv[i++];
			while (s->argv[i])
				s->argv[j++] = s->argv[i++];
			s->argc = i;
			s->argv[j] = NULL;
			break ;
		}
		i++;
	}
	return (new_env);
}
