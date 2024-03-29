/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:23:23 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/27 20:04:41 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

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
	free_double_arr(pipex->cmd_argv);
	free_double_arr(pipex->path);
	free(pipex->cmd_with_path);
}

void	error_and_exit(const char *error_msg, int ecode)
{
	perror(error_msg);
	exit(ecode);
}

void	error_free_exit(const char *error_msg, t_pipe *pipex, int ecode)
{
	perror(error_msg);
	free_pipex(pipex);
	if (pipex->is_heredoc && !access(pipex->infile, F_OK))
		unlink(pipex->infile);
	exit(ecode);
}
