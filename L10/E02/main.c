#include "elemento.h"
#include "smartfunctions.h"

const uint8_t MAX_STRING = 150;

int main() {
    char filename[] = "elementi.txt";
    array elementi  = parseFromFile(filename, MAX_STRING, (void *)&parseElemento);
    elemento *e     = (elemento *)elementi->Elementi;
    return 0;
}
