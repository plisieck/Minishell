/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:50:47 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 13:55:31 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		exec_env(t_struc *s, char **env2)
{
	int		i;
	int		j;
	int		option_i;
	char	**new_env;

	i = 1;
	j = 1;
	option_i = 0;
	new_env = env2 ? copy_env(env2) : (char **)malloc(sizeof(char *) * 1);
	if (s->argc == 1)
		print_env(new_env);
	else
	{
		if (get_env_options(s, &i, &option_i) == -1)
			return (-1);
		if (option_i)
			new_env = (char **)malloc(sizeof(char *) * 1);
		s->cmd = NULL;
		new_env = exec_env2(s, i, j, new_env);
		if (s->cmd)
			!is_builtin(s) ? exec_cmd(s, new_env) : exec_builtin(s, new_env);
		else
			print_env(new_env);
	}
	return (0);
}

void	run_minishell2(t_struc *s, char **tab)
{
	int		i;
	char	**tab2;

	i = 0;
	while (tab[i])
	{
		tab2 = ft_strdoublesplit(tab[i], ' ', '\t');
		if (replace_tild(s, &tab2) == -1)
			break ;
		s->argc = get_argc(tab2);
		s->cmd = tab2[0];
		if (!s->cmd)
			break ;
		s->argv = tab2;
		if (!ft_strcmp(s->cmd, "exit"))
			exec_exit(s);
		g_ctrl_c = 1;
		!is_builtin(s) ? exec_cmd(s, s->env) : exec_builtin(s, s->env);
		free(s->cmd);
		i++;
	}
}

int		run_minishell(t_struc *s)
{
	int		i;
	char	**tab;

	i = 0;
	if (!get_next_line(0, &s->line))
		exit (write(1, "\n", 1));
	if (s->line[0] == 0x0c)
		return (gestion_ctrl_l());
	tab = ft_strsplit(s->line, ';');
	run_minishell2(s, tab);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_struc	s;

	ft_poubelle(argc, argv);
	gestion_signaux();
	if (env[0])
		s.env = copy_env(env);
	else
		s.env = creat_minimalist_env();
	increment_shlvl(&s);
	s.line = ft_strnew(0);
	while (42)
	{
		ft_putstr("[\033[32mMinishell\033[33;0m] > ");
		run_minishell(&s);
	}
	free(s.line);
	return (0);
}
