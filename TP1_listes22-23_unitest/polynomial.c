#include <stdio.h>
#include <stdlib.h>
//#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON
//#include <math.h>

#include "linkedList.h"
#include "valCell.h"

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
	    cellule = cellule->next;
            LL_del_cell(p_cell_suppr);
        }
        else
        {
            cellule->val.coef = (cellule->val.coef) * (cellule->val.degree);
            cellule->val.degree = (cellule->val.degree) - 1;
	    cellule = cellule->next;
        }
	
    }
}

/**
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t **head1, cell_t **head2)
{
  cell_t *cel;
  cell_t *cour1;
  cell_t *cour2;
  int compare;
  if(monom_degree_cmp(&((*head1)->val), &((*head2)->val)) > 0){
    cel = *head1;
    *head1 = *head2;
    *head2 = cel;
  }

  cour1 = *head1;
  cour2 = *head2;
  *head2 = NULL;

  while(cour2 != NULL){
    compare = monom_degree_cmp(&(cour1->val), &(cour2->val));
    if(compare == 0){
      cour1->val.coef += cour2->val.coef;
      cel = cour2;
      cour2 = cour2->next;
      free(cel);
    }else {
      if(cour1->next == NULL || monom_degree_cmp(&(cour1->next->val), &(cour2->val)) > 0){
	cel = cour2;
	cour2 = cour2->next;
	cel->next = cour1->next;
	cour1->next = cel;
	cour1 = cour1->next;
      }else{
	cour1 = cour1->next;
      }
    }
  }

  cour1 = *head1;
  while (cour1 != NULL && cour1->val.coef == 0){
    *head1 = cour1->next;
    free(cour1);
    cour1 = *head1;
  }
  while (cour1 != NULL && cour1->next != NULL) {
    if(cour1->next->val.coef == 0){
      cel = cour1->next;
      cour1->next = cel->next;
      free(cel);
    }else{
      cour1 = cour1->next;
    }
  }
}
/*
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
*/
/**
 * @brief compute P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */
cell_t * poly_prod(cell_t * head1, cell_t * head2)
{
  cell_t *cour1 = head1;
  cell_t *cour2 = head2;
  cell_t *head3 = NULL;
  int maxdeg;
  float *values;
  int i;
  monom_t new;

  while(cour1->next != NULL)cour1 = cour1->next;
  while(cour2->next != NULL)cour2 = cour2->next;
  maxdeg = cour1->val.degree+cour2->val.degree;

  values = (float *)malloc((maxdeg+1)*sizeof(float));
  if(values){
    for(i = 0; i < maxdeg+1; i++){
      values[i] = 0;
    }
    cour1 = head1;
    while (cour1 != NULL) {
      cour2 = head2;
      while(cour2 != NULL){
	values[cour1->val.degree+cour2->val.degree] += cour1->val.coef*cour2->val.coef;
	cour2 = cour2->next;
      }
      cour1 = cour1->next;
    }
    for(i = maxdeg; i > -1; i--){
      if(values[i] != 0){
	new.coef = values[i];
	new.degree = i;
	cell_t *cel = LL_create_cell(&new);
	cel->next = head3;
	head3 = cel;
      }
    }
    free(values);
  }

  
  return &(*head3);
}
/*
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
    return &(*head3);
}
*/
