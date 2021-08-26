/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 02:25:21 by bmoulin           #+#    #+#             */
/*   Updated: 2021/08/26 02:25:24 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words_content(t_tokens *tokens)
{
	t_list	*tmp;

	tmp = tokens->words;
	while (tmp)
	{
		free(tmp->content.word);
		tmp = tmp->next;
	}
}

void	free_parse_things(t_list *parse)
{
	t_list	*first;

	first = parse;
	while (parse)
	{
		ft_lstclear(&parse->lst_struct->exec);
		ft_lstclear(&parse->lst_struct->redir);
		if (parse->lst_struct)
		{
			free(parse->lst_struct);
			parse->lst_struct = NULL;
		}
		parse = parse->next;
	}
	parse = first;
	ft_lstclear(&parse);
}

void	free_tokens_things(t_tokens *tokens, int error)
{
	ft_lstclear(&tokens->temp);
	ft_lstclear(&tokens->words);
	if (error)
	{
		printf("Error\n");
		wrdestroy();
		exit(0);
	}
}
