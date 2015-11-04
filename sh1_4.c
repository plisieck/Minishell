/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 08:57:39 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/14 22:12:17 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		exec_unsetenv(t_struc *s)
{
	if (s->argc == 1)
	{
		ft_putstr_fd("\033[33;31m-> Error: ", 2);
		ft_putendl_fd("\033[33;0munsetenv: Too few arguments.", 2);
		return (-1);
	}
	else
		exec_unsetenv2(s);
	return (0);
}

void	exec_unsetenv2(t_struc *s)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	i = 0;
	k = 1;
	while (s->env[i])
		i++;
	new_env = (char**)malloc(sizeof(char*) * i + 1);
	while (s->argv[k])
	{
		i = 0;
		j = 0;
		while (s->env[i])
		{
			if (ft_strcmp(get_variable_name(s->env[i]), s->argv[k]))
				new_env[j++] = s->env[i];
			i++;
		}
		new_env[j] = NULL;
		s->env = new_env;
		k++;
	}
}

int		replace_minus(t_struc *s, char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		if ((*tab)[i][0] == '-')
		{
			if (grep_env(s->env, "OLDPWD") == -1)
			{
				ft_putstr_fd("\033[33;31m-> Error: ", 2);
				ft_putendl_fd("\033[33;0m cd: No $OLDPWD variable set.", 2);
				return (-1);
			}
			else
				(*tab)[i] = replace_str((*tab)[i], get_variable_value
						(s->env[grep_env(s->env, "OLDPWD")]), 0, 1);
		}
		i++;
	}
	return (0);
}

int		exec_cmd(t_struc *s, char **env)
{
	if (!s->cmd)
		return (-1);
	s->pid = fork();
	if (s->pid == -1)
		ft_putendl("Fork failed");
	else if (s->pid == 0)
	{
		exec(s, env);
		exit(0);
	}
	else if (s->pid > 0)
		wait(NULL);
	return (0);
}

char	**creat_minimalist_env(void)
{
	char **env;

	env = (char **)malloc(sizeof(char*) * 4);
	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	env[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[2] = ft_strdup("SHLVL=1");
	env[3] = NULL;
	return (env);
}
