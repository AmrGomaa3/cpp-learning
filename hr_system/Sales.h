#ifndef SALES_H
#define SALES_H


#include "Employee.h"
#include <string>
#include <string_view>


class Sales : public Employee {
private:
float grossSales;
float commissionRate;

public:
    Sales(std::string_view name, int id, double salary, float grossSales, float commissionRate);

    void setGrossSales(float sales);

    void setCommissionRate(float commission);

    double getTotalSalary() const;

    void print() const;
};

#endif

