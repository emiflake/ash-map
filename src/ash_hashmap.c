/* ************************************************************************** */
/*                                                                            */
/*                                                             ::::::::       */
/*   ash_hashmap.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: emiflake <marvin@student.codam.nl>                +#+                */
/*                                                        +#+                 */
/*   Created: 2019/08/14 15:11:22 by emiflake            #+#    #+#           */
/*   Updated: 2019/08/14 20:00:20 by emiflake            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "../inc/ashmap.h"
#include "../inc/ash_common.h"

t_hashmap	*ash_hashmap_new(void)
{
	return (ash_hashmap_with_size(1024));
}

t_hashmap	*ash_hashmap_with_size(size_t length)
{
	t_hashmap	*hashmap;
	t_bucket	*buckets;

	hashmap = (t_hashmap*)malloc(sizeof(t_hashmap));
	if (!hashmap)
		return (NULL);
	buckets = (t_bucket*)malloc(sizeof(t_bucket) * length);
	if (!buckets)
		return (NULL);
	hashmap->buckets = buckets;
	hashmap->bucket_count = length;
	return (hashmap);
}

t_bucket	*ash_hashmap_get_bucket(t_hashmap *map, t_hasher hasher, char *key)
{
	const uint64_t	bucket_idx = hasher(key, ash_strlen(key)) % map->bucket_count;

	return (&map->buckets[bucket_idx]);
}

void		*ash_hashmap_insert(t_hashmap *map, t_hasher hasher, char *key, void *value)
{
	t_bucket	*bucket;

	bucket = ash_hashmap_get_bucket(map, hasher, key);
	return (ash_bucket_set(bucket, key, value));
}

void		*ash_hashmap_get(t_hashmap *map, t_hasher hasher, char *key)
{
	t_bucket	*bucket;

	bucket = ash_hashmap_get_bucket(map, hasher, key);
	return (ash_bucket_get(bucket, key));
}
