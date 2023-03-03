/**
 * @file linkedList_main.c
 * @brief Programme pour les tests de fonctions de gestion de liste chainee
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(linkedList)

TEST(monom_degree_cmp) {
        monom_t v1 = {5.11, 7};
        monom_t v2 = {3., 5};
        monom_t v3 = {5.25, 7};

        printf("\nComparaison des monomes : \n");
        CHECK( monom_degree_cmp(&v1, &v2) > 0 );
        CHECK( monom_degree_cmp(&v2, &v1) < 0 );
        CHECK( monom_degree_cmp(&v1, &v3) == 0 );
}

TEST(monom_save2file) {
        monom_t v = {5., 7};

	printf("\nPrint of a polynome : \n");
	
        // creation du flux de texte => buffer
        char buffer[1024] = "";
        FILE * file = fmemopen(buffer, 1024, "w");
        REQUIRE ( NULL != file);

        monom_save2file(file, &v);

        fclose(file);

        CHECK( 0 == strcmp(buffer, "5.000 7\n") );
}


TEST(LL_init_list) {
        cell_t *list;

        printf("\nInitialization of the linked list : \n");
        LL_init_list(&list);
        REQUIRE ( list == NULL );
}


TEST(LL_create_cell) { // test de creation de cellule
        cell_t *new = NULL;
        monom_t m1 = {3.245, 17};

        printf("\nCreate a new cell (3.245 17) : \n");
        new = LL_create_cell(&m1);
        REQUIRE ( NULL != new );
        CHECK ( NULL == new->next );

        char buffer[1024] = "";
        FILE * file = fmemopen(buffer, 1024, "w");
        REQUIRE ( NULL != file);

        monom_save2file(file, &(new->val));
        fclose(file);
        printf("buf = %s\n", buffer);
        CHECK( 0 == strcmp(buffer, "3.245 17\n") );
	free(new);
}

// test d'insertion de cellule - liste a une cellule
TEST(LL_add_cell1) {
        cell_t *list = NULL;
        cell_t *new = NULL;
        monom_t m1 = {3.45, 17};

        printf("\nAdd a cell to a linked list : \n");

        new = LL_create_cell(&m1);
        REQUIRE ( new != NULL );

        LL_add_cell(&list, new);
        CHECK( list == new );

        CHECK( list->val.coef == 3.45 );  // 3.45 est une valeur non approchee
        CHECK( list->val.degree == 17 );
        CHECK( list->next == NULL );

        free(list); // liberer la cellule
        list = NULL;
}

// test d'insertion de cellule - liste a deux cellules
TEST(LL_add_cell2) {
        cell_t *list = NULL;
        cell_t *new = NULL;
        monom_t m1 = {3.45, 17};
        monom_t m2 = {25.8, 9};

        printf("\nAdd two cells to a linked list : \n");

        new = LL_create_cell(&m1);
        REQUIRE ( new != NULL );
        LL_add_cell(&list, new);
        CHECK( list == new );

        new = LL_create_cell(&m2);
        REQUIRE ( new != NULL );
        LL_add_cell(&list, new);
        CHECK( list == new );

        // tester les valeurs de la liste
        char buffer[1024] = "";
        FILE * file = fmemopen(buffer, 1024, "w");
        REQUIRE ( NULL != file);

        LL_print_list(file, &list, &monom_save2file);
        fclose(file);
        CHECK(0 == strcmp(buffer, "25.800 9\n3.450 17\n"));

        // liberer la liste
        LL_free_list(&list);
}

// test d'insertion de cellule - liste a trois cellules
TEST(LL_add_cell3) {
        cell_t *list = NULL;
        cell_t *new = NULL;
        monom_t m1 = {3.245, 17};
        monom_t m2 = {25.8, 9};
        monom_t m3 = {12.4, 3};

        printf("\nAdd three cells to a linked list : \n");

        new = LL_create_cell(&m1);
        REQUIRE ( new != NULL );
        LL_add_cell(&list, new);
        CHECK( list == new );

        new = LL_create_cell(&m2);
        REQUIRE ( new != NULL );
        LL_add_cell(&list, new);
        CHECK( list == new );

        // ajouter le m3 en tete de la liste
        new = LL_create_cell(&m3);
        REQUIRE( new != NULL);
        LL_add_cell(&list, new);
        CHECK ( list == new );
	
        // tester les valeurs de la liste
        CHECK ( list->val.degree == m3.degree);
        CHECK ( list->next->val.degree == m2.degree);
        CHECK ( list->next->next->val.degree == m1.degree);
	CHECK ( list->next->next->next == NULL);

        // liberer la liste
        LL_free_list(&list);
        REQUIRE (NULL == list);
}


// test pour la creation d'un polynome a partir d'un fichier - exemple
TEST(LL_create_list_fromFileName0) {
        cell_t *list;

        printf("\nCreate a linked list from file that does not exist : \n");

        LL_create_list_fromFileName(&list, "notExist.txt");
        CHECK( NULL == list );
}

// test pour la creation d'un polynome a partir d'un fichier
TEST(LL_create_list_fromFileName) {
        cell_t *list;

	printf("\nCreate an empty linked list from file : \n");
	LL_create_list_fromFileName(&list, "empty.txt");
	CHECK(NULL == list);

	printf("\nCreate a linked list from file : \n");
        LL_create_list_fromFileName(&list, "test.txt");
        REQUIRE (NULL != list);
        CHECK( list->val.coef == 5.413);
        CHECK( list->val.degree == 2);
        CHECK( list->next->val.coef == 6.012);
        CHECK( list->next->val.degree == 3);
        CHECK( list->next->next->val.coef == 8.500);
        CHECK( list->next->next->val.degree == 8);
	LL_free_list(&list);

	printf("\nCreate a long linked list from file written in scientific way with negatives : \n");
	LL_create_list_fromFileName(&list, "listScient.txt");
        REQUIRE (NULL != list);
	// LL_print_list(stdout, &list, &monom_save2file);
	CHECK( list->val.coef == 0.0003);
        CHECK( list->val.degree == 1);
	CHECK( list->next->val.coef == 1200);
        CHECK( list->next->val.degree == 2);
	CHECK( list->next->next->val.coef == 0.000123);
        CHECK( list->next->next->val.degree == 3);
	CHECK( list->next->next->next->val.coef == 12300);
        CHECK( list->next->next->next->val.degree == 4);
	CHECK( list->next->next->next->next->val.coef == 3.21);
        CHECK( list->next->next->next->next->val.degree == 5);
	CHECK( list->next->next->next->next->next->val.coef == 6660000);
        CHECK( list->next->next->next->next->next->val.degree == 6);
	CHECK( list->next->next->next->next->next->next->val.coef == 0.0000066);
        CHECK( list->next->next->next->next->next->next->val.degree == 7);
	CHECK( list->next->next->next->next->next->next->next->val.coef == 0.42);
        CHECK( list->next->next->next->next->next->next->next->val.degree == 8);
	CHECK( list->next->next->next->next->next->next->next->next->val.coef == 0.00000000426);
        CHECK( list->next->next->next->next->next->next->next->next->val.degree == 10);
	CHECK( list->next->next->next->next->next->next->next->next->next->val.coef == -3300);
        CHECK( list->next->next->next->next->next->next->next->next->next->val.degree == 12);
	CHECK( list->next->next->next->next->next->next->next->next->next->next->val.coef == 11);
        CHECK( list->next->next->next->next->next->next->next->next->next->next->val.degree == 42);
	LL_free_list(&list);
}


TEST(LL_print_list) { // test pour l'ecriture d'un polynome sur un flux de sortie
	cell_t *list;

        // Test de la fonction à partir d'une liste vide
	printf("\nPrint of an empty list : \n");
	LL_create_list_fromFileName(&list, "empty.txt");
	char buffer[1024] = "";
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);
	LL_print_list(file,&list, monom_save2file);
	fclose(file);
	CHECK(0 == strcmp(buffer,""));	
	LL_free_list(&list);

	// Test d'une liste "normale"
	printf("\nPrint of a normale list : \n");
	LL_create_list_fromFileName(&list, "test.txt");
	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);
	LL_print_list(file,&list, monom_save2file);
	fclose(file);
	CHECK(0 == strcmp(buffer,"5.413 2\n6.012 3\n8.500 8\n"));	
	LL_free_list(&list);

        // Test d'une longue liste avec des nombres petits, grands, et négatifs
	printf("\nPrint of a long list with little, big and negatives numbers : \n");
	LL_create_list_fromFileName(&list, "listScient.txt");
	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);
	LL_print_list(file,&list, monom_save2file);
	fclose(file);
	CHECK(0 == strcmp(buffer,"0.000 1\n1200.000 2\n0.000 3\n12300.000 4\n3.210 5\n6660000.000 6\n0.000 7\n0.420 8\n0.000 10\n-3300.000 12\n11.000 42\n"));	
	LL_free_list(&list);
}

TEST(LL_search_prev) { // test pour la fonction de recherche d'une valeur
	cell_t *list;
	cell_t ** cel;

	printf("\nSearch of a standard cell : \n");
        LL_create_list_fromFileName(&list, "test.txt");
        REQUIRE (NULL != list);
	// LL_print_list(stdout, &list, &monom_save2file);
	cel = LL_search_prev(&list, (&list->next->next->val), &monom_degree_cmp);
	REQUIRE(*cel != NULL);
	CHECK(*cel == list->next->next);

	printf("\nSearch of a non-existing cell : \n");	
	monom_t tmp = {4, 100};
	cel = LL_search_prev(&list, (&tmp), &monom_degree_cmp);
	REQUIRE(*cel == NULL);

	printf("\nSearch of the first cell : \n");	
	cel = LL_search_prev(&list, (&list->val), &monom_degree_cmp);
	REQUIRE(*cel != NULL);
	CHECK(*cel == list);
	
	LL_free_list(&list);
	
}


TEST(LL_del_cell) { // test de la suppression d'un element
	cell_t *list;

        printf("\nDelete a standard cell : \n");
	LL_create_list_fromFileName(&list, "test.txt");
        REQUIRE (NULL != list);
	LL_del_cell(&(list->next));
	CHECK( list->val.coef == 5.413);
        CHECK( list->val.degree == 2);
        CHECK( list->next->val.coef == 8.500);
        CHECK( list->next->val.degree == 8);
	
        printf("\nDelete the first cell : \n");
	LL_del_cell(&(list));
	CHECK( list->val.coef == 8.500);
        CHECK( list->val.degree == 8);

	printf("\nDelete not existing cell : \n");
	LL_del_cell(&(list->next));

        printf("\nDelete the only cell of a list : \n");
	LL_del_cell(&(list));
	CHECK(list == NULL);
	
	LL_free_list(&list);
}

TEST(LL_free_list) { // test de la liberation de liste
	cell_t *list;

	printf("\nCreate and free a list : \n");
	LL_create_list_fromFileName(&list, "test.txt");
        REQUIRE (NULL != list);
	LL_free_list(&list);
	CHECK(list == NULL);

	printf("\nfree an empty list : \n");
	LL_free_list(&list);
	CHECK(list == NULL);
	  
	
}

TEST(LL_save_list_toFileName) { // BONUS - 3eme Seance
  cell_t *list;
  cell_t *list2;

  printf("\nCreate and write a list in file \"testingFonc.txt\" : \n");
  LL_create_list_fromFileName(&list, "listScient.txt");
  REQUIRE(list != NULL);
  // LL_print_list(stdout, &poly, &monom_save2file);
  LL_save_list_toFileName(&list, "testingFonc.txt", &monom_save2file);

  printf("\nReading the file \"testingFonc.txt\" and compare to the original : \n");
  LL_create_list_fromFileName(&list2, "testingFonc.txt");
  char buffer[1024] = "";
  char buffer2[1024] = "";
  FILE * file = fmemopen(buffer, 1024, "w");
  REQUIRE ( NULL != file);
  LL_print_list(file, &list, &monom_save2file);
  fclose(file);
  file = fmemopen(buffer2, 1024, "w");
  REQUIRE ( NULL != file);
  LL_print_list(file, &list2, &monom_save2file);
  fclose(file);
  // printf("%s\n", buffer);
  CHECK(0 == strcmp(buffer, buffer2));
  
  LL_free_list(&list);
  LL_free_list(&list2);  
}


END_TEST_GROUP(linkedList)

int main(void) {
	RUN_TEST_GROUP(linkedList);
	return EXIT_SUCCESS;
}
