/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:15:34 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:15:37 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_hash
{
	char		*str;
	char		*hash;
	uint32_t	len;
	uint32_t	hash_len;
}				t_hash;

typedef struct	s_read
{
	char		*str;
	int			len;
}				t_read;

typedef struct	s_env
{
	int			q;
	int			r;
	int			file;
	int			got;
	char		*algo;
}				t_env;

void			ft_md5(t_hash* hash);
void			ft_sha256(t_hash *hash);
uint32_t		ft_right_rotate(uint32_t x, uint32_t c);
uint32_t		ft_left_rotate(uint32_t x, uint32_t c);
void			ft_copy_len(void *dst, void *src, size_t len);
char			*ft_itao_base(int value, int size);
char			*ft_strrev(char *str);
void			ft_handle_arguments_md5(int ac, char **av, t_env *env);
void			ft_print_upper(char *str);
t_read			*ft_read(int fd);
void			ft_print_file_md5(char *hash, char *name, t_env *env);
void			ft_print_str_md5(char *hash, char *str, t_env *env);
void			ft_call_hash(t_env *env, t_hash *hash);
t_hash			*ft_get_hash_env(char *str);

#endif
