/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:11:08 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 15:55:47 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

void	child_do(t_pipe *p)
{
	int	file;

	if (p->index + 2 == p->max_i)
	{
		file = open(p->outfile, p->outfile_flag, 0644);
		if (file == -1)
			error_free_exit(NULL, p);
		dup2(file, 1);
	}
	else if (p->index == 2 || (p->index == 3 && p->is_heredoc == 1))
	{
		file = open(p->infile, O_RDONLY);
		if (file == -1)
			error_free_exit(NULL, p);
		dup2(p->fd[1], 1);
		dup2(file, 0);
	}
	else
		dup2(p->fd[1], 1);
	close(p->fd[0]);
	if (execve(p->cmd_with_path, p->cmd_argv, p->envp) == -1)
		error_free_exit(NULL, p);
}

void	parent_do(t_pipe *p, pid_t child)
{
	int	state;

	waitpid(child, &state, WNOHANG);
	dup2(p->fd[0], 0);
	close(p->fd[1]);
}

void	make_child(t_pipe *pipex)
{
	pid_t	child_p;

	if (pipe(pipex->fd) == -1)
		error_free_exit(NULL, pipex);
	child_p = fork();
	if (child_p > 0)
		parent_do(pipex, child_p);
	else if (child_p == 0)
		child_do(pipex);
	else if (child_p == -1)
		error_free_exit(NULL, pipex);
}
