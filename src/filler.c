/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:57:29 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/22 19:38:12 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler(void)
{
	int res;

	res = find_place();
	ft_putnbr(g_filler.candidat.y);
	ft_putchar(' ');
	ft_putnbr(g_filler.candidat.x);
	ft_putchar('\n');
	if (!res)
		ft_putstr("errror\n");
//		exit(1);
}

void	filler_p(void)
{
	int i;

	i = 0;
	ft_printf("FIELD\nheight = %i\nwidth = %i\n", g_filler.field.height, g_filler.field.width);
	while (i < g_filler.field.height)
		ft_printf("%s\n", g_filler.field.piece[i++]);
	i = 0;
	ft_printf("PIECE\nheight = %i\nwidth = %i\n", g_filler.piece.height, g_filler.piece.width);
	while (i < g_filler.piece.height)
		ft_printf("%s\n", g_filler.piece.piece[i++]);
}

void	clear_field(t_piece *squere)
{
	int i;

	i = 0;
	if (!squere->piece)
		return ;
	while (i < squere->height)
		ft_strdel(&squere->piece[i++]);
	ft_memdel((void **)&squere->piece);
}

void	read_field(t_piece *squere, int type)
{
	char	*str;
	int		i;

	i = 0;
	clear_field(squere);
	squere->piece = (char **)malloc(sizeof(char *) * squere->height);
	while (i < squere->height)
	{
		get_next_line(0, &str);
//		ft_printf("%s\n", str);
		if (type && str[type] == '0')
		{
			free(str);
			continue ;
		}
		squere->piece[i] = ft_strdup(&str[type]);
		free(str);
		i++;
//		ft_putchar('w');
	}
}

void	cycle_filler(void)
{
	char	*str;

	while (get_next_line(0, &str) > -1)
	{
		if (!str)
			continue ;
		if (!ft_strncmp(str, "Plateau ", 8))
		{
			g_filler.field.height = ft_atoi(&str[8]);
			g_filler.field.width = ft_atoi(ft_strchr(&str[8], ' '));
			read_field(&g_filler.field, 4);
//			ft_putchar('z');
		}
		if (!strncmp(str, "Piece ", 6))
		{
			
			g_filler.piece.height = ft_atoi(&str[6]);
			g_filler.piece.width = ft_atoi(ft_strchr(&str[6], ' '));
			read_field(&g_filler.piece, 0);
//			ft_putchar('x');
			filler();
		}
		ft_strdel(&str);
//		ft_putchar('e');
	}
}

int		main(void)
{
	char *str;

	ft_bzero(&g_filler, sizeof(t_filler));
	str = NULL;
	if (!get_next_line(0, &str) || ft_strncmp("$$$ exec p", str, 10))
		return (1);
	g_filler.player.number = str[10] == '1' ? 'O' : 'X';
	g_filler.enemy.number = str[10] == '1' ? 'X' : 'O';
	ft_strdel(&str);
	cycle_filler();
}
