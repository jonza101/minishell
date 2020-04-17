/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:21 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/17 21:26:34 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#include "gnl/get_next_line.h"


#define READ_BUFF_SIZE 256

#define BUILTIN 6


typedef	struct		s_env
{
	char			*name;
	char			*content;

	char			**content_env;
	int				count;

	struct s_env	*next;
}					t_env;

typedef	struct		s_env_lst
{
	t_env			*env;
	t_env			*env_std;
}					t_env_lst;

typedef	struct		s_builtin
{
	int				(*func)(char **args, int argc, t_env_lst *env_lst, t_env *inc_env);
	char			*name;

	t_env			*env;
}					t_builtin;

typedef	struct		s_shell
{
	t_builtin		builtin[BUILTIN];

	char			**args;
	int 			argc;

	t_env_lst		*env_lst;

	t_env			*path_env;
	t_env			*home_env;

	t_env			*env;
	t_env			*env_std;
	int				env_count;
}					t_shell;



void				*ft_realloc(void *ptr, size_t size);
void				_ft_putstr(const char *str);
void				_ft_putstr_endc(const char *str, char c);

char 				**ft_strsplit_whitespaces(char const *s);
char				**ft_strsplit_echo(char const *str);
char				**ft_strsplit_echo_whitespaces(char const *str);
void				ft_strsplit_free(char **split);

int 				ft_cd(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);
int					ft_exit(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);
int					ft_echo(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);
int					ft_env(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);
int					ft_setenv(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);
int					ft_unsetenv(char **args, int argc, t_env_lst * env_lst, t_env *inc_env);

void				ft_init_env(t_shell *shell, char **envp);
char				*ft_get_env_content(t_env *env_head, char *name);
