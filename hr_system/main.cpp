#include "Sales.h"
#include "Engineer.h"
#include <iostream>


int main() {
    Engineer engineer{"Amr Gomaa", "Civil Eningeer", 1001, 12000.0, 3, 2, 200};
    Sales sales{"Youssef Gomaa", 1003, 9000.0, 150000.0f, 0.1f};

    engineer.print();

    std::cout << "\n";

    sales.print();

    return 0;
}
