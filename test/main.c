/* ************************************************************************** */
/*                                                                            */
/*                                                             ::::::::       */
/*   main.c                                                  :+:    :+:       */
/*                                                          +:+               */
/*   By: emiflake <marvin@student.codam.nl>                +#+                */
/*                                                        +#+                 */
/*   Created: 2019/08/14 15:57:12 by emiflake            #+#    #+#           */
/*   Updated: 2019/08/14 19:58:58 by emiflake            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "../inc/ashmap.h"

void	generate_random_key(char *buf, size_t buf_len)
{
	while (buf_len)
	{
		buf[buf_len] = rand();
		buf_len--;
	}
}

void	test_uniformity(t_hasher hasher)
{
#define HASH_SIZE 409600
#define ENTRY_AMT 409600
	int		counts[HASH_SIZE] = {};
	char		buf[16];
	uint64_t	key;
	int		hits;
	int		collisions;
	int		maximum;
	double		average;

	hits = 0;
	collisions = 0;
	maximum = 0;
	average = 0.0;
	srand(time(NULL));
	printf("Test params: HashSize(%d), EntryAmt(%d)\n", HASH_SIZE, ENTRY_AMT);
	printf("Generating test set based on random values\n");
	for (int i = 0; i < ENTRY_AMT; i++)
	{
		generate_random_key(buf, 16);
		key = hasher(buf, 16) % HASH_SIZE;
		counts[key]++;
	}
	printf("Analyzing test results\n");
	for (int i = 0; i < HASH_SIZE; i++)
	{
		hits = counts[i];
		if (hits > maximum)
			maximum = hits;
		if (hits > 2)
			collisions++;
		average = (hits + average * (double)i) / (double)(i+1);
	}
	printf("Uniformity test results: \n");
	printf("Average hit count: %lf\n", average);
	printf("Total collision count: %d\n", collisions);
	printf("Maximum collision count: %d\n", maximum);
}

void	print_node(size_t bucket_n, size_t node_n, t_bucket_node *node)
{
	printf("[%zu, %zu]: \"%s\" => \"%s\", \n", bucket_n, node_n, node->key, node->value);
}

void	my_cleaner(void *ptr)
{
}

int	main(void)
{
	t_hashmap	*map;

	map = ash_hashmap_new();
	assert(map->bucket_count == 1024);

	t_hasher hasher = ash_hash;
	 test_uniformity(hasher);


	assert(ash_hashmap_insert(map, hasher, "foo", "bar") == NULL);
	assert(strcmp(ash_hashmap_get(map, hasher, "foo"), "bar") == 0);
	assert(ash_hashmap_insert(map, hasher, "bar", "foo") == NULL);
	assert(strcmp(ash_hashmap_get(map, hasher, "bar"), "foo") == 0);
	assert(strcmp(ash_hashmap_insert(map, hasher, "bar", "baz"), "foo") == 0);

	ash_hashmap_foreach_enum(map, print_node);
	ash_hashmap_clean(map, my_cleaner);

	getchar(); // LEAK CHECK
	return (0);
}
