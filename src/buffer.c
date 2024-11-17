#include "buffer.h"

char* CreateBuffer(int size) {
    char* buffer = malloc(size);

    for (int i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }

    return buffer;
}

void EmptyBuffer(char bufferToEmpty[], int size) {
    for (int i = 0; i < size; i++)
    {
        bufferToEmpty[i] = '\0';
    }
}