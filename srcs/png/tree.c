/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by magouin           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <png.h>

void			create_leaf(struct s_tree *node, struct s_length_code code)
{
	struct s_tree			*new;
	struct s_tree			**to_modify;

	if (code.length == 0)
	{
		node->l = NULL;
		node->r = NULL;
		node->symbol = code.symbol;
		return ;
	}
	if (code.code & (1 << (code.length - 1)))
		to_modify = &node->r;
	else
		to_modify = &node->l;
	code.length--;
	if (*to_modify)
		new = *to_modify;
	else
	{
		new = malloc(sizeof(struct s_tree));
		*new = (struct s_tree){NULL, NULL, 0};
		*to_modify = new;
	}
	create_leaf(new, code);
}

void			delete_tree(struct s_tree	*tree)
{
	if (!tree->r && !tree->l)
		free(tree);
	else
	{
		if (tree->r)
			delete_tree(tree->r);
		if (tree->l)
			delete_tree(tree->l);
		free(tree);
	}
}

struct s_tree	*create_tree(struct s_length_code *codes, size_t s)
{
	size_t					i;
	struct s_tree			*tree;

	i = 0;
	tree = malloc(sizeof(struct s_tree));
	tree->l = NULL;
	tree->r = NULL;
	while (i < s)
	{
		if (codes[i].length != 0)
		{
			create_leaf(tree, codes[i]);
		}
		i++;
	}
	return (tree);
}
