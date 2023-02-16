#include <stdio.h>
#include <stdlib.h>
//#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON
//#include <math.h>

#include "linkedList.h"

/**
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

/**
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t ** head1, cell_t ** head2)
{
	cell_t * cellule1 = (*head1);
    cell_t * courant1 = (*head1);
    cell_t * courant2 = (*head2);
    monom_t mon;
    int test = 1;

    while (courant1 != NULL || courant2 != NULL) {
        if (courant1 == NULL || (monom_degree_cmp(&(courant1->val), &(courant2->val)) > 0)) {
            mon.coef = courant2->val.coef;
            mon.degree = courant2->val.degree;
            cell_t * newCell = LL_create_cell(&mon);
            LL_add_cell(&cellule1, newCell);
            courant2 = courant2->next;
        }
        else if (courant2 == NULL || (monom_degree_cmp(&(courant1->val), &(courant2->val)) < 0)) {
            mon.coef = courant1->val.coef;
            mon.degree = courant1->val.degree;
            cell_t * newCell = LL_create_cell(&mon);
            LL_add_cell(&cellule1, newCell);
            courant1 = courant1->next;
        }
        else if ((monom_degree_cmp(&(courant1->val), &(courant2->val)) == 0) 
            && (courant1->val.coef + courant2->val.coef != 0)) {
            mon.coef = courant1->val.coef + courant2->val.coef;
            mon.degree = courant1->val.degree;
            cell_t * newCell = LL_create_cell(&mon);
            LL_add_cell(&cellule1, newCell);
            courant1 = courant1->next;
            courant2 = courant2->next;
        }
        if (test)
        {
            (*head1) = cellule1;
            test = 0;
        }
        cellule1 = cellule1->next;
    }
    LL_free_list(&cellule1);
    LL_free_list(head2);
}

/**
 * @brief compute P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */
cell_t * poly_prod(cell_t * head1, cell_t * head2)
{
    cell_t * head3;
    monom_t mon;
    
    LL_init_list(&head3);
    while (head1 != NULL)
    {
        while(head2 != NULL)
        {
            mon.coef = (head1->val.coef) * (head2->val.coef);
            mon.degree = (head1->val.degree) + (head2->val.degree);
            cell_t * newCell = LL_create_cell(&mon);
            cell_t ** find = LL_search_prev(&head3, &(newCell->val), &monom_degree_cmp);
            if (find == NULL || (*find) == NULL || (*find)->val.degree != newCell->val.degree)
                LL_add_cell(find, newCell);
            else 
                (*find)->val.coef += newCell->val.coef;

            head2 = head2->next;
        }
        head1 = head1->next;
    }
    return head3;
}
