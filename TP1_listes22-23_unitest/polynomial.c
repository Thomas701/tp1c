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
// poly_add()
// {
// 	// TO DO
// }

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
