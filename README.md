# AshMap ![travis badge](https://travis-ci.com/emiflake/ash-map.svg?branch=master) ![lang](https://img.shields.io/github/languages/top/emiflake/ash-map)
A C89 HashMap implementation

# Usage
AshMap hopes to provide a simple and useable interface for using hashmaps
```c
void	print_node(size_t bucket_n, size_t node_n, t_bucket_node *node)
{
	printf("[%zu, %zu]: \"%s\" => \"%s\", \n", bucket_n, node_n, node->key, node->value);
}

int main(void) {
	t_hashmap	*map;

	map = ash_hashmap_new(ash_hash);

	ash_hashmap_insert(map, "foo", "bar"));
	ash_hashmap_insert(map, "bar", "foo"));

	if (ash_hashmap_get(map, "foo"))
		printf("Silly foo!\n");

	ash_hashmap_foreach_enum(map, print_node);
	ash_hashmap_clean(map, my_cleaner);
}
```
