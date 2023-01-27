/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:40:35 by gunjkim           #+#    #+#             */
/*   Updated: 2023/01/27 17:13:26 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipe
{
	int		fd[2];
	int		index;
	int		max_i;
	int		outfile_flag;
	int		is_heredoc;
	char	**argv;
	char	**path;
	char	**cmd_argv;
	char	**envp;
	char	*cmd_with_path;
	char	*infile;
	char	*outfile;
}	t_pipe;

char	**get_path(char *envp[]);
char	*cmd_with_path(t_pipe *pipex);
void	error_and_exit(const char *error_msg);
void	error_free_exit(const char *error_msg, t_pipe *pipex);
void	make_child(t_pipe *pipex);
void	free_pipex(t_pipe *pipex);
char	**pipex_split(char const *s, char c);
void	free_double_arr(char **arr);
void	here_doc(char *argv[], t_pipe *pipex);

#endif