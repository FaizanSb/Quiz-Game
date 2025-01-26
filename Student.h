#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "User.h"

class Student : protected User {
	
public:
    
    std::string getStudentName() const;
    std::string getStudentId() const;
    std::string getStudentMail() const;
	void putStudentData();
    void reg();
    bool verify();
    void login();
    void reports();
};

#endif

