#ifndef USER_H
#define USER_H

#include <string>

class User {
	
protected:
	
    std::string name;
    std::string id;
    std::string email;
    char password[32];

public:
	
    virtual void login() = 0;
    virtual void reg() = 0;
    virtual bool verify() = 0;
    virtual void reports() = 0;
    virtual ~User() {}
};

#endif

