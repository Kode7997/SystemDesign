#include<iostream>

/*

2. O : Open/Closed Relationship

Consider a new feature is being added to the existing code and changes are added and shipped to the customer. say, new feature had a bug.
- Breaks the old functionality and changes the behaviour of old feature.
- Add
Solution: 
- Use inheritance, interfaces or polymorphism
Example1: w/o Open/Closed Principle
Example2: w/ Open/Closed Principle

*/

// Example1: w/o Open/Closed principle
// 
class Employee
{
    public:
        std::string getBadgeColor(std::string employeeType)
        {
            if (employeeType == "permanent") return "blueBage";
            if (employeeType == "contractor") return "redBadge";
        }
};


/*
Example2: w/ Open/Closed relationship
*/

class Employee {
    public:
        virtual std::string getBadgeColor(std::string type) = 0;
};

class PermanentEmployee: public Employee {
    public:
        std::string getBadgeColor(std::string type) override {
            return "Blue";
        }
};

class ContractorEmployee: public Employee {
    public:
        std::string getBadgeColor(std::string type) override {
            return "Red";
        }
};