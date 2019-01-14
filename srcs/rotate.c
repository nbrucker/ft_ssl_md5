#include "ft_ssl.h"

uint32_t	ft_right_rotate(uint32_t x, uint32_t c)
{
	return (x >> c) | (x << (32 - c));
}

uint32_t	ft_left_rotate(uint32_t x, uint32_t c)
{
	return (x << c) | (x >> (32 - c));
}
