/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:21 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/17 18:23:47 by zjeyne-l         ###   ########.fr       */
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

typedef	struct		s_builtin
{
	int				(*func)(char **args, int argc, t_env *env, t_env *env_std);
	char			*name;
}					t_builtin;

typedef	struct		s_shell
{
	t_builtin		builtin[BUILTIN];

	char			**args;
	int 			argc;

	t_env			*path_env;

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

int 				ft_cd(char **args, int argc, t_env *env, t_env *env_std);
int					ft_exit(char **args, int argc, t_env *env, t_env *env_std);
int					ft_echo(char **args, int argc, t_env *env, t_env *env_std);
int					ft_env(char **args, int argc, t_env *env, t_env *env_std);
int					ft_setenv(char **args, int argc, t_env *env, t_env *env_std);
int					ft_unsetenv(char **args, int argc, t_env *env, t_env *env_std);

void				ft_init_env(t_shell *shell, char **envp);
char				*ft_get_env_content(t_env *env_head, char *name);
