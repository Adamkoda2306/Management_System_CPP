#include<iostream>
#include<cstdlib> //for system()
#include<string> //for strings

// Checks if the system is Window or Linux
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Terminal text colors
#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define Blue "\033[34m"

//user defined Header Files
#include "Menu.h"
#include "TerminalUtils.h"
#include "Librarian_MainMenu.h"
#include "Students_MainMenu.h"

using namespace std;

// Student Login Menu
void Menu::Student_Login() {
    Student_Menu student_menu;
    bool exitStudentMenu = false;
    // Runs until they want to go to the Main Screen
    while (!exitStudentMenu) {
        system(CLEAR);
        addVerticalPadding(padding/5);
        printCentered(Green "Student Menu" Default);
        cout<<endl;
        printCentered("1. Create Profile");
        cout<<endl;
        printCentered("2. Login Page");
        cout<<endl;
        printCentered("3. Go to Main Menu");
        cout<<endl;
        printCentered(Blue "Enter Option: " Default);
        int op;
        cin>>op;
        switch (op) {
            case 1: {
                system(CLEAR);
                addVerticalPadding(padding/5);
                //creating new student profile
                student_menu.CreateProfile("Data/Student_Profiles.txt");
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {
                system(CLEAR);
                addVerticalPadding(padding/5);
                // going to the student menu
                student_menu.Login_to_Menu();
                break;
            }
            case 3: {
                // exiting this page and goto main screen
                exitStudentMenu = true;
                break;
            }
            default: {
                // invalid option handling
                addVerticalPadding(padding/5);
                printCentered(Red "Invalid option. Please try again." Default);
                cout<<endl;
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
}

// Librarian Login Menu
void Menu::Librarian_Login() {
    Librarian_Menu admin_menu;
    bool exitLibrarianMenu = false;
    // Runs until they want to go to the Main Screen
    while (!exitLibrarianMenu) {
        int op;
        system(CLEAR);
        addVerticalPadding(padding/5);
        printCentered(Green "Librarian Menu" Default);
        cout<<endl;
        printCentered("1. Perform Librarian Task");
        cout<<endl;
        printCentered("2. Exit to Main Menu");
        cout<<endl;
        printCentered(Blue "Enter Option: " Default);
        cin >> op;
        switch (op) {
            case 1: {
                system(CLEAR);
                addVerticalPadding(padding/5);
                // going to the Librarian menu
                admin_menu.Login_to_AdminMenu();
                break;
            }
            case 2: {
                // exiting this page and goto main screen
                exitLibrarianMenu = true;
                break;
            }
            default: {
                // invalid option handling
                printCentered(Red "Invalid option. Please try again." Default);
                cout<<endl;
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
}
