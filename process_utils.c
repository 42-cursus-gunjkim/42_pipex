/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:11:08 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/20 21:52:01 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	child_pipe_init(t_pipe *p)
{
	p->path = get_path(p->envp);
	if (p->path == NULL)
		error_free_exit("PATH parsing fail", p, 0);
	p->cmd_argv = pipex_split(p->argv[p->index], ' ');
	if (p->cmd_argv == NULL)
		error_free_exit("cmd argument parsing fail", p, 0);
	p->cmd_with_path = cmd_with_path(p);
	if (p->cmd_with_path == NULL)
		error_free_exit("command not found", p, 127);
}

void	child_do(t_pipe *p)
{
	int	file;

	if (p->index + 2 == p->max_i)
	{
		file = open(p->outfile, p->outfile_flag, 0644);
		if (file == -1)
			error_free_exit(NULL, p, 0);
		dup2(file, 1);
	}
	else if (p->index == 2 || (p->index == 3 && p->is_heredoc == 1))
	{
		file = open(p->infile, O_RDONLY);
		if (file == -1)
			error_free_exit(NULL, p, 0);
		dup2(p->fd[1], 1);
		dup2(file, 0);
	}
	else
		dup2(p->fd[1], 1);
	close(p->fd[0]);
	child_pipe_init(p);
	if (execve(p->cmd_with_path, p->cmd_argv, p->envp) == -1)
		error_free_exit(NULL, p, 0);
}

void	wait_all(int number_of_cmd)
{
	int	count;
	int	status;

	count = 0;
	while (count < number_of_cmd)
	{
		wait(&status);
		count++;
	}
}

void	parent_do(t_pipe *p)
{
	dup2(p->fd[0], 0);
	close(p->fd[1]);
}

void	make_child(t_pipe *pipex)
{
	pid_t	child_p;
	int		*fd_tmp;

	fd_tmp = pipex->fd;
	if (pipe(pipex->fd) == -1)
		error_free_exit(NULL, pipex, 0);
	child_p = fork();
	close(fd_tmp[0]);
	if (child_p > 0)
		parent_do(pipex);
	else if (child_p == 0)
		child_do(pipex);
	else if (child_p == -1)
		error_free_exit(NULL, pipex, 0);
}
