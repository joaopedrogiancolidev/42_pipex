/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:46:21 by jgiancol          #+#    #+#             */
/*   Updated: 2025/11/08 19:13:48 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	open_file(char *filename, int mode)
{
	int		fd;

	if (mode == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			return (-1);
		}
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			return (-1);
		}
	}
	return (fd);
}

static char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	char	**paths;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		write(2, "Error splitting command\n", 24);
		exit(1);
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		write(2, "Command not found: ", 19);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		ft_free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	write(2, "Error executing command: ", 25);
	write(2, cmd, strlen(cmd));
	write(2, "\n", 1);
	ft_free_split(args);
	free(path);
	exit(1);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
