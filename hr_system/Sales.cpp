#include "Sales.h"
#include <iostream>
#include <string>
#include <string_view>


Sales::Sales(std::string_view name, int id, double salary, float grossSales, float commissionRate): Employee(name, id, salary) {
    this->grossSales = grossSales;
    this->commissionRate = commissionRate;
}

void Sales::setGrossSales(float sales) {
    grossSales = sales;
}

void Sales::setCommissionRate(float commission) {
    commissionRate = commission;
}

double Sales::getTotalSalary() const {
    return salary + (grossSales * commissionRate);
}

void Sales::print() const {
    Employee::print();
    std::cout << "Gross Sales: " << grossSales << "\nCommission Rate: " << commissionRate << "\n";
}

