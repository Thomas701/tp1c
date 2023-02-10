/**
 * @file valCell.h
 * @brief relative to the value of linked list's cells
 */

#ifndef __VALCELL_H__
#define __VALCELL_H__

#include <stdio.h>

/** TO DO
 * @struct monom_t 
 * @brief Data structure of monomial (value of linked list's cell)
 * 2 fields :
 * 		- 'coef' : double precision real  
 * 		- 'degree' : integer
 */
typedef struct monom_t
{
    double coef;
    int degree;
} monom_t;


/** TO DO
 * @brief Compare the degree of two monomials
 * @param [in] xxx address of the first monomial
 * @param [in] xxx address of the second monomial
 * @return <0 if m1.degree<m2.degree; =0 if m1.degree=m2.degree;  >0 if m1.degree>m2.degree
 */
int monom_degree_cmp(monom_t * mon1, monom_t * mon2);


/** TO DO
 * @brief write the information of a monomial to the given output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx address of a monomial
 */
void monom_save2file(FILE * f, monom_t * mon);

#endif