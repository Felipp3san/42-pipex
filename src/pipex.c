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
char	***parse_commands(int argc, char **argv)
{
	char	***commands;
	char	**split_args;
	int		i;

	i = 0;
	commands = (char ***) malloc(argc * sizeof(char *));
	if (!commands)
		return (NULL);
	while (i < argc - 2)
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

char	*bin_lookup(char *command, char **paths)
{
	char	*bin_path;
	int		bin_found;

	bin_found = -1;
	while (*paths)
	{
		bin_path = build_cmd_path(*paths, command);
		if (!bin_path)
			return (NULL);
		bin_found = access(bin_path, F_OK);
		if (bin_found == 0)
			return (bin_path);
		free(bin_path);
		paths++;
	}
	return (NULL);
}

int	execute_cmds(t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_args = *(pipex->cmds);
	while (cmd_args)
	{
		cmd_path = bin_lookup(cmd_args[0], pipex->paths);
		if (!cmd_path)
			ft_printf("pipex: command not found: %s\n", *(pipex->cmds[i]));
		else
			execute_command(cmd_path, pipex->cmds[i]);
		cmd_args++;
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
		ft_printf("pipex: %s: %s\n", strerror(errno), filename);
	else {
		new_fd = dup2(input_fd, 0);
		if (new_fd == -1)
		{
			ft_printf("pipex: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
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


/* Initializes pipex struct with data from argv */
t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->cmds = parse_commands(argc, ++argv);
	pipex->paths = extract_paths_envp(envp);
	if (!pipex->cmds || !pipex->paths)
	{
		cleanup_pipex(pipex);
		return (NULL);
	}
	else
		return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc > 1)
	{
		setup_input(*(++argv));
		pipex = init_pipex(argc, argv, envp);
		if (!pipex)
			exit(EXIT_FAILURE);
		execute_cmds(pipex);
	}
	return (0);
}
