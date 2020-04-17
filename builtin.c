/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:04:01 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/17 18:28:51 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int		ft_cd(char **args, int argc, t_env *env, t_env *env_std)
{
	if (argc == 1)
	{
		struct passwd *pwd;
		pwd = getpwuid(getuid());
		if (chdir(pwd->pw_dir) == -1)
			printf("cd error\n");
	}
	else if (argc == 2)
	{
		if (args[1][0] == '~')
		{
			struct passwd *pwd;
			pwd = getpwuid(getuid());
			char *path = ft_strjoin(pwd->pw_dir, &args[1][1]);
			if (chdir(path) == -1)
			{
				char *error_s = ft_strjoin("bash: cd: ", path);
				char *error = ft_strjoin(error_s, " no such file or directory\n");
				_ft_putstr(error);
				free(error_s);
				free(error);
			}
			free(path);
		}
		else
		{
			if (chdir(args[1]) == -1)
			{
				char *error_s = ft_strjoin("bash: cd: ", args[1]);
				char *error = ft_strjoin(error_s, " no such file or directory\n");
				_ft_putstr(error);
				free(error_s);
				free(error);
			}
		}
	}
	else
		printf("bash: cd: too many arguments\n");

	return (1);
}

int		ft_exit(char **args, int argc, t_env *env, t_env *env_std)
{
	exit(1);
	return (1);
}

int		ft_echo(char **args, int argc, t_env *env, t_env *env_std)
{
	int i = 0;
	while (++i < argc)
	{
		char *entr = ft_strchr(args[i], '$');
		if (entr)
		{
			char *temp = ft_get_env_content(env, (entr + 1));
			free(args[i]);
			args[i] = ft_strdup(temp);
			return (0);
		}
	}
	return (0);
}

int		ft_env(char **args, int argc, t_env *env, t_env *env_std)
{
	t_env *e = env;
	while (e)
	{
		char *env_s = ft_strjoin(e->name, "=");
		char *env_str = ft_strjoin(env_s, e->content);
		_ft_putstr_endc(env_str, '\n');
		free(env_s);
		free(env_str);

		e = e->next;
	}
	return (1);
}

int		ft_setenv(char **args, int argc, t_env *env, t_env *env_std)
{
	if (argc != 3)
	{
		write(1, "using: setenv [VAR] [VALUE]\n", 29);
		return (1);
	}

	t_env *e = env;
	while (e)
	{
		if (!ft_strcmp(args[1], e->name))
		{
			free(e->content);
			ft_strsplit_free(e->content_env);

			e->content = ft_strdup(args[2]);
			e->content_env = ft_strsplit(args[2], ':');
			e->count = 0;
			while (e->content_env[e->count])
				e->count++;

			return (1);
		}
		e = e->next;
	}

	write(1, "using: setenv [VAR] [VALUE]\n", 29);
	return (1);
}

int		ft_unsetenv(char **args, int argc, t_env *env, t_env *env_std)
{
	if (argc != 2)
	{
		write(1, "using: unsetenv [VAR]\n", 22);
		return (1);
	}

	t_env *e = env;
	t_env *e_std = env_std;
	while (e)
	{
		if (!ft_strcmp(args[1], e->name))
		{
			free(e->content);
			ft_strsplit_free(e->content_env);

			e->content = ft_strdup(e_std->content);
			e->content_env = ft_strsplit(e->content, ':');
			e->count = 0;
			while (e->content_env[e->count])
				e->count++;
			
			return (1);
		}

		e = e->next;
		e_std = e_std->next;
	}

	write(1, "using: unsetenv [VAR]\n", 22);
	return (1);
}
