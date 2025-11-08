/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:39:48 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 20:03:11 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "unistd.h"
# include "sys/wait.h"
# include "stdlib.h"
# include "stdio.h"
# include "string.h"
# include "../../libft/libft.h"
# include "../../ft_printf/includes/ft_printf.h"

# define ARG_ERROR "Error: Invalid number of arguments\n"
# define PIPE_ERROR "Error: Pipe creation failed\n"
# define FORK_ERROR "Error: Fork failed\n"

typedef struct s_cmd
{
	char	*cmd1;
	char	*cmd2;
	char	**envp;
}	t_cmd;

typedef struct s_pipex
{
	int		fd[2];
	__pid_t	pid1;
	__pid_t	pid2;
	int		infile;
	int		outfile;
	int		status;
	t_cmd	cmd;
}	t_pipex;

void	child_process_one(int *fd, int infile, int outfile, t_cmd *cmd);
void	child_process_two(int *fd, int infile, int outfile, t_cmd *cmd);
char	*find_path(char *cmd, char **envp);
int		open_file(char *filename, int mode);
void	execute_command(char *cmd, char **envp);
void	ft_free_split(char **split);
#endif