/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:46:21 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/07 13:34:02 by jgiancol         ###   ########.fr       */
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
	printf("DEBUG find_path: Looking for '%s'\n", cmd); // ← ADICIONE
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
	printf("DEBUG find_path: PATH found, splitting...\n"); // ← ADICIONE
	
	// Dividir PATH por :
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	
	// Tentar cada diretório no PATH
	i = 0;
	while (paths[i])
	{
		// CORREÇÃO: Use ft_strjoin corretamente
		printf("DEBUG find_path: Trying directory %s\n", paths[i]); // ← ADICIONE
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		char *temp = ft_strjoin(full_path, cmd);
		free(full_path);
		full_path = temp;
		
		if (full_path && access(full_path, X_OK) == 0)
		{
			printf("DEBUG find_path: FOUND at %s\n", full_path); // ← ADICIONE
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
		printf("DEBUG find_path: Command not found\n"); // ← ADICIONE
	return (NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd,' ');
	if (!args)
	{
		write(2, "Error splitting command\n", 24);
		exit(1);
	}
	path = find_path(args[0], envp);
	execve(path, args, envp);
	write(2, "Error executing command: ", 25);
	write(2, cmd , strlen(cmd));
	write(2, "\n", 1);
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