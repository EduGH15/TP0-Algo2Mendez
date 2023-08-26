#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LONGITUD 100
#define MAX_NOMBRE 20

enum TIPO { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA };

struct ataque {
	char nombre[20];
	enum TIPO tipo;
	unsigned int poder;
};

void copiar_datos(char nuevo_dato[20], char datos[MAX_LONGITUD],int inicio ,int limite){
	for(int i = inicio; i < limite; i++){
		nuevo_dato[i] = datos[i];
	}
	nuevo_dato[limite] = 0;
}

void copiar_tipo(char* tipo, char datos[MAX_LONGITUD],int inicio ,int limite){
	for(int i = inicio; i < limite; i++){
		*tipo = datos[i];
	}
}

void copiar_poder(char poder[3], char datos[MAX_LONGITUD],int inicio ,int limite){
	int iterador = 0;
	for(int i = inicio; i < limite; i++){
		poder[iterador] = datos[i];
		iterador++;
	}
	poder[iterador] = 0;
}

bool contiene_solo_numeros(char poder[3]){
	bool es_numero = true;
	for(int i = 0; poder[i] != 0; i++){
		if(!isdigit(poder[i])){
			es_numero = false;
		}
	}
	return es_numero;
}

struct ataque *parsear_ataque(char *texto, struct ataque *ataque){
	char copia_texto[MAX_LONGITUD];
	char campo_nombre[20];
	char campo_tipo;
	char campo_poder[3];
	int posicion_delimitador_1 = -1;
	int posicion_delimitador_2 = -1;
	int posicion_delimitador_3 = -1;

	strcpy(copia_texto, texto);

	int i = 0;
	bool encontrado = false;
	while(copia_texto[i] != '\0' && !encontrado){
		if(copia_texto[i] == ';'){
			posicion_delimitador_1 = i;
			posicion_delimitador_2 = i + 2;
			encontrado = true;
		}
		i++;
	}
	posicion_delimitador_3 = strlen(texto);

	copiar_datos(campo_nombre, copia_texto, 0, posicion_delimitador_1);
	copiar_tipo(&campo_tipo, copia_texto, posicion_delimitador_1 + 1, posicion_delimitador_2);
	copiar_poder(campo_poder, copia_texto, posicion_delimitador_2 + 1, posicion_delimitador_3);

	strcpy(ataque->nombre, campo_nombre);

	if (campo_tipo == 'N') {
		ataque->tipo = NORMAL;
	} else if (campo_tipo == 'F') {
		ataque->tipo = FUEGO;
	} else if (campo_tipo == 'A') {
		ataque->tipo = AGUA;
	} else if (campo_tipo == 'P') {
		ataque->tipo = PLANTA;
	} else if (campo_tipo == 'E') {
		ataque->tipo = ELECTRICO;
	} else if (campo_tipo == 'R') {
		ataque->tipo = ROCA;
	} else {
		return NULL;
	}

	if(strlen(campo_poder) == 0){
		return NULL;
	}else if(!contiene_solo_numeros(campo_poder)){
		return NULL;
	}

	ataque->poder = atoi(campo_poder);

	return ataque;
}

int main(){
	struct ataque un_ataque;
	int errores = 0;

	if (parsear_ataque("", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string vacío D:\n");
		errores++;
	} else
		printf("Parseo de un string vacío 👍\n");

	if (parsear_ataque("Rayo;E;", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string incorrecto D:\n");
		printf("%s\n", un_ataque.nombre);
		printf("%c\n", un_ataque.tipo);
		printf("%i\n", un_ataque.poder);

		errores++;
	} else
		printf("Parseo de un string incorrecto 👍\n");

	if (parsear_ataque("Rayo;E;5", &un_ataque) == NULL) {
		printf("Se espera que se pueda parsear un string correcto D:\n");
		errores++;
	} else if (strcmp(un_ataque.nombre, "Rayo") == 0 &&
		 un_ataque.tipo == ELECTRICO && un_ataque.poder == 5) {
		printf("Parseo de un string correcto 👍\n");
	} else {
		printf("Se parseó el string pero los valores son incorrectos 🤔\n");
		errores++;
	}

	printf("Total de errores: %i\n", errores);
	return errores;
}
