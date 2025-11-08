/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:39:48 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 18:51:39 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PIPEX_H
// # define PIPEX_H

// # include "fcntl.h"
// # include "unistd.h"
// # include "sys/wait.h"
// # include "stdlib.h"
// # include "stdio.h"
// # include "string.h"
// # include "../../libft/libft.h"
// # include "../../ft_printf/includes/ft_printf.h"

// # define BONUS_ARG_ERROR "Error: Invalid number of arguments\n"
// # define PIPE_ERROR "Error: Pipe creation failed\n"
// # define FORK_ERROR "Error: Fork failed\n"

// // pipex_utils.c

// int		open_file(char *filename, int mode);
// void	execute_command(char *cmd, char **envp);
// void	ft_free_split(char **split);

// //void	child_process_first(int *fd, int infile,
// int outfile, char *cmd, char **envp);
// //void	child_process_last(int *fd, int infile,
// int outfile, char *cmd, char **envp);

// void debug_pipes(int (*pipes)[2], int num_pipes, const char *label);

// // Novas funções para bônus
// void	handle_multiple_pipes(int argc, char **argv,
// char **envp, int is_heredoc);
// void	child_process_middle(int *prev_pipe, int *next_pipe,
// char *cmd, char **envp);
// void	child_process_first(int *pipe_fd, int infile, char *cmd, char **envp);
// void	child_process_last(int *pipe_fd, int outfile, char *cmd, char **envp);

// #endif