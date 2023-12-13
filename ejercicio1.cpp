#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4096

int main() {
    // Crear una región de memoria compartida de SIZE bytes
    char *shared_memory = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Verificar si la asignación de memoria compartida fue exitosa
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Crear un nuevo proceso usando fork()
    pid_t pid = fork();

    // Verificar errores en la creación del proceso hijo
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Código ejecutado por el proceso hijo

        // Imprimir el contenido de la memoria compartida
        printf("Child reads: %s\n", shared_memory);

        // Liberar la memoria compartida utilizada por el hijo
        munmap(shared_memory, SIZE);

        // Salir con éxito
        exit(EXIT_SUCCESS);
    } else {
        // Código ejecutado por el proceso padre

        // Escribir en la memoria compartida desde el padre
        strcpy(shared_memory, "Hello, child process!");

        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Liberar la memoria compartida utilizada por el padre
        munmap(shared_memory, SIZE);
    }

    // Terminar el programa con éxito
    return 0;
}