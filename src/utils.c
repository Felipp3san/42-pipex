/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:27:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/09 01:28:39 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	open_file(char *filename, int filetype)
{
	int	fd;

	if (filetype == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), filename);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
				error();
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1)
		{
			ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), filename);
			error();
		}
	}
	return (fd);
}

void	error()
{
	if (errno == ENOENT)
		exit(127);
	else
		exit(EXIT_FAILURE);
}

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

char	*build_cmd_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*full_path;

	if (!path || !cmd)
		return (NULL);
	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (full_path);
}
