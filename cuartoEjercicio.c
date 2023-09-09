#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo
{
    int dato;
    struct nodo *sig;
    struct nodo *ant;
};

struct nodo *Cabeza;

// -- Funcion para limpiar el buffer por el uso de scanf (que deja un salto de línea en el buffer)
void limpiarBuffer()
{
    while (getchar() != '\n')
        ;
}

// -- Variable global para la longitud de la lista
int longitud = 0;

// -- Función para mostrar el menú
void mostrarMenu()
{
    printf("******* INTERFAZ LISTA DOBLEMENTE ENLAZADA *******\n");
    printf("*                                                *\n");
    printf("* 1. Insertar elemento                           *\n");
    printf("* 2. Mostrar elemento                            *\n");
    printf("* 3. Eliminar elemento                           *\n");
    printf("* 4. Buscar elemento                             *\n");
    printf("* 5. Modificar elemento                          *\n");
    printf("* 6. Salir                                       *\n");
    printf("*                                                *\n");
    printf("*************************************************\n");
}

// -- Funcion para agregar un nodo al final de la lista
void agregarNodo(struct nodo *ultimoNodo, int indice, int datoNodo)
{
    struct nodo *nuevoNodo = (struct nodo *)malloc(sizeof(struct nodo));
    struct nodo *nodoPrevio = (struct nodo *)malloc(sizeof(struct nodo));
    struct nodo *nodoActual = Cabeza;
    nuevoNodo->dato = datoNodo;
    // obtener el ultimo nodo de toda la lista
    if (indice > longitud)
    {
        printf("Indice fuera de rango\n");
        return;
    }
    else if (nodoActual == NULL)
    {
        nodoActual = (struct nodo*)malloc(sizeof(struct nodo));
        nodoActual->dato = datoNodo;
        nodoActual->sig = NULL;
        nodoActual->ant = NULL;
        Cabeza = nodoActual;
        longitud++;
    }
    else if (indice == -1)
    {
        while (nodoActual->sig != NULL)
        {
            nodoPrevio = nodoActual;
            nodoActual = nodoActual->sig;
            longitud++;
        }
        nodoActual->ant = nodoPrevio;
        return;
    }
    else if (indice == 0)
    {
        // intercambiar elementos del nuevo nodo y de la cabeza
        nuevoNodo->sig = Cabeza;
        Cabeza = nuevoNodo;
        longitud++;
        return;
    }
    else
    {
        int i = 0;
        while (i < indice - 1)
        {
            nodoActual = nodoActual->sig;
            i++;
        }
        nuevoNodo->sig = nodoActual->sig;
        nuevoNodo->ant = nodoActual;
        nodoActual->sig = nuevoNodo;
        struct nodo* temp = nodoActual->sig;
        temp->ant = nuevoNodo;
        longitud++;
        return;
    }
}

// -- Funcion para mostrar los elementos de la lista
void mostrarLista(struct nodo *nodoActual)
{
    while (nodoActual != NULL)
    {
        printf("%d ", nodoActual->dato);
        nodoActual = nodoActual->sig;
    }
    printf("\n");
}

// -- Funcion para eliminar un nodo de la lista
void eliminarNodo(int indice)
{
    struct nodo *nodoActual = Cabeza;
    struct nodo *nodoPosterior = (struct nodo *)malloc(sizeof(struct nodo));
    if (indice > longitud)
    {
        printf("Indice fuera de rango\n");
        return;
    }
    else if (indice == 0)
    {
        Cabeza = nodoActual->sig;
        free(nodoActual);
        longitud--;
        return;
    }
    else
    {
        int i = 0;
        while (i < indice - 1)
        {
            nodoActual = nodoActual->sig;
            i++;
        }
        nodoPosterior = nodoActual->sig;
        nodoActual->sig = nodoPosterior->sig;
        free(nodoPosterior);
        longitud--;
        return;
    }
}

// -- Funcion para buscar un elemento en la lista
bool buscarElemento(int elemento)
{
    struct nodo *nodoActual = Cabeza;
    while (nodoActual != NULL)
    {
        if (nodoActual->dato == elemento)
            return true;
        nodoActual = nodoActual->sig;
    }
    return false;
}

// -- Función para modificar un elemento de la lista
void modificarElemento(int indice, int nuevoElemento)
{
    struct nodo *nodoActual = Cabeza;
    if (indice > longitud)
    {
        printf("Indice fuera de rango\n");
        return;
    }
    else
    {
        int i = 0;
        while (i < indice)
        {
            nodoActual = nodoActual->sig;
            i++;
        }
        nodoActual->dato = nuevoElemento;
        return;
    }
}

int main()
{
    Cabeza = NULL;
    int opcion = 0;
    do
    {
        mostrarMenu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        switch (opcion)
        {
        case 1:
            // Ingresar elementos a la lista en una posicion especifica
            printf("Ingrese el indice donde desea ingresar el elemento (-1 para ingresar al final): ");
            int indice;
            scanf("%d", &indice);
            limpiarBuffer();
            printf("Ingrese el numero entero que contendrá el elemento: ");
            int numero;
            scanf("%d", &numero);
            limpiarBuffer();
            agregarNodo(Cabeza, indice, numero);
            break;
        case 2:
            // Mostrar elementos de la lista
            printf("Los elementos de la lista son:\n");
            mostrarLista(Cabeza);
            break;
        case 3:
            // Eliminar elementos de la lista  
            printf("Ingrese el indice del elemento que desea eliminar: ");
            int indiceEliminar;
            scanf("%d", &indiceEliminar);
            limpiarBuffer();
            eliminarNodo(indiceEliminar);
            break;
        case 4:
            // Buscar elementos de la lista
            printf("Ingrese el elemento que desea buscar: ");
            int elemento;
            scanf("%d", &elemento);
            limpiarBuffer();
            if (buscarElemento(elemento))
                printf("El elemento %d se encuentra en la lista\n", elemento);
            else
                printf("El elemento %d no se encuentra en la lista\n", elemento);
            break;
        case 5:
            // Modificar elementos de la lista
            printf("Ingrese el indice del elemento que desea modificar: ");
            int indiceModificar;
            scanf("%d", &indiceModificar);
            limpiarBuffer();
            printf("Ingrese el nuevo elemento: ");
            int nuevoElemento;
            scanf("%d", &nuevoElemento);
            limpiarBuffer();
            modificarElemento(indiceModificar, nuevoElemento);
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 6);
}