
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4096

int main() {
    // Crear una región de memoria compartida
    char *shared_memory = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Verificar si la asignación de memoria compartida fue exitosa
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    // Crear un nuevo proceso
    pid_t pid = fork();

    // Verificar errores en la creación del proceso
    if (pid < 0) {
        perror("fork");
        // Liberar la memoria compartida antes de salir en caso de error
        munmap(shared_memory, SIZE);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Código ejecutado por el proceso hijo