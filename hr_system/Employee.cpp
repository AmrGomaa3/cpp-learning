#include "Employee.h"
#include <iostream>
#include <string_view>


Employee::Employee(std::string_view name, int id, double salary) {
    this->name = name;
    this->empID = id;
    this->salary = salary;
}

void Employee::print() const {
    std::cout << "ID: " << empID << "\nName: " << name << "\nSalary: " << salary << "\n";
}
