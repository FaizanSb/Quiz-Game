#ifndef Interface_H
#define Interface_H

#include "User.h"
#include "Student.h"
#include "Staff.h"
#include "SubjectQuestions.h"
#include "Quiz.h"
#include "QuizResultHandler.h"

class Interface {
	
    int choice;
    SubjectQuestions admin;
    Staff staff;
    Student student;
    Quiz quiz;
    QuizResultHandler result;

public:
	
    void uniInterface();
    void welcome();
    void menu();
    void staffloginMenu();
    void studentloginMenu();
    void subjectManagmentMenu();
    void quizManagmentMenu();
    void studentMenu();
    void staffMenu();
    void reportMenu();
    void setColor(int color);
};

#endif

