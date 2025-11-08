/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:39:29 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 18:53:09 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc_bonus/pipex_bonus.h"

// void	child_process_first(int *pipe_fd, int infile, char *cmd, char **envp)
// {
// 	close(pipe_fd[0]);
// 	dup2(infile, STDIN_FILENO);
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(infile);
// 	close(pipe_fd[1]);
// 	execute_command(cmd, envp);
// 	exit(1);
// }

// void	child_process_middle(int *prev_pipe, int *next_pipe,
// char *cmd, char **envp)
// {
// 	close(prev_pipe[1]);
// 	close(next_pipe[0]);
// 	dup2(prev_pipe[0], STDIN_FILENO);
// 	dup2(next_pipe[1], STDOUT_FILENO);
// 	close(prev_pipe[0]);
// 	close(next_pipe[1]);
// 	execute_command(cmd, envp);
// 	exit(1);
// }

// void	child_process_last(int *pipe_fd, int outfile, char *cmd, char **envp)
// {
// 	close(pipe_fd[1]);
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	close(pipe_fd[0]);
// 	dup2(outfile, STDOUT_FILENO);
// 	close(outfile);
// 	execute_command(cmd, envp);
// 	exit(1);
// }

// void	free_pipes(int **pipes, int num_pipes)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_pipes)
// 	{
// 		free(pipes[i]);
// 		i++;
// 	}
// 	free(pipes);
// }

// int	**create_pipes(int num_pipes)
// {
// 	int	**pipes;
// 	int	i;

// 	pipes = malloc(num_pipes * sizeof(int *));
// 	if (!pipes)
// 		return (NULL);
// 	i = 0;
// 	while (i < num_pipes)
// 	{
// 		pipes[i] = malloc(2 * sizeof(int));
// 		if (!pipes[i] || pipe(pipes[i]) == -1)
// 		{
// 			while (--i >= 0)
// 				free(pipes[i]);
// 			free(pipes);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (pipes);
// }

// int	here_doc(char *limiter)
// {
// 	int		pipe_fd[2];
// 	char	*line;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		line = get_next_line(0);
// 		if (!line)
// 			break;
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 			&& line[ft_strlen(limiter)] == '\n')
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(pipe_fd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }

// void	handle_multiple_pipes(int argc, char **argv, 
//char **envp, int is_heredoc)
// {
// 	int		i;
// 	int		infile;
// 	int		outfile;
// 	int		num_cmds;
// 	int		**pipes;
// 	pid_t	pid;
// 	int		cmd_start;

// 	if (is_heredoc)
// 	{
// 		cmd_start = 3;
// 		num_cmds = argc - 4;
// 		infile = here_doc(argv[2]);
// 		outfile = open_file(argv[argc - 1], 2);
// 	}
// 	else
// 	{
// 		cmd_start = 2;
// 		num_cmds = argc - 3;
// 		infile = open_file(argv[1], 0);
// 		outfile = open_file(argv[argc - 1], 1);
// 	}

// 	pipes = create_pipes(num_cmds - 1);
// 	if (!pipes)
// 	{
// 		perror("pipe creation");
// 		exit(1);
// 	}

// 	pid = fork();
// 	if (pid == 0)
// 		child_process_first(pipes[0], infile, argv[cmd_start], envp);
// 	close(infile);

// 	i = 1;
// 	while (i < num_cmds - 1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			child_process_middle(pipes[i - 1], pipes[i],
// argv[cmd_start + i], envp);
// 		close(pipes[i - 1][0]);
// 		close(pipes[i - 1][1]);
// 		i++;
// 	}

// 	pid = fork();
// 	if (pid == 0)
// 		child_process_last(pipes[num_cmds - 2], outfile, argv[argc - 2], envp);
// 	close(pipes[num_cmds - 2][0]);
// 	close(pipes[num_cmds - 2][1]);
// 	close(outfile);

// 	i = 0;
// 	while (i < num_cmds)
// 	{
// 		wait(NULL);
// 		i++;
// 	}

// 	free_pipes(pipes, num_cmds - 1);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int	is_heredoc;

// 	is_heredoc = 0;
// 	if (argc >= 2 && ft_strncmp(argv[1], "here_doc", 8) == 0)
// 	{
// 		if (argc < 6)
// 		{
// 			write(2, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 48);
// 			return (1);
// 		}
// 		is_heredoc = 1;
// 	}
// 	else if (argc < 5)
// 	{
// 		write(2, BONUS_ARG_ERROR, ft_strlen(BONUS_ARG_ERROR));
// 		return (1);
// 	}
// 	handle_multiple_pipes(argc, argv, envp, is_heredoc);
// 	return (0);
// }
