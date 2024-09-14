#include<iostream>
#include<cstdlib>
#include<string>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define Blue "\033[34m"

#include "Menu.h"
#include "TerminalUtils.h"
#include "Librarian_MainMenu.h"
#include "Students_MainMenu.h"

using namespace std;

void Menu::Student_Login() {
    Student_Menu student_menu;
    bool exitStudentMenu = false;
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
                student_menu.CreateProfile("Data/Student_Profiles.txt");
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {
                system(CLEAR);
                addVerticalPadding(padding/5);
                student_menu.Login_to_Menu();
                break;
            }
            case 3: {
                exitStudentMenu = true;
                break;
            }
            default: {
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

void Menu::Librarian_Login() {
    Librarian_Menu admin_menu;
    bool exitLibrarianMenu = false;
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
                admin_menu.wish();
                printCentered("Press Enter to continue...");
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {
                exitLibrarianMenu = true;
                break;
            }
            default: {
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
