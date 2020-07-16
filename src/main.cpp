
#include <iostream>

#include "../include/runtime/runtime.h"


// usage alpharuntime <inputFilename>

int main(int argc, char * argv[])
{
    if (argc != 2) {
        std::cout << "Usage: alpharuntime <inputFilename>" << std::endl;

        return -1;
    }

    Runtime runtime;

    return runtime.start(argv[1]);
}

