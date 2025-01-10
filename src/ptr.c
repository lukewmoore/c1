#include "ptr.h"

// Define a base offset for handles
#define PTR_HANDLE_BASE 0x400

// Define the global containers
ptr_container_t g_entry_container = { 0 };
ptr_container_t g_pte_container = { 0 };
ptr_container_t g_zone_path_container = { 0 };
ptr_container_t g_zone_entity_container = { 0 };
ptr_container_t g_gool_object_container = { 0 };
ptr_container_t g_generic_container = { 0 };

// Initialize an individual container
static int init_container(ptr_container_t *container, uint32_t initial_capacity) {
    if (!container || container->initialized) {
        return 0;
    }

    container->pointers = (void **)malloc(initial_capacity * sizeof(void *));
    if (!container->pointers) {
        return 0;
    }

    container->capacity = initial_capacity;
    container->count = 0;
    container->initialized = 1;
    return 1;
}

// Initialize all global containers
int init_global_containers(uint32_t initial_capacity) {
    return init_container(&g_entry_container, initial_capacity) &&
           init_container(&g_pte_container, initial_capacity) &&
           init_container(&g_zone_path_container, initial_capacity) &&
           init_container(&g_zone_entity_container, initial_capacity) &&
           init_container(&g_gool_object_container, initial_capacity) &&
           init_container(&g_generic_container, initial_capacity);
}

// Helper function to expand container capacity
static int expand_container(ptr_container_t *container) {
    uint32_t new_capacity = container->capacity * 2;
    void **new_pointers = (void **)realloc(container->pointers, new_capacity * sizeof(void *));
    if (!new_pointers) {
        return 0;
    }

    container->pointers = new_pointers;
    container->capacity = new_capacity;
    return 1;
}

// Store a pointer and get a handle
static ptr_handle_t store_pointer(ptr_container_t *container, void *ptr) {
    if (!container || !container->initialized) {
        return 0;
    }

    if (container->count >= container->capacity) {
        if (!expand_container(container)) {
            return 0;
        }
    }

    // Special case: if storing NULL pointer, return 0 handle
    if (ptr == NULL) {
        // return 0;
    }

    // We use 1-based handles (0 = invalid/NULL)
    // So first pointer gets handle 1, second gets 2, etc.
    container->pointers[container->count] = ptr;
    container->count++;
    return (container->count + PTR_HANDLE_BASE) << 1;
}

// Store a pointer and get a handle
static ptr_handle_t replace_pointer(ptr_container_t *container, void *ptr, ptr_handle_t handle) {
    if (handle == 0) {
        return store_pointer(container, ptr);
    }

    // Special case: if storing NULL pointer, return 0 handle
    if (ptr == NULL) {
        // return 0;
    }

    // Handle 0 is already checked above, so we can safely subtract 1
    // This converts from 1-based handles to 0-based array indices
    uint32_t index = (handle >> 1) - PTR_HANDLE_BASE - 1;
    if (index >= container->count) {
        return 0;
    }

    container->pointers[index] = ptr;
    return handle;
}

// Retrieve a pointer from a handle
static void *get_pointer(ptr_container_t *container, ptr_handle_t handle) {
    if (!container || !container->initialized || handle == 0) {
        return NULL;
    }

    // Handle 0 is already checked above, so we can safely subtract 1
    // This converts from 1-based handles to 0-based array indices
    return container->pointers[(handle >> 1) - PTR_HANDLE_BASE - 1];
}

// Global accessor function implementations
ptr_handle_t store_entry(struct entry *entry) {
    return store_pointer(&g_entry_container, entry);
}

ptr_handle_t store_pte(struct nsd_pte *pte) {
    return store_pointer(&g_pte_container, pte);
}

ptr_handle_t store_zone_path(struct zone_path *path) {
    return store_pointer(&g_zone_path_container, path);
}

ptr_handle_t store_zone_entity(struct zone_entity *entity) {
    return store_pointer(&g_zone_entity_container, entity);
}

ptr_handle_t store_gool_object(struct gool_object *obj) {
    return store_pointer(&g_gool_object_container, obj);
}

ptr_handle_t replace_gool_object(struct gool_object *obj, ptr_handle_t handle) {
    return replace_pointer(&g_gool_object_container, obj, handle);
}

ptr_handle_t store_generic(void *ptr) {
    return store_pointer(&g_generic_container, ptr);
}

ptr_handle_t replace_generic(void *ptr, ptr_handle_t handle) {
    return replace_pointer(&g_generic_container, ptr, handle);
}

struct entry *get_entry(ptr_handle_t handle) {
    return (struct entry *)get_pointer(&g_entry_container, handle);
}

struct nsd_pte *get_pte(ptr_handle_t handle) {
    return (struct nsd_pte *)get_pointer(&g_pte_container, handle);
}

struct zone_path *get_zone_path(ptr_handle_t handle) {
    return (struct zone_path *)get_pointer(&g_zone_path_container, handle);
}

struct zone_entity *get_zone_entity(ptr_handle_t handle) {
    return (struct zone_entity *)get_pointer(&g_zone_entity_container, handle);
}

struct gool_object *get_gool_object(ptr_handle_t handle) {
    return (struct gool_object *)get_pointer(&g_gool_object_container, handle);
}

uint32_t *get_int_ptr(ptr_handle_t handle) {
    return (uint32_t *)get_pointer(&g_generic_container, handle);
}

void *get_generic(ptr_handle_t handle) {
    return get_pointer(&g_generic_container, handle);
}

void cleanup_global_containers(void) {
    free(g_entry_container.pointers);
    free(g_pte_container.pointers);
    free(g_zone_path_container.pointers);
    free(g_zone_entity_container.pointers);

    g_entry_container.initialized = 0;
    g_pte_container.initialized = 0;
    g_zone_path_container.initialized = 0;
    g_zone_entity_container.initialized = 0;
}
