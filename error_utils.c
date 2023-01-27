/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:23:23 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 15:52:40 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	free_double_arr(char **arr)
{
	char	**arr_tmp;

	arr_tmp = arr;
	if (arr == NULL)
		return ;
	while (*arr_tmp != NULL)
	{
		free(*arr_tmp);
		arr_tmp++;
	}
	free(arr);
}

void	free_pipex(t_pipe *pipex)
{
	free_double_arr(pipex->path);
	free_double_arr(pipex->cmd_argv);
	free(pipex->cmd_with_path);
}

void	error_and_exit(const char *error_msg)
{
	perror(error_msg);
	exit(0);
}

void	error_free_exit(const char *error_msg, t_pipe *pipex)
{
	perror(error_msg);
	free_pipex(pipex);
	if (pipex->is_heredoc && !access(pipex->infile, F_OK))
		unlink(pipex->infile);
	exit(0);
}
