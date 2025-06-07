/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:41:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/07 12:08:16 by fde-alme         ###   ########.fr       */
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
	char	*cmd_path;
	char	***cmds;
	char	**paths;
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		cmd_count;
}	t_pipex;

int		open_file(char *filename, int file_type);
void	free_split(char **arr);
void	free_pipex(t_pipex *pipex);
char	***parse_commands(char **argv, int cmd_count);
char	*build_cmd_path(char *path, char *command);
char	*bin_lookup(char *command, char **paths);
char	**extract_paths_envp(char *envp[]);

#endif
