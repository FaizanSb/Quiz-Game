#include "QuizResultHandler.h"
#include "Interface.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <direct.h>

using namespace std;

void QuizResultHandler::resultCard(const Student &student) {
    
	Interface interface;
    int choice;
    string studentResult = "Student Results/" + student.getStudentName() + ".txt";

    string newFile = studentResult;

    int count = 1;

    int dotPos = newFile.find_last_of('.');
    studentResult = (dotPos != string::npos) ? newFile.substr(0, dotPos) : newFile;

    while (_access(newFile.c_str(), 0) == 0) {
    	
        newFile = studentResult + "[" + to_string(count) + "]" + ".txt";
        count++;
    }

    ofstream resultFile(newFile.c_str());
    ofstream highScoreFile("High Score/High Score.txt", ios::app);

    if (!resultFile) {
        cerr << "\aError Writing on file " << endl;
        return;
    }

    if (!highScoreFile) {
        cerr << "Error writing the file" << endl;
        return;
    }

    system("cls");
    interface.setColor(607);
    cout << "\t\t\t\t====================================================" << endl;
    cout << "\t\t\t\t                      Result Card                   " << endl;
    cout << "\t\t\t\t====================================================" << endl;
    interface.setColor(287);

    if (Quiz::score < Quiz::passingMarks) {
        interface.setColor(111);
        cout << "\n\t\t\tDon't feel bad, you can retake this Quiz." << endl;
        interface.setColor(287);
    }

    percentage = (static_cast<double>(Quiz::score) / Quiz::totalQuiz) * 100;

    if (percentage >= 80.0)
        grade = 'A';
    else if (percentage >= 70.0)
        grade = 'B';
    else if (percentage >= 60.0)
        grade = 'C';
    else
        grade = 'D';

    cout << setw(22) << left << "\n\n\t\t\t\t\tStudent Name:" << student.getStudentName() << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tStudent ID:" << student.getStudentId() << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tQuiz Subject:" << SubjectQuestions::subject << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tDifficulty:" << SubjectQuestions::quizDiff << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tQuestions:" << Quiz::totalQuiz << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tYour Score:" << Quiz::score << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tPercentage:" << percentage << " %" << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tGrade:" << grade << endl;
    cout << setw(21) << left << "\n\t\t\t\t\tStatus:" << ((Quiz::score >= Quiz::passingMarks) ? "PASS" : "FAIL") << endl;
    
    cout << "\n\nYour result card has been generated in Location: " << newFile << endl;

    resultFile << "\t\t\t===============================================================================" << endl;
    resultFile << "\t\t\t                    Result Card                                             " << endl;
    resultFile << "\t\t\t===============================================================================" << endl;
    resultFile << setw(22) << left << "\n\n\t\t\t\t\t\tPlayer Name:" << student.getStudentName() << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tRoll Number:" << student.getStudentId() << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tQuiz Subject:" << SubjectQuestions::subject << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tDifficulty:" << SubjectQuestions::quizDiff << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tQuestions:" << Quiz::totalQuiz << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tYour Score:" << Quiz::score << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tPercentage:" << percentage << " %" << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tGrade:" << grade << endl;
    resultFile << setw(21) << left << "\n\t\t\t\t\t\tStatus:" << ((Quiz::score >= Quiz::passingMarks) ? "PASS" : "FAIL") << endl;
    resultFile << "\n\n\n\t\t\t\t\t\t\t\tErrors and omissions are excepted " << endl;
    resultFile.close();

    highScoreFile << student.getStudentName() << endl; // writing line by line in the file
    highScoreFile << student.getStudentId() << endl;
    highScoreFile << SubjectQuestions::quizDiff << endl;
    highScoreFile << SubjectQuestions::subject << endl;
    highScoreFile << Quiz::score << endl;
    highScoreFile << Quiz::totalQuiz << endl;

    highScoreFile.close();
    interface.setColor(607);
    
    cout << "\nEnter 1 to return to the Student Menu: ";
    interface.setColor(287);
    cin >> choice;
    interface.studentMenu();
}

void QuizResultHandler::displayHighScore() {
	
    Interface interface;
    int choice;
    system("cls");
    system("COLOR 1F");
    ifstream highScoreFile;

    try {
    	
        highScoreFile.open("High Score/High Score.txt");
        if (!highScoreFile)
            throw 0;
    } 
	catch (int) {
		
        ofstream file("High Score/High Score.txt");
        file.close();
        highScoreFile.open("High Score/High Score.txt");
    }

    if (highScoreFile.peek() == ifstream::traits_type::eof()) { // when the file is empty
    
        cout << "Nothing Here yet. Be the first one to add your name in the Hall Of Fame" << endl;
    }

    vector<vector<string>> playerScores;
    vector<string> playerRecord(6);
    string line;

    while (getline(highScoreFile, line)) { // condition becomes false when looping through all lines
    
        playerRecord[0] = line;             // Player Name
        getline(highScoreFile, playerRecord[1]); // Roll Number
        getline(highScoreFile, playerRecord[2]); // Difficulty
        getline(highScoreFile, playerRecord[3]); // Subject
        getline(highScoreFile, playerRecord[4]); // Score
        getline(highScoreFile, playerRecord[5]); // Total Questions
        playerScores.push_back(playerRecord);    // Pushing in the 2D vector
    }

    highScoreFile.close();

    sort(playerScores.begin(), playerScores.end(), QuizResultHandler::compareScores); // function compare scores act as a comparator argument for sorting
    interface.setColor(607);
    cout << "===============================================================================================================" << endl;
    cout << "                                                   High Scores                                                 " << endl;
    cout << "===============================================================================================================" << endl;
    interface.setColor(287);
    interface.setColor(15);
    cout << setw(5) << left << "No" // formatting the output
         << setw(20) << left << "Player Name"
         << setw(20) << left << "Roll Number"
         << setw(20) << left << "Difficulty"
         << setw(20) << left << "Subject"
         << setw(11) << left << "Score"
         << setw(15) << left << "Total Questions" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    interface.setColor(287);
    for (int i = 0; i < playerScores.size(); ++i) { // for displaying high scores // condition depends upon rows // outer loop
        if (i > 0) {                                  // to display a line after the first loop
        
            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        }
        cout << setw(5) << left << (i + 1); // for numbering

        for (int j = 0; j < playerScores[i].size(); ++j) { // condition depends upon columns in the 2D vector // inner loop
        
            cout << setw(20) << left << playerScores[i][j]; // To display 2D playerScores vector elements
        }

        cout << endl;
    }

    interface.setColor(607);
    cout << "\nEnter 1 to return to the Student Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.studentMenu();
}

bool QuizResultHandler::compareScores(const vector<string> &a, const vector<string> &b) {
	
    return atoi(a[4].c_str()) > atoi(b[4].c_str()); // the formula that will compare scores on index 4 of playerScores vector
}

