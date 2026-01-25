
class Singleton{
    
    // static variable of type singleton
    static Singleton* volatile instance;

    // private constructor
    Singleton() {}

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    public:
        // static method
        static Singleton& getInstance()
        {
            static Singleton instance;
            return instance;
        }
};