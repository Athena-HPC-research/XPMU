#ifndef bufferh
#define bufferh

#include <stdlib.h>

/// @brief Creates a new buffer dynamically
/// @param size The size of the new buffer
/// @return The newly created buffer
char* CreateBuffer(int size);

/// @brief Deletes all of the data from the buffer
/// @param buffer The buffer to clear
/// @param size The size of the buffer
void EmptyBuffer(char buffer[], int size);

#endif