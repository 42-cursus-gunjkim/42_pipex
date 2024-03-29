/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:10:45 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/27 20:04:44 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	pipex_init(t_pipe *pipex, int argc, char *argv[], char *envp[])
{
	pipex->envp = envp;
	pipex->max_i = argc;
	pipex->path = NULL;
	pipex->cmd_with_path = NULL;
	pipex->cmd_argv = NULL;
	pipex->argv = argv;
	pipex->index = 2;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->outfile_flag = O_CREAT | O_WRONLY | O_TRUNC;
	pipex->is_heredoc = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;
	int		number_of_cmd;

	if (argc <= 4)
		error_and_exit("Too few arguments", 0);
	pipex_init(&pipex, argc, argv, envp);
	number_of_cmd = pipex.max_i - pipex.index - 1;
	if (strequal(argv[1], "here_doc", 0))
		here_doc(argv, &pipex);
	while (pipex.index + 1 != argc)
	{
		make_child(&pipex);
		pipex.index++;
	}
	close(pipex.fd[0]);
	if (pipex.is_heredoc && !access(pipex.infile, F_OK))
		unlink(pipex.infile);
	wait_all(number_of_cmd);
	return (0);
}
