#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Contacto agenda[MAX_CONTACTOS];
int numContactos = 0;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarMenu() {
    printf("\n--- MENÚ DE AGENDA ---\n");
    printf("1. Agregar contacto\n");
    printf("2. Buscar contacto\n");
    printf("3. Listar todos los contactos\n");
    printf("4. Salir\n");
}

void cargarContactos() {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        return;
    }

    while (!feof(archivo) && numContactos < MAX_CONTACTOS) {
        Contacto c;
        if (fscanf(archivo, "%59[^,],%59[^,],%9[^,],%d,%99[^,],%99[^\n]\n",
                  c.nombre, c.apellido, c.numero, &c.tipoNumero, c.correo, c.referencia) == 6) {
            agenda[numContactos++] = c;
        }
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
        fprintf(archivo, "%s,%s,%s,%d,%s,%s\n",
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

    Contacto nuevo;
    
    printf("Ingrese el nombre: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
    
    printf("Ingrese el apellido: ");
    fgets(nuevo.apellido, sizeof(nuevo.apellido), stdin);
    nuevo.apellido[strcspn(nuevo.apellido, "\n")] = '\0';
    
    printf("Ingrese el número de teléfono: ");
    fgets(nuevo.numero, sizeof(nuevo.numero), stdin);
    nuevo.numero[strcspn(nuevo.numero, "\n")] = '\0';
    
    printf("Ingrese el tipo de número (1 para Móvil, 2 para Fijo): ");
    scanf("%d", &nuevo.tipoNumero);
    limpiarBuffer();
    
    printf("Ingrese el correo electrónico: ");
    fgets(nuevo.correo, sizeof(nuevo.correo), stdin);
    nuevo.correo[strcspn(nuevo.correo, "\n")] = '\0';
    
    printf("Ingrese una referencia: ");
    fgets(nuevo.referencia, sizeof(nuevo.referencia), stdin);
    nuevo.referencia[strcspn(nuevo.referencia, "\n")] = '\0';
    
    agenda[numContactos++] = nuevo;
    printf("Contacto agregado con éxito.\n");
}

void buscarContacto() {
    if (numContactos == 0) {
        printf("No hay contactos en la agenda.\n");
        return;
    }

    printf("\nBuscar por:\n");
    printf("1. Nombre\n");
    printf("2. Número de teléfono\n");
    printf("3. Correo electrónico\n");
    printf("Seleccione una opción: ");
    
    int opcion;
    scanf("%d", &opcion);
    limpiarBuffer();
    
    char busqueda[100];
    printf("Ingrese el término de búsqueda: ");
    fgets(busqueda, sizeof(busqueda), stdin);
    busqueda[strcspn(busqueda, "\n")] = '\0';
    
    int encontrados = 0;
    
    for (int i = 0; i < numContactos; i++) {
        int coincide = 0;
        
        switch(opcion) {
            case 1: // Nombre
                if (strstr(agenda[i].nombre, busqueda) != NULL || 
                    strstr(agenda[i].apellido, busqueda) != NULL) {
                    coincide = 1;
                }
                break;
            case 2: // Número
                if (strstr(agenda[i].numero, busqueda) != NULL) {
                    coincide = 1;
                }
                break;
            case 3: // Correo
                if (strstr(agenda[i].correo, busqueda) != NULL) {
                    coincide = 1;
                }
                break;
            default:
                printf("Opción no válida.\n");
                return;
        }
        
        if (coincide) {
            printf("\nContacto #%d:\n", i+1);
            printf("Nombre: %s %s\n", agenda[i].nombre, agenda[i].apellido);
            printf("Número: %s (%s)\n", agenda[i].numero, 
                  agenda[i].tipoNumero == 1 ? "Móvil" : "Fijo");
            printf("Correo: %s\n", agenda[i].correo);
            printf("Referencia: %s\n", agenda[i].referencia);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron contactos con ese criterio de búsqueda.\n");
    } else {
        printf("\nSe encontraron %d contactos.\n", encontrados);
    }
}

void listarContactos() {
    if (numContactos == 0) {
        printf("No hay contactos en la agenda.\n");
        return;
    }

    printf("\n--- LISTA DE CONTACTOS ---\n");
    for (int i = 0; i < numContactos; i++) {
        printf("\nContacto #%d:\n", i+1);
        printf("Nombre: %s %s\n", agenda[i].nombre, agenda[i].apellido);
        printf("Número: %s (%s)\n", agenda[i].numero, 
              agenda[i].tipoNumero == 1 ? "Móvil" : "Fijo");
        printf("Correo: %s\n", agenda[i].correo);
        printf("Referencia: %s\n", agenda[i].referencia);
    }
    printf("\nTotal: %d contactos\n", numContactos);
}
