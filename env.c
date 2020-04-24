/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 19:47:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2020/04/24 15:45:59 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void	ft_init_env(t_shell *shell, char **envp)
{
	shell->path_env = NULL;
	shell->home_env = NULL;
	shell->pwd_env = NULL;

	t_env *env_head = NULL;
	t_env *env_std_head = NULL;
	shell->env = NULL;
	shell->env_std = NULL;
	shell->env_count = 0;

	shell->env_lst = (t_env_lst*)malloc(sizeof(t_env_lst));

	int i = -1;
	while (envp[++i])
	{
		int name_len = 0;
		while (envp[i][name_len] && envp[i][name_len] != '=')
			name_len++;
		char *name = (char*)malloc(sizeof(char) * (name_len + 1));
		int n = -1;
		while (++n < name_len)
			name[n] = envp[i][n];
		name[n] = '\0';
		name_len++;

		if (shell->env_count == 0)
		{
			shell->env = (t_env*)malloc(sizeof(t_env));
			shell->env->name = ft_strdup(name);
			shell->env->content = ft_strdup(&envp[i][name_len]);
			shell->env->content_env = ft_strsplit(&envp[i][name_len], ':');
			shell->env->count = 0;
			while (shell->env->content_env[shell->env->count])
				shell->env->count++;
			shell->env->next = NULL;

			shell->env_std = (t_env*)malloc(sizeof(t_env));
			shell->env_std->name = ft_strdup(name);
			shell->env_std->content = ft_strdup(&envp[i][name_len]);
			shell->env_std->content_env = ft_strsplit(&envp[i][name_len], ':');
			shell->env_std->count = 0;
			while (shell->env_std->content_env[shell->env_std->count])
				shell->env_std->count++;
			shell->env_std->next = NULL;

			env_head = shell->env;
			env_std_head = shell->env_std;
		}
		else
		{
			shell->env->next = (t_env*)malloc(sizeof(t_env));
			shell->env->next->name = ft_strdup(name);
			shell->env->next->content = ft_strdup(&envp[i][name_len]);
			shell->env->next->content_env = ft_strsplit(&envp[i][name_len], ':');
			shell->env->next->count = 0;
			while (shell->env->next->content_env[shell->env->next->count])
				shell->env->next->count++;
			shell->env = shell->env->next;
			shell->env->next = NULL;

			shell->env_std->next = (t_env*)malloc(sizeof(t_env));
			shell->env_std->next->name = ft_strdup(name);
			shell->env_std->next->content = ft_strdup(&envp[i][name_len]);
			shell->env_std->next->content_env = ft_strsplit(&envp[i][name_len], ':');
			shell->env_std->next->count = 0;
			while (shell->env_std->next->content_env[shell->env_std->next->count])
				shell->env_std->next->count++;
			shell->env_std = shell->env_std->next;
			shell->env_std->next = NULL;
		}
		shell->env_count++;

		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			shell->path_env = shell->env;
		else if (envp[i][0] == 'H' && envp[i][1] == 'O' && envp[i][2] == 'M' && envp[i][3] == 'E')
			shell->home_env = shell->env;
		else if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
		{
			shell->pwd_env = shell->env;
			shell->promt_pwd = ft_strdup(shell->env->content);
		}
		else if (envp[i][0] == 'U' && envp[i][1] == 'S' && envp[i][2] == 'E' && envp[i][3] == 'R')
			shell->user_env = shell->env;

		free(name);
	}

	shell->env = env_head;
	shell->env_std = env_std_head;
	shell->env_lst->env = env_head;
	shell->env_lst->env_std = env_std_head;
}

char	*ft_get_env_content(t_env *env_head, char *name)
{
	t_env *env = env_head;
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->content);

		env = env->next;
	}
	return ("");
}
