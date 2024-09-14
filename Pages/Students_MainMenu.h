#ifndef STUDENTS_MAINMENU_H
#define STUDENTS_MAINMENU_H

#include "Book.h"
#include<string>
#include<vector>
using namespace std;

struct Profile{
    string Username;
    string Password;
    string Email;
    string PhoneNumber;
    int Books_rented;
};

class Student_Menu{
private:
    vector<Profile> profile_Details;
public:
    void CreateProfile(const string& filename);
    void UpdateProfile_BookRented(Profile student, bool issue);
    vector<Profile> StoreProfiles(const string& filename);
    void DisplayProfile(Profile profile);
    Profile SearchProfile(string Name);
    void Login_to_Menu();
    void Display_Books();
    void Search_Book_Name();
    void Search_Book_ISBN();
};

#endif
