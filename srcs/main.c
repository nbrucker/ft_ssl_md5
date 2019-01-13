#include "ft_ssl.h"
#include "libft.h"

void	ft_handle_error(int ac, char **av)
{
	if (ac < 2 || ac > 4)
		ft_error("usage: ft_ssl command [command opts] [command args]");
	else if (ft_strcmp(av[1], "md5") != 0 && ft_strcmp(av[1], "sha256") != 0)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[1]);
		ft_putendl("' is an invalid command.");
		ft_putendl("\nStandart commands:");
		ft_putendl("\nMessage Digest commands:");
		ft_putendl("md5");
		ft_putendl("sha256");
		ft_error("\nCipher commands:");
	}
}

char	*ft_get_text(void)
{
	char    buf[4096 + 1];
	char	*str;
	char	*tmp;
	int		ret;

	if (!(str = ft_strnew(1)))
		ft_error("Malloc error");
	while ((ret = read(0, buf, 4096)) > 0)
	{
		buf[ret] = 0;
		tmp = str;
		if (!(str = ft_strjoin(str, buf)))
			ft_error("Malloc error");
		ft_strdel(&tmp);
	}
	if (ret == -1)
		ft_error("Error reading input");
	return (str);
}

int		main(int ac, char **av)
{
	char	*str;
	char	*hash;

	ft_handle_error(ac, av);
	str = ft_get_text();
	if (ft_strcmp(av[1], "md5") == 0)
		hash = ft_md5(str);
	return (0);
	(void)hash;
}
