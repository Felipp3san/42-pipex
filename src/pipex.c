/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:26:02 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/03 20:33:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_paths_envp(char *envp[])
{
	char	**paths;
	char	*env_path;

	paths = NULL;
	env_path = NULL;
	while (*envp && !env_path)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			env_path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (env_path)
		paths = ft_split(env_path, ':');
	return (paths);
}

/* Create a matrix of commands with its arguments 
	ex: [["ls", "-la"], ["wc", "-l"]] */
char	***parse_commands(int argc, char *argv[])
{
	char	***commands;
	char	**split_args;
	int		i;

	i = 0;
	commands = (char ***) malloc(argc * sizeof(char *));
	if (!commands)
		return (NULL);
	while (i < argc - 1)
	{
		split_args = ft_split(argv[i], ' ');
		if (!split_args)
		{
			i = 0;
			while(i < argc)
				free_split(commands[i++]);
			return (free(commands), NULL);
		}
		commands[i] = split_args;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

void	execute_command(char *fullpath, char **command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execv(fullpath,	command);
	else
		waitpid(pid, NULL, 0);
}

int	execute_pipeline(char ***commands, char **paths)
{
	char	*full_path;
	int		bin_found;
	int		i;

	while (**commands)
	{
		i = 0;
		bin_found = -1;
		while (paths[i])
		{
			full_path = build_cmd_path(paths[i], **commands);
			if (!full_path)
				return (-1);
			bin_found = access(full_path, F_OK);
			if (bin_found == 0)
			{
				execute_command(full_path, *commands);
				break ;
			}
			free(full_path);
			i++;
		}
		if (bin_found == -1)
		{
			ft_printf("pipex: command not found: %s\n", **commands);
			exit(EXIT_FAILURE);
		}
		commands++;
	}
	return (0);
}

/* Opens input file, redirects it to stdin */
int	setup_input(char *filename)
{
	int	input_fd;
	int	new_fd;

	input_fd = open_file(filename, 0);
	if (input_fd == -1)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), filename);
		exit(EXIT_FAILURE);
	}
	new_fd = dup2(input_fd, 0);
	if (new_fd == -1)
	{
		ft_printf("pipex: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(input_fd);
	return (0);
}

int	init_pipe(int pipe_fd[2])
{
	int	status;

	status = pipe(pipe_fd);
	if (status == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	***commands;
	char	**paths;
	int		pipe_fd[2];

	if (argc > 1)
	{
		setup_input(*(++argv));
		init_pipe(pipe_fd);
		commands = parse_commands(argc, ++argv);
		if (!commands)
			exit(EXIT_FAILURE);
		paths = extract_paths_envp(envp);
		if (!paths)
			exit(EXIT_FAILURE);
		execute_pipeline(commands, paths);
	}
	return (0);
}
