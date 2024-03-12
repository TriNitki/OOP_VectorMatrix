#include <iostream>
#include "Base.h"

int main()
{
    try
    {
        double values1[8] = { 1, 2, 3, 4, 4, 3, 2, 1 };
        double values2[8] = { 10, 20, 30, 40};
        Vector aaa(4, values2);
        Matrix test1(2, 4, values1);
        Matrix test11(4, 2, values1);
        
        test1[0][0] = 10;

        std::cout << test1[0][0] << std::endl;
        Vector test2 = Vector(4, values1);

        Matrix test3 = Matrix(1, 4, values2);
        Vector test4 = Vector(4, values2);

        test3 += test4;
        test4 += test3;

        std::cout << test3 << std::endl;
        std::cout << test4 << std::endl;

        std::cout << test1 * test11 << std::endl;

        std::cout << test1 * test2 << std::endl;
    }
    catch (const std::exception error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
}