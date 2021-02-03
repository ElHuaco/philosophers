/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:27:44 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/02/03 19:38:55 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}

t_list		*ft_lstlast(t_list *lst)
{
	t_list *last;

	last = lst;
	if (lst == 0)
		return (last);
	while (last->next)
		last = last->next;
	return (last);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *temp;

	if (alst != 0 && new != 0 && *alst != 0)
	{
		temp = *alst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*alst = new;
}

void		ft_lstdel_back(t_list *alst)
{
	t_list *temp;
	if (alst != 0)
	{
		temp = alst->next;
		while (temp->next != NULL)
		{
			alst = temp;
			temp = temp->next;
		}
		free(alst->next);
		alst->next = 0;
	}
}

void		ft_lstclear(t_list **lst)
{
	t_list *temp;

	temp = *lst;
	while ((*lst)->next)
	{
		temp = temp->next;
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = 0;
}
