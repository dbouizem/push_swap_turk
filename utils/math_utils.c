/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/02/20 00:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	min_value(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
