/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:52:38 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/07 14:39:32 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"
#include <stdio.h>

// void	child_process_middle(int *prev_pipe, int *next_pipe, char *cmd, char **envp)
// {
// 	printf("DEBUG Child middle: Starting - cmd: %s\n", cmd);
// 	// Fechar extremidades não utilizadas
// 	close(prev_pipe[1]);
// 	close(next_pipe[0]);


// 	// Redireciona stdin do pipe anterior
// 	dup2(prev_pipe[0], STDIN_FILENO); // Não precisa escrever no pipe anterior
// 	close(prev_pipe[0]);

// 	// Redireciona stdout para o próximo pipe
// 	dup2(next_pipe[1], STDOUT_FILENO);
// 	close(next_pipe[1]);

// 	printf("DEBUG Child middle: Calling execute_command\n");
// 	execute_command(cmd, envp);
// 	printf("DEBUG Child middle: execute_command FAILED\n");
// 	exit(1);
// }

void debug_pipes(int (*pipes)[2], int num_pipes, const char *label)
{
	printf("🔍 %s - Pipes state:\n", label);
	for (int i = 0; i < num_pipes; i++)
	{
		printf("  Pipe %d: [%d, %d]\n", i, pipes[i][0], pipes[i][1]);
	}
}

// void	child_process_first(int *pipe_fd, int infile, char *cmd, char **envp)
// {
// 	printf("DEBUG Child 1: Starting - cmd: %s\n", cmd);
// 	sleep(1);
// 	printf("DEBUG Child 1: Closing pipe[0]\n");
// 	close(pipe_fd[0]);
	
// 	printf("DEBUG Child 1: dup2 infile to STDIN\n");
// 	dup2(infile, STDIN_FILENO);
// 	printf("DEBUG Child 1: Closing infile\n");
// 	close(infile);
	
// 	printf("DEBUG Child 1: dup2 pipe[1] to STDOUT\n");
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	printf("DEBUG Child 1: Closing pipe[1]\n");
// 	close(pipe_fd[1]);
	
// 	printf("DEBUG Child 1: Calling execute_command\n");
// 	execute_command(cmd, envp);
	
// 	printf("DEBUG Child 1: execute_command FAILED\n");
// 	exit(1);
// }

void	child_process_first(int *pipe_fd, int infile, char *cmd, char **envp)
{
	printf("DEBUG Child 1: Starting - cmd: %s\n", cmd);
	
	// PRIMEIRO: Fechar o que não vamos usar
	close(pipe_fd[0]);  // Não vamos ler deste pipe
	
	// SEGUNDO: Redirecionar
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	
	// TERCEIRO: Fechar os originais (AGORA pode travar se necessário)
	close(infile);
	close(pipe_fd[1]);
	
	printf("DEBUG Child 1: Calling execute_command\n");
	execute_command(cmd, envp);
	exit(1);
}

void	child_process_middle(int *prev_pipe, int *next_pipe, char *cmd, char **envp)
{
	printf("DEBUG Child middle: Starting - cmd: %s\n", cmd);
	
	// PRIMEIRO: Fechar extremidades não usadas
	close(prev_pipe[1]);  // Não vamos escrever no pipe anterior
	close(next_pipe[0]);  // Não vamos ler do próximo pipe
	
	// SEGUNDO: Redirecionar
	dup2(prev_pipe[0], STDIN_FILENO);
	dup2(next_pipe[1], STDOUT_FILENO);
	
	// TERCEIRO: Fechar os originais
	close(prev_pipe[0]);
	close(next_pipe[1]);
	
	printf("DEBUG Child middle: Calling execute_command\n");
	execute_command(cmd, envp);
	exit(1);
}

// void	child_process_middle(int *prev_pipe, int *next_pipe, char *cmd, char **envp)
// {
// 	printf("DEBUG Child middle: Starting - cmd: %s\n", cmd);
// 	sleep(1);
// 	printf("DEBUG Child middle: Closing prev_pipe[1] and next_pipe[0]\n");
// 	close(prev_pipe[1]);
// 	close(next_pipe[0]);

// 	printf("DEBUG Child middle: dup2 prev_pipe[0] to STDIN\n");
// 	dup2(prev_pipe[0], STDIN_FILENO);
// 	printf("DEBUG Child middle: Closing prev_pipe[0]\n");
// 	close(prev_pipe[0]);

// 	printf("DEBUG Child middle: dup2 next_pipe[1] to STDOUT\n");
// 	dup2(next_pipe[1], STDOUT_FILENO);
// 	printf("DEBUG Child middle: Closing next_pipe[1]\n");
// 	close(next_pipe[1]);

// 	printf("DEBUG Child middle: Calling execute_command\n");
// 	execute_command(cmd, envp);
	
// 	printf("DEBUG Child middle: execute_command FAILED\n");
// 	exit(1);
// }

void	child_process_last(int *pipe_fd, int outfile, char *cmd, char **envp)
{
	printf("DEBUG Child last: Starting - cmd: %s\n", cmd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	printf("DEBUG Child last: Calling execute_command\n");
	execute_command(cmd, envp);
	printf("DEBUG Child last: execute_command FAILED\n");
	exit(1);
}

void	handle_multiple_pipes(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;
	int		num_cmds;
	int		**pipes;  // ← MUDE para int**
	pid_t	pid;

	num_cmds = argc - 3;
	printf("Multiple pipes mode - %d commands\n", argc - 3);

	infile = open_file(argv[1], 0);
	outfile = open_file(argv[argc - 1], 1);

	// ALOCAR PIPES DINAMICAMENTE
	pipes = malloc((num_cmds - 1) * sizeof(int *));
	if (!pipes)
	{
		perror("malloc");
		exit(1);
	}
	
	i = 0;
	while (i < num_cmds - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		printf("✅ Created pipe %d: [%d, %d]\n", i, pipes[i][0], pipes[i][1]);
		i++;
	}

	// Processo 1 (primeiro)
	pid = fork();
	if (pid == 0)
	{
		printf("👶 Child 1: %s\n", argv[2]);
		child_process_first(pipes[0], infile, argv[2], envp);
	}
	// Processos do meio (cmd2, cmd3, ..., cmdn-1)
	i = 1;
	while (i < num_cmds - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("👶 Child %d: %s\n", i + 1, argv[i + 2]);
			child_process_middle(pipes[i - 1], pipes[i], argv[i + 2], envp);
		}
		i++;
	}
	// last process
	pid = fork();
	if (pid == 0)
	{
		printf(" Child %d: %s \n", num_cmds, argv[argc - 2]);
		child_process_last(pipes[num_cmds - 2], outfile, argv[argc - 2], envp);
	}
	printf("👨 Parent: Closing all pipes and waiting...\n");
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	close(infile);
	close(outfile);

	// Esperar todos os processos filhos
	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
	
	free(pipes);
}


int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, BONUS_ARG_ERROR, ft_strlen(BONUS_ARG_ERROR));
		return (1);
	}
	
	printf("=========================================\n");
	handle_multiple_pipes(argc, argv, envp);
	printf("=========================================\n");
	return (0);
}