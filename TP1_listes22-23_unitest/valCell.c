/**
 * @file valCell.c
 * Implementation file for comparison and display of linked list's cells
 */

#include <stdio.h>
#include <string.h>
#include "valCell.h"

/** TO DO
 * @brief Compare the degree of two monomials
 * @param [in] xxx address of the first monomial
 * @param [in] xxx address of the second monomial
 * @return <0 if degree1<degree2; =0 if degree1=degree2;  >0 if degree1>degree2
 */ 
int monom_degree_cmp(monom_t * mon1, monom_t * mon2)
{
 	return (mon1->degree < mon2->degree) ? -1 : ((mon1->degree > mon2->degree) ? 1 : 0);
}


/** TO DO
 * @brief write the information of a monomial to the given output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx address of a monomial
 */
void monom_save2file(FILE * f, monom_t * mon)
{
    printf("monom_save2 enclenché\n");
    fprintf(f, "%.3f %d\n", mon->coef, mon->degree);
    printf("->%.3f %d\n", mon->coef, mon->degree);
    return;
}