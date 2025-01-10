
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declarations
struct entry;
struct nsd_pte;
struct zone_path;
struct zone_entity;
struct gool_object;

typedef uint32_t ptr_handle_t;

typedef struct {
    void **pointers;
    uint32_t capacity;
    uint32_t count;
    int initialized;
} ptr_container_t;

// Function declarations
int init_global_containers(uint32_t initial_capacity);
void cleanup_global_containers(void);

// Global accessor functions - declarations only
ptr_handle_t store_entry(struct entry *entry);
ptr_handle_t store_pte(struct nsd_pte *pte);
ptr_handle_t store_zone_path(struct zone_path *path);
ptr_handle_t store_zone_entity(struct zone_entity *entity);
ptr_handle_t store_gool_object(struct gool_object *obj);
ptr_handle_t replace_gool_object(struct gool_object *obj, ptr_handle_t handle);
ptr_handle_t store_generic(void *ptr);
ptr_handle_t replace_generic(void *ptr, ptr_handle_t handle);

struct entry *get_entry(ptr_handle_t handle);
struct nsd_pte *get_pte(ptr_handle_t handle);
struct zone_path *get_zone_path(ptr_handle_t handle);
struct zone_entity *get_zone_entity(ptr_handle_t handle);
struct gool_object *get_gool_object(ptr_handle_t handle);
uint32_t *get_int_ptr(ptr_handle_t handle);
void *get_generic(ptr_handle_t handle);
