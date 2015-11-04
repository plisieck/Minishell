/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 14:48:02 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/16 14:47:58 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef	struct	s_struc
{
	pid_t		pid;
	char		*cmd;
	int			argc;
	char		*line;
	char		**env;
	char		**argv;
}				t_struc;

int				g_ctrl_c;

int				is_builtin(t_struc *s);
char			**get_paths(t_struc *s);
int				exec(t_struc *s, char **env);
char			*get_variable_name(char *str);
char			**add_variable_to_env(char **env, char *str);

char			**replace_existing_variable(char **env, char *name, char *str);
char			*get_variable_value(char *str);
void			print_env(char **env);
int				grep_env(char **env, char *str);
void			increment_shlvl(t_struc *s);

char			*replace_str(char *str, char *add, int start, int end);
int				does_not_contain(char *str, char c);
int				check_if_variable_exist(char **env, char *variable_name);
int				exec_setenv(t_struc *s);
void			exec_setenv2(t_struc *s);

int				exec_unsetenv(t_struc *s);
void			exec_unsetenv2(t_struc *s);
int				replace_minus(t_struc *s, char ***tab);
int				exec_cmd(t_struc *s, char **env);
char			**creat_minimalist_env(void);

int				exec_cd(t_struc *s);
void			exec_cd2(t_struc *s, int pos);
int				exec_builtin(t_struc *s, char **env);
int				replace_tild(t_struc *s, char ***tab);
int				is_only_digit(char *str);

void			ft_poubelle(int argc, char **argv);
int				exec_exit(t_struc *s);
void			gestion_ctrl_c(int i);
int				gestion_ctrl_l(void);
void			gestion_ctrl_backslash(int i);

void			gestion_signaux(void);
int				get_argc(char **tab);
int				print_string_is_not_in_pwd_error(char *s1);
int				exec_cd_change_path(t_struc *s, char *pwd, char *s1, char *s2);
char			**copy_env(char **env);

int				get_env_options(t_struc *s, int *i, int *option_i);
char			**exec_env2(t_struc *s, int i, int j, char **new_env);

int				exec_env(t_struc *s, char **env2);

#endif
