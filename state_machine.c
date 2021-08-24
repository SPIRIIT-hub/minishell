#include "minishell.h"

void	init_states(t_state *state)
{
	state->reading_word = 1;
	state->d_quoted_word = 0;
	state->s_quoted_word = 0;
	state->dollar = 0;
	state->cmd_state = 0;
}

int	s_quoted_word(char *line, t_list **lst, int i)
{
	t_list	*new;
	while (line[i] && line[i] != '\'')
	{
		new = ft_lstnew(NULL, line[i]);
		if (!new)
			return (-1);
		new->flag = NONE;
		ft_lstadd_back(lst, new);
		i++;
	}
	return (i++);
}

int	d_quoted_word(char *line, t_tokens *tokens, int i, t_shell *exec_part)
{
	t_list	*new;

	while (line[i] && line[i] != '\"')
	{
		while (line[i] && line[i] != '$' && line[i] != '\"')
		{
			new = ft_lstnew(NULL, line[i]);
			if (!new)
				free_tokens_things(tokens, 1);
			new->flag = NONE;
			ft_lstadd_back(&tokens->temp, new);
			i++;
		}
		if (line[i] == '$')
		{
			if (tokens->temp)
				if (!from_lst_a_to_lst_b(&tokens->temp, &tokens->words))
					free_tokens_things(tokens, 1);
			i++;
			i = there_is_env_var(line, i, tokens, exec_part);
		}
	}
	return (i++);
}

void	ft_scan_line(char *line, t_tokens *tokens, t_shell *exec_part)
{
	int	i;

	i = 0;
	tokens->temp = NULL;
	tokens->words = NULL;
	while (line[i])
	{
		init_states(&tokens->state);
		if (line[i] == '\"')
			tokens->state.d_quoted_word = 1;
		else if (line[i] == '\'')
			tokens->state.s_quoted_word = 1;
		else if (line[i] == '$')
			tokens->state.dollar = 1;
		if (line[i] == ' ')
			i = there_is_space(line, i, tokens);
		else
			i = whats_the_state(line, tokens, i, exec_part);
		if (line[i] && !(tokens->words && !tokens->temp
				&& ft_lstlast(tokens->words)->flag == DOLLAR))
			i++;
	}
	if (tokens->temp)
		from_lst_a_to_lst_b(&tokens->temp, &tokens->words);
	join_the_tokens(tokens, &tokens->words);
}
