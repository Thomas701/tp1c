/**
 * @file polynomial_main.c
 * @brief Programme pour les tests des operations sur les polynomes
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "polynomial.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(polynomial)

TEST(LL_init_list) {
	cell_t *list;

	printf("\nInitialization of the linked list : \n");
	LL_init_list(&list);

	REQUIRE ( list == NULL );
}


TEST(Poly_derive1) {  
	cell_t *poly = NULL;
	FILE   *file = NULL;
	char   buffer[1024] = "";

	printf("\nDerive of polynomial 1 : \n");

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	LL_create_list_fromFileName(&poly, "poly1.txt");
	LL_print_list(file, &poly, monom_save2file);
	fclose(file);
	// LL_print_list(stdout, &poly, monom_save2file);
	// printf("\n");
	CHECK( 0 == strcmp(buffer, "5.000 1\n4.000 2\n5.000 3\n6.000 4\n3.000 5\n") );

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	poly_derive(&poly);
	LL_print_list(file, &poly, monom_save2file);
	fclose(file);
	// LL_save_list_toFile(stdout, poly, monom_save2file);
	// printf("\n");
	CHECK( 0 == strcmp(buffer, "5.000 0\n8.000 1\n15.000 2\n24.000 3\n15.000 4\n") );
	LL_free_list(&poly);
}

TEST(Poly_derive) { // test sur la derivation d'un polynome
	cell_t *list;
	monom_t v1 = {5.11, 0};
	char   buffer[1024] = "";
	FILE* file;
	
	LL_init_list(&list);

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	list = LL_create_cell(&v1);
	LL_print_list(file, &list, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "5.110 0\n") );

	
	
	poly_derive(&list);
	LL_print_list(stdout, &list, monom_save2file);
	CHECK (list == NULL);
	
	
	LL_free_list(&list);
}
/*

TEST(Poly_addition) { // test sur l'addition de deux polymones
	cell_t *list;

	//TO DO
}


TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
	cell_t *list;

	//TO DO
}


TEST(LL_save_list_toFileName) { // test pour l'ecriture d'un polynome dans un fichier
	cell_t *list;

	//TO DO
}
*/

END_TEST_GROUP(polynomial)

int main(void) {
	RUN_TEST_GROUP(polynomial);
	return EXIT_SUCCESS;
}
