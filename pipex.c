/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 08:09:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/02/17 23:04:20 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	command_one(int *fd, char **env, char **argv)
{
	int	infile;

	infile = openfile(argv[1], 0);
	if (dup2(infile, STDIN_FILENO) == -1)
		error("dup2");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("pipe");
	close(fd[0]);
	close(fd[1]);
	close(infile);
	run_command(argv[2], env);
}

static	void	command_tow(int *fd, char **env, char **argv)
{
	int	outfile;

	outfile = openfile(argv[4], 1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error("dup2");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2");
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	run_command(argv[3], env);
}

void	pipex(char **argv, char **env)
{
	pid_t	child1;
	pid_t	child2;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		error("pipe");
	child1 = fork();
	if (child1 == -1)
		error("Fork");
	if (child1 == 0)
		command_one(fd, env, argv);
	child2 = fork();
	if (child2 == -1)
		error("Fork");
	if (child2 == 0)
		command_tow(fd, env, argv);
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(child1, &status, 0);
		waitpid(child2, &status, 0);
		exit(WEXITSTATUS(status));
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		pipex(argv, env);
	}
	else
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}
