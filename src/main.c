/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:50:51 by jgiancol          #+#    #+#             */
/*   Updated: 2025/10/06 21:59:01 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	main(int argc, char **argv, char **envp)
// {
// 	validate_args(argc);
// 	pipes_maker();
// 	child();
// 	standby_process();
// 	resources_cleaner();
// }

#include "../inc/pipex.h"
#include <stdio.h>

int	main(int argc, char**argv, char **envp)
{
	int		fd[2];
	__pid_t	pid1;
	__pid_t	pid2;
	int		infile;
	int		outfile;
	(void)envp;

	if (argc != 5)
	{
		write(2, ARG_ERROR, sizeof(ARG_ERROR));
		return (1);
	}
	// Passo 1: Criar pipe
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	// Passo 2: Abrir arquivos (ANTES dos forks para dectatar os erros!)
	infile = open_file(argv[1], 0); // input.text - modo leitura.
	outfile = open_file(argv[4], 1); // output.txt - modo escrita.
	printf("Pipe created sucessfully\n");

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (1);
	}

if (pid1 == 0)
{
    printf("Child 1 - I will handle '%s' and command '%s'\n", argv[1], argv[2]);
    
    // FECHA o que não vamos usar
    close(fd[0]);   // Não precisa ler do pipe
    close(outfile); // Só o filho 2 usa output
    
    // PASSO 1: Redirecionar stdin para o arquivo de entrada
    printf("DEBUG: Redirecting stdin to input file...\n");
    dup2(infile, STDIN_FILENO);  // stdin ← input.txt
    close(infile);
    
    // PASSO 2: Redirecionar stdout para o pipe (escrita)
    printf("DEBUG: Redirecting stdout to pipe...\n");
    dup2(fd[1], STDOUT_FILENO);  // stdout → pipe[1]
    close(fd[1]);
    
    printf("DEBUG: Starting command execution...\n");
    execute_command(argv[2], envp);
    
    // Se chegou aqui, deu erro
    write(2, "Fatal: execute_command failed\n", 30);
    exit(1);
}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (1);
	}
if (pid2 == 0)
{
    printf("Will handle command '%s' and file '%s'\n", argv[3], argv[4]);
    
    // FECHA o que não vamos usar
    close(fd[1]);   // Não precisa escrever no pipe
    close(infile);  // Só o filho 1 usa input
    
    // PASSO 2: Redirecionar stdin para o pipe (leitura)
    printf("DEBUG Child 2: Redirecting stdin to pipe...\n");
    dup2(fd[0], STDIN_FILENO);  // stdin ← pipe[0]
    close(fd[0]);
    
    // PASSO 2: Redirecionar stdout para o arquivo de saída
    printf("DEBUG Child 2: Redirecting stdout to output file...\n");
    dup2(outfile, STDOUT_FILENO);  // stdout → output.txt
    close(outfile);
    
    printf("DEBUG Child 2: Starting command execution...\n");
    execute_command(argv[3], envp);
    
    // Se chegou aqui, deu erro
    write(2, "Fatal: execute_command failed\n", 30);
    exit(1);
}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	printf("Pipex completed sucessfully!\n");
	return (0);
}


// sugestoes posteriores:
// Criar um checkup para argumentos
// melhorar error handler
// colocar automatico para pid -1 tambem no return