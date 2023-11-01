#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

///DEFINE DE ESPECIES
#define MAMIFEROS 1
#define AVES 2
#define REPTILES 3
#define PECES 4
#define ANFIBIOS 5

#define NOMBREARCHI  "animales.dat"

#define ARCHIMAMIFEROS "mamiferos.bin"
#define ARCHIAVES "aves.bin"
#define ARCHIREPTILES "reptiles.bin"
#define ARCHIPECES "peces.bin"

#define DIM 30
///ESTRUCTURAS:
typedef struct {
   char animal[30];
   int cant;
   int habitat;
   int idEspecie;
   char especie[20];
} registroArchivo;

typedef struct {
    char nombreAnimal [30];
	int cantidad;
	int habitat;
} animal;
/// 1 - selva, 2- savana, 3-bosque, 4-mar
typedef struct {
   animal animales;
   struct nodoArbol * izq;
   struct nodoArbol * der;
} nodoArbol;

typedef struct{
   int idEspecie;
   char especie [20];
/// "Mamiferos", "Aves", "Reptiles", "Peces" y "Anfibios"
   nodoArbol * arbolDeAnimales;
} celdaEspecie;

///PROTOTIPADO FUNCIONES
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(animal datoAnimal);
nodoArbol *insertarAnimalEnArbol(nodoArbol *arbol, animal datoAnimal);
void printfMostrarAnimalesArbol(animal animales);
void mostrarArbolPreOrden(nodoArbol *arbol);
void mostrarArbolEnOrden(nodoArbol *arbol);
void mostrarArbolPostOrden(nodoArbol *arbol);
void cargandoEspecies(celdaEspecie especies[]);
void mostrarArchivo();
void printfDelArchivo(registroArchivo registro);
void inicializarArbolesIndixArr(celdaEspecie especies[]);
void pasarDelArchivoACeldasDeArbol(celdaEspecie especies[]);
void mostrarAnimalesSegunEspecie(celdaEspecie especies[], char especie[]);
animal RecorrerYRetornarUnAnimalEnArbol(nodoArbol *arbol);

int main(){
    celdaEspecie especies[DIM];
    int validos = 0;
    ///Los animales se insertan en el arbol por cantidad
    ///Mostrando el archivo:
    mostrarArchivo();
    ///CARGANDO ESPECIES AL ARREGLO:
    cargandoEspecies(especies);
    ///Inicializamos los arboles de los indices del arreglo
    inicializarArbolesIndixArr(especies);
    printf("\nTesteo de q los arboles estan inicializados en NULL: \n");
    for(int i = 1; i <= 4; i++)printf("\nArbol del indice %i --> %p\n", i, especies[i].arbolDeAnimales);

    printf("\nPasando los animales al arreglo de arboles...\n");
    pasarDelArchivoACeldasDeArbol(especies);

    char especie[20];
    printf("\nIngrese la especie --> Mamiferos, Aves, Reptiles, Peces y Anfibios \n");
    fflush(stdin);
    gets(especie);

    mostrarAnimalesSegunEspecie(especies,especie);

    cargarArchivos(especies[MAMIFEROS].arbolDeAnimales, ARCHIMAMIFEROS);
    cargarArchivos(especies[AVES].arbolDeAnimales, ARCHIAVES);
    cargarArchivos(especies[REPTILES].arbolDeAnimales, ARCHIREPTILES);
    cargarArchivos(especies[PECES].arbolDeAnimales, ARCHIPECES);

}

///FUNCIONES
///Inicializar Arbol
nodoArbol *inicArbol(){
    return NULL;
}

///Crear Nodo Arbol
nodoArbol *crearNodoArbol(animal datoAnimal){
    nodoArbol *nuevoNodo = (nodoArbol*) malloc(sizeof(nodoArbol));
    nuevoNodo->animales = datoAnimal;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

nodoArbol *insertarAnimalEnArbol(nodoArbol *arbol, animal datoAnimal){
    if(arbol == NULL) arbol = crearNodoArbol(datoAnimal);
    else{
        if(datoAnimal.cantidad > arbol->animales.cantidad) arbol->der = insertarAnimalEnArbol(arbol->der, datoAnimal);
        else arbol->izq = insertarAnimalEnArbol(arbol->izq, datoAnimal);
    }
    return arbol;
}
///Printf para mostrar el arbol
void printfMostrarAnimalesArbol(animal animales){
    printf("\n-----------------------------------------\n");
    printf("Nombre: %s\n",animales.nombreAnimal);
    printf("Cantidad: %i\n",animales.cantidad);
    printf("Habitat: %i",animales.habitat);
    printf("\n-----------------------------------------\n");
}
///Mostrar el arbol en PRE ORDEN
void mostrarArbolPreOrden(nodoArbol *arbol){
    if(arbol == NULL) return;
    else{
        printfMostrarAnimalesArbol(arbol->animales);
        mostrarArbolPreOrden(arbol->izq);
        mostrarArbolPreOrden(arbol->der);
    }
}
///Mostrar el arbol EN ORDEN
void mostrarArbolEnOrden(nodoArbol *arbol){
    if(arbol == NULL) return;
    else{
        mostrarArbolEnOrden(arbol->izq);
        printfMostrarAnimalesArbol(arbol->animales);
        mostrarArbolEnOrden(arbol->der);
    }
}
///Mostrar el arbol en POST ORDEN
void mostrarArbolPostOrden(nodoArbol *arbol){
    if(arbol == NULL) return;
    else{
        mostrarArbolPostOrden(arbol->izq);
        mostrarArbolPostOrden(arbol->der);
        printfMostrarAnimalesArbol(arbol->animales);
    }
}
///MOSTRAR TODOS LOS ANIMALES DEPENDIENDO LA ESPECIE
void mostrarAnimalesSegunEspecie(celdaEspecie especies[], char especie[]){
    int flag = 0;
    for(int i = 1; i <= 4; i++){
        if(strcmp(especies[i].especie, especie) == 0){
            flag = 1;
            printf("\nESPECIE: %s\n", especies[i].especie);
            printf("ID ESPECIE: %i\n", especies[i].idEspecie);
            mostrarArbolEnOrden(especies[i].arbolDeAnimales);
        }
    }
    if(flag == 0) printf("\nLa especie que desea buscar no se encuentra en el sistema.\n");
}

void cargandoEspecies(celdaEspecie especies[]){
    especies[MAMIFEROS].idEspecie = MAMIFEROS;
    strcpy( especies[MAMIFEROS].especie, "Mamiferos");
    especies[MAMIFEROS].arbolDeAnimales = inicArbol();

    especies[AVES].idEspecie = AVES;
    strcpy( especies[AVES].especie, "Aves");
    especies[AVES].arbolDeAnimales = inicArbol();

    especies[REPTILES].idEspecie = REPTILES;
    strcpy( especies[REPTILES].especie, "Reptiles");
    especies[REPTILES].arbolDeAnimales = inicArbol();

    especies[PECES].idEspecie = PECES;
    strcpy( especies[PECES].especie, "Peces");
    especies[PECES].arbolDeAnimales = inicArbol();

    especies[ANFIBIOS].idEspecie = ANFIBIOS;
    strcpy( especies[ANFIBIOS].especie, "Anfibios");
    especies[ANFIBIOS].arbolDeAnimales = inicArbol();
}
///MOSTRAR ARCHIVO
void mostrarArchivo(){
    FILE *punteroArchi = fopen(NOMBREARCHI, "rb");
    registroArchivo registro;
    if(punteroArchi != NULL){
        while (fread(&registro, sizeof(registroArchivo), 1, punteroArchi) == 1){
            printfDelArchivo(registro);
        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo.\n");
}
void printfDelArchivo(registroArchivo registro){
    printf("\n.................................................\n");
    printf("ESPECIE: %s\n", registro.especie);
    printf("ID ESPECIE: %i\n", registro.idEspecie);
    printf("ANIMAL: %s\n", registro.animal);
    printf("CANTIDAD: %i\n", registro.cant);
    printf("HABITAT: %i", registro.habitat);
    printf("\n.................................................\n");
}
void inicializarArbolesIndixArr(celdaEspecie especies[]){
    for(int i = 1; i <= 4; i++) especies[i].arbolDeAnimales = inicArbol();
}
///Pasar del archivo a el arrreglo de arboles
void pasarDelArchivoACeldasDeArbol(celdaEspecie especies[]){
    FILE *punteroArchi = fopen(NOMBREARCHI, "rb");
    registroArchivo registro;
    animal unAnimal;
    if(punteroArchi != NULL){
        while (fread(&registro, sizeof(registroArchivo), 1, punteroArchi) == 1){
            fread(&registro,sizeof(registroArchivo),1,punteroArchi);

                ///Copiamos el registro del archivo a un tipo de dato animal, para ingresarlo al arbol dependiendo la especie
                strcpy(unAnimal.nombreAnimal, registro.animal);
                unAnimal.cantidad = registro.cant;
                unAnimal.habitat = registro.habitat;

                if(registro.idEspecie > 0 && registro.idEspecie <= 4){
                    especies[registro.idEspecie].arbolDeAnimales = insertarAnimalEnArbol(especies[registro.idEspecie].arbolDeAnimales, unAnimal);
                }else printf("\nEse ID De Especie No Es Valido.\n");

        }
        fclose(punteroArchi);
    }else printf("\nError al abrir el archivo.\n");
    printf("\nAnimales transferidos al arreglo correctamente.\n");
} /// "Mamiferos = 1", "Aves = 2", "Reptiles = 3", "Peces = 4" y "Anfibios = 5"

///Pasar cada especie a un archivo diferente
void cargarArchivos(nodoArbol *arbol, char nombreArchivo[]){
    if(arbol == NULL) return;
    else{
        cargarArchivos(arbol->izq, nombreArchivo);
        ingresandoAnimalesArchivos(nombreArchivo, arbol->animales);
        cargarArchivos(arbol->der, nombreArchivo);
    }
}
void ingresandoAnimalesArchivos(char nombreArchivo[], animal unAnimal){
    FILE *punteroArchi = fopen(nombreArchivo, "wb");

    fwrite(&unAnimal, sizeof(animal),1,punteroArchi);

    fclose(punteroArchi);
    printf("\nDEBUGGG ARCHIVO --> %s CARGADO CON EXITO\n", nombreArchivo);
}
