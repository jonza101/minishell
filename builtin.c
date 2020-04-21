/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:04:01 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/21 20:39:36 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int		ft_cd(char **args, int argc, t_env_lst * env_lst, t_env *inc_env)
{
	if (argc == 1)
	{
		if (chdir(inc_env->content) == -1)
		{
			char *error_s = ft_strjoin("bash: cd: ", inc_env->content);
			char *error = ft_strjoin(error_s, " no such file or directory\n");
			_ft_putstr(error);
			free(error_s);
			free(error);
		}
	}
	else if (argc == 2)
	{
		if (args[1][0] == '~')
		{
			char *path = ft_strjoin(inc_env->content, &args[1][1]);
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

int		ft_exit(char **args, int argc, t_env_lst * env_lst, t_env *inc_env)
{
	exit(1);
	return (1);
}

char	*ft_echo_line(char *line)
{
	int len = 0;
	while (line[len])
		len++;

	char *str = ft_strnew(len);

	int j = 0;
	int i = 0;
	while (i < len)
	{
		if (line[i + 1] && line[i] == '\\')
		{
			if (line[i + 1] == 'n')
			{
				str[i - j] = '\n';
				i += 1;
				j++;
			}
			else if (line[i + 1] == 't')
			{
				str[i - j] = '\t';
				i += 1;
				j++;
			}
			else if (line[i + 1] == 'v')
			{
				str[i - j] = '\v';
				i += 1;
				j++;
			}
			else if (line[i + 1] == 'f')
			{
				str[i - j] = '\f';
				i += 1;
				j++;
			}
			else if (line[i + 1] == 'r')
			{
				str[i - j] = '\r';
				i += 1;
				j++;
			}
		}
		else
		{
			str[i - j] = line[i];
		}
		i++;
	}
	free(line);
	//printf("%s\n", str);
	return (str);
}

int		ft_echo(char **args, int argc, t_env_lst *env_lst, t_env *inc_env)
{
	int n = 0;
	int e = 0;
	int E = 1;
	int l_n = 0;
	int l_e = 0;
	int l_E = 1;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return (1);
	}

	int flag = 1;

	int i = 0;
	while (++i < argc)
	{
		flag = 0;
		if (args[i][0] == '-' && flag)
		{
			int f = 0;
			while (args[i][++f])
			{
				if (args[i][f] == 'n')
				{
					l_n = 1;
				}
				else if (args[i][f] == 'e')
				{
					l_e = 1;
					l_E = 0;
				}
				else if (args[i][f] == 'E')
				{
					l_E = 1;
					l_e = 0;
				}
				else
				{
					flag = 0;
					break;
				}
			}
		}
		if (flag)
		{
			n = l_n;
			e = l_e;
			E = l_E;
			continue;
		}

		flag = 0;

		char *str = (char*)malloc(sizeof(char) * 1);
		str[0] = '\0';

		char *line = ft_echo_line(args[i]);
		int l_len = 0;
		while (line[l_len])
			l_len++;

		char ws_str[3];
		ws_str[0] = '\0';
		ws_str[1] = '\0';
		ws_str[2] = '\0';
		int pos = 0;
		while (line[pos] && (line[pos] == ' ' || line[pos] == '\n' || line[pos] == '\t' || line[pos] == '\v' || line[pos] == '\f' || line[pos] == '\r' || line[pos] == '\b'))
		{
			ws_str[0] = '\\';
			ws_str[1] = '\0';
			if (E)
			{
				if (line[pos] == '\n')
					ws_str[1] = 'n';
				else if (line[pos] == '\t')
					ws_str[1] = 't';
				else if (line[pos] == '\v')
					ws_str[1] = 'v';
				else if (line[pos] == '\f')
					ws_str[1] = 'f';
				else if (line[pos] == '\r')
					ws_str[1] = 'r';
				else if (line[pos] == '\b')
					ws_str[1] = 'b';
				else if (line[pos] == '\a')
					ws_str[1] = 'a';
				else
					ws_str[0] = ' ';
			}
			else if (e)
				ws_str[0] = line[pos];

			//ws_str[0] = line[pos];
			char *temp = ft_strjoin(str, ws_str);
			free(str);
			str = temp;

			pos++;
		}

		char **split_d = ft_strsplit_echo(line);
		int sd = -1;
		while (split_d[++sd])
		{
			char **split_ws = ft_strsplit_whitespaces(split_d[sd]);
			int ws = -1;
			while (split_ws[++ws])
			{
				if (split_ws[ws][0] == '$')
				{
					char *temp = ft_strjoin(str, ft_get_env_content(env_lst->env, &split_ws[ws][1]));
					free(str);
					str = temp;
				}
				else
				{
					char *temp = ft_strjoin(str, split_ws[ws]);
					free(str);
					str = temp;
				}

				int s_len = 0;
				while (split_ws[ws][s_len])
					s_len++;
				pos += s_len;
				while (line[pos] && (line[pos] == ' ' || line[pos] == '\n' || line[pos] == '\t' || line[pos] == '\v' || line[pos] == '\f' || line[pos] == '\r' || line[pos] == '\b'))
				{
					ws_str[0] = '\\';
					ws_str[1] = '\0';
					if (E)
					{
						if (line[pos] == '\n')
							ws_str[1] = 'n';
						else if (line[pos] == '\t')
							ws_str[1] = 't';
						else if (line[pos] == '\v')
							ws_str[1] = 'v';
						else if (line[pos] == '\f')
							ws_str[1] = 'f';
						else if (line[pos] == '\r')
							ws_str[1] = 'r';
						else if (line[pos] == '\b')
							ws_str[1] = 'b';
						else if (line[pos] == '\a')
							ws_str[1] = 'a';
						else
							ws_str[0] = ' ';
					}
					else if (e)
						ws_str[0] = line[pos];

					//ws_str[0] = line[pos];
					char *temp = ft_strjoin(str, ws_str);
					free(str);
					str = temp;

					pos++;
				}
			}
			ft_strsplit_free(split_ws);
		}
		ft_strsplit_free(split_d);

		ft_putstr(str);
		free(str);
		if (i < argc - 1)		//		NOT SURE
			write(1, " ", 1);

		// char *entr = ft_strchr(args[i], '$');
		// if (entr)
		// {
		// 	char *temp = ft_get_env_content(env_lst->env, (entr + 1));
		// 	free(args[i]);
		// 	args[i] = ft_strdup(temp);
		// 	return (0);
		// }
	}
	if (!n)
		write(1, "\n", 1);
	return (1);
}

int		ft_env(char **args, int argc, t_env_lst * env_lst, t_env *inc_env)
{
	t_env *e = env_lst->env;
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

int		ft_setenv(char **args, int argc, t_env_lst * env_lst, t_env *inc_env)
{
	if (argc != 3)
	{
		write(1, "using: setenv [VAR] [VALUE]\n", 29);
		return (1);
	}

	t_env *e = env_lst->env;
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

int		ft_unsetenv(char **args, int argc, t_env_lst * env_lst, t_env *inc_env)
{
	if (argc != 2)
	{
		write(1, "using: unsetenv [VAR]\n", 22);
		return (1);
	}

	t_env *e = env_lst->env;
	t_env *e_std = env_lst->env_std;
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
