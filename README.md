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