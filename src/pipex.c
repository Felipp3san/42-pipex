/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:26:02 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/07 13:48:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *pipex, int cmd_idx, int end)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipex->pipe_fd[0]);
		if (end)
			dup2(pipex->outfile_fd, STDOUT_FILENO);
		else
			dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
		if (execv(pipex->cmd_path, pipex->cmds[cmd_idx]) == -1)
		{
			free_pipex(pipex);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	execute_pipeline(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_path = bin_lookup(*(pipex->cmds[i]), pipex->paths);
		if (!pipex->cmd_path)
			ft_dprintf(2, "pipex: command not found: %s\n", *(pipex->cmds[i]));
		else
		{
			if (pipe(pipex->pipe_fd) == -1)
			{
				ft_dprintf(2, "pipex: pipe: %s\n", strerror(errno));
				free_pipex(pipex);
				exit(EXIT_FAILURE);
			}
			if (i == pipex->cmd_count - 1)
				execute_command(pipex, i, 1);
			else
				execute_command(pipex, i, 0);
			free(pipex->cmd_path);
			pipex->cmd_path = NULL;
		}
		i++;
	}
}

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		cmd_count;

	cmd_count = argc - 3;
	pipex = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->cmd_path = NULL;
	pipex->cmds = parse_commands(argv, cmd_count);
	pipex->cmd_count = cmd_count;
	pipex->paths = extract_paths_envp(envp);
	pipex->infile_fd = open_file(argv[1], 0);
	pipex->outfile_fd = open_file(argv[argc - 1], 1);
	if (!pipex->cmds || !pipex->paths || pipex->outfile_fd == -1)
		return (free_pipex(pipex), NULL);
	else
		return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
	{
		ft_dprintf(2,
			"Usage: %s infile \"cmd1\" [\"cmd2\" ...] outfile\n",
			argv[0]);
		return (EXIT_FAILURE);
	}
	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
		return (EXIT_FAILURE);
	execute_pipeline(pipex);
	free_pipex(pipex);
	return (EXIT_SUCCESS);
}
