#include<iostream>

/*
- S - single responsibility principle
- A class should have a single responsibility. just give one single job
- example_1: w/o single responsibility
- example_2: w/ single responsibility
*/

/*
Example1: w/o Single Responsibility Principle
    Consider a backend services that accepts user authentication(signup, login), database connection.
    this class will be filled with all serverices which overloads and limits sharing of it's services to others if required.
    - one bug can break everything. all the services will be down, that is complex to debug.
*/

class User{

    public:
        User(){}

        ~User(){}

        // signup
        void SignUp(std::string name, std::string password)
        {
            // implement signup 
        }

        void LogIn(std::string name, std::string password)
        {
            // implement login
        }

        void DBConnetion(std::string dbName, std::string IP)
        {
            // db connection
        }
};


/*
Example2: w/ Single Responsibility
- Seperates functionality of each services
- In practice these classes will be a file each serving a different service
*/

class UserLogin{

    public:
        UserLogin(){}

        ~UserLogin(){}
};

class UserSignUp{
    public:

        UserSignUp(){}

        ~UserSignUp(){}

};

class UserDataBaseConnection
{
    public:
        UserDataBaseConnection(){}

        ~UserDataBaseConnection(){}
};
