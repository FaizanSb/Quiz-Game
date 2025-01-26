#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>
#include "SubjectQuestions.h"
#include "Student.h"

class Quiz : protected SubjectQuestions {
	
private:
	
    double correctScore;
    double incorrectScore;
    int correctAnswers;
    int incorrectAnswers;
    int remainingQuestions;
    std::vector<char> correctOptions;
    std::vector<std::string> questions;
    std::vector<std::string> options;

public:
	
    Quiz();
    static Student student;
    static double passingMarks;
    static double score;
    static int totalQuiz;
    std::string viewSubjects();
    void scoreHeader(Student& stud);
    bool startQuiz();
    void displayKey(std::vector<char> userAnswers, std::vector<int> indices, int RandomIndex);
    void displayQuizRules();
};

#endif // QUIZ_H

