/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:06 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/24 19:55:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void	ft_execute_process(t_shell *shell, char **envp)
{
	if (shell->argc <= 0)
		return;

	int i = -1;
	while (++i < BUILTIN)
	{
		if (!ft_strcmp(shell->args[0], shell->builtin[i].name))
		{
			int stat = shell->builtin[i].func(shell->args, shell->argc, shell->env_lst, shell->builtin[i].env);
			if (stat == 1)
				return;
		}
	}

	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char *prog_path = NULL;
		int p = -1;
		while (++p < shell->path_env->count)
		{
			char *path_s = ft_strjoin(shell->path_env->content_env[p], "/");
			prog_path = ft_strjoin(path_s, shell->args[0]);
			free(path_s);
			if (access(prog_path, X_OK) == 0)
				break;
			if (prog_path)
			{
				free(prog_path);
				prog_path = NULL;
			}
		}

		if (execve(prog_path, shell->args, envp) == -1)
		{
			char *error_s = ft_strjoin("bash: ", shell->args[0]);
			char *error = ft_strjoin(error_s, ": not found\n");
			_ft_putstr(error);
			free(error_s);
			free(error);

			//ft_putstr("Execution failed\n");
		}	
		(prog_path) ? free(prog_path) : 1;
		exit(1);
	}
	else if (pid < 0)
		ft_putstr("Forking failed\n");
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
}

char 	*ft_readline()
{
	int buff_size = READ_BUFF_SIZE;
	int len = 0;
	char *buffer = (char*)malloc(sizeof(char) * buff_size);
	char read_buffer[1];

	while (1)
	{
		read(1, read_buffer, 1);

		if (read_buffer[0] == '\n')
		{
			buffer[len] = '\0';
			return (buffer);
		}
		buffer[len] = read_buffer[0];
		len += 1;
		if (len >= buff_size)
		{
			buff_size += READ_BUFF_SIZE;
			buffer = ft_realloc(buffer, buff_size);
		}
	}
}

void	ft_init_builtins(t_shell *shell)
{
	shell->builtin[0].func = ft_cd;
	shell->builtin[1].func = ft_exit;
	shell->builtin[2].func = ft_echo;
	shell->builtin[3].func = ft_env;
	shell->builtin[4].func = ft_setenv;
	shell->builtin[5].func = ft_unsetenv;

	shell->builtin[0].name = "cd";
	shell->builtin[1].name = "exit";
	shell->builtin[2].name = "echo";
	shell->builtin[3].name = "env";
	shell->builtin[4].name = "setenv";
	shell->builtin[5].name = "unsetenv";

	shell->builtin[0].env = shell->home_env;
	shell->builtin[1].env = NULL;
	shell->builtin[2].env = NULL;
	shell->builtin[3].env = NULL;
	shell->builtin[4].env = NULL;
	shell->builtin[5].env = NULL;
}

void	ft_set_pwd(t_shell *shell)
{
	int max_dir = MAX_DIR;
	char *dir = (char*)malloc(sizeof(char) * max_dir);
	while (!getcwd(dir, max_dir))
	{
		free(dir);
		max_dir += MAX_DIR;
		dir = (char*)malloc(sizeof(char) * max_dir);
	}

	char *home_str = _ft_strstr(dir, shell->home_env->content);
	free(shell->promt_pwd);
	if (home_str)
	{
		if (shell->home_env->content[0] == '/' && !shell->home_env->content[1] && ft_strcmp(dir, "/"))
			shell->promt_pwd = ft_strjoin("~/", home_str);
		else
			shell->promt_pwd = ft_strjoin("~", home_str);
	}
	else
		shell->promt_pwd = ft_strdup(dir);

	free(shell->pwd_env->content);
	ft_strsplit_free(shell->pwd_env->content_env);

	shell->pwd_env->content = dir;
	shell->pwd_env->content_env = ft_strsplit(dir, ':');
	shell->pwd_env->count = 1;
}

int		main(int argc, char **argv, char **envp)
{
	t_shell *shell = (t_shell*)malloc(sizeof(t_shell));

	ft_init_env(shell, envp);
	ft_init_builtins(shell);

	system("clear");
	while (1)
	{
		ft_set_pwd(shell);

		write(1, COLOR_GREEN, 7);
		_ft_putstr(shell->user_env->content);
		write(1, COLOR_WHITE, 4);
		write(1, ":", 1);
		write(1, COLOR_BLUE, 7);
		_ft_putstr(shell->promt_pwd);
		write(1, COLOR_WHITE, 4);
		write(1, "$>", 2);

		char *line = ft_readline();

		char **command = ft_strsplit(line, ';');
		int i = -1;
		while (command[++i])
		{
			shell->args = ft_strsplit_whitespaces(command[i]);
			shell->argc = 0;
			while (shell->args[shell->argc])
				shell->argc++;

			ft_execute_process(shell, envp);

			ft_strsplit_free(shell->args);
		}

		free(line);
		ft_strsplit_free(command);
	}
	return (0);
}
