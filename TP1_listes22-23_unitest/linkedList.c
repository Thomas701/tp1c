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
    cellule->val = mon;
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
    if (*precedent == NULL)
        *precedent = cellule;
    else
    {
        cell_t * cellSave;
        cellSave = (*precedent)->next;
        (*precedent)->next = cellule;
        cellule->next = cellSave;
    }
    return;
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
    LL_init_list(head);
    FILE * f;
    cell_t * cellule = *head;
    double value;
    int degrees;

    f = fopen(name, "r");
    char *file_contents = malloc(sizeof(char)*63);

    while (fscanf(f, "%[^\n] ", file_contents) != EOF) 
    {
        monom_t * mon = (monom_t*) malloc(sizeof(monom_t));
        sscanf(file_contents,"%lf %d\n",&value, &degrees);
        mon->coef = value;
        mon->degree = degrees;
        if (cellule == NULL)
        {
            cell_t * cellule2 = LL_create_cell(mon);
            *cellule = *cellule2;
        }
        else
        {
            cell_t * cellule2 = LL_create_cell(mon);
            cellule->next = cellule2;
            cellule = cellule->next;
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
void LL_print_list(FILE * f, cell_t ** head, void (*pf) (cell_t *))
{
    // TO DO
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
    f = fopen(name, "a");
    cell_t * cellule = *head;
    while (cellule != NULL)
    {
        printf("TEST\n");
        (*pf)(f ,cellule->val);
        printf("TEST2\n");
        cellule = cellule->next;
    }
    return;
}


/** TO DO
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] xxx address of the head pointer
 * @param [in] xxx address of the value to search
 * @param  xxx fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */
// LL_search_prev()
// {
//     // TO DO
// }


/** TO DO
 * @brief Delete a cell from a linked list
 * @param [in, out] xxx address of the previous pointer of the cell to delete
 */
// LL_del_cell()
// {
//     // TO DO
// }


/** TO DO
 * @brief Free the memory location occupied by a linked list
 * @param [in, out] xxx address of head pointer of a linked list
 */
// LL_free_list()
// {
//     // TO DO
// }
