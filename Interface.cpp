#include "Interface.h"
#include <iostream>
#include <limits>
#include "User.h"
#include "Student.h"
#include "Staff.h"
#include "SubjectQuestions.h"
#include "Quiz.h"
#include "QuizResultHandler.h"
#include<windows.h>

using namespace std;

void Interface::uniInterface(){
	
	system("COLOR 4F");
	setColor(335);
    cout << "\n\n\t\t\t\t\t\tOOP Semester Project" << endl;
    cout << "\n\n\n\n\t\t\t\tGroup Members\t\t\t1.Abubakar Saeed\n\t\t\t\t\t\t\t\t2.Muhammad Faizan" << endl;
    cout << "\n\t\t\t\tProject Title\t\t\tQuiz Managment System" << endl;
    cout << "\n\t\t\t\tInstitute\t\t\tGCUF Chiniot Campus" << endl;
    cout << "\n\t\t\t\tFaculty\t\t\t\tPhysical Sciences" << endl;
    cout << "\n\t\t\t\tDepartment\t\t\tComputer Science" << endl;
    cout << "\n\t\t\t\tInstructor\t\t\tDr.Waqar Hussain" << endl;
    cout << "\n\t\t\t\tDeveloped by\t\t\tAbubakar & Faizan" << endl;
    cout << "\n\n\n\n\n\t\t\t\t\t Press Enter to Continue......" ;
    cin.get();
}
void Interface::welcome(){
	
	system("cls");
	system( "COLOR 1F");
	setColor(607);
    cout << "\n\n\n\n\n" << endl;
    cout << "     __          __  _                            _           ____        _        _____                      \n";
    cout << "     \\ \\        / / | |                          | |         / __ \\      (_)      / ____|                     \n";
    cout << "      \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |  | |_   _ _ ____ | |  __  __ _ _ __ ___   ___ \n";
    cout << "       \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | |  | | | | | |_  / | | |_ |/ _` | '_ ` _ \\ / _ \\\n";
    cout << "        \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |__| | |_| | |/ /  | |__| | (_| | | | | | |  __/\n";
    cout << "         \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \\___\\_\\\\__,_|_/___|  \\_____|\\__,_|_| |_| |_|\\___|\n";
    cout << "                                                                                                              \n" << endl;
	setColor(287);
	cout << "\n\n\t\t\t\tTest your knowledge and have fun answering the quiz questions\n" << endl;
	cout << "\t\t\t\tLet's get started!\n" << endl;
	cout << "\t\t\t\tPress Enter to go Main Menu..." << endl;
	setColor(607);
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tDeveloped By: Abubakar & Faizan" ;
	setColor(287);
    cin.get();
  
}
void Interface::menu(){
	 
	system("cls");
	do {
		
		try{
		
			system( "COLOR 1F");
			setColor(607);
			cout << "\t\t\t\t====================================================" << endl;
			cout << "\t\t		                       Main Menu                    " << endl;
			cout << "\t\t\t\t====================================================" << endl;  
			setColor(287);
			cout << "\n\n\t\t\t\t\t\t1. Admin Portal"<<endl;
			cout << "\n\t\t\t\t\t\t2. Student Portal"<<endl;
			cout << "\n\t\t\t\t\t\t3. Exit"<<endl;
			setColor(607);
			cout << "\n\t\t\t\t\tEnter your Choice: ";
			cin >> choice;
		
			if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
		    
		switch(choice){
			
			case 1:
				
				system("cls");
				staffloginMenu();
				break;
			case 2:
				
				system("cls");
				studentloginMenu();
				break;
			case 3:
				
				system("cls");
				exit(0);
				break;
			default:
				
				system("cls");
				cerr << "\a\t\t\aInvalid choice. Please try again." << endl;	
		}
	}while(choice!=3);
}
void Interface::staffloginMenu(){
	
	do{
		
		try{
			
			system("COLOR 1F");
			setColor(607);
			cout << "\t\t\t\t====================================================" << endl;
			cout << "\t\t		                    Admin Portal                    " << endl;
			cout << "\t\t\t\t====================================================" <<endl;  
			setColor(287);
			cout << "\n\n\t\t\t\t\t\t1. Log in " << endl;
			cout << "\n\t\t\t\t\t\t2. Register" << endl;
			cout << "\n\t\t\t\t\t\t3. Return to Main Menu" << endl;
			setColor(607);
			cout << "\n\t\t\t\t\tEnter your Choice: ";
			cin >> choice;
			
	    	if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
		
		switch(choice){
			
			case 1:
				
				system("cls");
				staff.login();
				system("cls");				
				staffMenu();
				break;
				
			case 2:
				
				system("cls");
				staff.reg();
				break;
				
			case 3:
				
				system("cls");
				menu();
				break;	
				
			default:
				
				system("cls");
				cerr << "\a\t\tInvalid choice. Please try again." << endl;
		}
	}while(choice!=3);
}
void Interface::studentloginMenu(){

	do{
		
		try{
		
			system("COLOR 1F");
			setColor(607);
			cout << "\t\t\t\t====================================================" << endl;
			cout << "\t\t		                   Student Portal                   " << endl;
			cout << "\t\t\t\t====================================================" << endl;  
			setColor(287);
			cout << "\n\n\t\t\t\t\t\t1. Log in " << endl;
			cout << "\n\t\t\t\t\t\t2. Register" << endl;
			cout << "\n\t\t\t\t\t\t3. Return to Main Menu" << endl;
			setColor(607);
			cout << "\n\t\t\t\t\tEnter your Choice: ";
			cin >> choice;
		
			if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
		
		switch(choice){
			
			case 1:
				
				system("cls");
				student.login();
				system("cls");
				studentMenu();
				break;
			case 2:
				
				system("cls");
				student.reg();
				break;
				
			case 3:
				
				system("cls");
				menu();
				break;	
			default:
				
				system("cls");
				cerr << "\a\n\t\t\t\aInvalid choice. Please try again." << endl;
				
		}
	}while(choice!=3);
}
void Interface::subjectManagmentMenu() {
    
    	system("cls");
    do{
    	
    	try{
		
	    	system("COLOR 1F");
		    setColor(15);
			admin.adminHeader(SubjectQuestions::staff);
			setColor(607);
		    cout << "\t\t\t====================================================================" << endl;
		    cout << "\t\t\t                        Subject Managment                           " << endl;
		    cout << "\t\t\t====================================================================" << endl;
		    setColor(287);
		    cout << "\n\n\n\t\t\t\t\t\t1. Add subjects" << endl;
		    cout << "\n\t\t\t\t\t\t2. View Subjects" << endl;
		    cout << "\n\t\t\t\t\t\t3. Search Subjects" << endl;
		    cout << "\n\t\t\t\t\t\t4. Update Subject Name" << endl;
		    cout << "\n\t\t\t\t\t\t5. Delete Subject" << endl;
		    cout << "\n\t\t\t\t\t\t6. Return to Menu " << endl;

		    setColor(607);
		    cout << "\n\t\t\t\t\tEnter your Choice: ";
		    cin >> choice;
		    
	    	if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
	    	
	    switch (choice) {
	
		    case 1:
		    	
		        system("cls");
		        admin.addSubject();
		        break;
		    case 2:
		    	
		        system("cls");
		        admin.viewSubjects();
		        break;
		    case 3:
		    	
		        system("cls");
		        admin.searchSubject();
		        break;
		    case 4:
		    	
		        system("cls");
		        admin.updateSubjectName();
		        break;
		    case 5:
		    	
		        system("cls");
		        admin.deleteSubject();
		        break;
		    case 6:
		    	
		    	system("cls");
		    	staffMenu();
		    	break;
		    default:
		    	
		    	system("cls");
		        cerr << "\a\tInvalid Choice.please try again" << endl;
    	}
	}while (choice!=6);
}
void Interface::quizManagmentMenu() {
	
    system("cls");
	do{
		
		try{
		
			system("COLOR 1F");
			setColor(15);
			admin.adminHeader(SubjectQuestions::staff);
			setColor(607);
		    cout << "\t\t\t===============================================================" << endl;
		    cout << "\t\t\t                           Quiz Managment                      " << endl;
		    cout << "\t\t\t===============================================================" << endl;
		    setColor(287);
		    cout << "\n\n\n\t\t\t\t\t\t1. Add Quiz" << endl;
		    cout << "\n\t\t\t\t\t\t2. View Quiz" << endl;
		    cout << "\n\t\t\t\t\t\t3. Search Quiz" << endl;
		    cout << "\n\t\t\t\t\t\t4. Update Quiz" << endl;
		    cout << "\n\t\t\t\t\t\t5. Delete Quiz " << endl;
		    cout << "\n\t\t\t\t\t\t6. Quiz Rules " << endl;
		    cout << "\n\t\t\t\t\t\t7. Return to Menu" << endl;
		    setColor(607);
		    cout << "\n\t\t\t\t\tEnter your Choice: ";
		    cin >> choice;
	    
			if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
	    switch (choice) {
	
		    case 1:
		    	
		        system("cls");
		        admin.addQuiz();
		        break;
		    case 2:
		    	
		        system("cls");
		       	admin.viewQuiz();
		        break;
		    case 3:
		    	
		        system("cls");
		        admin.searchQuiz();
		        break;
		    case 4:
		    	
		        system("cls");
		        admin.updateQuiz();
		        break;
		    case 5:
		    	
		        system("cls");
		        admin.deleteQuiz();
		        break;
		    case 6:
		    	
				system("cls");
		    	admin.setQuizRules();
		    	break;
		    	
		    case 7:
		    	
		    	system("cls");
		    	subjectManagmentMenu();
		    	break;
		    	
		    default:
		    	
		    	system("cls");
		        cout << "\a\tInvalid Choice.Please Try Again" << endl;
	    }
	}while(choice!=7);
}
void Interface::studentMenu(){
    
    system("cls");
    do {
		
		try{
			
	    	system("COLOR 1F");
	    	setColor(607);
		    cout << "\t\t\t==========================================================================" << endl;
		    cout << "\t\t\t                            Student Menu                                  " << endl;
		    cout << "\t\t\t==========================================================================" << endl;
		    setColor(287);
			cout << "\n\n\t\t\t\t\t\t1. Select Quiz " << endl;
		    cout << "\n\t\t\t\t\t\t2. View Hall of Fame" << endl;
		    cout << "\n\t\t\t\t\t\t3. Send Report" << endl;
		    cout << "\n\t\t\t\t\t\t4. Log out" << endl;
		    cout << "\n\t\t\t\t\t\t5. Exit" << endl;
		    setColor(607);
		    cout << "\n\t\t\t\t\tEnter your choice: ";
		    cin >> choice;
		    setColor(287);
	    
	    	if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
		   
		switch (choice) {
                
			case 1:
					
				quiz.viewSubjects();
				quiz.displayQuizRules();
				system("cls");
				quiz.scoreHeader(student);
				if(!quiz.startQuiz())
					student.reports();
				else
					result.resultCard(student);
                break;
            case 2:
                	
                result.displayHighScore();
                break;    
            case 3:
                
	            student.reports();
	            system("cls");
                break;
            case 4:
                	
	            system("cls");
	    		menu();
	    		break;
    		case 5:
    				
                cout << "\nExiting the quiz game. Goodbye!" << endl;
                cout << "\nThanks for playing our Quiz Game. Good luck have a great day! " << endl;
                exit(0);
                break;

            default:
            	
                system("cls");
                cerr << "\t\t\aInvalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}

void Interface::staffMenu(){
	
    system("cls");
	do{
		
		try{
		
			system("COLOR 1F");
			setColor(15);
			admin.adminHeader(staff);
			setColor(607);
			cout << "\t\t\t========================================================================" << endl;
		    cout << "\t\t\t                            Admin Menu                                  " << endl;
		    cout << "\t\t\t========================================================================" << endl;
		    setColor(287);
			cout << "\n\n\n\t\t\t\t\t\t1. Subject Managment" << endl;
		    cout << "\n\t\t\t\t\t\t2. Quiz Managment" << endl;
		    cout << "\n\t\t\t\t\t\t3. Manage Quiz Rules" << endl;
		    cout << "\n\t\t\t\t\t\t4. Manage Reports" << endl;
		    cout << "\n\t\t\t\t\t\t5. Log out" << endl;
		    cout << "\n\t\t\t\t\t\t6. Exit" << endl;
		    setColor(607);
		    cout << "\n\t\t\t\t\tEnter your choice: ";
			cin >> choice;
		
			if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}	    
		
		switch (choice) {
	                
			case 1:
			 	
				subjectManagmentMenu();
				break;
				 
		    case 2:
		                
				quizManagmentMenu();	
				break;   
		                    
		    case 3:
		         
			    admin.setQuizRules();
			    break;
		
		    case 4:
		        system("cls");
				reportMenu();
				break;
			     
			case 5:
			
				system("cls");
				menu();
				break;
			 	
			case 6:
				
				cout << "\nExiting the quiz game. Goodbye!" << endl;
				cout << "\nThanks for playing our Quiz Game. Good luck have a great day! " << endl;
				exit(0);
				break;
		
		    default:
		        
				system("cls");	
			    cerr << "\t\t\aInvalid choice. Please try again." << endl;
			    break;
		}
 	} while (choice != 6);
}
void Interface::reportMenu(){
	
	system("cls");
	do{
		
		try{

			system("COLOR 1F");
			setColor(15);
			admin.adminHeader(SubjectQuestions::staff);
			setColor(607);
			cout << "\t\t\t=========================================================================" << endl;
		    cout << "\t\t\t                            Report Menu                                  " << endl;
		    cout << "\t\t\t=========================================================================" << endl;
		    setColor(287);
			cout << "\n\n\n\n\n\t\t\t\t\t\t1. View Reports" << endl;
		    cout << "\n\t\t\t\t\t\t2. Manage Reports" << endl;
		    cout << "\n\t\t\t\t\t\t3. Return to Menu" << endl;
		    setColor(607);
		    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
		    cin >> choice;
	
			if (cin.fail())
				throw 0;
		}
		catch(int){
			
			cin.clear(); 										 			
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 			
            system("cls");
			cerr << "\a\t\t\aInvalid choice. Please try again." << endl;  
            continue;
		}
			    
		
		switch (choice) {
	                
			case 1:
			 	
				system("cls");
				staff.reports();
				setColor(607);
				cout << "\n\t Enter 1 to Manage Reports Menu ";
				cin >> choice;
				system("cls");
				staff.manageReports();
				break;
				 
		    case 2:
		     	
		        system("cls");
				if(staff.manageReports()){
					
					system("cls");
				}
				break;        
				     
		    case 3:
		         
		        system("cls");
			    staffMenu();
			    break;
			default:
		         
				system("cls");  	
			    cerr << "\t\t\aInvalid choice. Please try again." << endl;
			    break;
		}
	} while (choice != 3);
}
void Interface::setColor(int color){
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the handle to the console window
   
	WORD colorAttribute = color;
	
    // Set the console text attribute to the  color attribute
    SetConsoleTextAttribute(hConsole, colorAttribute);
    // Set console font type, size 
    CONSOLE_FONT_INFOEX fo;					// Declares a CONSOLE_FONT_INFOEX
	fo.cbSize = sizeof(fo);					// Intializing with current font size 
	fo.dwFontSize.X = 0;                    // Width of each character in the font
	fo.dwFontSize.Y = 20;                   // Height
	fo.FontFamily = FF_DONTCARE;			// font family can be chosen freely
	fo.FontWeight = FW_NORMAL;				// regular font size
	wcscpy(fo.FaceName, L"Consolas"); 		// Choose your font family
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fo); 

}
