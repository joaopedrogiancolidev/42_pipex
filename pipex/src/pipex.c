/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:50:51 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 20:01:01 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	init_pipex(t_pipex *data, char **argv, char **envp)
{
	if (pipe(data->fd) == -1)
		return (perror("pipe"), 1);
	data->infile = open_file(argv[1], 0);
	data->outfile = open_file(argv[4], 1);
	data->cmd.cmd1 = argv[2];
	data->cmd.cmd2 = argv[3];
	data->cmd.envp = envp;
	return (0);
}

static void	cleanup_and_wait(t_pipex *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &data->status, 0);
}

static int	fork_processes(t_pipex *data)
{
	data->pid1 = fork();
	if (data->pid1 == -1)
		return (perror("fork"), 1);
	if (data->pid1 == 0)
		child_process_one(data->fd, data->infile, data->outfile, &data->cmd);
	data->pid2 = fork();
	if (data->pid2 == -1)
		return (perror("fork"), 1);
	if (data->pid2 == 0)
		child_process_two(data->fd, data->infile, data->outfile, &data->cmd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
		return (write(2, ARG_ERROR, sizeof(ARG_ERROR)), 1);
	if (init_pipex(&data, argv, envp))
		return (1);
	if (fork_processes(&data))
		return (1);
	cleanup_and_wait(&data);
	if (data.outfile == -1)
		return (1);
	if (WIFEXITED(data.status))
		return (WEXITSTATUS(data.status));
	return (1);
}
