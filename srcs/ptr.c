/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:11:12 by nbrucker          #+#    #+#             */
/*   Updated: 2019/03/04 12:11:12 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

t_f		*add_ptr(t_f *ptr, char *str, void (*f)())
{
	t_f	*new;
	t_f *move;

	if (!(new = (t_f*)malloc(sizeof(t_f))))
		ft_error("Malloc error");
	new->str = str;
	new->f = f;
	new->next = NULL;
	move = ptr;
	if (!move)
		ptr = new;
	else
	{
		while (move && move->next)
			move = move->next;
		move->next = new;
	}
	return (ptr);
}

t_f		*get_ptr(void)
{
	t_f	*new;

	new = NULL;
	new = add_ptr(new, "md5", &ft_md5);
	new = add_ptr(new, "sha256", &ft_sha256);
	return (new);
}

void	free_ptr(t_f *ptr)
{
	t_f	*next;

	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}
