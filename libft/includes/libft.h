/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
void	ft_error(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_memdel(void **ap);
char	*ft_strnjoin(char const *s1, char const *s2, size_t len1, size_t len2);
char	*ft_strnew(size_t size);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
int		ft_toupper(int c);

#endif
