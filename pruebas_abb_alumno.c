#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pruebas_abb_vacio() {
	// Creo un ABB y chequeo sus condiciones iniciales
	printf(" # Pruebas ABB vacio #\n");
	abb_t* abb = abb_crear(NULL, NULL);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB inicial es 0", !abb_cantidad(abb));
	print_test("ABB borrar clave 'a' es invalido", !abb_borrar(abb, "a"));
	print_test("ABB obtener clave 'a' es invalido", !abb_obtener(abb, "a"));
	print_test("ABB 'a' pertenece es falso", !abb_pertenece(abb, "a"));
	abb_destruir(abb);
}

void pruebas_iter_abb_vacio() {
	// Creo un iterador para un ABB vacio y chequeo sus condiciones iniciales
	printf(" # Pruebas iterador en ABB vacio #\n");
	abb_t* abb = abb_crear(NULL, NULL);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB es 0", !abb_cantidad(abb));
	abb_iter_t* iter = abb_iter_in_crear(abb);
	print_test("Iterador creado", iter);
	print_test("Avanzar en iterador es invalido", !abb_iter_in_avanzar(iter));
	print_test("Obtener en iterador es invalido", !abb_iter_in_ver_actual(iter));
	print_test("Iterador esta al final es correcto", abb_iter_in_al_final(iter));
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

void pruebas_abb_guardar () {
	// Prueba de guardar valores en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	char* clave_a = "a";
	char* clave_b = "b";
	char* clave_c = "c";
	char* clave_d = "d";
	char* valor_a = "letra a";
	char* valor_b = "letra b";
	char* valor_c = "letra_c";
	char* valor_d = "letra_d";
	printf(" # Pruebas guardar en ABB #\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB es 0", !abb_cantidad(abb));
	print_test("Guardo clave 'a'", abb_guardar(abb, clave_a, valor_a));
	print_test("Cantidad ABB es 1", abb_cantidad(abb) == 1);
	print_test("Guardo clave 'd'", abb_guardar(abb, clave_d, valor_d));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_c, valor_c));
	print_test("Cantidad ABB es 3", abb_cantidad(abb) == 3);
	print_test("Guardo clave 'b'", abb_guardar(abb, clave_b, valor_b));
	print_test("Cantidad ABB es 4", abb_cantidad(abb) == 4);
	print_test("Obtener 'b' es correcto", abb_obtener(abb, clave_b) == valor_b);
	print_test("Obtener 'a' es correcto", abb_obtener(abb, clave_a) == valor_a);
	print_test("Pertenece 'd' es correcto", abb_pertenece(abb, clave_d));
	print_test("Pertenece 'c' es correcto", abb_pertenece(abb, clave_c));
	abb_destruir(abb);
}

void pruebas_abb_reemplazar() {
	// Prueba de reemplazar valores en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	char* clave_m = "m";
	char* clave_c = "c";
	char* valor_m = "letra m";
	char* valor_c = "letra c";
	printf(" # Pruebas reemplazar en ABB #\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB es 0", !abb_cantidad(abb));
	print_test("Guardo clave 'm'", abb_guardar(abb, clave_m, valor_m));
	print_test("Cantidad ABB es 1", abb_cantidad(abb) == 1);
	print_test("Valor de 'm' es correcto", abb_obtener(abb, clave_m) == valor_m);
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_c, valor_c));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Valor de 'c' es correcto", abb_obtener(abb, clave_c) == valor_c);
	print_test("Guardo clave 'm' con valor de 'c'", abb_guardar(abb, clave_m, valor_c));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Guardo clave 'c' con valor de 'm'", abb_guardar(abb, clave_c, valor_m));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Valor de 'm' es el nuevo valor", abb_obtener(abb, clave_m) == valor_c);
	print_test("Valor de 'c' es el nuevo valor", abb_obtener(abb, clave_c) == valor_m);
	abb_destruir(abb);
}

void pruebas_abb_reemplazar_con_destruir() {
	// Prueba de reemplazar valores en el ABB con free
	// Como comparador uso STRCMP de la libreria string.h
	char* clave_m = "m";
	char* clave_c = "c";
	char* valor_m = malloc(sizeof(char) * 5);
	char* valor_m_nuevo = malloc(sizeof(char) * 10);
	char* valor_c = malloc(sizeof(int));
	char* valor_c_nuevo = malloc(sizeof(size_t));
	printf(" # Pruebas reemplazar en ABB con destruir 'free' #\n");
	abb_t* abb = abb_crear(strcmp, free);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB es 0", !abb_cantidad(abb));
	print_test("Guardo clave 'm'", abb_guardar(abb, clave_m, valor_m));
	print_test("Cantidad ABB es 1", abb_cantidad(abb) == 1);
	print_test("Valor de 'm' es correcto", abb_obtener(abb, clave_m) == valor_m);
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_c, valor_c));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Valor de 'c' es correcto", abb_obtener(abb, clave_c) == valor_c);
	print_test("Guardo clave 'm' con valor nuevo", abb_guardar(abb, clave_m, valor_m_nuevo));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Guardo clave 'c' con valor nuevo", abb_guardar(abb, clave_c, valor_c_nuevo));
	print_test("Cantidad ABB es 2", abb_cantidad(abb) == 2);
	print_test("Valor de 'm' es el nuevo valor", abb_obtener(abb, clave_m) == valor_m_nuevo);
	print_test("Valor de 'c' es el nuevo valor", abb_obtener(abb, clave_c) == valor_c_nuevo);
	abb_destruir(abb);
}

void pruebas_abb_borrar() {
	// Prueba de borrar valores en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	char* clave_a = "a";
	char* valor_a = "letra a";
	char* clave_b = "b";
	char* valor_b = "letra b";
	char* clave_c = "c";
	char* valor_c = "letra c";
	char* clave_d = "d";
	char* valor_d = "letra d";
	char* clave_e = "e";
	char* valor_e = "letra e";
	char* clave_f = "f";
	char* valor_f = "letra f";
	char* clave_g = "g";
	char* valor_g = "letra g";
	char* clave_h = "h";
	char* valor_h = "letra h";
	char* clave_i = "i";
	char* valor_i = "letra i";
	char* clave_j = "j";
	char* valor_j = "letra j";
	printf(" # Pruebas reemplazar en ABB #\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Cantidad ABB es 0", !abb_cantidad(abb));
	print_test("Guardo clave 'e'", abb_guardar(abb, clave_e, valor_e));
	print_test("Guardo clave 'b'", abb_guardar(abb, clave_b, valor_b));
	print_test("Guardo clave 'a'", abb_guardar(abb, clave_a, valor_a));
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_c, valor_c));
	print_test("Guardo clave 'd'", abb_guardar(abb, clave_d, valor_d));
	print_test("Guardo clave 'h'", abb_guardar(abb, clave_h, valor_h));
	print_test("Guardo clave 'i'", abb_guardar(abb, clave_i, valor_i));
	print_test("Guardo clave 'g'", abb_guardar(abb, clave_g, valor_g));
	print_test("Guardo clave 'f'", abb_guardar(abb, clave_f, valor_f));
	print_test("Guardo clave 'j'", abb_guardar(abb, clave_j, valor_j));
	print_test("Cantidad ABB es 10", abb_cantidad(abb) == 10);
	print_test("Borro hoja 'j'", abb_borrar(abb, clave_j) == valor_j);
	print_test("Cantidad ABB es 9", abb_cantidad(abb) == 9);
	print_test("'j' no pertence", !abb_pertenece(abb,clave_j));
	print_test("Borro 'c', tiene un hijo", abb_borrar(abb, clave_c) == valor_c);
	print_test("Cantidad ABB es 8", abb_cantidad(abb) == 8);
	print_test("'c' no pertence", !abb_obtener(abb, clave_c));
	print_test("El hijo de 'c', 'd', pertence", abb_obtener(abb, clave_d) == valor_d);
	print_test("Borro 'e', es la raiz y tiene 2 hijos", abb_borrar(abb, clave_e) == valor_e);
	print_test("Cantidad ABB es 7", abb_cantidad(abb) == 7);
	print_test("'e' no pertence", !abb_pertenece(abb, clave_e));
	print_test("Los hijos de 'e', 'b' y 'h', pertenecen", abb_pertenece(abb, clave_b) && abb_pertenece(abb, clave_h));
	print_test("Borro 'h' tiene 2 hijos", abb_borrar(abb, clave_h) == valor_h);
	print_test("Cantidad ABB es 6", abb_cantidad(abb) == 6);
	print_test("'h' no pertence", !abb_pertenece(abb, clave_h));
	print_test("Los hijos de 'h', 'g' y 'i', pertenecen", abb_pertenece(abb, clave_g) && abb_pertenece(abb, clave_i));
	print_test("Borro 'i'", abb_borrar(abb, clave_i) == valor_i);
	print_test("Borro 'i' de nuevo es null", !abb_borrar(abb, clave_i));
	print_test("'i' no pertenece", !abb_pertenece(abb, clave_i));
	print_test("No se puede obtener 'i'", !abb_obtener(abb, clave_i));
	abb_destruir(abb);
}

void pruebas_abb_clave_vacia() {
	// Prueba de usar clave vacia en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	printf(" # Pruebas con clave vacia en ABB #\n");
	char *clave_vac = "";
	char* valor_vac = "";
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Guardar clave vacia", abb_guardar(abb, clave_vac, valor_vac));
	print_test("Cantidad es 1", abb_cantidad(abb) == 1);
	print_test("Obtener clave vacia es correcto", abb_obtener(abb, clave_vac) == valor_vac);
	print_test("Pertenece clave vacia es correcto", abb_pertenece(abb, clave_vac));
	print_test("Borrar clave vacia es correcto", abb_borrar(abb, clave_vac) == valor_vac);
	print_test("Cantidad es 0", abb_cantidad(abb) == 0);
	abb_destruir(abb);
}

void pruebas_abb_valor_null() {
	// Prueba de usar valor vacio en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	printf(" # Pruebas con valor NULL en ABB #\n");
	char* clave_vac = "";
	char* valor_null = NULL;
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Guardar clave", abb_guardar(abb, clave_vac, valor_null));
	print_test("Cantidad es 1", abb_cantidad(abb) == 1);
	print_test("Obtener clave es correcto", abb_obtener(abb, clave_vac) == valor_null);
	print_test("Pertenece clave es correcto", abb_pertenece(abb, clave_vac));
	print_test("Borrar valor NULL es correcto", abb_borrar(abb, clave_vac) == valor_null);
	print_test("Cantidad es 0", abb_cantidad(abb) == 0);
	abb_destruir(abb);
}

bool ver_tres_nodos(const char* dato, void* valor, void* extra) {
	int* contador = extra;
	if((*contador) > 2) return false;
	printf("%d. %s ~ %s\n", ++(*contador), dato, (char*) valor);
	return true;
}

void pruebas_abb_volumen(size_t largo, bool debug) {
	// Pruebas ABB volumen, utilizando las pruebas del hash como base
	printf(" # Pruebas de volumen en ABB #\n");
	abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);
}

bool corte_rama_izquierda(const char* dato, void* valor, void* extra) {
	/*dato = dato;
	valor = valor;
	extra = extra;*/
	printf("%s ~ %s\n", dato, (char*)valor);
	return false;
}

bool corte_rama_der_izq(const char* dato, void* valor, void* extra) {
	if(strcmp(dato, (char*)extra) != 0) {
		printf("%s ~ %s\n", dato, (char*)valor);
		return true;
	}
	printf("%s ~ %s\n", dato, (char*)valor);
	return false;
}

void pruebas_iter_int_abb() {
	// Prueba de iterador interno en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	printf(" # Pruebas con iterador interno en ABB #\n");
	char* clave_a = "a";
	char* clave_b = "b";
	char* clave_c = "c";
	char* clave_d = "d";
	char* valor_a = "letra a";
	char* valor_b = "letra b";
	char* valor_c = "letra c";
	char* valor_d = "letra d";
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Guardo clave 'd'", abb_guardar(abb, clave_d, valor_d));
	print_test("Guardo clave 'b'", abb_guardar(abb, clave_b, valor_b));
	print_test("Guardo clave 'a'", abb_guardar(abb, clave_a, valor_a));
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_c, valor_c));
	print_test("Cantidad ABB es 4", abb_cantidad(abb) == 4);
	int numero_items = 0;
	printf(" * Pruebas corte por numero *\n");
	abb_in_order(abb, ver_tres_nodos, &numero_items);
	printf(" * Pruebas corte rama izquierda *\n");
	abb_in_order(abb, corte_rama_izquierda, NULL);
	printf(" * Pruebas corte rama derecha de izquierda *\n");
	abb_in_order(abb, corte_rama_der_izq, clave_c);
	abb_destruir(abb);
}

void pruebas_iter_ext_abb() {
	// Prueba de iterador externo en el ABB
	// Como comparador uso STRCMP de la libreria string.h
	char* clave_b = "b";
	char* valor_b = "letra b";
	char* clave_e = "e";
	char* valor_e = "letra e";
	char* clave_h = "h";
	char* valor_h = "letra h";
	printf(" # Pruebas iterador externo en ABB #\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("ABB creado", abb);
	print_test("Guardo clave 'e'", abb_guardar(abb, clave_e, valor_e));
	print_test("Guardo clave 'h'", abb_guardar(abb, clave_h, valor_h));
	print_test("Guardo clave 'b'", abb_guardar(abb, clave_b, valor_b));
	print_test("Cantidad ABB es 3", abb_cantidad(abb) == 3);
	abb_iter_t* iter = abb_iter_in_crear(abb);
	print_test("El iterador esta al final es falso", !abb_iter_in_al_final(iter));
	print_test("El valor actual es el valor de 'b'", strcmp(abb_iter_in_ver_actual(iter), clave_b) == 0);
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));
	print_test("El valor actual es el valor de 'e'", strcmp(abb_iter_in_ver_actual(iter), clave_e) == 0);
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));
	print_test("El valor actual es el valor de 'h'", strcmp(abb_iter_in_ver_actual(iter), clave_h) == 0);
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));
	print_test("El iterador esta al final es correcto", abb_iter_in_al_final(iter));
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

void pruebas_iter_abb_volumen(size_t largo) {
		// Pruebas de volumen en iterador externo de ABB, utilizando las pruebas del hash como base
		printf(" # Pruebas de volumen en iterador externo del ABB #\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el ABB */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba ABB iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba ABB iteración en volumen", ok);
    print_test("Prueba ABB iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba ABB iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba ABB iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

int comparador_aux (const char* clave1, const char* clave2) {
	int largo1 = (int)strlen(clave1);
	int largo2 = (int)strlen(clave2);
	return largo1 - largo2;
}

void pruebas_abb_cmp_aux() {
	printf(" # Pruebas ABB con funcion auxiliar como comparador #\n");
	abb_t* abb = abb_crear(comparador_aux, NULL);
	print_test("ABB creado", abb);
	char* clave_largo_1 = "c";
	char* valor_largo_1 = "una c";
	char* clave_largo_2 = "bb";
	char* valor_largo_2 = "dos b";
	char* clave_largo_3 = "aaa";
	char* valor_largo_3 = "tres a";
	print_test("Guardo clave 'bb'", abb_guardar(abb, clave_largo_2, valor_largo_2));
	print_test("Guardo clave 'c'", abb_guardar(abb, clave_largo_1, valor_largo_1));
	print_test("Guardo clave 'aaa'", abb_guardar(abb, clave_largo_3, valor_largo_3));
	print_test("Cantidad ABB es 3", abb_cantidad(abb) == 3);
	printf(" * Usamos iterador interno para ver los elementos *\n");
	int numero_items = 0;
	abb_in_order(abb, ver_tres_nodos, &numero_items);
	abb_destruir(abb);
}

void abb_destruir_aux(void* aux) {
	abb_destruir(aux);
}

void pruebas_abb_destruir_abb() {
	printf(" # Pruebas ABB usando ABB_DESTRUIR como destructor #\n");
	abb_t* abb = abb_crear(strcmp, abb_destruir_aux);
	print_test("ABB creado", abb);
	abb_t* abb_aux = abb_crear(NULL, NULL);
	print_test("ABB auxiliar creado", abb_aux);
	print_test("Guardo un ABB auxiliar en el ABB principal", abb_guardar(abb, "arbol_aux", abb_aux));
	abb_t* abb_extra = abb_crear(NULL, NULL);
	print_test("ABB extra creado", abb_extra);
	print_test("Reemplazo el elemento guardado para corroborar que funciona el destruir", abb_guardar(abb, "arbol_aux", abb_extra));
	abb_destruir(abb);
}

void pruebas_abb_alumno(void) {
	pruebas_abb_vacio();
	pruebas_iter_abb_vacio();
	pruebas_abb_guardar();
	pruebas_abb_reemplazar();
	pruebas_abb_reemplazar_con_destruir();
	pruebas_abb_borrar();
	pruebas_abb_clave_vacia();
	pruebas_abb_valor_null();
	pruebas_abb_volumen(1000, true);
	pruebas_iter_int_abb();
	pruebas_iter_ext_abb();
	pruebas_iter_abb_volumen(1000);
	pruebas_abb_cmp_aux();
	pruebas_abb_destruir_abb();
	return;
}
