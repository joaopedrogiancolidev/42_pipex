/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:46:21 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/06 22:01:26 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

//Precisamos encontrar o caminho do PATH para o execv!

static char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	char	**paths;
	int		i;

	// Se o comando já tem /, verifica se existe
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	
	// Buscar a variável PATH no environment
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	
	path = envp[i] + 5; // Pula "PATH="
	
	// Dividir PATH por :
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	
	// Tentar cada diretório no PATH
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
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


	printf("DEBUG: Starting execute_command for '%s'\n", cmd); // DEBUG 1
	args = ft_split(cmd,' ');
	if (!args)
	{
		printf("DEBUG: ft_split failed\n"); // DEBUG 2
		write(2, "Error splitting command\n", 24);
		exit(1);
	}
	printf("DEBUG: Args[0] = '%s'\n", args[0]); // DEBUG 3
	path = find_path(args[0], envp);
	printf("DEBUG: Path found = '%s'\n", path); // DEBUG 4
	printf("DEBUG: Calling execve...\n"); // DEBUG 5
	execve(path, args, envp);
	printf("DEBUG: execve FAILED - calling perror\n"); // DEBUG 6
	write(2, "Error executing command: ", 25);
	write(2, cmd , strlen(cmd));
	write(2, "\n", 1);
	printf("DEBUG: Exiting with error\n"); // DEBUG 7
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