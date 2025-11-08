/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:50:51 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 19:01:19 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	__pid_t	pid1;
	__pid_t	pid2;
	int		infile;
	int		outfile;
	int		status;

	if (argc != 5)
	{
		write(2, ARG_ERROR, sizeof(ARG_ERROR));
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	infile = open_file(argv[1], 0);
	outfile = open_file(argv[4], 1);
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		if (infile != -1)
			close(infile);
		if (outfile != -1)
		{
			close(outfile);
		}
		return (1);
	}
	if (pid1 == 0)
	{
		close(fd[0]);
		close(outfile);
		if (infile != -1)
		{
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		else
		{
			close(STDIN_FILENO);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(argv[2], envp);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid2 == 0)
	{
		close(fd[1]);
		close(infile);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (outfile != -1)
		{
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		execute_command(argv[3], envp);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	if (infile != -1)
		close(infile);
	if (outfile != -1)
		close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (outfile == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
