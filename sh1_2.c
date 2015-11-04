/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 16:24:23 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:13:48 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

char	**replace_existing_variable(char **env, char *name, char *str)
{
	int	i;

	i = 0;
	while (ft_strcmp(get_variable_name(env[i]), name))
		i++;
	env[i] = ft_strjoin(ft_strjoin(get_variable_name(env[i]), "="), str);
	return (env);
}

char	*get_variable_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i++])
		j++;
	value = (char*)malloc(sizeof(char) * j + 1);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

int		grep_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(get_variable_name(env[i]), get_variable_name(str)))
			return (i);
		i++;
	}
	return (-1);
}

void	increment_shlvl(t_struc *s)
{
	int	pos;
	int	lvl;

	if ((pos = grep_env(s->env, "SHLVL")) == -1)
		return ;
	lvl = ft_atoi(get_variable_value(s->env[pos]));
	s->env[pos] = ft_strjoin(get_variable_name(s->env[pos]), "=");
	lvl += 1;
	s->env[pos] = ft_strjoin(s->env[pos], ft_itoa(lvl));
}
