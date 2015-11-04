/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1_7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 10:39:45 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:32:51 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		get_argc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	gestion_signaux(void)
{
	signal(SIGINT, gestion_ctrl_c);
	signal(SIGQUIT, gestion_ctrl_backslash);
}

int		print_string_is_not_in_pwd_error(char *s1)
{
	ft_putstr_fd("\033[33;31m-> Error: ", 2);
	ft_putstr_fd("\033[33;0mcd: String \"", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd("\" is not in pwd.", 2);
	return (-1);
}

int		exec_cd_change_path(t_struc *s, char *pwd, char *s1, char *s2)
{
	int	i;
	int	j;
	int	start;
	int	replaced_something;

	i = -1;
	replaced_something = 0;
	while (pwd[++i])
	{
		j = 0;
		while (pwd[i] && pwd[i] != s1[j])
			i++;
		if (!pwd[i] && !replaced_something)
			return (print_string_is_not_in_pwd_error(s1));
		else if (!pwd[i])
			return (0);
		start = i;
		while (pwd[i] && s1[j] && pwd[i++] == s1[j++])
			;
		if (!s1[j])
			s->argv[1] = replace_str(pwd, s2, start, i);
		if (!s1[j])
			replaced_something = 1;
	}
	return (0);
}

char	**copy_env(char **env)
{
	int		i;
	char	**copy_of_env;

	i = 0;
	while (env[i])
		i++;
	copy_of_env = (char**)malloc(sizeof(char*) * i + 1);
	i = 0;
	while (env[i])
	{
		copy_of_env[i] = ft_strdup(env[i]);
		i++;
	}
	copy_of_env[i] = NULL;
	return (copy_of_env);
}
