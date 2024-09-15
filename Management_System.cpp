#include<iostream>
#include<cstdlib> // for using system()

// Checks if the system is Window or Linux
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Colors for the Terminal text
#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define lightGreen "\033[32m"
#define Blue "\033[34m"

// User Created Header Files
#include "Pages\TerminalUtils.h"
#include "Pages\Students_MainMenu.h"
#include "Pages\Librarian_MainMenu.h"
#include "Pages\Menu.h"
using namespace std;


int main(){
    int option;
    Menu menu;
    // Runs the Program Infinitely
    while(1){
        system(CLEAR);
        addVerticalPadding(padding/5); // gives the top Padding of size of (padding/5)
        printCentered(Green "*****Library Management System******" Default);
        cout<<endl;
        printCentered("1. Student Login");
        cout<<endl;
        printCentered("2. Librarian Login");
        cout<<endl;
        printCentered("3. Exit the Application");
        cout<<endl<<endl;
        printCentered(Blue "Enter Option: " Default);
        cin>>option;
        switch (option){
            case 1:{
                system(CLEAR);// Clears the Screen
                // Goes to the Student Login Page
                menu.Student_Login();
                break;
            }
            case 2:{
                system(CLEAR);
                // Goes to the Librarian Login Page
                menu.Librarian_Login();
                break;
            }
            case 3:{
                system(CLEAR);
                addVerticalPadding(15); // gives padding to top of size 15 units
                //User Defined Print statement with left padding
                printCentered(Green "Thank You For Using This Application." Default);
                cout<<endl;
                // It is used for Waiting for Response for ending
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                return 0;
            }
            default:{
                // runs the program again since given option is invalid
                system(CLEAR);
                addVerticalPadding(20);
                printCentered(Red "Invalid option. Please try again." Default);
                break;
            }
        }

        cout<<endl;
        printCentered("Press Enter to continue...");
        cin.ignore();
        cin.get();
    }
    return 0;
}
