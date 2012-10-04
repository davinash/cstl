/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/

#include "c_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int 
compare_e ( void* left, void* right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}
static void 
free_e ( void* ptr ) {
    if ( ptr )
    free ( ptr);
}

static void 
replace_values_using_iterators(struct clib_deque* myDeq) {
	struct clib_iterator *myItr;
	struct clib_object *pElement;

	myItr     = new_iterator_c_deque (myDeq);
	pElement  = myItr->get_next(myItr);
	while ( pElement ) {
		void* old_value = myItr->get_value(pElement);
		int new_value = *(int*)old_value;
		new_value = new_value * 2;
		myItr->replace_value( myItr, &new_value, sizeof(new_value));
		free ( old_value );
		pElement = myItr->get_next(myItr);
	}
	delete_iterator_c_deque( myItr );
}
static struct clib_deque* 
create_deque() {
    int flip = 1;
    int i = 0;
    int limit = 20;
    struct clib_deque* myDeq = new_c_deque ( 10, compare_e, NULL);
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
static void
print_using_iterator(struct clib_deque* myDeq) {
	struct clib_iterator *myItr;
	struct clib_object *pElement;

	printf ( "------------------------------------------------\n");
	myItr     = new_iterator_c_deque (myDeq);
	pElement  = myItr->get_next(myItr);
	while ( pElement ) {
		void* value = myItr->get_value(pElement);
		printf ( "%d\n", *(int*)value);
		free ( value );
		pElement = myItr->get_next(myItr);
	}
	delete_iterator_c_deque( myItr );
}

static void
test_with_deque_iterator() {
	struct clib_deque* myDeq = create_deque();
	print_using_iterator(myDeq);
	replace_values_using_iterators(myDeq);
	print_using_iterator(myDeq);
	delete_c_deque ( myDeq );
}

void 
test_c_deque() {
    int flip = 1;
    int i = 0;
    int limit = 20;
    void*  element;
    int j = 0;

    struct clib_deque* myDeq = new_c_deque ( 10, compare_e, NULL);
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
    front_c_deque ( myDeq, &element );
    assert ( *(int*)element == limit - 1 );
    free ( element );

    back_c_deque ( myDeq, &element );
    assert ( *(int*)element == limit);
    free ( element );

    while ( empty_c_deque(myDeq) != clib_true ) {
        pop_front_c_deque ( myDeq);
    }
    delete_c_deque(myDeq);

    myDeq = new_c_deque ( 10, compare_e, free_e); 
    for ( i = 0; i <= limit; i ++ ) { 
        int *v = (int*)malloc(sizeof(int ));
        memcpy ( v, &i, sizeof ( int ));
        push_back_c_deque ( myDeq, v , sizeof(int*));
        free ( v );
    }   
    for ( i = myDeq->head + 1; i < myDeq->tail; i++ ){
        void* elem;
        if ( element_at_c_deque( myDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                assert ( *(int*)elem == j++ );
                free ( elem );
        }
    }
    delete_c_deque(myDeq);
	test_with_deque_iterator();
}
