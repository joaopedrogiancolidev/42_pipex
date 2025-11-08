/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:01:34 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 20:02:10 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_process_one(int *fd, int infile, int outfile, t_cmd *cmd)
{
	close(fd[0]);
	close(outfile);
	if (infile != -1)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else
		close(STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(cmd->cmd1, cmd->envp);
	exit(1);
}

void	child_process_two(int *fd, int infile, int outfile, t_cmd *cmd)
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
	execute_command(cmd->cmd2, cmd->envp);
	exit(1);
}
