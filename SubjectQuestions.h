#ifndef SUBJECTQUESTIONS_H
#define SUBJECTQUESTIONS_H

#include <string>
#include "Staff.h"

class SubjectQuestions {
	
protected:
	
    std::string questionId;
    int totalQuestions;
    std::string question;
    std::string option1, option2, option3, option4;
    char correctOption;
    std::string subjectLocation;
    std::string quizLocation;
    int flag;

public:
	
    static std::string subject;
    static Staff staff;
    static std::string quizDiff;

    void setQuizRules();
    void addSubject();
    void updateSubjectName();
    void deleteSubject();
    void searchSubject();
    virtual std::string viewSubjects();
    void addQuiz(const std::string subjectName = " ");
    void searchQuiz();
    void updateQuiz();
    void deleteQuiz();
    void viewQuiz();
    std::string getSubjectFilePath();
    std::string getQuizFilePath();
    bool isSubjectFound();
    bool isQuizFound();
    void adminHeader(Staff &admin);
};

#endif

