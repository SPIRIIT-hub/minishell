#include "minishell.h"

int	there_is_redir(char *line, int i, t_tokens *tokens)
{
	t_list	*new;
	int		k;

	k = 0;
	if (line[i + 1] == '>' || line[i + 1] == '<')
	{
		new = ft_lstnew(NULL, line[i + 1]);
		if (!new)
			free_tokens_things(tokens, 1);
		ft_lstadd_back(&tokens->temp, new);
		k = 1;
	}
	if (tokens->temp)
		from_lst_a_to_lst_b(&tokens->temp, &tokens->words);
	return (i + k);
}

int	check_fd_redir(char *word)
{
	int		i;

	i = 0;
	if (!word)
		return (0);
	while (word[i] && word[i] >= 48 && word[i] <= 57)
		i++;
	if (!word[i])
		return (1);
	return (0);
}
