#include <iostream>
#include "Base.h"

int main()
{
    try
    {
        double values1[8] = { 1, 2, 3, 4, 4, 3, 2, 1 };
        Matrix test1 = Matrix(2, 4, values1);
        std::cout << test1[0] << std::endl;
        Vector test2 = Vector(4, values1);

        std::cout << test1[1] - test2 << std::endl;
    }
    catch (const std::invalid_argument error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
}