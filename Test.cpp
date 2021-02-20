// Name: Base62 From Base64
// Data: 2018.10.14
// Editer: Hwanin

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Base62.h"

// Function    : main
// Parameter   : ...
// Return      : (int)0
int main(int argv, char* argc[])
{
    Base62 base62;
    srand((unsigned int)time(nullptr));
    int i = 0;
    int nRand = 0;
    std::string strTest = "\0";

    while (i < 1000)
    {
        nRand = rand();
        strTest.push_back(nRand % (126-33) + '!');
        i++;
    }


    std::cout << "String" << std::endl;
    std::cout << strTest << std::endl;
    strTest = base62.Base62Encode(strTest);
    std::cout << "Encode" << std::endl;
    std::cout << strTest << std::endl;
    strTest = base62.Base62Decode(strTest);
    std::cout << "Decode" << std::endl;
    std::cout << strTest << std::endl;
    return 0;
}