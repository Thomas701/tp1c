#include <stdio.h>
#include <stdlib.h>
//#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON
//#include <math.h>

#include "linkedList.h"

/** TO DO
 * @brief compute 'in place' the derive of a polynomial 
 * @param [in, out] xxx address of a polynomial's head pointer
 */
void poly_derive(cell_t ** head)
{
	cell_t * cellule = (*head);
    while (cellule != NULL)
    {
        if (cellule->val.degree == 0)
        {
            cell_t ** p_cell_suppr = LL_search_prev(head, &(cellule->val), &monom_degree_cmp);
            LL_del_cell(p_cell_suppr);
        }
        else
        {
            cellule->val.coef = (cellule->val.coef) * (cellule->val.degree);
            cellule->val.degree = (cellule->val.degree) - 1;
        }
    }
}

/** TO DO
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t ** head1, cell_t ** head2)
{
	cell_t * cellule1 = (*head1);
    cell_t * cellule2 = (*head2);
    cell_t * cellule3;

    LL_init_list(&cellule3);
    while (cellule1 != NULL && cellule2 != NULL)
    {
        if (monom_degree_cmp(&(cellule1->val), &(cellule2->val)) == 0)
        {
            if (cellule1->val.coef + cellule2->val.coef != 0)
            {
                monom_t * mon = malloc(sizeof(mon));
                mon->coef = cellule1->val.coef + cellule2->val.coef;
                mon->degree = cellule1->val.degree;
                cell_t * cell = LL_create_cell(mon);
                LL_add_end_list(&cellule3, cell);
            }
        }
    }
    
}

/** TO DO
 * @brief compute P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */
// poly_prod()
// {
// 	// TO DO
// }
