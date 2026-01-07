#include<iostream>

/*
SOLID Principle

L : Liskov substitution principle

It states, if class B implements class A, class B should replace class A without
breaking any code. basically, class B should behave same as class A 

Example1: w/o Liskov principle
Example2: w/ Liskov principle

*/


// Example1: w/o Liskov Principle
class Bird {
    public:
        virtual void flying() {
            std::cout<<"flies"<<std::endl;
        }
};

class Ostrich : public Bird {   // this class doesn't behave like base class Bird which violates Liskov principle
    public:
        void flying() override {
            throw std::logic_error("Ostrich doesn't fly");
        }
};

class Pegion : public Bird {
    public:
        void flying() override {
            std::cout<<"pegion flies"<<std::endl;
        }
};

// Example2: w/ Liskov Principle
class BirdClass {
    public:
        virtual void layEggs() {
            std::cout<<"Lay Eggs"<<std::endl;
        }
};

class FlyingBird: public BirdClass {
    public:
        virtual void fly(){
            std::cout<<"Flying"<<std::endl;
        }
};

class PegionClass : public FlyingBird {
    public:
        void fly() override {
            std::cout<<"Pegion flies"<<std::endl;
        }
};

class OstrichClass : public Bird {
    public:
        // no fly method and that's okay!
};
