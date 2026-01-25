
#pragma once

class DBConnection {

    static DBConnection* dbInstance;
    
    DBConnection() {} // private constructor

    public:
        static DBConnection& getDBInstance()
        {
            static DBConnection dbInstance;
            return dbInstance;
        }
};