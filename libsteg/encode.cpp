#include <iostream>
#include <fstream>
#include "qsteg.h"

int main()
{
    encode("in.bmp", "out.bmp", "in.txt"); 
    return 0;
} 
