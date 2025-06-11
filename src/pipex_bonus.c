/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:15:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/10 19:18:46 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*full_path;
	char	*path_slash;
	int		i;

	paths = extract_paths_envp(envp);
	if (!paths)
		return (NULL);
	if (strchr(cmd, '/'))
		return (cmd);
	i = 0;
	while (paths && paths[i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_slash, cmd);
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
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split_quotes(cmd, ' ');
	if (!cmd_split)
		error();
	if (cmd_split[0])
		path = find_path(cmd_split[0], envp);
	else
		path = find_path(" ", envp); 
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd_split[0], 2);
		ft_putchar_fd('\n', 2);
		free_split(cmd_split);
		exit(127);
	}
	if (execv(path, cmd_split) == -1)
	{
		ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), cmd_split[0]);
		free_split(cmd_split);
		error();
	}
}

pid_t	children_process(char *cmd, char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute(cmd, envp);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (pid);
}

void	here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		error();
	if (!fork())
	{
		close(pipe_fd[0]);
		while (1)
		{
			write(1, "heredoc> ", 9);
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strcmp(line, limiter) - 10 == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		output_fd;

	if (argc > 4)
	{
		i = 2;
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			here_doc(argv[2]);
			i++;
		}
		else
			open_file(argv[1], 0);
		output_fd = open_file(argv[argc - 1], 1);
		while (i < argc - 2)
			children_process(argv[i++], envp);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		execute(argv[argc - 2], envp);
	}
	else
	{
		ft_printf("Usage: ./pipex infile \"cmd1\" [\"cmd2\" ...] outfile\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
