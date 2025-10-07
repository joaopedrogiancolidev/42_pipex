/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:43:56 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/07 14:46:48 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

int		open_file(char *filename, int mode)
{
	int		fd;

	if (mode == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file");
			exit(1);
		}
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error opening output file");
			exit(1);
		}
	}
	return (fd);
}

static char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	char	*temp;
	char	**paths;
	int		i;

	fprintf(stderr, "DEBUG: find_path called with cmd='%s'\n", cmd);
	
	// Se o comando já tem /, verifica se existe
	if (ft_strchr(cmd, '/'))
	{
		fprintf(stderr, "DEBUG: Command has '/', checking access...\n");
		if (access(cmd, X_OK) == 0)
		{
			fprintf(stderr, "DEBUG: Command is executable, returning\n");
			return (ft_strdup(cmd));
		}
		fprintf(stderr, "DEBUG: Command not executable or not found\n");
		return (NULL);
	}
	
	// Buscar a variável PATH no environment
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		fprintf(stderr, "DEBUG: PATH not found in environment\n");
		return (NULL);
	}
	
	path = envp[i] + 5;
	paths = ft_split(path, ':');
	if (!paths)
	{
		fprintf(stderr, "DEBUG: ft_split failed\n");
		return (NULL);
	}
	
	// Tentar cada diretório no PATH
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		temp = ft_strjoin(full_path, cmd);
		free(full_path);
		
		if (temp && access(temp, X_OK) == 0)
		{
			fprintf(stderr, "DEBUG: Found at %s\n", temp);
			ft_free_split(paths);
			return (temp);
		}
		free(temp);
		i++;
	}
	ft_free_split(paths);
	fprintf(stderr, "DEBUG: Command not found in PATH\n");
	return (NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	fprintf(stderr, "DEBUG: execute_command called with cmd='%s'\n", cmd);
	
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		fprintf(stderr, "ERROR: empty command\n");
		exit(127);
	}
	
	fprintf(stderr, "DEBUG: args[0]='%s'\n", args[0]);
	
	path = find_path(args[0], envp);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		ft_free_split(args);
		exit(127);
	}
	
	fprintf(stderr, "DEBUG: About to execve with path='%s'\n", path);
	execve(path, args, envp);
	
	// Se chegou aqui, execve falhou
	perror("execve failed");
	free(path);
	ft_free_split(args);
	exit(126);
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