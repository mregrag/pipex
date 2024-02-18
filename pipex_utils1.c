/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:06:13 by mregrag           #+#    #+#             */
/*   Updated: 2024/02/17 22:08:45 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	openfile(char *filename, int mode)
{
	int	file;

	if (mode == 0)
	{
		if (access(filename, F_OK) == -1)
			error(filename);
		file = open(filename, O_RDONLY);
	}
	if (mode == 1)
		file = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (file == -1)
		error(filename);
	return (file);
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	if (*env)
		return (*env + 5);
	else
		return (NULL);
}

char	*get_path_command(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	*path;

	if (find_path(env) == NULL)
		msg("pipex: ", "command not found 1: ", cmd, 127);
	paths = ft_split(find_path(env), ':');
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(path, cmd);
		free (path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (cmd);
}

void	run_command(char *cmd, char **env)
{
	char	*path;
	char	**scmd;

	scmd = ft_split(cmd, ' ');
	if ((access(cmd, F_OK | X_OK) == 0) && ft_strchr(cmd, '.'))
		execve(cmd, scmd, env);
	path = get_path_command(scmd[0], env);
	if (execve(path, scmd, env) == -1)
	{
		ft_free_tab(scmd);
		msg("pipex: ", "command not found 2: ", cmd, 127);
	}
}
