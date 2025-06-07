/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:19:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/07 13:30:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Open the file and returns its FD. file_type: 0 - input | 1 - output */
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
		}
		dup2(fd, STDIN_FILENO);
	}
	if (filetype == 1)
	{
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1)
			ft_dprintf(2, "pipex: %s: %s\n", strerror(errno), filename);
	}
	return (fd);
}

/* Frees the strings and the array allocated by the function ft_split */
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

/* Frees up the pipex struct */
void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->cmds)
	{
		i = 0;
		while (i < pipex->cmd_count)
		{
			free_split(pipex->cmds[i]);
			pipex->cmds[i] = NULL;
			i++;
		}
		free(pipex->cmds);
		pipex->cmds = NULL;
	}
	if (pipex->paths)
		free_split(pipex->paths);
	if (pipex->infile_fd > 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > 0)
		close(pipex->outfile_fd);
	free(pipex);
}
