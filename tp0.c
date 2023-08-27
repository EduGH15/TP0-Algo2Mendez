#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LONGITUD 100
#define MAX_NOMBRE 20
#define MAX_PODER 3

const int NO_ENCONTRADO = -1;
const int SIN_LONGITUD = 0;
const char SIN_CAMPO = ' ';
const char TIPO_NORMAL = 'N';
const char TIPO_FUEGO = 'F';
const char TIPO_AGUA = 'A';
const char TIPO_PLANTA = 'P';
const char TIPO_ELECTRICO = 'E';
const char TIPO_ROCA = 'R';


enum TIPO { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA };

struct ataque {
	char nombre[MAX_NOMBRE];
	enum TIPO tipo;
	unsigned int poder;
};

//Pre: Los parámetros inicio y limite deben ser parámetros válidos (inicio tiene que ser menor a limite).  
//Post: Modifica el vector de nuevo_dato con los valores presentes en el vector de datos, desde "inicio" hasta "limite".	
void copiar_datos(char nuevo_dato[MAX_NOMBRE], char datos[MAX_LONGITUD],int inicio ,int limite){
	for(int i = inicio; i < limite; i++){
		nuevo_dato[i] = datos[i];
	}
	nuevo_dato[limite] = 0;
}


//Pre: Los parámetros inicio y limite deben ser parámetros válidos (inicio tiene que ser menor a limite).  
//Post: Modifica el valor de la variable tipo con los valores presentes en el vector de datos, desde "inicio" hasta "limite".	
void copiar_tipo(char* tipo, char datos[MAX_LONGITUD],int inicio ,int limite){
	for(int i = inicio; i < limite; i++){
		*tipo = datos[i];
	}
}


//Pre: Los parámetros inicio y limite deben ser parámetros válidos (inicio tiene que ser menor a limite).  
//Post: Modifica el valor del vector poder con los valores presentes en el vector de datos, desde "inicio" hasta "limite".	
void copiar_poder(char poder[3], char datos[MAX_LONGITUD],int inicio ,int limite){
	int iterador = 0;
	for(int i = inicio; i < limite; i++){
		poder[iterador] = datos[i];
		iterador++;
	}
	poder[iterador] = 0;
}

//Pre: el parametro texto no puede ser un string vacío y debe contener punto y coma.
//post: A los parámetros posicion_delimitador_1/2/3 se les asigna la posición donde se encuentran los punto y comas.
void definir_posicion_delimitador(int* posicion_delimitador_1, int* posicion_delimitador_2, int* posicion_delimitador_3, char* texto, char copia_texto[MAX_LONGITUD]){
	int i = 0;
	bool encontrado = false;
	while(copia_texto[i] != '\0' && !encontrado){
		if(copia_texto[i] == ';'){
			*posicion_delimitador_1 = i;
			*posicion_delimitador_2 = i + 2;
			encontrado = true;
		}
		i++;
	}
	*posicion_delimitador_3 = strlen(texto);
}

//Pre: -------------------------------------------------------------------------------------------------------
//Post: Dependiendo del valor del campo_tipo, se le asignará un valor al campo_nuevo. Si campo_tipo es igual a 'N','F','A','P','E','R', se le asignará
//respectivamente los tipos NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA al campo_nuevo.
void definir_tipo(char campo_tipo, enum TIPO* campo_nuevo){
	if (campo_tipo == TIPO_NORMAL) {
		*campo_nuevo = NORMAL;
	} else if (campo_tipo == TIPO_FUEGO) {
		*campo_nuevo = FUEGO;
	} else if (campo_tipo == TIPO_AGUA) {
		*campo_nuevo = AGUA;
	} else if (campo_tipo == TIPO_PLANTA) {
		*campo_nuevo = PLANTA;
	} else if (campo_tipo == TIPO_ELECTRICO) {
		*campo_nuevo = ELECTRICO;
	} else if (campo_tipo == TIPO_ROCA) {
		*campo_nuevo = ROCA;
	}else{
		*campo_nuevo = SIN_CAMPO;
	}
}

//Pre: El parámetro poder debe ser un string.
//Post: Dado un string, valida si contiene solo numeros. Si contiene letras, retornará false.
bool contiene_solo_numeros(char poder[MAX_PODER]){
	bool es_numero = true;
	for(int i = 0; poder[i] != 0; i++){
		if(!isdigit(poder[i])){
			es_numero = false;
		}
	}
	return es_numero;
}

//Pre:-------------------------------------------
//Post; deuelve un puntero a ataque, dicho struct contendrá la información proporcionada por el texto. En caso de que los datos del texto
//sean inválidos, la función retornará NULL.
struct ataque *parsear_ataque(char *texto, struct ataque *ataque){
	char copia_texto[MAX_LONGITUD];
	char campo_nombre[MAX_NOMBRE];
	char campo_tipo;
	char campo_poder[MAX_PODER];
	int posicion_delimitador_1 = NO_ENCONTRADO;
	int posicion_delimitador_2 = NO_ENCONTRADO;
	int posicion_delimitador_3 = NO_ENCONTRADO;

	strcpy(copia_texto, texto);

	definir_posicion_delimitador(&posicion_delimitador_1, &posicion_delimitador_2, &posicion_delimitador_3, texto, copia_texto);
	copiar_datos(campo_nombre, copia_texto, 0, posicion_delimitador_1);
	copiar_tipo(&campo_tipo, copia_texto, posicion_delimitador_1 + 1, posicion_delimitador_2);
	copiar_poder(campo_poder, copia_texto, posicion_delimitador_2 + 1, posicion_delimitador_3);

	strcpy(ataque->nombre, campo_nombre);

	definir_tipo(campo_tipo, &(ataque)->tipo);
	if(ataque->tipo == SIN_CAMPO){
		return NULL;
	}

	if(strlen(campo_poder) == SIN_LONGITUD){
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
	}else
		printf("Parseo de un string vacío 👍\n");

	if(parsear_ataque("Rayo;E;", &un_ataque) != NULL) {
		printf("Se espera que no se pueda parsear un string incorrecto D:\n");
		errores++;
	}else
		printf("Parseo de un string incorrecto 👍\n");

	if(parsear_ataque("Rayo;E;5", &un_ataque) == NULL) {
		printf("Se espera que se pueda parsear un string correcto D:\n");
		errores++;
	}else if (strcmp(un_ataque.nombre, "Rayo") == 0 &&
		 un_ataque.tipo == ELECTRICO && un_ataque.poder == 5) {
		printf("Parseo de un string correcto 👍\n");
	}else {
		printf("Se parseó el string pero los valores son incorrectos 🤔\n");
		errores++;
	}
	return errores;
}
