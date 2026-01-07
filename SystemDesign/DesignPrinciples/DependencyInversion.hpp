#include<iostream>

/*
Principle states that High level modules should not depend directly on low-level modules. rather they should be abstracted by interface class.
This helps what?
    - Abstract low and high level implementation. high-level doesn't know what is actually implemented
    - Changes at low-level can be done independently, doesnot affect high-level implementation.
    - Easy to scale services or new functionality at low or high level
    - Easy to test changes
*/

// high level abstraction
class INotifier{
    public:
        virtual void send(std::string data);
};

class NotificationService{
    INotifier& notifier;

    public:
        NotificationService(INotifier& notifier) : notifier(notifier) {}
        
        void sendEmail(){
            notifier.send("send email");
        }

        void sendPassword(){
            notifier.send("send passwd");
        }

};



// At low-level

class SMTP{
    public:
        explicit SMTP() {}
};

class SMS{
    public:
        explicit SMS() {}
};

class EmailNotifier: public INotifier {
    // SMTP class instance
    SMTP smtp_;
    public:
        void send() {
            // implement email notification service.
        }

};

class SMSNotifier: public INotifier {
    SMS sms_;
    public:
        void send() {
            // implement sms notification service.
        }
};

// caller or composition root class
class InitiateNotification {

    // email or sms object
    EmailNotifier email;
    NotificationService ns;

    public:
        InitiateNotification() : ns(email) {}
        
        void sendNotification() {
            ns.sendEmail();
        }
};
