#ifndef MINIX_R3_2_1_OPT_H
#define MINIX_R3_2_1_OPT_H

#include <machine/vm.h>


#include "vm.h"
#include "pagetable.h"
#include "pt.h"



/*  A pagetable.   */

typedef struct
{
 pt_t *inner_page_tables[I386_VM_OPT_ENTRIES];   
} opt_t;



#endif