#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include <string>
#include <string_view>


class Employee {
protected:
    std::string name;
    int empID;
    double salary;

public:
    Employee(std::string_view name, int id, double salary);

    virtual double getTotalSalary() const = 0;

    virtual void print() const;
};

#endif
