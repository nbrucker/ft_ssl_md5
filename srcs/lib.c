#include "ft_ssl.h"
#include "libft.h"

char	*ft_copy_len(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (j > i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itao_base(int value, int size)
{
	unsigned long long	nbr;
	int					i;
	char				*str;
	char				*hex;

	if ((hex = ft_strdup("0123456789abcdef")) == NULL)
		ft_error("Malloc error");
	if ((str = ft_strnew((size * 2) + 1)) == NULL)
		ft_error("Malloc error");
	nbr = value;
	i = 0;
	while (nbr != 0 && i < size * 2)
	{
		str[i] = hex[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i < size * 2)
	{
		str[i] = '0';
		i++;
	}
	str[i] = 0;
	free(hex);
	return (ft_strrev(str));
}
