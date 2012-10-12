# CSTL - STL like container support in C language

## Dynamic Array
```cpp
struct clib_array {
    int no_max_elements; /* Number of maximum elements array can hold without reallocation */
    int no_of_elements;  /* Number of current elements in the array */
    struct clib_object** pElements; /* actual storage area */
    clib_compare compare_fn; /* Compare function pointer*/
    clib_destroy destruct_fn; /* Destructor function pointer*/
};

struct clib_array* new_c_array ( int init_size, clib_compare fn_c, clib_destroy fn_d);
clib_error push_back_c_array ( struct clib_array* pArray, void* elem, size_t elem_size);
clib_error element_at_c_array( struct clib_array* pArray, int pos, void**e);
clib_error insert_at_c_array ( struct clib_array* pArray, int index, void* elem, size_t elem_size);
int size_c_array( struct clib_array* pArray);
int capacity_c_array( struct clib_array* pArray );
clib_bool  empty_c_array( struct clib_array* pArray);
clib_error reserve_c_array( struct clib_array* pArray, int pos);
clib_error front_c_array( struct clib_array* pArray,void* elem);
clib_error back_c_array( struct clib_array* pArray,void* elem);
clib_error remove_from_c_array ( struct clib_array*, int pos);
clib_error delete_c_array( struct clib_array* pArray);

struct clib_iterator* new_iterator_c_array(struct clib_array* pArray);
void delete_iterator_c_array ( struct clib_iterator* pItr);
```

## deque
```cpp
struct clib_deque {
    struct clib_object**pElements;
    int no_max_elements;
    int head;
    int tail;
    int no_of_elements;
    clib_compare compare_fn;
    clib_destroy destruct_fn;
}c_deque;

struct clib_deque* new_c_deque( int deq_size , clib_compare fn_c, clib_destroy fn_d);
clib_error     push_back_c_deque (struct clib_deque* pDeq, void* elem, size_t elem_size);
clib_error     push_front_c_deque(struct clib_deque* pDeq, void* elem,size_t elem_size);

clib_error     front_c_deque     (struct clib_deque* pDeq,void*);
clib_error     back_c_deque      (struct clib_deque* pDeq,void*);
clib_error     pop_back_c_deque  (struct clib_deque* pDeq);
clib_error     pop_front_c_deque (struct clib_deque* pDeq);
clib_bool      empty_c_deque     (struct clib_deque* pDeq);
int            size_c_deque ( struct clib_deque* pDeq);
clib_error     delete_c_deque ( struct clib_deque* pDeq);
clib_error     element_at_c_deque (struct clib_deque* pDeq, int index, void**elem);

struct clib_iterator* new_iterator_c_deque(struct clib_deque* pDeq);
void delete_iterator_c_deque ( struct clib_iterator* pItr);
```

## list
```cpp
struct clib_slist_node {
    struct clib_object* elem;
    struct clib_slist_node *next;
};
struct clib_slist {
    struct clib_slist_node* head;
    clib_destroy destruct_fn;
    clib_compare compare_key_fn;
    int size;
};
struct clib_slist* new_c_slist(clib_destroy fn_d, clib_compare fn_c);
void           delete_c_slist   (struct clib_slist* pSlist);
clib_error     insert_c_slist   (struct clib_slist* pSlist, int pos, void* elem, size_t elem_size);
clib_error     push_back_c_slist(struct clib_slist* pSlist, void* elem, size_t elem_size);
void           remove_c_slist   (struct clib_slist* pSlist, int pos);
void           for_each_c_slist (struct clib_slist* pSlist, void (*fn)(void* ));
clib_bool      find_c_slist     (struct clib_slist* pSlist, void* find_value, void**out_value);


struct clib_iterator* new_iterator_c_slist(struct clib_slist* pSlit);
void delete_iterator_c_slist ( struct clib_iterator* pItr);
```
## set
```cpp
struct clib_set {
    struct clib_rb* root;
};
struct clib_set* new_c_set( clib_compare fn_c, clib_destroy fn_d);
clib_error   insert_c_set ( struct clib_set* pSet, void* key, size_t key_size);
clib_bool    exists_c_set ( struct clib_set* pSet, void* key);
clib_error   remove_c_set ( struct clib_set* pSet, void* key);
clib_bool    find_c_set   ( struct clib_set* pSet, void* key, void* outKey);
clib_error   delete_c_set ( struct clib_set* pSet);

struct clib_iterator* new_iterator_c_set(struct clib_set* pSet);
void delete_iterator_c_set ( struct clib_iterator* pItr);
```

## map
```cpp
struct clib_map {
    struct clib_rb* root;
};

struct clib_map* new_c_map    ( clib_compare fn_c_k, clib_destroy fn_k_d, clib_destroy fn_v_d);
clib_error   insert_c_map ( struct clib_map* pMap, void* key, size_t key_size, void* value,  size_t value_size);
clib_bool    exists_c_map ( struct clib_map* pMap, void* key);
clib_error   remove_c_map ( struct clib_map* pMap, void* key);
clib_bool    find_c_map   ( struct clib_map* pMap, void* key, void**value);
clib_error   delete_c_map ( struct clib_map* pMap);

struct clib_iterator* new_iterator_c_map(struct clib_map* pMap);
void delete_iterator_c_map ( struct clib_iterator* pItr);
```


