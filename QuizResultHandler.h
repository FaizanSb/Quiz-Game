#ifndef QUIZRESULTHANDLER_H
#define QUIZRESULTHANDLER_H

#include <string>
#include <vector>
#include "Quiz.h"

using namespace std;

class QuizResultHandler : protected Quiz {
	
private:
	
    double percentage;
    char grade;

public:
	
    void resultCard(const Student &student);
    void displayHighScore();
    static bool compareScores(const vector<string> &a, const vector<string> &b);
};

#endif

