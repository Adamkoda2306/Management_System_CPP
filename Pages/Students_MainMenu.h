#ifndef STUDENTS_MAINMENU_H
#define STUDENTS_MAINMENU_H

#include "Book.h"
#include<string>
#include<vector>
using namespace std;

struct Profile{
    string Username;
    string Password;
    int Books_rented;
};

class Student_Menu{
public:
    void CreateProfile(const string& filename);
    vector<Profile> StoreProfiles(const string& filename);
    void DisplayProfile(Profile profile);
    void Login_to_Menu();
    void Display_Books();
    void Search_Book_Name();
    void Search_Book_ISBN();
};

#endif
