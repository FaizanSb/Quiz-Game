#include "Quiz.h"
#include "SubjectQuestions.h"
#include "Interface.h"
#include <iostream>
#include "Student.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

double Quiz::passingMarks = 0;
double Quiz::score = 0;
int Quiz::totalQuiz = 0;
Student Quiz::student;

Quiz::Quiz() : correctScore(0), incorrectScore(0), correctAnswers(0), incorrectAnswers(0), remainingQuestions(0) {}

string Quiz::viewSubjects() {
	
    Student student;
    Interface interface;
    int choice;
    string line;
    vector<string> subjects;
    system("cls");
    system("COLOR 1F");
    subjectLocation = SubjectQuestions::getSubjectFilePath();
    quizLocation = SubjectQuestions::getQuizFilePath();
    
    ifstream readFile(subjectLocation.c_str());
    if (!readFile) {
        cout << "Error reading file" << endl;
    }

    while (getline(readFile, line)) {
    	
        subjects.push_back(line);
    }
    bool validChoice;
    system("cls");
    do {
    	
        try {

            system("COLOR 1F");
            interface.setColor(607);
            cout << "\t\t\t===============================================================" << endl;
            cout << "\t\t\t                         Select a Quiz Subject                 " << endl;
            cout << "\t\t\t===============================================================" << endl;
            interface.setColor(287);

            if (subjects.size() == 0) {

                cout << "No Subject here..Please Contact Administator" << endl;
                interface.setColor(607);
                cout << "Enter 1 to report to Admin: ";
                cin >> choice;
                interface.setColor(287);
                student.reports();
                break;
            }
            interface.setColor(15);
            cout << "\n\t\t\t\tPlease choose the subject for the Quiz\n" << endl;
            interface.setColor(287);

            for (int i = 0; i < subjects.size(); i++) {
            	
                cout << "\t\t\t\t\t" << i + 1 << ". " << subjects[i] << "\n" << endl;

                if (i == subjects.size() - 1) {
                	
                    cout << "\t\t\t\t\t" << i + 2 << ". Return to Menu" << endl;
                }
            }

            interface.setColor(607);
            cout << "\n\t\t\t\tEnter your Choice: ";
            cin >> choice;

            if (cin.fail())
                throw 0;
        } 
		catch (int) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cerr << "\a\t\t\aInvalid choice. Please try again." << endl;
            continue;
        }

        interface.setColor(287);
        if (choice == subjects.size() + 1) {
        	
            validChoice = true;
            interface.studentMenu();
            break;
        }
        subject = subjects[choice - 1];
        validChoice = true;

    } while (!validChoice);

    return subject;
}

void Quiz::displayQuizRules() {

    Interface interface;
    int choice;
    double num;
    ifstream quizRules;

    try {

        quizRules.open("Record/Quiz Rules.txt");
        if (!quizRules)
            throw 0;
    } 
	catch (int) {

        ofstream rules("Record/Quiz Rules.txt");
        correctScore = 1;
        rules << correctScore << endl;
        incorrectScore = 0.5;
        rules << incorrectScore << endl;
        totalQuiz = 10;
        rules << totalQuiz << endl;
        passingMarks = 5;
        rules << passingMarks << endl;
        rules.close();
        quizRules.open("Record/Quiz Rules.txt");
    }

    quizRules >> num;
    correctScore = num;
    quizRules >> num;
    incorrectScore = num;
    quizRules >> num;
    totalQuiz = num;
    quizRules >> num;
    passingMarks = num;

    quizRules.close();

    system("cls");
    interface.setColor(607);
    cout << "\t\t\t========================================================================== " << endl;
    cout << "\t\t\t                                Quiz Rules                                 " << endl;
    cout << "\t\t\t========================================================================== " << endl;
    interface.setColor(287);
    cout << "\n\t\t\t\ta.There are " << totalQuiz << " questions in total." << endl;
    cout << "\n\t\t\t\tb.Every Question have four options Enter the correct one." << endl;
    cout << "\n\t\t\t\tc.Each question carries " << correctScore << " point." << endl;
    cout << "\n\t\t\t\td.Each incorrect answer results in a deduction of " << incorrectScore << " point." << endl;
    cout << "\n\t\t\t\te.Skip questions cannot consider as wrong." << endl;
    cout << "\n\t\t\t\tf.Student Who got " << passingMarks << " points are considered as PASS otherwise FAIL." << endl;
    interface.setColor(607);
    cout << "\n\t\t\tEnter 1 to start the quiz: ";
    cin >> choice;
    interface.setColor(287);

    remainingQuestions = totalQuiz - 1;
}

bool Quiz::startQuiz() {

    Interface interface;

    vector<char> studentAnswers;

    string line, fileName;
    int questionNumber = 0, randomIndex, choice;
    bool validAnswer = false;
    string userOption;
    quizLocation = SubjectQuestions::getQuizFilePath();

    ifstream quizFile(quizLocation.c_str());

    if (!quizFile) {

        cerr << "\n\aFailed to open the file." << endl;
        return false;
    }

    while (getline(quizFile, line)) {

        getline(quizFile, line);
        questions.push_back(line); // pushing question in to question vector // line 0 txt file

        for (int i = 0; i < 4; i++) { // pushing 4 options into the options vector line 1-4 txt file

            getline(quizFile, line);
            options.push_back(line);
        }

        getline(quizFile, line);
        correctOptions.push_back(line[0]); // pushing correct option into the correctOptions vector // line 5 txt file

        questionNumber++;
    }

    quizFile.close();

    if (questionNumber < totalQuiz) {

        cerr << "\aNot enough quiz please contact Administrator.." << endl;
        interface.setColor(607);
        cout << "\nPress 1 to send report to admin: ";
        cin >> choice;
        interface.setColor(287);
        return false;
    }

    interface.setColor(287);

    vector<int> questionIndices(questionNumber); // for random shuffling vector index will be proportional to questionNumber

    for (int i = 0; i < totalQuiz; i++) {

        questionIndices[i] = i; // giving values to question indices for index 0-9
    }

    srand(static_cast<int>(time(NULL))); // for randomizing questions every time the quiz starts
    random_shuffle(questionIndices.begin(), questionIndices.end()); // random shuffling
    correctAnswers = 0;
    incorrectAnswers = 0;

    for (int i = 0; i < totalQuiz; i++) { // printing questions

        cin.get();
        remainingQuestions--;
        randomIndex = questionIndices[i]; // Assigning question indices vector elements to random index for using in question, option, correctOption index
        interface.setColor(831);
        cout << "\n\nQuestion #" << (i + 1) << ": " << questions[randomIndex] << "\n" << endl; // Displaying Question
        interface.setColor(287);

        for (int j = 0; j < 4; j++) { // printing options

            cout << static_cast<char>('A' + j) << ". " << options[randomIndex * 4 + j] << endl; // printing 4 options respective to random index
        }
        do {

            interface.setColor(607);
            cout << "\nEnter your answer (A, B, C, D or E to End quiz): ";
            cin >> userOption;
            interface.setColor(287);
            userOption[0] = toupper(userOption[0]);

            if (userOption.length() == 1 && (userOption[0] == 'A' || userOption[0] == 'B' || userOption[0] == 'C' || userOption[0] == 'D' || userOption[0] == 'E')) {

                validAnswer = true;

                if (userOption[0] == 'E') { // Quiz End by user

                    system("cls");
                    scoreHeader(student);
                    interface.setColor(287);
                    interface.studentMenu(); // After ending the quiz return to resultCard() function to show result
                } else if (userOption[0] == correctOptions[randomIndex]) { // authentication

                    score += correctScore;
                    correctAnswers++;
                    studentAnswers.push_back(userOption[0]);
                    system("cls");
                    scoreHeader(student);
                } else {

                    incorrectAnswers++;
                    score -= incorrectScore;
                    studentAnswers.push_back(userOption[0]);
                    system("cls");
                    scoreHeader(student);
                }

            } else {

                cerr << "\aInvalid input. Please enter a valid character (A, B, C, or D).\n";
                validAnswer = false;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!validAnswer);
    }
    interface.setColor(607);
    cout << "\n\n\n\n\tEnter 1 to see Quiz Key: ";
    cin >> choice;
    interface.setColor(287);

    displayKey(studentAnswers, questionIndices, randomIndex);
}

void Quiz::displayKey(vector<char> userAnswers, vector<int> indices, int randomIndex) {

    Interface interface;
    int choice;
    system("cls");
    interface.setColor(607);
    cout << "===============================================================================================" << endl;
    cout << "                                        " << subject << " Key                                                " << endl;
    cout << "===============================================================================================" << endl;
    interface.setColor(287);

    for (int i = 0; i < totalQuiz; i++) { // printing questions

        randomIndex = indices[i];
        cout << "\nQuestion #" << (i + 1) << ": " << questions[randomIndex] << "\n" << endl; // Displaying Question
        interface.setColor(287);

        for (int j = 0; j < 4; j++) { // printing options

            cout << static_cast<char>('A' + j) << ". " << options[randomIndex * 4 + j] << endl; // printing 4 options respective to random index
        }

        interface.setColor(15);
        cout << "\nCorrect Option: " << correctOptions[randomIndex];
        interface.setColor(287);
        interface.setColor(335);
        cout << "\tStudent Answer: " << userAnswers[i] << endl;
        interface.setColor(287);
    }

    interface.setColor(607);
    cout << "Enter 1 to see your Result Card: ";
    cin >> choice;
    interface.setColor(287);
}

void Quiz::scoreHeader(Student &stud) {

    Interface interface;
    student = stud;

    interface.setColor(607);

    cout << "===============================================================================================" << endl;
    cout << "                                        " << subject << " Quiz                                                " << endl;
    cout << "===============================================================================================" << endl;
    interface.setColor(287);
    interface.setColor(15);
    cout << "Total Questions: " << totalQuiz
         << setw(24) << "Questions Left: " << ((remainingQuestions == -1) ? remainingQuestions = 0 : remainingQuestions)
         << setw(25) << "Correct Answers: " << correctAnswers
         << setw(24) << "Incorrect Answers : " << incorrectAnswers << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    interface.setColor(351);
    cout << "Student Name: " << stud.getStudentName() << "                 Roll Number: " << stud.getStudentId() << "                Difficulty: " << SubjectQuestions::quizDiff << endl;
    interface.setColor(287);
}

