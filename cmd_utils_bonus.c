/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:12:00 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 15:49:11 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

char	**get_path(char *envp[])
{
	char	**path;

	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	if (envp == NULL)
		return (NULL);
	path = ft_split(*envp + 5, ':');
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*cmd_with_path(t_pipe *pipex)
{
	char	*path_with_slash;
	char	*path_with_cmd;
	char	**path;

	path = pipex->path;
	while (*path != NULL)
	{
		path_with_slash = ft_strjoin(*path, "/");
		path_with_cmd = ft_strjoin(path_with_slash, pipex->cmd_argv[0]);
		free(path_with_slash);
		if (access(path_with_cmd, X_OK) == 0)
			return (path_with_cmd);
		free(path_with_cmd);
		path++;
	}
	return (NULL);
}
