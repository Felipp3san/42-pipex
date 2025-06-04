/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:41:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/03 20:33:40 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft.h"

typedef struct s_pipex
{
	char	***cmds;
	char	**paths;
	int		pipe_fd[2];
}	t_pipex;

char	*build_cmd_path(char *path, char *command);
int		open_file(char *filename, int file_type);
void	free_split(char **arr);
void	cleanup_pipex(t_pipex *pipex);

#endif
