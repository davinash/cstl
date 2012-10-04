#include "c_lib.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void print_integers( void *ptr ) {
	if ( ptr ) {
		printf ( "%d\n", *(int*)ptr);
	}
}
static void 
free_element ( void* ptr ) {
    if ( ptr )
        free ( ptr);
}

static int
compare_strings ( void* left, void* right ) {
    return strcmp ( (const char *)left, (const char *) right );
}

static int 
compare_integers ( void* left, void* right ) {
    int *l = (int*)left;
    int *r = (int*)right;

    if ( *l < *r ) 
        return -1;
    else if ( *l > *r ) 
        return 1;
    return 0;
}
static int 
compare_integers_ptr ( void* left, void* right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}


static struct clib_array*
create_c_array() {
    int size = 10;
    int i = 0;
    int rc ;
    void* p_rv = (void* )0;
    int rv = 0;

    struct clib_array* myArray  = new_c_array (8,compare_integers,NULL);
    assert ( clib_true == empty_c_array( myArray ));

    for ( i = 0; i <= size; i++) {
        push_back_c_array ( myArray, &i ,sizeof(int));
    }
    assert ( clib_false == empty_c_array( myArray ));
    assert ( size == size_c_array( myArray ));
	for ( i = 0; i <= size; i++) {	    
        rc = element_at_c_array ( myArray, i , &p_rv );
        rv = *(int*)p_rv;
	    assert ( rv == i );
        free ( p_rv );
    }	
	return myArray;
}

static struct clib_deque* 
create_deque() {
    int flip = 1;
    int i = 0;
    int limit = 20;
    struct clib_deque* myDeq = new_c_deque ( 10, compare_integers, NULL);
    assert ( (struct clib_deque*)0 != myDeq );

    for ( i = 0; i <= limit; i++ ) { 
        if ( flip ) {
            push_back_c_deque ( myDeq, &i , sizeof(int));
            flip = 0;
        } else {
            push_front_c_deque ( myDeq, &i, sizeof(int) );
            flip = 1;
        }
	}
	return myDeq;
}
static struct clib_set* 
create_set() {
	int test[] = {13,8,17,1,11,15,25,6,22,27};
	int	index  = 0;
	int size   = sizeof (test) /sizeof(test[0]);
	struct clib_set* pSet = new_c_set ( compare_integers, NULL);

	for ( index = 0; index < size; index++ ) {
		int v = test[index];
		insert_c_set ( pSet, &v, sizeof(int));
	}
	return pSet;
}

static struct clib_map* 
create_map () {
	char *char_value[] = {  "A","B","C","D","E","F","G","H","I","J","K","L","M",
                        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	int int_value[] = { 1,2,3,4,5,6,7,8,9,10,
                      11,12,13,14,15,16,17,18,19,20,
                      21,22,23,24,25,26};
    int size = sizeof(char_value)/sizeof(char_value[0]);
    int i = 0;
	struct clib_map *pMap = new_c_map ( compare_strings, NULL, NULL);
    for ( i = 0; i < size; i++ ) {
        char *key = clib_strdup( char_value[i]);
        int key_length = (int)strlen ( key ) + 1;
        int value = int_value[i];
        insert_c_map ( pMap, key, key_length, &value, sizeof(int)); 
        free ( key );
    }	
	return pMap;
}
static struct clib_slist*
create_slist() {
	struct clib_slist* pList = new_c_slist(free_element,compare_integers_ptr);
    int i = 0;
    for ( i = 0; i <= 10; i++ ) { 
        int *v = ( int *) malloc ( sizeof ( int ));
        memcpy ( v, &i, sizeof ( int ));
        push_back_c_slist ( pList, v , sizeof(v));
        free ( v );
    }
	return pList;
}

static void 
t_clib_for_each() {
	struct clib_array *pArray;
	struct clib_deque *pDeq;
	struct clib_set   *pSet;
	struct clib_map   *pMap;
	struct clib_slist *pSlist;
	struct clib_iterator *pArrayIterator;
	struct clib_iterator *pDequeIterator;
	struct clib_iterator *pSetIterator;
	struct clib_iterator *pMapIterator;
	struct clib_iterator *pSlistIterator;
	
	printf ( "Performing for_each for array\n");
	pArray = create_c_array();
	pArrayIterator = new_iterator_c_array ( pArray );
	clib_for_each ( pArrayIterator, print_integers );
	delete_c_array( pArray );
	delete_iterator_c_array ( pArrayIterator );

	printf ( "Performing for_each for deque\n");
	pDeq   = create_deque();
	pDequeIterator = new_iterator_c_deque ( pDeq );
	clib_for_each ( pDequeIterator, print_integers );
	delete_c_deque( pDeq );
	delete_iterator_c_deque ( pDequeIterator );

	printf ( "Performing for_each for set\n");
	pSet   = create_set();
	pSetIterator = new_iterator_c_set ( pSet );
	clib_for_each ( pSetIterator, print_integers );
	delete_c_set( pSet );
	delete_iterator_c_set ( pSetIterator );

	printf ( "Performing for_each for map\n");
	pMap   = create_map();
	pMapIterator = new_iterator_c_map ( pMap );
	clib_for_each ( pMapIterator, print_integers );
	delete_c_map( pMap );
	delete_iterator_c_map ( pMapIterator );

	printf ( "Performing for_each for slist\n");
	pSlist = create_slist();
	pSlistIterator = new_iterator_c_slist ( pSlist );
	clib_for_each ( pSlistIterator, print_integers );
	delete_c_slist( pSlist );
	delete_iterator_c_slist ( pSlistIterator );
}

void 
test_c_algorithms(){
	t_clib_for_each();
}