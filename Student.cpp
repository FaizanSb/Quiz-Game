#include "Student.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <conio.h>
#include "Interface.h"

using namespace std;

string Student::getStudentName() const {
	
    return name;
}

string Student::getStudentId() const {
	
    return id;
}

string Student::getStudentMail() const {
	
    return email;
}

void Student::putStudentData() {
	
    Interface interface;
    interface.setColor(607);
    int i = 0;
    char a;

    cout << "\n\n\n\t\t\t\t\tEnter Student Id: ";
    getline(cin, id);

    cout << "\n\n\t\t\t\t\tEnter Student Name: ";
    getline(cin, name);

    cout << "\n\n\t\t\t\t\tEnter Student Email: ";
    getline(cin, email);

    cout << "\n\n\t\t\t\t\tEnter Password: ";
    for (i = 0;;) {
    	
        a = getch();

        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || (a >= 32 && a <= 126)) {
        	
            password[i] = a;
            ++i;
            cout << "*";
        }

        else if (a == '\b' && i >= 1) {
        	
            cout << "\b \b";
            --i;
        }

        else if (a == '\r') {
        	
            password[i] = '\0';
            break;
        }
    }
}

void Student::reports() {
	
    Interface interface;
    string title, description;
    ofstream report("Record/Reports.txt", ios::app);

    if (!report) {
        cout << "Error writing on file" << endl;
    }

    cin.ignore();
    system("cls");
    system("COLOR 1F");
    interface.setColor(607);

    cout << "\t\t\t=====================================================================" << endl;
    cout << "\t\t\t                            Send Report                              " << endl;
    cout << "\t\t\t=====================================================================" << endl;

    report << id << endl;
    report << name << endl;

    cout << "\n\n\n\t\t\t\tEnter report title: ";
    getline(cin, title);

    cout << "\n\n\t\t\t\tEnter report Description: ";
    getline(cin, description);

    report << title << endl;
    report << description << endl;
    report.close();
    system("cls");
}

void Student::reg() {
	
    Interface interface;
    string fileName;
    verify();
    fileName = "Record/Student Record.txt";
    ofstream regFile(fileName.c_str(), ios::app);

    if (!regFile) {
        cerr << "Error Writing on file" << endl;
    }

    interface.setColor(287);
    cout << "\n\n\n\t\t\t\t\t\t\tRegistered Successfully";
    interface.setColor(607);

    for (int dots = 0; dots < 3; ++dots) {
    	
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ".";
        cout.flush();
    }

    cout << endl;

    regFile << id << endl;
    regFile << name << endl;
    regFile << email << endl;
    regFile << password << endl;

    regFile.close();
    system("cls");
}

bool Student::verify() {
	
    Interface interface;
    string fileId, fileName;
    bool found = false;

    fileName = "Record/Student Record.txt";
    ifstream checkFile(fileName.c_str());
    cin.ignore();

    do {
    	
        system("COLOR 1F");
        interface.setColor(607);

        cout << "\t\t\t\t====================================================" << endl;
        cout << "\t\t		                    Student Register                " << endl;
        cout << "\t\t\t\t====================================================" << endl;

        putStudentData();
        checkFile.clear();
        checkFile.seekg(0);

        found = false;

        while (getline(checkFile, fileId)) {
        	
            if (id == fileId) {
            	
                system("cls");
                cout << "\aThis Id is already registered" << endl;
                found = true;
                break;
            }
        }

    } while (found);
}

void Student::login() {
	
    Interface interface;
    string fileId, filePassword, filedire;
    bool found = false;
    int i = 0,choice;
    char a;

    filedire = "Record/Student Record.txt";
    ifstream logFile;

    try {
    	
        logFile.open(filedire.c_str(), ios::app);

        if (!logFile)
            throw 0;
    } 
	catch (int) {
    	
        ofstream file(filedire.c_str());
        file.close();
        logFile.open(filedire.c_str());
    }

    cin.ignore();

    do {
    	
        system("COLOR 1F");
        interface.setColor(607);

        cout << "\t\t\t\t====================================================" << endl;
        cout << "\t\t		                    Student Login                   " << endl;
        cout << "\t\t\t\t====================================================" << endl;

        cout << "\n\n\n\n\n\t\t\t\t\t\tEnter Id: ";
        getline(cin, id);

        cout << "\n\n\t\t\t\t\t\tEnter password: ";
        for (i = 0;;) {
        	
            a = getch();

            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || (a >= 32 && a <= 126)) {
            	
                password[i] = a;
                ++i;
                cout << "*";
            }

            else if (a == '\b' && i >= 1) {
            	
                cout << "\b \b";
                --i;
            }

            else if (a == '\r') {
            	
                password[i] = '\0';
                break;
            }
        }

        logFile.clear();
        logFile.seekg(0);

        found = false;

        while (getline(logFile, fileId)) {
        	
            if (id == fileId) {
            	
                getline(logFile, filePassword);
                name = filePassword;
                getline(logFile, filePassword);
                email = filePassword;

                getline(logFile, filePassword);

                if (password == filePassword) {
                	
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
        	
            cout << "\a\n\nIncorrect id or password Enter 1 to try again or 2 to Register: " ;
            cin>>choice;
            if (choice==1){
            	
            	system("cls");
            	cin.ignore();
            	continue;
			}
			else if (choice==2){
				
				system("cls");
				reg();
			}
            
        }

        if (found) {
        	
            interface.setColor(287);
            cout << "\n\n\n\t\t\t\t\t\t\tLogin Successfully";
            interface.setColor(607);

            for (int dots = 0; dots < 3; ++dots) {
            	
                this_thread::sleep_for(std::chrono::seconds(1));
                cout << ".";
                cout.flush();
            }

            cout << endl;
        }

    } while (!found);
}

