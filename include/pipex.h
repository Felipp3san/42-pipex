/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:58:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/06/08 23:59:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

int		open_file(char *filename, int filetype);
char	**extract_paths_envp(char *envp[]);
char	*build_cmd_path(char *path, char *cmd);
void	free_split(char **arr);
void	error();

#endif
