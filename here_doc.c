/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:45:07 by gunjkim           #+#    #+#             */
/*   Updated: 2023/02/20 21:27:34 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	here_doc_init(t_pipe *pipex)
{
	pipex->index = 3;
	pipex->infile = "here_tmp";
	pipex->outfile_flag = O_CREAT | O_WRONLY | O_APPEND;
	pipex->is_heredoc = 1;
}

int	strequal(char *str1, char *str2, int flag)
{
	size_t	str1_len;
	size_t	str2_len;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (flag == 1)
		str2_len = str2_len - 1;
	if (!ft_strncmp(str1, str2, str1_len) && (str1_len == str2_len))
		return (1);
	else
		return (0);
}

char	*getline_stdin(t_pipe *pipex)
{
	char	*line;

	write(1, "here_doc > ", 10);
	line = get_next_line(0);
	if (line == NULL)
		error_free_exit(NULL, pipex, 0);
	return (line);
}

void	here_doc(char *argv[], t_pipe *pipex)
{
	char	*line;
	int		tmp_fd;

	line = NULL;
	here_doc_init(pipex);
	tmp_fd = open(pipex->infile, O_CREAT | O_EXCL | O_WRONLY, 0664);
	if (tmp_fd < 0)
	{
		free_pipex(pipex);
		error_and_exit(NULL, 0);
	}
	while (1)
	{
		line = getline_stdin(pipex);
		if (strequal(argv[2], line, 1))
			break ;
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	free(line);
	close(tmp_fd);
}
