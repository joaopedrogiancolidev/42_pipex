/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:39:48 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/06 22:04:58 by jgiancol         ###   ########.fr       */
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

// pipex_utils.c

int		open_file(char *filename, int mode);
void	execute_command(char *cmd, char **envp);
void	ft_free_split(char **split);
#endif