/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:13:37 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/11 00:37:05 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	words_numbers(char const *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cont++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (cont);
}

static int	num_characters(char const *s, char c, int i)
{
	int	cont;

	cont = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		cont++;
		i++;
	}
	return (cont);
}

static char	**liberar(char **aux, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)aux[j]);
	}
	free(aux);
	return (0);
}

static char	**spliit(char const *s, char c, int len, char **aux)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		while (s[i] == c)
			i++;
		aux[j] = (char *)malloc((num_characters(s, c, i) + 1));
		if (aux[j] == NULL)
			return (liberar((char **)aux, j));
		k = 0;
		while (s[i] != c && s[i] != '\0')
			aux[j][k++] = s[i++];
		aux[j][k] = '\0';
		j++;
	}
	aux[j] = 0;
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**aux;

	if (s == NULL)
		return (0);
	len = words_numbers(s, c);
	aux = (char **)malloc(sizeof(char *) * (len + 1));
	if (aux == NULL)
		return (0);
	aux = spliit(s, c, len, aux);
	return (aux);
}
/* void	imprimir_doble_puntero(char **a)
{
	int	i;
	int	j;

	i = 0, j = 0;
	while (a[i] != 0)
	{
		while (a[i][j] != '\0')
		{
			printf("%c", a[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}
int	main(void)
{
	char *s1 = " 3ha oal ha rtrragfdgfdhgdfgdfgaaaahiaaagsaghdfgdfhga   sddsfsaa";
	char s2 = 'a';
	char **a;
	a = ft_split(s1, s2);
	imprimir_doble_puntero(a);
	return (0);
} */