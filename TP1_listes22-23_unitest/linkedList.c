/**
 * @file linkedList.c
 * @brief Implementation file of linked list module
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

/** Example
 * @fn void LL_init_list(cell_t **adrHeadPt)
 * @brief Initialize a void list
 * @param [in, out] adrHeadPt address of head pointer of the list 
 */
void LL_init_list(cell_t ** adrHeadPt)
{
    *adrHeadPt = NULL;
}


/** TO DO
 * @brief Create a new cell for linked list from its data 
 * @param [in] xxx address of the data
 * @return address of the new cell
 */
cell_t * LL_create_cell(monom_t * mon)
{
    cell_t * cellule = (cell_t *) malloc(sizeof(cell_t));
    cellule->val.coef = mon->coef;
    cellule->val.degree = mon->degree;
    cellule->next = NULL;
    return cellule;
}


/** TO DO
 * @brief Insert a cell into a linked list at the given position
 * @param [in, out]  xxx address of previous pointer of the cell
 * @param [in]  xxx address of the cell to be added to the linked list
 */
void LL_add_cell(cell_t ** precedent, cell_t * cellule)
{
    cellule->next = (*precedent);
    (*precedent) = cellule;
}


/** TO DO
 * @brief Create a linked list from a file
 * @param [in, out] xxx address of head pointer of a linked list
 * @param [in] xxx name of a file containing the data for a linked list
 * @param xxx fonction pointer for comparison of two cell's value
 * @return head pointer of the linked list
 */
void LL_create_list_fromFileName(cell_t ** head, char * name, int (*pf) (monom_t *, monom_t *))
{
    //#Declaration
    LL_init_list(head); // met *head à NULL
    FILE * f;
    cell_t * cellule;;
    double value;
    int degrees;
    //#Initialisation
    f = fopen(name, "r");
    char *file_contents = malloc(sizeof(char)*60);
    //#code
    if (f == NULL) //si le fichier n'existe pas, on ne fait rien
        return;
    while (fscanf(f, "%[^\n] ", file_contents) != EOF) 
    {
        monom_t * mon = (monom_t*) malloc(sizeof(monom_t));
        sscanf(file_contents,"%lf %d",&value, &degrees);
        mon->coef = value; //printf("monCoef: %.3f, monDegree: %d\n", value, degrees);
        mon->degree = degrees;
        if ((*head) == NULL)
        {
            cellule = LL_create_cell(mon);
            (*head) = cellule;
        }
        else
        {
            cell_t * cellule2 = LL_create_cell(mon);
            cellule->next = cellule2;
            cellule = cellule2;
        }
    }
    return;
}

/** TO DO
 * @brief Print/Write the linked list on/to an output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx head pointer of a linked list
 * @param xxx fonction pointer for printing the data of a cell on an output stream
 */
void LL_print_list(FILE * f, cell_t ** head, void (*pf) (FILE *, monom_t *))
{
  cell_t * cellule = *head;
  while (cellule != NULL)
    {
      (*pf)(f, &(cellule->val));
      cellule = cellule->next;
    }
}

/** TO DO
 * @brief Save a linked list into a file
 * @param [in, out] xxx head pointer of a linked list
 * @param [in] xxx name of the backup file
 * @param xxx fonction pointer for writing the data of a cell to a output stream
 */
void LL_save_list_toFileName(cell_t ** head, char * name, void (*pf)(FILE * ,monom_t *))
{
    FILE * f;
    f = fopen(name, "w");
    LL_print_list(f, head, pf);
    fclose(f);
}


/** TO DO
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] xxx address of the head pointer
 * @param [in] xxx address of the value to search
 * @param  xxx fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */
cell_t ** LL_search_prev(cell_t ** head, monom_t * value, int (*pf) (monom_t *, monom_t *))
{
    cell_t ** cellule = head;
    //#
    while (*cellule != NULL && (*pf) (value, &((*cellule)->val)) >= 0 )
    {
        cellule = &((*cellule)->next);
    }
    return cellule;
}


/** TO DO
 * @brief Delete a cell from a linked list
 * @param [in, out] xxx address of the previous pointer of the cell to delete
 */
void LL_del_cell(cell_t ** precedent)
{
    cell_t * save = (*precedent);

    if ((*precedent) != NULL)
    {
        (*precedent) = (*precedent)->next;
        free(save);
    }
}


/** TO DO
 * @brief Free the memory location occupied by a linked list
 * @param [in, out] xxx address of head pointer of a linked list
 */
void LL_free_list(cell_t ** head)
{
    cell_t * suivant;
    while ((suivant) != NULL)
    {
        suivant = (*head)->next;
        free(*head);
        (*head) = suivant;
    }
}
