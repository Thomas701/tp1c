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
	printf("\nDerive of polynomial becoming null : \n");
	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	list = LL_create_cell(&v1);
	LL_print_list(file, &list, monom_save2file);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "5.110 0\n") );

	
	
	poly_derive(&list);
	// LL_print_list(stdout, &list, monom_save2file);
	CHECK (list == NULL);
	
	
	LL_free_list(&list);
}


TEST(Poly_addition) { // test sur l'addition de deux polymones
	cell_t *poly;
	cell_t *poly2;

	printf("\nAdd two polynomial same coef: \n");
	
	LL_create_list_fromFileName(&poly, "test.txt");
	LL_create_list_fromFileName(&poly2, "test.txt");

	REQUIRE(poly != NULL && poly2 != NULL);
	// LL_print_list(stdout, &poly, &monom_save2file);
	poly_add(&poly, &poly2);
	REQUIRE(poly != NULL);

	char buffer[1024] = "";
        FILE * file = fmemopen(buffer, 1024, "w");
        REQUIRE ( NULL != file);

        LL_print_list(file, &poly, &monom_save2file);
        fclose(file);
	// printf("%s\n", buffer);
        CHECK(0 == strcmp(buffer, "10.826 2\n12.024 3\n17.000 8\n"));

	LL_create_list_fromFileName(&poly2, "test2.txt");

	printf("\nAdd two polynomial different coef: \n");
	
	// printf("Liste 2 : \n");
	// LL_print_list(stdout, &poly2, &monom_save2file);
	poly_add(&poly, &poly2);
	REQUIRE(poly != NULL);


        file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

        LL_print_list(file, &poly, &monom_save2file);
        fclose(file);
	//printf("liste 1 : %s\n", buffer);
        CHECK(0 == strcmp(buffer, "1.233 1\n10.826 2\n-110.988 3\n345.500 7\n17.000 8\n"));
	
	LL_free_list(&poly);

	printf("\nAdd two polynomial that lead to 0: \n");
	
	LL_create_list_fromFileName(&poly, "test.txt");
	LL_create_list_fromFileName(&poly2, "testNeg.txt");

	REQUIRE(poly != NULL && poly2 != NULL);
	// LL_print_list(stdout, &poly, &monom_save2file);

	poly_add(&poly, &poly2);


        CHECK(poly == NULL);

	LL_free_list(&poly);
	
}


TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
	cell_t *poly;
	cell_t *poly2;
	cell_t *poly3;

	LL_create_list_fromFileName(&poly, "test.txt");
	LL_create_list_fromFileName(&poly2, "test.txt");

	REQUIRE(poly != NULL && poly2 != NULL);
	// LL_print_list(stdout, &poly, &monom_save2file);
	poly3 = poly_prod(poly, poly2);
	REQUIRE(poly != NULL);

	char buffer[1024] = "";
        FILE * file = fmemopen(buffer, 1024, "w");
        REQUIRE ( NULL != file);

        LL_print_list(file, &poly3, &monom_save2file);
        fclose(file);
	// printf("%s\n", buffer);
        CHECK(0 == strcmp(buffer, "29.301 4\n65.086 5\n36.144 6\n92.021 10\n102.204 11\n72.250 16\n"));

	
	LL_free_list(&poly);
	LL_free_list(&poly2);
	LL_free_list(&poly3);
}


TEST(LL_save_list_toFileName) { // test pour l'ecriture d'un polynome dans un
				// fichier
  cell_t *poly;
  cell_t *poly2;
  cell_t *poly3;
  
  LL_create_list_fromFileName(&poly, "test.txt");
  LL_create_list_fromFileName(&poly2, "listScient.txt");
  
  REQUIRE(poly != NULL && poly2 != NULL);
  // LL_print_list(stdout, &poly, &monom_save2file);
  poly3 = poly_prod(poly, poly2);
  REQUIRE(poly != NULL);

  LL_save_list_toFileName(&poly3, "poly3.txt", &monom_save2file);

  LL_free_list(&poly);
  LL_free_list(&poly2);

  LL_create_list_fromFileName(&poly, "poly3.txt");
  
  char buffer[1024] = "";
  char buffer2[1024] = "";
  FILE * file = fmemopen(buffer, 1024, "w");
  REQUIRE ( NULL != file);
  LL_print_list(file, &poly3, &monom_save2file);
  fclose(file);
  file = fmemopen(buffer2, 1024, "w");
  REQUIRE ( NULL != file);
  LL_print_list(file, &poly, &monom_save2file);
  fclose(file);
  // printf("%s\n", buffer);
  CHECK(0 == strcmp(buffer, buffer2));

	
  LL_free_list(&poly);
  LL_free_list(&poly3);  
  
}


END_TEST_GROUP(polynomial)

int main(void) {
	RUN_TEST_GROUP(polynomial);
	return EXIT_SUCCESS;
}
