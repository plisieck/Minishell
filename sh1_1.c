/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 16:24:23 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 15:31:39 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		is_builtin(t_struc *s)
{
	char *str;

	if (s->cmd)
	{
		str = s->cmd;
		if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "setenv") || !ft_strcmp
		(str, "unsetenv") || !ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
			return (1);
	}
	return (0);
}

char	**get_paths(t_struc *s)
{
	int		i;
	int		j;
	int		pos;
	char	**path;
	char	**temp;

	if ((pos = grep_env(s->env, "PATH")) == -1)
		return (s->env);
	temp = ft_strsplit(get_variable_value(s->env[pos]), ':');
	i = 0;
	while (temp[i])
		i++;
	path = (char **)malloc(sizeof(char *) * i);
	j = 0;
	while (j < i)
	{
		path[j] = ft_strjoin(temp[j], "/");
		free(temp[j]);
		j++;
	}
	path[j] = NULL;
	free(temp);
	return (path);
}

int		exec(t_struc *s, char **env)
{
	int		i;
	char	*temp;
	char	**paths;

	paths = get_paths(s);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], s->cmd);
		if ((access(temp, F_OK) == 0) && (access(temp, X_OK) == -1))
		{
			ft_putendl_fd(ft_strjoin("\033[33;31m-> Error:\033[33;0m ",
				ft_strjoin(s->cmd, ": Permission denied. ")), 2);
			return (0);
		}
		execve(temp, s->argv, env);
		free(temp);
		i++;
	}
	ft_putendl_fd(ft_strjoin("\033[33;31m-> Error:\033[33;0m ",
	ft_strjoin(s->cmd, ": Command not found. ")), 2);
	return (0);
}

char	*get_variable_name(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	name = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=')
		name[j++] = str[i++];
	name[j] = '\0';
	return (name);
}

char	**add_variable_to_env(char **env, char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	return (new_env);
}
