#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "valCell.h"

/**
 * @brief compute 'in place' the derive of a polynomial
 * @param [in, out] xxx address of a polynomial's head pointer
 */
void poly_derive(cell_t ** head)
{
  cell_t ** cour = head;
  while ((*cour) != NULL)
  {
    if((*cour)->val.degree == 0) //si le degré de la cellule = 0, on la supprime
    {
      cell_t * sup = (*cour);
      (*cour) = (*cour)->next;
      free(sup);
    }
    else
    { // sinon on calcule le nouveau coefficient (coef*degree) et on décrémente le degré de 1 
      (*cour)->val.coef = ((*cour)->val.coef) * ((*cour)->val.degree);
      (*cour)->val.degree = ((*cour)->val.degree) - 1;
      cour = &(*cour)->next;
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
  int compare;
  cell_t ** cour1 = head1;
  cell_t * cour2 = *head2;
  cell_t * cel;
  *head2 = NULL;
  
  while(cour2 != NULL){
    compare = monom_degree_cmp(&((*cour1)->val), &(cour2->val));
    cel = cour2;
    if(compare == 0){ //si les cellule on le même degré, on les ajoute dans le polynome 1
      (*cour1)->val.coef += cour2->val.coef;
      cour2 = cour2->next;
      free(cel);
      if((*cour1)->val.coef == 0){ //si l'addition des deux cellules donne un coefficient de 0, on la supprime
	      cel = (*cour1);
	      (*cour1) = (*cour1)->next;
	      free(cel);
      }
    }else if(compare > 0){ // si le degré du premier monome est supérieur à celui du second
      cour2 = cour2->next; // on met le monome du second polynôme en tête de liste du premier polynôme
      cel->next = (*cour1);
      (*cour1) = cel;
      cour1 = &(*cour1)->next;
    }else{ //sinon on incrémente cour1
      cour1 = &(*cour1)->next;
    }
  }
}

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
  maxdeg = cour1->val.degree+cour2->val.degree; //on calcule le degré maximum du nouveau polynôme

  values = (float *)malloc((maxdeg+1)*sizeof(float)); //création et initialisation d'un tableau de taille maxdeg
  if(values){
    for(i = 0; i < maxdeg+1; i++){
      values[i] = 0;
    }
    cour1 = head1;
    while (cour1 != NULL) {
      cour2 = head2;
      while(cour2 != NULL){
	values[cour1->val.degree+cour2->val.degree] += cour1->val.coef*cour2->val.coef; //on ajoute le résultat dans le tableau au bon index
	cour2 = cour2->next;
      }
      cour1 = cour1->next;
    }
    for(i = maxdeg; i > -1; i--){ //parcour du tableau et création du nouveau polynôme en conséquence
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
