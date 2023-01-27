/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:45:07 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/27 17:59:22 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

int	getline_and_isequal(char **line, char *limiter, t_pipe *pipex)
{
	int	line_len;
	int	lim_len;

	write(1, "here_doc > ", 10);
	*line = get_next_line(0);
	if (*line == NULL)
		error_free_exit(NULL, pipex);
	line_len = ft_strlen(*line) - 1;
	lim_len = ft_strlen(limiter);
	if (!ft_strncmp(*line, limiter, line_len) && line_len == lim_len)
		return (1);
	else
		return (0);
}

void	here_doc(char *argv[], t_pipe *pipex)
{
	char	*line;
	int		tmp_fd;
	int		is_equal;

	line = NULL;
	pipex->index = 3;
	pipex->infile = "here_tmp";
	pipex->outfile_flag = O_CREAT | O_WRONLY | O_APPEND;
	pipex->is_heredoc = 1;
	tmp_fd = open(pipex->infile, O_CREAT | O_EXCL | O_WRONLY, 0664);
	if (tmp_fd < 0)
	{
		free_pipex(pipex);
		error_and_exit(NULL);
	}
	while (1)
	{
		is_equal = getline_and_isequal(&line, argv[2], pipex);
		if (is_equal)
			break ;
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	free(line);
	close(tmp_fd);
}
