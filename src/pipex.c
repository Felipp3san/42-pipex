/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:53:49 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/09 01:28:41 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *paths[])
{
	char	*full_path;
	char	*path_slash;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		if (cmd)
			full_path = ft_strjoin(path_slash, cmd);
		else
			full_path = ft_strjoin(path_slash, " ");
		free(path_slash);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute(char *cmd, char *envp[])
{
	char	**paths;
	char	**cmd_split;
	char	*path;

	paths = extract_paths_envp(envp);
	if (!paths)
		return ;
	cmd_split = ft_split_quotes(cmd, ' ');
	if (strchr(cmd_split[0], '/'))
		path = cmd_split[0];
	else
		path = find_path(cmd_split[0], paths);
	if (!path)
	{
		free_split(cmd_split);
		cmd_split = NULL;
		error("command not found", cmd);
	}
	if (execv(path, cmd_split) == -1)
	{
		free_split(cmd_split);
		cmd_split = NULL;
		error(NULL, cmd);
	}
}

void	children_process(char *cmd, char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error(NULL, NULL);
	pid = fork();
	if (pid == -1)
		error(NULL, NULL);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute(cmd, envp);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	input_fd;
	int	output_fd;

	if (argc == 5)
	{
		input_fd = open_file(argv[1], 0);
		output_fd = open_file(argv[argc - 1], 1);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		children_process(argv[2], envp);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		execute(argv[argc - 2], envp);
	}
	else
		ft_printf("Usage: ./pipex infile \"cmd1\" [\"cmd2\" ...] outfile\n");
	return (EXIT_SUCCESS);
}
