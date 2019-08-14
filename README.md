# AshMap
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

	map = ash_hashmap_new();

	t_hasher hasher = ash_hash;

	ash_hashmap_insert(map, hasher, "foo", "bar"));
	ash_hashmap_insert(map, hasher, "bar", "foo"));

	if (ash_hashmap_get(map, hasher, "foo"))
		printf("Silly foo!\n");

	ash_hashmap_foreach_enum(map, print_node);
	ash_hashmap_clean(map, my_cleaner);
}
```
