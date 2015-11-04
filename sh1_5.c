/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 09:14:53 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:52:59 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		exec_cd(t_struc *s)
{
	int	pos;

	if (s->argc > 3)
	{
		ft_putstr_fd("\033[33;31m-> Error: ", 2);
		ft_putendl_fd("\033[33;0mcd: Too many arguments.", 2);
	}
	else
	{
		if (s->argc == 3)
			if (exec_cd_change_path(s, get_variable_value(s->env
			[grep_env(s->env, "PWD")]), s->argv[1], s->argv[2]) == -1)
				return (-1);
		if (replace_minus(s, &s->argv) == -1)
			return (-1);
		if ((pos = grep_env(s->env, "OLDPWD")))
			s->env[pos] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		exec_cd2(s, pos);
	}
	if ((pos = grep_env(s->env, "PWD")))
		s->env[pos] = ft_strjoin("PWD=", getcwd(NULL, 0));
	return (0);
}

void	exec_cd2(t_struc *s, int pos)
{
	if (s->argc == 1)
	{
		if ((pos = grep_env(s->env, "HOME")) == -1)
		{
			ft_putstr_fd("\033[33;31m-> Error: ", 2);
			ft_putendl_fd("\033[33;0mcd: No home directory.", 2);
		}
		else
			chdir(get_variable_value(s->env[grep_env(s->env, "HOME")]));
	}
	else
	{
		if (access(s->argv[1], F_OK) == -1)
		{
			ft_putstr_fd("\033[33;31m-> Error: \033[33;0mcd: No such file ", 2);
			ft_putendl_fd(ft_strjoin("or directory : ", s->argv[1]), 2);
		}
		else if (access(s->argv[1], X_OK) == -1)
		{
			ft_putstr_fd("\033[33;31m-> Error: ", 2);
			ft_putendl_fd("\033[33;0mcd: Permission denied.", 2);
		}
		else
			chdir(s->argv[1]);
	}
}

int		exec_builtin(t_struc *s, char **env)
{
	if (!s->cmd)
		return (-1);
	if (!ft_strcmp(s->cmd, "cd"))
		exec_cd(s);
	else if (!ft_strcmp(s->cmd, "env"))
		exec_env(s, env);
	else if (!ft_strcmp(s->cmd, "setenv"))
		exec_setenv(s);
	else if (!ft_strcmp(s->cmd, "unsetenv"))
		exec_unsetenv(s);
	return (0);
}

int		replace_tild(t_struc *s, char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		if ((*tab)[i][0] == '~')
		{
			if (grep_env(s->env, "HOME") == -1)
			{
				ft_putstr_fd("\033[33;31m-> Error: ", 2);
				ft_putendl_fd("\033[33;0m cd: No $home variable set.", 2);
				return (-1);
			}
			else
				(*tab)[i] = replace_str((*tab)[i], get_variable_value
						(s->env[grep_env(s->env, "HOME")]), 0, 1);
		}
		i++;
	}
	return (0);
}

int		is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
