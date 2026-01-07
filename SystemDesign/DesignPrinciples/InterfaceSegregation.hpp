#include<iostream>
/*
I : Interface Segregation Principle

Principle states that, classes that implements interface class should not force to implement the methods of interface 
class when there is no requiement.

Example1: w/o Interface segregation principle
Example2: w/ Interface segregation principle

*/

// Example1: w/o interface segregation principle
class Worker {
    public:
        virtual void works() = 0;
        virtual void eats() = 0;

        virtual ~Worker() = default;            // significance of default
};

class Human : public Worker {
    public:
        void works() override {
            std::cout<<"human works"<<std::endl;
        }

        void eats() override {
            std::cout<<"human eats"<<std::endl;
        }
};

class Robot : public Worker {
    public:
        void works() override {
            std::cout<<"robo works"<<std::endl;
        }
        
        void eats() override {
            // force derived to implement the method of interface class which violates 4th principle of SOLID.
        }
};


// Example2: w/ interface segregation principle

class WorkerClass {
    public:
        virtual void works() = 0;
};

class EaterClass {                          // segregates interface class
    public:
        virtual void eats() = 0;
};

class HumanClass : public WorkerClass, public EaterClass {
    public: 
        void works() override {
            std::cout<<"Human eats"<<std::endl;
        }
        
        void eats() override {
            std::cout<<"Human eats"<<std::endl;
        }
};

class RobotClass : public WorkerClass {     // implements only required interface class
    public:
        void works() override {
            std::cout<<"Robo works"<<std::endl;
        }
};