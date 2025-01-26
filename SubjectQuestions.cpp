#include "SubjectQuestions.h"
#include "Interface.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

string SubjectQuestions::quizDiff = " ";
string SubjectQuestions::subject = " ";
Staff SubjectQuestions::staff;

void SubjectQuestions::adminHeader(Staff &admin) {
	
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Admin Id: " << admin.getStaffId()
         << setw(25) << right << "Admin Name: " << admin.getStaffName()
         << setw(25) << right << "Admin Email: " << admin.getStaffMail() << "                 " << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    SubjectQuestions::staff = admin;
    flag = 5;
    
}

void SubjectQuestions::setQuizRules() {
	
    Interface interface;
    double correctScore, wrongScore, totalQuestions, passingMarks;
    int choice;
    ofstream rules;

    system("cls");
    do {
    	
        rules.open("Record/Quiz Rules.txt");
        if (!rules)
            cout << "\aError writing on file" << endl;
        try {
        	
            system("COLOR 1F");
            interface.setColor(15);
            adminHeader(staff);
            interface.setColor(607);
            cout << "\t\t\t===============================================================" << endl;
            cout << "\t\t\t                           Quiz Rules                          " << endl;
            cout << "\t\t\t===============================================================" << endl;
            cout << "\n\n\t\t\t\tEnter Marks for correct answers: ";
            cin >> correctScore;
            cout << "\n\n\t\t\t\tEnter Marks for wrong answers: ";
            cin >> wrongScore;
            cout << "\n\n\t\t\t\tEnter total number of quiz Student can take: ";
            cin >> totalQuestions;
            cout << "\n\n\t\t\t\tEnter Passing marks: ";
            cin >> passingMarks;
            interface.setColor(287);
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

    } while (cin.fail());

    rules << correctScore << endl;
    rules << wrongScore << endl;
    rules << totalQuestions << endl;
    rules << passingMarks << endl;
    rules.close();
    system("cls");
}

bool SubjectQuestions::isSubjectFound() {
	
    string fileSubject;
    bool found;

    ifstream checkFile(subjectLocation.c_str());

    if (!checkFile) {
        cout << "Error opening file" << endl;
    }

    do {
    	
        found = false;

        checkFile.clear();
        checkFile.seekg(0, ios::beg);

        while (getline(checkFile, fileSubject)) {
            if (subject == fileSubject) {
            	
                found = true;
                break;
            }
        }
        return found;
    } while (!found);
    checkFile.close();
}

bool SubjectQuestions::isQuizFound() {
	
    string fileID;
    bool found;

    ifstream checkFile(quizLocation.c_str());

    if (!checkFile) {
        cout << "Error opening file in check quiz id" << endl;
    }

    do {
    	
        found = false;

        checkFile.clear();
        checkFile.seekg(0, ios::beg);

        while (getline(checkFile, fileID)) {
        	
            if (questionId == fileID) {
            	
                found = true;
                break;
            }
            getline(checkFile, fileID);
            getline(checkFile, fileID);
            getline(checkFile, fileID);
            getline(checkFile, fileID);
            getline(checkFile, fileID);
            getline(checkFile, fileID);
        }
        
        return found;
    } while (!found);
    checkFile.close();
}

void SubjectQuestions::addSubject() {
	
    Interface interface;
    int choice;
    string tempSubject;
    system("COLOR 1F");
    bool found = false;
    cin.ignore();
    system("cls");

    do {
    	
        subjectLocation = getSubjectFilePath();
        system("cls");
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                            Add Subject                        " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        interface.setColor(607);
        cout << "\n\n\n\n\n\t\t\t\t\tEnter Subject Name: ";
        getline(cin.ignore(), tempSubject);
        interface.setColor(287);
        subject = tempSubject;

        found = false;

        if (isSubjectFound()) {
        	
            found = true;
            system("cls");
            cout << subject << "\a subject already present." << endl;
        }
       
    } while (found);

    ofstream subjectFile(subjectLocation.c_str(), ios::app);

    if (!subjectFile) {
    	
        cerr << "Error writing to file" << endl;
        return;
    }

    subjectFile << subject << endl;
    subjectFile.close();
    cout << "Subject Successfully added.........." << endl;
    addQuiz(subject);
}

string SubjectQuestions::getSubjectFilePath() {
	
    Interface interface;
    int choice;

    do {
    	
        if (flag == 5) {
            interface.setColor(15);
            adminHeader(staff);
        }
        try {
        	
            interface.setColor(607);
            cout << "\t\t\t===============================================================" << endl;
            cout << "\t\t\t                            Difficulty                         " << endl;
            cout << "\t\t\t===============================================================" << endl;
            interface.setColor(287);
            cout << "\n\n\t\t\t\t\t\t1. Easy" << endl;
            cout << "\n\t\t\t\t\t\t2. Medium" << endl;
            cout << "\n\t\t\t\t\t\t3. Hard" << endl;
            interface.setColor(607);
            cout << "\n\t\t\t\t\tEnter your Choice: ";
            cin >> choice;
            interface.setColor(287);

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

        if (choice == 1) {
        	
            quizDiff = "Easy";
            return "Subjects/Easy/Subject List.txt";
        } 
		else if (choice == 2) {
			
            quizDiff = "Medium";
            return "Subjects/Medium/Subject List.txt";
        } 
		else if (choice == 3) {
			
            quizDiff = "Hard";
            return "Subjects/Hard/Subject List.txt";
        } 
		else {
			
            system("cls");
            cout << "\aInvalid Subject difficulty. Please enter Easy, Medium, or Hard." << endl;
        }
    } while (true);
}

void SubjectQuestions::addQuiz(const string subjectName) {
	
    string tempSubject;
    Interface interface;
    int i = 1, choice;
    string cOption;
    bool found = false, validOption;

    if (subjectName == " ") {
    	
        found = false;
        cin.ignore();
        system("cls");
        do {
        	
            system("COLOR 1F");
            subjectLocation = getSubjectFilePath();
            system("cls");
            interface.setColor(15);
            adminHeader(staff);
            interface.setColor(607);
            cout << "\t\t\t\t===============================================================" << endl;
            cout << "\t\t\t\t                            Add Quiz                           " << endl;
            cout << "\t\t\t\t===============================================================" << endl;
            interface.setColor(287);
            interface.setColor(607);
            cout << "\n\n\n\n\n\t\t\t\t\tEnter Subject for Quiz: ";
            getline(cin.ignore(), tempSubject);
            interface.setColor(287);
            subject = tempSubject;
            quizLocation = getQuizFilePath();

            found = false;
            if (isSubjectFound()) {
                found = true;
            }
            if (!found) {
            	
                system("cls");
                cout << "\aSubject not Exist. Please Add this First " << endl;
            }
        } while (!found);
		
    } 
	else {
    	
        system("cls");
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                               Add Quiz                        " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        quizLocation = getQuizFilePath();

    }

    ofstream quizFile(quizLocation.c_str(), ios::app);

    if (!quizFile) {
        cout << "Error writing on file" << endl;
        return;
    }
    interface.setColor(607);
    cout << "\n\t\t\tEnter total Questions to Add: ";
    cin >> totalQuestions;
    interface.setColor(287);
    cin.ignore();
    system("cls");

    while (i <= totalQuestions) {
    	
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                               Add Quiz                        " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        interface.setColor(607);
        cout << "\n\t\t\t" << i << ". Question ID: ";
        cin >> questionId;
        interface.setColor(287);
        if (isQuizFound()) {
        	
            system("cls");
            cout << "\a\t\tThis quiz ID is already exist.please enter different ID" << endl;
            continue;
        }
        
        interface.setColor(287);
        interface.setColor(831);
        cout << "\n\t\t\t\t" << i << ". Question Statement :";
        getline(cin.ignore(), question);
        interface.setColor(287);
        quizFile << questionId << endl;
        quizFile << question << endl;
        cout << "\n\t\t\t\t\tOption A: ";
        getline(cin, option1);
        cout << "\t\t\t\t\tOption B: ";
        getline(cin, option2);
        cout << "\t\t\t\t\tOption C: ";
        getline(cin, option3);
        cout << "\t\t\t\t\tOption D: ";
        getline(cin, option4);
        interface.setColor(287);
        quizFile << option1 << endl;
        quizFile << option2 << endl;
        quizFile << option3 << endl;
        quizFile << option4 << endl;

        do {
        	
            interface.setColor(15);
            cout << "\n\t\t\t\tEnter Correct Option: ";
            cin >> cOption;
            cOption[0] = toupper(cOption[0]);
            if (cOption.length() == 1 && (cOption[0] == 'A' || cOption[0] == 'B' || cOption[0] == 'C' || cOption[0] == 'D')) {
                validOption = true;
            }
            interface.setColor(287);
            if (!validOption)
                cerr << "\a\t\t\tIncorrect Option. Please Enter valid Option" << endl;

        } while (!validOption);

        quizFile << cOption << endl;
        i++;

        system("cls");
    }

    if (i > totalQuestions) {
    	
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                               Add Quiz                        " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        cout << "\n\t\t\t\t" << totalQuestions << " Quiz Added Sucessfully......" << endl;
    }

    quizFile.close();

    cout << "\nEnter 1 to return to  Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.quizManagmentMenu();
}
string SubjectQuestions::getQuizFilePath() {
  	
	if (quizDiff == "Easy" || quizDiff == "easy" || quizDiff == "EASY") {
        return "Subjects/Easy/" + subject + ".txt";
    } else if (quizDiff == "Medium" || quizDiff == "medium" || quizDiff == "MEDIUM") {
        return "Subjects/Medium/" + subject + ".txt";
    } else if (quizDiff == "Hard" || quizDiff == "hard" || quizDiff == "HARD") {
        return "Subjects/Hard/" + subject + ".txt";
    }

}

void SubjectQuestions::searchQuiz() {
	
    Interface interface;
    int choice;
    system("COLOR 1F");
    string fileId, cOption, tempSubject;
    bool found = false;

    ifstream fileread;
    system("cls");

    do {
    	
        subjectLocation = getSubjectFilePath();
        system("cls");
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                           Search Quiz                         " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        interface.setColor(607);
        cout << "\n\t\t\t\t\tEnter Quiz Subject: ";
        getline(cin.ignore(), tempSubject);
        interface.setColor(287);
        subject = tempSubject;
        quizLocation = getQuizFilePath();
        interface.setColor(607);
        cout << "\n\t\t\t\t\tEnter Quiz ID: ";
        cin >> questionId;
        interface.setColor(287);

        fileread.open(quizLocation.c_str());
        if (!fileread) {

            cout << "\n\t\t\tWrong Subject Name please add this Subject first" << endl;
            interface.setColor(607);
            cout << "\n\t\t\tEnter 1 to add this Subject: ";
            cin >> choice;
            interface.setColor(287);
            addSubject();

        }

        fileread.clear();           // Clear any error flags
        fileread.seekg(0, ios::beg); // Rewind the file to the beginning to search for existing subjects
        found = false;
        while (getline(fileread, fileId)) {

            getline(fileread, question);
            getline(fileread, option1);
            getline(fileread, option2);
            getline(fileread, option3);
            getline(fileread, option4);
            getline(fileread, cOption);
            if (questionId == fileId) {

                found = true;
                cout << "\n\t\tQuiz Found Successfully..." << endl;
                interface.setColor(607);
                cout << "\n\t\t\tQuestion ID: " << questionId << endl;
                interface.setColor(831);
                cout << "\n\t\t\t\tQuestion: " << question << endl;
                interface.setColor(287);
                cout << "\n\t\t\t\t\tOption A: " << option1 << endl;
                cout << "\t\t\t\t\tOption B: " << option2 << endl;
                cout << "\t\t\t\t\tOption C: " << option3 << endl;
                cout << "\t\t\t\t\tOption D: " << option4 << endl;
                interface.setColor(15);
                cout << "\n\t\t\t\tCorrect Option: " << cOption << endl;
                interface.setColor(607);
                break;

            }
        }
        if (!found) {
        	
            system("cls");
            cout << "\aWrong Quiz ID try again" << endl;
        }

    } while (!found);
    fileread.close();

    interface.setColor(607);
    cout << "\nEnter 1 to return to  Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.quizManagmentMenu();
}

void SubjectQuestions::updateQuiz() {

    system("COLOR 1F");
    Interface interface;
    string fileId, updateId, updateQuestion, updateOptions, updateCorrectOption, cOption, tempSubject;

    bool found = false, validOption;
    int selection;
    char choice;
    system("cls");
    subjectLocation = getSubjectFilePath();
    system("cls");
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                        Update Quiz                            " << endl;
    cout << "\t\t\t===============================================================" << endl;
    interface.setColor(607);
    cout << "\n\t\t\t\t\tEnter Subject: ";
    getline(cin.ignore(), tempSubject);
    interface.setColor(287);
    subject = tempSubject;
    quizLocation = getQuizFilePath();

    ifstream file(quizLocation.c_str()); // Read
    ofstream tempFile("temp.txt");       // Write

    if (!file) {
    	
        cout << "\n\t\t\tWrong Subject Name please add this Subject first" << endl;
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        interface.setColor(287);
        addSubject();
    }

    if (!tempFile) {
    	
        cout << "Error creating temporary file" << endl;
        return;
    }

    interface.setColor(607);
    cout << "\n\t\t\t\t\tEnter Quiz ID :";
    cin >> questionId;
    interface.setColor(287);
    cin.ignore();
    while (getline(file, fileId)) {
    	
        getline(file, question);
        getline(file, option1);
        getline(file, option2);
        getline(file, option3);
        getline(file, option4);
        getline(file, cOption);

        if (questionId == fileId) {

            found = true;
            cout << "\n\t\tIs this Quiz you want to update?" << endl;
            interface.setColor(607);
            cout << "\n\t\tQuestion ID: " << questionId << endl;
            interface.setColor(831);
            cout << "\n\t\t\tQuestion: " << question << endl;
            interface.setColor(287);
            cout << "\n\t\t\tOption A: " << option1 << endl;
            cout << "\t\t\tOption B: " << option2 << endl;
            cout << "\t\t\tOption C: " << option3 << endl;
            cout << "\t\t\tOption D: " << option4 << endl;
            interface.setColor(15);
            cout << "\n\t\tCorrect Option: " << cOption << endl;
            interface.setColor(607);
            cout << "\n\t\tDo you want to update this quiz? (y/n): ";
            cin >> choice;
            choice = toupper(choice);
            interface.setColor(287);

            if (choice == 'Y') {

                interface.setColor(607);
                cout << "\n\t\tEnter question ID: ";
                cin >> updateId;
                interface.setColor(287);
                tempFile << updateId << endl;
                cin.ignore();
                interface.setColor(831);
                cout << "\n\t\t\tQuestion: ";
                getline(cin, updateQuestion);
                interface.setColor(287);
                tempFile << updateQuestion << endl;
                cout << "\n";
                for (int i = 0; i < 4; i++) {

                    cout << "\t\t\tOption " << static_cast<char>('A' + i) << ": ";
                    getline(cin, updateOptions);
                    tempFile << updateOptions << endl;

                }

                do {

                    interface.setColor(15);
                    cout << "\n\t\t\t\tEnter Correct Option: ";
                    cin >> updateCorrectOption;
                    updateCorrectOption[0] = toupper(updateCorrectOption[0]);
                    if (updateCorrectOption.length() == 1 && (updateCorrectOption[0] == 'A' || updateCorrectOption[0] == 'B' || updateCorrectOption[0] == 'C' || updateCorrectOption[0] == 'D')) {
                    	
                        validOption = true;
                    }
                    interface.setColor(287);
                    if (!validOption)
                        cerr << "a\t\t\tIncorrect Option.Please Enter valid Option" << endl;
				} while (!validOption);

                tempFile << updateCorrectOption << endl;
                cout << "\n\t\t\tQuiz updated successfully!" << endl;
            }

        } else {

            tempFile << fileId << endl;
            tempFile << question << endl;
            tempFile << option1 << endl;
            tempFile << option2 << endl;
            tempFile << option3 << endl;
            tempFile << option4 << endl;
            tempFile << cOption << endl;

        }
    }

    if (!found) {
    	
        cout << "\n\t\tQuiz not found. Please add Quiz first." << endl;
        interface.setColor(607);
        cout << "\n\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        interface.setColor(287);
        addQuiz();
    }

    file.close();
    tempFile.close();
    remove(quizLocation.c_str());
    rename("temp.txt", quizLocation.c_str());
    interface.setColor(607);
    cout << "\nEnter 1 to return to  Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.quizManagmentMenu();
}

void SubjectQuestions::deleteQuiz() {
	
    system("COLOR 1F");
    string fileId, cOption, tempSubject;
    Interface interface;
    bool found = false;
    char choice;
    system("cls");

    subjectLocation = getSubjectFilePath();
    system("cls");
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                          Delete Quiz                          " << endl;
    cout << "\t\t\t===============================================================" << endl;
    interface.setColor(287);
    interface.setColor(607);
    cout << "\n\t\t\t\t\tEnter Subject: ";
    getline(cin.ignore(), tempSubject);
    interface.setColor(287);
    subject = tempSubject;
    quizLocation = getQuizFilePath();
    ifstream file(quizLocation.c_str()); // Read
    ofstream tempFile("temp.txt");      // Write

    if (!file) {
    	
        cout << "\n\t\t\tWrong Subject Name, please add this Subject first" << endl;
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        interface.setColor(287);
        addSubject();
    }

    interface.setColor(607);
    cout << "\n\t\t\t\t\tEnter Quiz ID: ";
    cin >> questionId;
    interface.setColor(287);

    if (!tempFile) {
        cout << "Error creating temporary file" << endl;
        return;
    }

    while (getline(file, fileId)) {
    	
        getline(file, question);
        getline(file, option1);
        getline(file, option2);
        getline(file, option3);
        getline(file, option4);
        getline(file, cOption);

        if (questionId == fileId) {
        	
            found = true;
            cout << "\n\t\tIs this Quiz you want to delete?" << endl;
            interface.setColor(607);
            cout << "\n\t\tQuestion ID: " << questionId << endl;
            interface.setColor(831);
            cout << "\n\t\t\tQuestion: " << question << endl;
            interface.setColor(287);
            cout << "\n\t\t\tOption A: " << option1 << endl;
            cout << "\t\t\tOption B: " << option2 << endl;
            cout << "\t\t\tOption C: " << option3 << endl;
            cout << "\t\t\tOption D: " << option4 << endl;
            interface.setColor(15);
            cout << "\n\t\tCorrect Option: " << cOption << endl;
            interface.setColor(607);
            cout << "\t\tDo you want to delete this quiz? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
            	
                cout << "\n\t\t\tQuiz deleted successfully!" << endl;
            } 
			else {
				
                tempFile << fileId << endl;
                tempFile << question << endl;
                tempFile << option1 << endl;
                tempFile << option2 << endl;
                tempFile << option3 << endl;
                tempFile << option4 << endl;
                tempFile << cOption << endl;
            }
        } 
		else {
        	
            tempFile << fileId << endl;
            tempFile << question << endl;
            tempFile << option1 << endl;
            tempFile << option2 << endl;
            tempFile << option3 << endl;
            tempFile << option4 << endl;
            tempFile << cOption << endl;
        }
    }

    if (!found) {
    	
        tempFile.close();
        remove("temp.txt");
        cout << "\n\t\tQuiz not found. Nothing to delete." << endl;
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to add this Quiz: ";
        cin >> choice;
        interface.setColor(287);
        addQuiz();
    }

    file.close();
    tempFile.close();
    remove(quizLocation.c_str());
    rename("temp.txt", quizLocation.c_str());
    interface.setColor(607);
    cout << "\nEnter 1 to return to Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.quizManagmentMenu();
}

void SubjectQuestions::viewQuiz() {
	
    system("COLOR 1F");
    string line, tempSubject;
    bool found = false;
    int choice;
    system("cls");

    subjectLocation = getSubjectFilePath();
    system("cls");
    Interface interface;
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                          View Quiz                            " << endl;
    cout << "\t\t\t===============================================================" << endl;
    interface.setColor(287);
    interface.setColor(607);
    cout << "\n\t\t\t\t\tEnter Subject: ";
    getline(cin.ignore(), tempSubject);
    interface.setColor(287);
    subject = tempSubject;
    quizLocation = getQuizFilePath();

    ifstream file(quizLocation.c_str()); // Read

    if (!file) {
    	
        cout << "\n\t\t\tWrong Subject Name, please add this Subject first" << endl;
        cout << "\n\t\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        addSubject();
    }
    cout << "\n" << endl;
    while (getline(file, line)) {
    	
        interface.setColor(607);
        cout << "\tQuestion Id: " << line << endl;
        getline(file, line);
        interface.setColor(831);
        cout << "\n\t\tQuestion Statement: " << line << endl;
        getline(file, line);
        interface.setColor(287);
        cout << "\t\tOption A: " << line << endl;
        getline(file, line);
        cout << "\t\tOption B: " << line << endl;
        getline(file, line);
        cout << "\t\tOption C: " << line << endl;
        getline(file, line);
        cout << "\t\tOption D: " << line << endl;
        getline(file, line);
        interface.setColor(15);
        cout << "\t\tCorrect Option: " << line << endl;
        interface.setColor(287);
        cout << "\n\t--------------------------------------------" << endl;
    }

    file.close();
    interface.setColor(607);
    cout << "\nEnter 1 to return to Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.quizManagmentMenu();
}

void SubjectQuestions::updateSubjectName() {
	
    Interface interface;
    system("COLOR 1F");
    string fileSubject, updateQuiz;
    bool found = false;
    char choice;
    system("cls");

    subjectLocation = getSubjectFilePath();
    system("cls");
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                        Update Subject                         " << endl;
    cout << "\t\t\t===============================================================" << endl;
    interface.setColor(287);
    interface.setColor(607);
    cout << "\n\n\n\n\n\t\t\t\t\tEnter Subject to Update: ";
    getline(cin.ignore(), subject);
    interface.setColor(287);
    quizLocation = getQuizFilePath();
    ifstream file(subjectLocation.c_str()); // read
    ofstream tempFile("temp.txt");          // write

    if (!file) {
    	
        cout << "\n\t\t\tWrong Subject Name, please add this Subject first" << endl;
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        interface.setColor(287);
        addSubject();
    }

    if (!tempFile) {
        cout << "Error Temp file" << endl;
    }

    while (getline(file, fileSubject)) { 
    
        if (subject == fileSubject) {    
		  
            interface.setColor(607);
            cout << "\n\t\t\t\t\tIs that subject you want to update (y/n): ";
            cout << "\n\t\t\t\t\tSubject: " << fileSubject << " ";
            cin >> choice;
            interface.setColor(287);

            if (choice == 'y') {
            	
                found = true;
                subject = getQuizFilePath();
                interface.setColor(607);
                cout << "\n\t\t\t\t\tEnter subject name to update: ";
                getline(cin.ignore(), subject);
                interface.setColor(287);
                updateQuiz = getQuizFilePath();
                tempFile << subject << endl;
            }
        } 
		else {
			
            tempFile << fileSubject << endl;
        }
    }

    if (found) {
    	
        tempFile.close();
        file.close();
        cout << "\n\t\t\t\t\tUpdated Successfully" << endl;
        rename(quizLocation.c_str(), updateQuiz.c_str());
    }

    if (!found) {
    	
        cout << "\n\t\t\t\t\tNot found. Please add the Subject....." << endl;
        interface.setColor(607);
        cout << "\n\t\t\t\t Press Enter to add Subject: ";
        cin.get();
        interface.setColor(287);
        addSubject();
    }

    tempFile.close();
    file.close();

    remove(subjectLocation.c_str());
    rename("temp.txt", subjectLocation.c_str());
    interface.setColor(607);
    cout << "\nEnter 1 to return to Menu: ";
    cin >> choice;
    interface.setColor(287);

    interface.subjectManagmentMenu();
}

void SubjectQuestions::deleteSubject() {
	
    system("COLOR 1F");
    Interface interface;
    int choice;
    string fileSubject, quizFileName, tempSubject;
    bool found = false;
    system("cls");

    subjectLocation = getSubjectFilePath();
    system("cls");
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                           Delete Subject                      " << endl;
    cout << "\t\t\t===============================================================" << endl;
    interface.setColor(287);
    interface.setColor(607);
    cout << "\n\n\n\n\n\t\t\t\t\tEnter Subject to Delete: ";
    getline(cin.ignore(), tempSubject);
    interface.setColor(287);
    subject = tempSubject;
    quizLocation = getQuizFilePath();
    ifstream file(subjectLocation.c_str()); //read
    ofstream tempFile("temp.txt");          //write

    if (!file) {
    	
        cout << "\n\t\t\tWrong Subject Name, please add this Subject first" << endl;
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to add this Subject: ";
        cin >> choice;
        interface.setColor(287);
        addSubject();
    }

    if (!tempFile) {
    	
        cout << "Error Temp file" << endl;
    }

    while (getline(file, fileSubject)) {
    	
        if (subject == fileSubject) {
            found = true;
        } 
		else {
            tempFile << fileSubject << endl;
        }
    }

    if (found) {
    	
        cout << "\n\n\t\t\t\t\tDeleted Successfully" << endl;
        remove(quizLocation.c_str());
    } 
	else {
    	
        cout << "\n\n\t\t\t\t\tSubeject Not Found. Nothing to delete" << endl;
    }

    file.close();
    tempFile.close();
    remove(subjectLocation.c_str());
    rename("temp.txt", subjectLocation.c_str());
    interface.setColor(607);
    cout << "\nEnter 1 to return to Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.subjectManagmentMenu();
}

string SubjectQuestions::viewSubjects() {
	
    system("COLOR 1F");
    Interface interface;
    int choice,i;
    vector<string> subjects;

    system("cls");
    subjectLocation = getSubjectFilePath();
    system("cls");
    interface.setColor(15);
    adminHeader(staff);
    interface.setColor(607);
    cout << "\t\t\t===============================================================" << endl;
    cout << "\t\t\t                          View Subjects                        " << endl;
    cout << "\t\t\t===============================================================\n\n" << endl;
    interface.setColor(287);

    ifstream readFile(subjectLocation.c_str());
    if (!readFile) {
        cout << "Error reading file" << endl;
    }

    string line;
    while (getline(readFile, line)) {
    	
        subjects.push_back(line);
    }

    do {
    	
        try {
        	
            system("cls");
            interface.setColor(15);
            adminHeader(staff);
            interface.setColor(607);
            cout << "\t\t\t===============================================================" << endl;
            cout << "\t\t\t                          View Subjects                        " << endl;
            cout << "\t\t\t===============================================================\n\n" << endl;
            interface.setColor(287);

            if (subjects.size() == 0) {
                cout << "\n\t\t\tNo Subject here. Please Add subjects to show here  " << endl;
                interface.setColor(607);
                cout << "\n\t\t\tEnter to Add Subjects: ";
                cin.get();
                interface.setColor(287);
                addSubject();
            }

            for (i = 0; i < subjects.size(); i++) {
            	
                cout << "\t\t\t\t\t\t" << i + 1 << "." << subjects[i] << "\n" << endl;

                if (i == subjects.size() - 1) {
                	
                    cout << "\t\t\t\t\t\t" << i + 2 << ".Manage Quizes\n" << endl;
                    cout << "\t\t\t\t\t\t" << i + 3 << ".Return to Menu" << endl;
                }
            }

            interface.setColor(607);
            cout << "\n\t\t\tEnter your Choice: ";
            cin >> choice;
            interface.setColor(287);

            if (cin.fail()) {
                throw 0;
            }
        } 
		catch (int) {
			
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cerr << "\aInvalid choice. Please try again." << endl;
            continue;
        }

        for (int j = 0; j < subjects.size(); j++) {
        	
            if (choice == j + 1) {
            	
                subject = subjects[j];
                interface.subjectManagmentMenu();
            } 
			else if (choice == subjects.size() + 1) {
				
                interface.quizManagmentMenu();
            } 
			else if (choice == subjects.size() + 2) {
				
                interface.subjectManagmentMenu();
            }
        }

    } while (choice = i + 3);
}

void SubjectQuestions::searchSubject() {
	
    Interface interface;
    int choice;
    system("COLOR 1F");
    bool found = false;
    string tempSubject;
    system("cls");

    do {
    	
        subjectLocation = getSubjectFilePath();
        system("cls");
        interface.setColor(15);
        adminHeader(staff);
        interface.setColor(607);
        cout << "\t\t\t===============================================================" << endl;
        cout << "\t\t\t                        Search Subject                         " << endl;
        cout << "\t\t\t===============================================================" << endl;
        interface.setColor(287);
        interface.setColor(607);
        cout << "\n\n\n\n\n\t\t\t\t\tEnter Subject to Search: ";
        getline(cin.ignore(), tempSubject);
        interface.setColor(287);
        subject = tempSubject;

        if (isSubjectFound()) {
        	
            found = true;
            break;
        }

        if (!found) {
        	
            found = false;
            system("cls");
            cout << "\aSubject Not Found. Please try again" << endl;
        }
    } while (!found);

    if (found) {
    	
        cout << "\n\t\t\t\t\t\tThe subject is found" << endl;
        cout << "\n\t\t\t\t\t\t\tSubject: " << subject << endl;
    }

    interface.setColor(607);
    cout << "\nEnter 1 to return to Menu: ";
    cin >> choice;
    interface.setColor(287);
    interface.subjectManagmentMenu();
}
