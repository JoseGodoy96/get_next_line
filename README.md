get_next_line


Una función en C que lee un fichero línea a línea desde un descriptor de
fichero (fd), devolviendo una línea completa en cada llamada.



Proyecto realizado en la escuela 42 (campus de 42 Málaga). Por tratarse de una
entrega ya evaluada y cerrada, el repositorio contiene un único commit: el
proyecto está terminado y no recibe nuevos cambios.


📖 Descripción

get_next_line (GNL) es un proyecto clásico de 42 cuyo objetivo es implementar
una función capaz de leer el contenido de un fichero una línea por llamada, sin
saber de antemano cuántas líneas tiene ni cómo de largas son.

cchar *get_next_line(int fd);


Cada llamada devuelve la siguiente línea del fichero, incluido el salto de
línea \n (salvo, posiblemente, en la última línea si el archivo no termina con
un \n).
Cuando no queda nada por leer (final de fichero), devuelve NULL.
Funciona tanto leyendo de un archivo como de la entrada estándar.


La gran particularidad del proyecto es la macro BUFFER_SIZE: define cuántos
bytes se leen en cada read. La función debe funcionar correctamente con cualquier
valor (por ejemplo 1, 42 o 9999), lo que obliga a manejar bien el estado entre
llamadas.

¿Cómo funciona esta implementación?


Mantiene su estado entre llamadas mediante una variable static (una lista
enlazada de fragmentos leídos).
Lee bloques de BUFFER_SIZE bytes y los va acumulando en la lista hasta
encontrar un salto de línea o llegar al final del fichero.
Cuando ya hay un \n (o se acabó el fichero), extrae la línea completa y la
devuelve.
Conserva el sobrante posterior al \n en la lista para usarlo en la siguiente
llamada.



⚙️ Configuración: BUFFER_SIZE

BUFFER_SIZE se define en tiempo de compilación. Si no se especifica, el header usa
un valor por defecto:

c# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

Para fijarlo manualmente al compilar:

bashcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl


🧠 Conceptos trabajados


Uso de la llamada al sistema read y manejo de descriptores de fichero.
Variables static para conservar estado entre llamadas.
Gestión dinámica de memoria sin fugas (malloc / free).
Manejo de buffers y casos límite (ficheros vacíos, sin salto final, lecturas
parciales, etc.).



🗂️ Estructura del proyecto

get_next_line/
├── get_next_line.h        # prototipos, estructura y macro BUFFER_SIZE
├── get_next_line.c        # lógica principal (get_next_line y auxiliares)
├── get_next_line_utils.c  # funciones auxiliares (lista enlazada, copia, etc.)
└── main.c                 # programa de prueba


🚀 Compilación y uso

Ejemplo de uso de la función:

c#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("text.txt", O_RDONLY);
    char  *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}

Compilación (eligiendo el tamaño de buffer):

bashcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl


👤 Autor

jgodoy-m — Estudiante de 42 Málaga


📝 Nota sobre el repositorio

Este proyecto forma parte del currículo de 42. Al ser una entrega ya finalizada
y corregida, el historial del repositorio se compone de un solo commit. No está
en desarrollo activo: el código está completo y cumple los requisitos de la consigna.
