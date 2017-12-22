#include "hex_hashmap.h"

#include "assert.h"


size_t hex_hashmap_get_list_index_for_name(char *name) {
	assert_not_null(name);

	char c = name[0];

	if (c >= '0' && c <= '9') return (size_t) (c - '0');
	if (c >= 'a' && c <= 'f') return (size_t) (c - 'a' + 10);

	panic("Failed to calculate index for name '%s'", name);
	return (size_t) -1;
}


hex_hashmap_list_t *hex_hashmap_get_list(hex_hashmap_t *map, char *name) {
	assert_not_null(map);
	assert_not_null(name);

	return map->items[hex_hashmap_get_list_index_for_name(name)];
}


void *hex_hashmap_get_item(hex_hashmap_t *map, char *name) {
	assert_not_null(map);
	assert_not_null(name);

	hex_hashmap_list_t *list = hex_hashmap_get_list(map, name);
	return hex_hashmap_list_get_item(list, name);
}


bool hex_hashmap_add_item(hex_hashmap_t *map, char *name, void *value) {
	assert_not_null(map);
	assert_not_null(name);
	// NOTE: Not allowing NULL value
	assert_not_null(value);

	hex_hashmap_list_t *list = hex_hashmap_get_list(map, name);
	assert_not_null(list);

	// Don't allow duplicates
	if (hex_hashmap_list_contains_item(list, name)) {
		panic("Can not add item: already in map");
		return NULL;
	}

	return hex_hashmap_list_add_item(list, name, value);
}


bool hex_hashmap_remove_item(hex_hashmap_t *map, char *name) {
	assert_not_null(map);
	assert_not_null(name);

	hex_hashmap_list_t *list = hex_hashmap_get_list(map, name);
	assert_not_null(list);

	return hex_hashmap_list_remove_item(map, list, name);
}


size_t hex_hashmap_amount(hex_hashmap_t *map) {
	assert_not_null(map);

	// TODO: Optimise
	size_t amount = 0;

	HEX_HASHMAP_EACH_VALUE(*map, void *_x) {
		(void) _x;

		amount++;
	}

	return amount;
}



void *hex_hashmap_list_get_item(hex_hashmap_list_t *list, char *name) {
	assert_not_null(list);
	assert_not_null(name);

	hex_hashmap_list_t *item = list;

	if (item->name == NULL) {
		goto fail;
	}

	while (item != NULL) {
		if (strcmp(item->name, name) == 0) {
			return item->value;
		}

		item = item->next;
	}

	fail:
	warn("Failed to find hex_hashmap item for name '%s'", name);
	return NULL;
}


bool hex_hashmap_list_remove_item(hex_hashmap_t *map, hex_hashmap_list_t *list, char *name) {
	assert_not_null(list);
	assert_not_null(name);

	hex_hashmap_list_t *item = list;

	if (item->name == NULL) {
		goto notfound;
	}

	// Check if first item
	if (strcmp(item->name, name) == 0) {
		if (item->next != NULL) {
			// Replace the first item with the next
			map->items[hex_hashmap_get_list_index_for_name(name)] = item->next;
		}
		else {
			// Reset to initial state
			item->name = NULL;
			item->value = NULL;
		}

		return true;
	}


	while (item->next != NULL) {
		if (strcmp(item->next->name, name) == 0) {
			item->next = item->next->next;
			return true;
		}

		item = item->next;
	}

	notfound:
	warn("Failed to remove item %s, since it's not in the hexmap", name);
	return false;
}


bool hex_hashmap_list_contains_item(hex_hashmap_list_t *list, char *name) {
	assert_not_null(list);
	assert_not_null(name);

	hex_hashmap_list_t *item = list;

	if (item->name == NULL) {
		return false;
	}

	while (item != NULL) {
		if (strcmp(item->name, name) == 0) {
			return true;
		}

		item = item->next;
	}

	return false;
}


bool hex_hashmap_list_add_item(hex_hashmap_list_t *list, char *name, void *value) {
	assert_not_null(list);
	assert_not_null(name);
	// NOTE: Not allowing NULL value
	assert_not_null(value);

	// First item
	if (list->name == NULL) {
		// Replace first item
		list->name = name;
		list->value = value;
		return true;
	}

	// Create new item
	hex_hashmap_list_t *item = malloc(sizeof(hex_hashmap_list_t));
	hex_hashmap_list_init(item);

	item->name = name;
	item->value = value;

	// Add item to list
	hex_hashmap_list_t *last = hex_hashmap_list_get_last(list);

	last->next = item;

	return true;
}


hex_hashmap_list_t *hex_hashmap_list_get_last(hex_hashmap_list_t *list) {
	assert_not_null(list);


	hex_hashmap_list_t *last = list;

	if (last == NULL) {
		warn("Failed to get last item of list: lits doesn't have any items");
		return NULL;
	}

	while (last->next != NULL) {
		last = last->next;
	}

	return last;
}



void hex_hashmap_init(hex_hashmap_t *map) {
	for (size_t i=0; i < 16; i++) {
		map->items[i] = malloc(sizeof(hex_hashmap_list_t));
		hex_hashmap_list_init(map->items[i]);
	}
}


void hex_hashmap_free(hex_hashmap_t *map) {
	for (size_t i=0; i < 16; i++) {
		hex_hashmap_list_free(map->items[i]);
		free(map->items[i]);
	}
}



void hex_hashmap_list_init(hex_hashmap_list_t *item) {
	item->name = NULL;
	item->value = NULL;
	item->next = NULL;
}


void hex_hashmap_list_free(hex_hashmap_list_t *item) {
	// if (item->name) free(item->name);
	// if (item->value) free(item->value);

	if (item->next != NULL) {
		hex_hashmap_list_free(item->next);
		free(item->next);
	}
}
