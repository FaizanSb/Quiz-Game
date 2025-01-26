#include "Staff.h"
#include "Interface.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <thread>
#include "Interface.h"

using namespace std;

string Staff::getStaffId() const {
	
    return id;
}

string Staff::getStaffName() const {
	
    return name;
}

string Staff::getStaffMail() const {
	
    return email;
}

void Staff::putStaffData() {
	
	int i = 0;
    char a;
    Interface interface;
    interface.setColor(607);

    cout << "\n\n\n\t\t\t\t\tEnter Admin Id: ";
    getline(cin, id);

    cout << "\n\n\t\t\t\t\tEnter Admin Name: ";
    getline(cin, name);

    cout << "\n\n\t\t\t\t\tEnter Admin Email: ";
    getline(cin, email);

    cout << "\n\n\t\t\t\t\tEnter Password: ";

    for (i = 0;;) {
        a = getch();

        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || (a >= 32 && a <= '7')) {
            password[i] = a;
            ++i;
            cout << "*";
        }

        if (a == '\b' && i >= 1) {
            cout << "\b \b";
            --i;
        }

        if (a == '\r') {
            password[i] = '\0';
            break;
        }
    }
}

void Staff::reg() {
	
    Interface interface;
    string fileName;
    cin.ignore();
    verify();
    fileName = "Record/Staff Record.txt";

    ofstream regFile(fileName.c_str(), ios::app);

    if (!regFile)
        cerr << "Error Writing on file" << endl;

    regFile << id << endl;
    regFile << name << endl;
    regFile << email << endl;
    regFile << password << endl;

    regFile.close();

    interface.setColor(287);
    cout << "\n\n\n\t\t\t\t\t\t\tRegistered Successfully";
    interface.setColor(607);

    for (int dots = 0; dots < 3; ++dots) {
    	
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    system("cls");
}

bool Staff::verify() {
	
    Interface interface;
    string fileId, fileName;
    bool found = false;

    fileName = "Record/Staff Record.txt";

    ifstream checkFile(fileName.c_str());

    do {
    	
        system("COLOR 1F");
        interface.setColor(607);
        cout << "\t\t\t\t====================================================" << endl;
        cout << "\t\t		                    Admin Register                  " << endl;
        cout << "\t\t\t\t====================================================" << endl;

        putStaffData();

        checkFile.clear(); // Clear any error flags
        checkFile.seekg(0); // Start from line 0 every time wrong authentication

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

void Staff::login() {
	
	int i = 0, choice;
    char a;
    Interface interface;
    string fileId, filePassword, filedire;
    bool found = false;

    filedire = "Record/Staff Record.txt";
    ifstream logFile;

    try {
    	
        logFile.open(filedire.c_str());

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
        cout << "\t\t		                    Admin Login                     " << endl;
        cout << "\t\t\t\t====================================================" << endl;

        cout << "\n\n\n\n\n\t\t\t\t\t\tEnter Id: ";
        getline(cin, id);

        cout << "\n\n\t\t\t\t\t\tEnter password: ";
       
        for (i = 0;;) {
        	
            a = getch();

            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || (a >= 32 && a <= '6')) {
            	
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

        logFile.clear(); // Clear any error flags
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

void Staff::reports() {
	
    Interface interface;
    string line;
    int choice;
    ifstream reportFile;

    try {
    	
        reportFile.open("Record/Reports.txt");

        if (!reportFile) {
            throw 0;
        }
    } 
	catch (int) {
    	
        ofstream file("Record/Reports.txt");
        file.close();
        reportFile.open("Record/Reports.txt");
    }

    if (reportFile.peek() == ifstream::traits_type::eof()) {
    	
        cout << "Currently, there is not a single report." << endl;
    }

    system("COLOR 1F");
    interface.setColor(607);
    cout << "\t\t\t================================================================" << endl;
    cout << "\t\t\t                             Reports                            " << endl;
    cout << "\t\t\t================================================================" << endl;
    interface.setColor(287);

    while (getline(reportFile, line)) {
    	
        cout << "\n\t\t\t\t Reporter ID: " << line << endl;
        getline(reportFile, line);
        cout << "\n\t\t\t\t Reporter Name: " << line << endl;
        getline(reportFile, line);
        cout << "\n\t\t\t\t Report Title: " << line << endl;
        getline(reportFile, line);
        cout << "\n\t\t\t\t Report Description: " << line << endl;

        cout << "\n\t\t\t\t--------------------------------------------------------" << endl;
    }

    reportFile.close();
}

bool Staff::manageReports() {
	
    bool found;
    string reportId, reportName, reportTitle, reportDescription, fReportId, fileName;
    int choice;
    char option;
    Interface interface;

    fileName = "Record/Reports.txt";
    ifstream report(fileName.c_str());
    ofstream tempFile("Record/temp.txt");

    if (!report) {
        cerr << "Error reading the file." << endl;
    }

    if (report.peek() == ifstream::traits_type::eof()) {
    	
        reports();
        interface.setColor(607);
        cout << "\n\t\t\tEnter 1 to Return Admin Menu ";
        cin >> choice;
        return true;
    }

    system("cls");
    reports();

    interface.setColor(607);
    cout << "\n\tEnter 1 to approve a report 2 to Return to the Report Menu: ";
    cin >> choice;
    interface.setColor(287);

    if (choice == 1) {
    	
        system("cls");
        do {
        	
            tempFile.close();
            tempFile.open("Record/temp.txt", ofstream::out | ofstream::trunc);

            reports();
            interface.setColor(607);
            cout << "\n\t\t\tEnter the report ID for approval: ";
            cin >> reportId;
            interface.setColor(287);
            found = false;

            report.clear();
            report.seekg(0, ios::beg);

            while (getline(report, fReportId)) {
            	
                getline(report, reportName);
                getline(report, reportTitle);
                getline(report, reportDescription);

                if (reportId == fReportId) {
                	
                    found = true;
                    interface.setColor(607);
                    cout << "\n\t\tAre you sure you want to Approve(Y/N): ";
                    cin >> option;
                    interface.setColor(287);
                    option = toupper(option);

                    if (option == 'Y') {
                    	
                        cout << "\n\t\t\t\tReport Approved successfully!" << endl;
                    } 
					else {
						
                        tempFile << fReportId << endl;
                        tempFile << reportName << endl;
                        tempFile << reportTitle << endl;
                        tempFile << reportDescription << endl;
                    }
                } else {
                	
                    tempFile << fReportId << endl;
                    tempFile << reportName << endl;
                    tempFile << reportTitle << endl;
                    tempFile << reportDescription << endl;
                }
            }

            if (!found) {
            	
                system("cls");
                cout << "\aWrong Report ID. Please try again." << endl;
            }
        } while (!found);

        report.close();
        tempFile.close();
        remove(fileName.c_str());
        rename("Record/temp.txt", fileName.c_str());

    } else {
        system("cls");
        return true;
    }

    interface.setColor(607);
    cout << "\n\t\t\tEnter 1 to Return Admin Menu ";
    cin >> choice;
    interface.setColor(287);
    system("cls");

    return true;
}

