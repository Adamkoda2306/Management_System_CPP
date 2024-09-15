//Librarian_Mainmenu Header File
#ifndef LIBRARIAN_MAINMENU_H
#define LIBRARIAN_MAINMENU_H

#include<string> // for strings

// user defined Header File
#include "Book.h"
using namespace std;

//Issuebook structure
struct Issued_Book{
    string Name;
    string ISBN;
    string StudentUserID;
    string email;
    string PhoneNumber;
};

class Librarian_Menu{
private:
    // Private Variables
    Book bookdetails;
    string password;
    Issued_Book issue; 
    vector<Issued_Book> IssuedBookList;
    vector<Book> BooksList;
public:
    // Constructor
    Librarian_Menu();
    // Functions for Librarian_Mainmenu Header file
    void AddNewBook();
    void Login_to_AdminMenu();
    vector<Issued_Book> StoreIssuedBook(const string& filename);
    void IssueBook(const string& filename);
    void ReturnBook(const string& filename);
    void UpdateBookPosition(const string& filename);
    void RemoveBook();
};

#endif
