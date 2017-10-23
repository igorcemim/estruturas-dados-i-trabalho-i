#include <stdio.h>
#include "pprint.h"

void pseparador() {
    printf("\n----------------------------\n");
}

void ptitulo(char* message) {
    pseparador();
    printf("\n %s\n", message);
    pseparador();
}

void psubtitulo(char* message) {
    printf("\n# %s\n", message);
}
