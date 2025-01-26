#ifndef STAFF_H
#define STAFF_H

#include <string>
#include "User.h"

class Staff : protected User {
	
public:
	
    void putStaffData();
    std::string getStaffName() const;
    std::string getStaffId() const;
    std::string getStaffMail() const;
    void reg();
    bool verify();
    void login();
    void reports();
    bool manageReports();
};

#endif

