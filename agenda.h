#ifndef _AGENDA_H_
#define _AGENDA_H_

#define ARCHIVO "agenda.txt"
#define MAX_CONTACTOS 200

struct _contacto{
    char nombre[60];
    char apellido[60];
    char numero[10];
    int tipoNumero;
    char correo[100];
    char referencia[100];
};


typedef struct _contacto Contacto;

Contacto agenda[];
int numContactos;

void cargarContactos();
void guardarContactos();
void agregarContacto();
void buscarContacto();
void mostrarMenu();
void listarContactos();
void limpiarBuffer();


#endif
