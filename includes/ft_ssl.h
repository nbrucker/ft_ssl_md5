#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdio.h>
# include <stdlib.h>

char		*ft_md5(char *str);
char		*ft_sha256(char *str);
uint32_t	ft_right_rotate(uint32_t x, uint32_t c);
uint32_t	ft_left_rotate(uint32_t x, uint32_t c);
char		*ft_copy_len(char *dst, const char *src, size_t len);
char		*ft_itao_base(int value, int size);
char		*ft_copy_len(char *dst, const char *src, size_t len);
char		*ft_strrev(char *str);

#endif
