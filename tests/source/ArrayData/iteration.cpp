#include "aquila/source/ArrayData.h"
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 10;
    double testArray[SIZE] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Aquila::ArrayData<double> data(testArray, SIZE, 22050);
    std::cout << data.getSamplesCount();
    return 0;
}
