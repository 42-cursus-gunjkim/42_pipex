/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:10:45 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/25 15:49:21 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

void	pipex_init(t_pipe *pipex, int argc, char *argv[], char *envp[])
{
	pipex->envp = envp;
	pipex->max_i = argc;
	pipex->path = get_path(envp);
	pipex->cmd_with_path = NULL;
	pipex->cmd_argv = NULL;
	pipex->index = 2;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->outfile_flag = O_CREAT | O_WRONLY | O_TRUNC;
	pipex->is_heredoc = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;

	if (argc <= 4)
		error_and_exit("Too few arguments");
	pipex_init(&pipex, argc, argv, envp);
	if (ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])) == 0)
		here_doc(argv, &pipex);
	while (pipex.index + 1 != argc)
	{
		free_double_arr(pipex.cmd_argv);
		pipex.cmd_argv = pipex_split(argv[pipex.index], ' ');
		free(pipex.cmd_with_path);
		pipex.cmd_with_path = cmd_with_path(&pipex);
		make_child(&pipex);
		pipex.index++;
	}
	free_pipex(&pipex);
	if (pipex.is_heredoc && !access(pipex.infile, F_OK))
		unlink(pipex.infile);
	return (0);
}
