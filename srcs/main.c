/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:19:10 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:19:10 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	ft_handle_error(int ac, char **av)
{
	if (ac < 2)
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

char	*ft_read(int fd)
{
	char	buf[4096 + 1];
	char	*str;
	char	*tmp;
	int		ret;

	if (!(str = ft_strnew(1)))
		ft_error("Malloc error");
	while ((ret = read(fd, buf, 4096)) > 0)
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

char	*ft_call_hash(t_env *env, char *str)
{
	if (ft_strcmp(env->algo, "md5") == 0)
		return (ft_md5(str));
	else if (ft_strcmp(env->algo, "sha256") == 0)
		return (ft_sha256(str));
	ft_error("Unexpected error");
	return (NULL);
}

char	*ft_str_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

void	ft_print_str(char *hash, char *str, t_env *env)
{
	if (env->q == 1)
		ft_putendl(hash);
	else if (env->r == 1)
	{
		ft_putstr(hash);
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putendl("\"");
	}
	else 
	{
		ft_putstr(ft_str_upper(env->algo));
		ft_putstr(" (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
		ft_putendl(hash);
	}
}

void	ft_handle_s(int ac, char **av, t_env *env, int *i)
{
	char	*hash;

	if (*i + 1 >= ac)
		ft_error("ft_ssl: Error: option requires an argument -- s");
	hash = ft_call_hash(env, av[*i + 1]);
	ft_print_str(hash, av[*i + 1], env);
	ft_strdel(&hash);
	*i += 1;
	env->got = 1;
	env->option = 0;
}

void	ft_handle_p(t_env *env)
{
	char	*str;
	char	*hash;

	str = ft_read(0);
	hash = ft_call_hash(env, str);
	ft_putstr(str);
	ft_putendl(hash);
	ft_strdel(&hash);
	ft_strdel(&str);
	env->got = 1;
}

void	ft_print_file(char *hash, char *name, t_env *env)
{
	if (env->q == 1)
		ft_putendl(hash);
	else if (env->r == 1)
	{
		ft_putstr(hash);
		ft_putchar(' ');
		ft_putendl(name);
	}
	else 
	{
		ft_putstr(ft_str_upper(env->algo));
		ft_putstr(" (");
		ft_putstr(name);
		ft_putstr(") = ");
		ft_putendl(hash);
	}
}

void	ft_handle_file(char **av, t_env *env, int i)
{
	char	*str;
	char	*hash;
	int		fd;

	env->file = 1;
	if ((fd = open(av[i], O_RDONLY)) == -1)
		ft_error("Error opening file");
	str = ft_read(fd);
	if (close(fd) == -1)
		ft_error("Error closing file");
	hash = ft_call_hash(env, str);
	ft_print_file(hash, av[i], env);
	ft_strdel(&hash);
	ft_strdel(&str);
	env->got = 1;
	env->option = 0;
}

void	ft_handle_no_arg(t_env *env)
{
	char	*str;
	char	*hash;

	str = ft_read(0);
	hash = ft_call_hash(env, str);
	ft_putendl(hash);
	ft_strdel(&hash);
	ft_strdel(&str);
}

void	ft_handle_arguments(int ac, char **av, t_env *env)
{
	int		i;

	i = 2;
	env->algo = av[1];
	while (i < ac)
	{
		if ((ft_strcmp(av[i], "-q") == 0 ||
			ft_strcmp(av[i], "-r")) && env->file == 0)
			env->option = 1;
		if (ft_strcmp(av[i], "-q") == 0 && env->file == 0)
			env->q = 1;
		else if (ft_strcmp(av[i], "-r") == 0 && env->file == 0)
			env->r = 1;
		else if (ft_strcmp(av[i], "-s") == 0 && env->file == 0)
			ft_handle_s(ac, av, env, &i);
		else if (ft_strcmp(av[i], "-p") == 0 && env->file == 0)
			ft_handle_p(env);
		else
			ft_handle_file(av, env, i);
		i++;
	}
	if (env->got == 0 || env->option == 1)
		ft_handle_no_arg(env);
}

t_env	*ft_get_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_error("Malloc error");
	env->q = 0;
	env->r = 0;
	env->file = 0;
	env->got = 0;
	env->option = 0;
	return (env);
}

int		main(int ac, char **av)
{
	t_env	*env;

	ft_handle_error(ac, av);
	env = ft_get_env();
	ft_handle_arguments(ac, av, env);
	return (0);
}
