#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Contacto agenda[MAX_CONTACTOS];
int numContactos = 0;

void cargarContactos() {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        return;
    }

    numContactos = 0;
    while (numContactos < MAX_CONTACTOS && 
           fscanf(archivo, "%59s %59s %9s %d %99s %99s", 
                  agenda[numContactos].nombre,
                  agenda[numContactos].apellido,
                  agenda[numContactos].numero,
                  &agenda[numContactos].tipoNumero,
                  agenda[numContactos].correo,
                  agenda[numContactos].referencia) == 6) {
        numContactos++;
    }

    fclose(archivo);
}

void guardarContactos() {
    FILE *archivo = fopen(ARCHIVO, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }

    for (int i = 0; i < numContactos; i++) {
        fprintf(archivo, "%s %s %s %d %s %s\n", 
                agenda[i].nombre,
                agenda[i].apellido,
                agenda[i].numero,
                agenda[i].tipoNumero,
                agenda[i].correo,
                agenda[i].referencia);
    }

    fclose(archivo);
}

void agregarContacto() {
    if (numContactos >= MAX_CONTACTOS) {
        printf("La agenda está llena. No se pueden agregar más contactos.\n");
        return;
    }

    printf("Agregar nuevo contacto:\n");
    printf("Nombre: ");
    scanf("%59s", agenda[numContactos].nombre);
    printf("Apellido: ");
    scanf("%59s", agenda[numContactos].apellido);
    printf("Número telefónico: ");
    scanf("%9s", agenda[numContactos].numero);
    printf("Tipo de número (1-Casa, 2-Trabajo, 3-Móvil, 4-Otro): ");
    scanf("%d", &agenda[numContactos].tipoNumero);
    printf("Correo electrónico: ");
    scanf("%99s", agenda[numContactos].correo);
    printf("Referencia: ");
    scanf("%99s", agenda[numContactos].referencia);

    numContactos++;
    guardarContactos();
    printf("Contacto agregado exitosamente.\n");
}

void buscarContacto() {
    char nombre[60];
    printf("Ingrese el nombre a buscar: ");
    scanf("%59s", nombre);

    int encontrado = 0;
    for (int i = 0; i < numContactos; i++) {
        if (strcmp(agenda[i].nombre, nombre) == 0) {
            printf("\nContacto encontrado:\n");
            printf("Nombre: %s %s\n", agenda[i].nombre, agenda[i].apellido);
            printf("Teléfono: %s (Tipo: %d)\n", agenda[i].numero, agenda[i].tipoNumero);
            printf("Correo: %s\n", agenda[i].correo);
            printf("Referencia: %s\n\n", agenda[i].referencia);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontraron contactos con ese nombre.\n");
    }
}

void listarContactos() {
    if (numContactos == 0) {
        printf("La agenda está vacía.\n");
        return;
    }

    printf("\nLista de contactos:\n");
    for (int i = 0; i < numContactos; i++) {
        printf("%d. %s %s - %s\n", i+1, 
               agenda[i].nombre, agenda[i].apellido, agenda[i].numero);
    }
    printf("\n");
}

void mostrarMenu() {
    printf("\nAGENDA TELEFÓNICA\n");
    printf("1. Agregar contacto\n");
    printf("2. Buscar contacto\n");
    printf("3. Listar contactos\n");
    printf("4. Salir\n");
    printf("Seleccione una opción: ");
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
