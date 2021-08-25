#include "minishell.h"

t_list	*get_redirections_list(t_tokens *tokens, t_list **parse, t_list *words)
{
	t_list	*new;
	int		i;

	i = 1;
	new = NULL;
	while (words && words->flag == SPECIAL
		&& words->content.word[0] != '|')
	{
		i = 1;
		while (words && i > 0 && words->content.word[0] != '|')
		{
			if (words->flag != SPACEE)
			{
				new = ft_lstnew(words->content.word, '0');
				if (!new)
				{
					free_parse_things(*parse);
					free_tokens_things(tokens, 1);
				}
				ft_lstadd_back(&(*parse)->lst_struct->redir, new);
			}
			if (words->flag != SPECIAL && words->flag != SPACEE)
				i--;
			words = words->next;
		}
	}
	return (words);
}

t_list	*from_token_to_parse(t_tokens *tokens, t_list *parse, t_list *new, t_list *words)
{
	while (words && words->content.word[0] != '|')
	{
		if (words->flag == NONE || words->flag == DOLLAR)
		{
			if (words->next && words->next->flag == SPECIAL
				&& check_fd_redir(words->content.word))
				words = get_redirections_list(tokens, &parse, words);
			else
			{
				new = ft_lstnew(words->content.word, '0');
				if (!new)
				{
					free_parse_things(parse);
					free_tokens_things(tokens, 1);
				}
				ft_lstadd_back(&parse->lst_struct->exec, new);
			}
		}
		else if (words->flag == SPECIAL)
		{
			if (words->content.word[0] == '>'
				|| words->content.word[0] == '<')
				words = get_redirections_list(tokens, &parse, words);
		}
		if (words && words->content.word[0] != '|')
			words = words->next;
	}
	return (words);
}

void	get_exec_list(t_tokens *tokens, t_list **parse)
{
	t_list		*new;
	t_list		*tmp;
	t_list		*parse_2;

	parse_2 = *parse;
	tmp = tokens->words;
	while (tmp)
	{
		new = ft_lst_struct_new();
		if (!new)
		{
			free_parse_things(*parse);
			free_tokens_things(tokens, 1);
		}
		ft_lstadd_back(parse, new);
		parse_2 = ft_lstlast(*parse);
		parse_2->lst_struct = malloc(sizeof(t_parse));
		parse_2->lst_struct->exec = NULL;
		parse_2->lst_struct->redir = NULL;
		if (!parse_2->lst_struct)
			return ;
		tmp = from_token_to_parse(tokens, parse_2, new, tmp);
		if (tmp)
			tmp = tmp->next;
	}
	free_tokens_things(tokens, 0);
	// if (*parse)
	// 	print_lst_after_parse(*parse);
}
