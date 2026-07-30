/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: q- <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 04:17:02 by q-                #+#    #+#             */
/*   Updated: 2026/07/30 05:55:00 by q-               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_init(t_heap *heap)
{
	heap->size = 0;
}

int	is_higher_priority(t_request a, t_request b, int scheduler)
{
	if (!scheduler)
		return (a.enter_time < b.enter_time);
	else
	{
		if (a.time_to_burnout == b.time_to_burnout)
			return (a.enter_time < b.enter_time);
		return (a.time_to_burnout < b.time_to_burnout);
	}
}

void	heap_push(t_heap *heap, t_request *node, int scheduler)
{
	heap->nodes[heap->size] = *node;
	heap->size++;
	heapify_up(heap, heap->size - 1, scheduler);
}

t_request	heap_pop(t_heap *heap, int scheduler)
{
	t_request	res;

	heap->size--;
	res = heap->nodes[0];
	heap->nodes[0] = heap->nodes[heap->size];
	heapify_down(heap, 0, scheduler);
	return (res);
}
