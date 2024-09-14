#include<iostream>
#include<cstdlib>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define lightGreen "\033[32m"
#define Blue "\033[34m"

#include "TerminalUtils.h"
#include "Librarian_MainMenu.h"
#include "Book.h"
#include "Students_MainMenu.h"
using namespace std;

Librarian_Menu::Librarian_Menu(){
    password = "admin123";
}

void Librarian_Menu::AddNewBook(){
    printCentered("ENTER NEW BOOK DETAILS: \n\n");
    printCentered("Enter Book Name: ");
    getline(cin, bookdetails.newBook.Name);
    printCentered("Enter Book ISBN: ");
    getline(cin, bookdetails.newBook.ISBN);
    printCentered("Enter Book Year: ");
    cin>>bookdetails.newBook.Year;
    printCentered("Book Shelf no: ");
    cin>>bookdetails.newBook.pos.Shelf;
    printCentered("Row: ");
    cin>>bookdetails.newBook.pos.row;
    printCentered("Book Number: ");
    cin>>bookdetails.newBook.pos.bookNumber;
    bookdetails.WriteBook_to_File("Data/Books.txt");
}

void Librarian_Menu::IssueBook(const string& filename){
    ofstream UpdateFile(filename,ios::app);  // Append mode to add new issued books
    if (!UpdateFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return;
    }
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    cin>>isbn;
    BooksList = bookdetails.ReadBook_from_File("Data/Books.txt");
    for(Book i: BooksList){
        if(i.newBook.ISBN == isbn){
            printCentered(Green "Book Found!\n" Default);
            bookdetails.newBook = i.newBook;
        }
    }
    if(bookdetails.newBook.ISBN != isbn){
        printCentered(Red "Book Not Found!!!\n\n" Default);
        return;
    }
    string user;
    printCentered(Blue "Enter Student UserID: " Default);
    cin>>user;
    Student_Menu menu;
    Profile Student;
    Student = menu.SearchProfile(user);
    if(Student.Username != user){
        return;
    }
    issue.Name = bookdetails.newBook.Name;
    issue.ISBN = bookdetails.newBook.ISBN;
    issue.StudentUserID = Student.Username;
    issue.email = Student.Email;
    issue.PhoneNumber = Student.PhoneNumber;
    UpdateFile<<"Issued Book Name: "<<issue.Name<<endl;
    UpdateFile<<"Issued Book ISBN: "<<issue.ISBN<<endl;
    UpdateFile<<"Student UserID: "<<issue.StudentUserID<<endl;
    UpdateFile<<"Student Email: "<<issue.email<<endl;
    UpdateFile<<"Student PhoneNumber: "<<issue.PhoneNumber<<endl;
    UpdateFile<<"-----------------------------"<<endl;
    UpdateFile.close();
    menu.UpdateProfile_BookRented(Student, true);
    printCentered(Green "Issued Book Updated Successfully!!\n\n" Default);
    return;
}

vector<Issued_Book> Librarian_Menu::StoreIssuedBook(const string& filename){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return IssuedBookList;
    }
    string line;
    Issued_Book issuedbook;
    while (getline(inputFile, line)) {
        if (line.find("Issued Book Name:") != string::npos) {
            issuedbook.Name = line.substr(line.find(":") + 2);  // Extract book name
        } else if (line.find("Issued Book ISBN:") != string::npos) {
            issuedbook.ISBN = line.substr(line.find(":") + 2);  // Extract ISBN
        } else if (line.find("Student UserID:") != string::npos) {
            issuedbook.StudentUserID = line.substr(line.find(":") + 2);  // Extract Student UserID
        } else if (line.find("Student Email:") != string::npos) {
            issuedbook.email = line.substr(line.find(":") + 2);  // Extract Email
        } else if (line.find("Student PhoneNumber:") != string::npos) {
            issuedbook.PhoneNumber = line.substr(line.find(":") + 2);  // Extract PhoneNumber (as string)
        }

        if (line.find("-----------------------------") != string::npos) {
            IssuedBookList.push_back(issuedbook);
            issuedbook = Issued_Book();
        }
    }

    inputFile.close();
    return IssuedBookList;
}

void Librarian_Menu::ReturnBook(const string& filename){
    IssuedBookList = StoreIssuedBook(filename);
    if(IssuedBookList.empty()){
        printCentered(Red "No Books are Issued!!!\n\n" Default);
        return;
    }
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    cin>>isbn;
    for(Issued_Book i: IssuedBookList){
        if(i.ISBN == isbn){
            printCentered(Green "Book Found!" Default);
            issue = i;
        }
    }
    if(issue.ISBN != isbn){
        printCentered(Red "Book Not Found!!!\n\n" Default);
        return;
    }
    Student_Menu menu;
    Profile Student;
    Student = menu.SearchProfile(issue.StudentUserID);
    menu.UpdateProfile_BookRented(Student, false);
    ofstream outputFile(filename,ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    for(Issued_Book &i: IssuedBookList){
        if(i.ISBN == issue.ISBN){
            // Removes the Issued Book
        }else{
            outputFile<<"Issued Book Name: "<<issue.Name<<endl;
            outputFile<<"Issued Book ISBN: "<<issue.ISBN<<endl;
            outputFile<<"Student UserID: "<<issue.StudentUserID<<endl;
            outputFile<<"Student Email: "<<issue.email<<endl;
            outputFile<<"Student PhoneNumber: "<<issue.PhoneNumber<<endl;
            outputFile<<"-----------------------------"<<endl;
        }
    }
    IssuedBookList.clear();
    IssuedBookList.shrink_to_fit();
    outputFile.close();
}

void Librarian_Menu::RemoveBook(){
    BooksList = bookdetails.ReadBook_from_File("Data/Books.txt");
    ofstream outputFile("Data/Books.txt",ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    string bookName;
    printCentered("Enter Book ISBN: ");
    cin>>bookName;
    for(Book i: BooksList){
        if(i.newBook.ISBN == bookName){
            // Skips the books => remove the book in that file
        }else{
            outputFile<<"Book Name: "<<i.newBook.Name<<endl;
            outputFile<<"ISBN: "<<i.newBook.ISBN<<endl;
            outputFile<<"Year: "<<i.newBook.Year<<endl;
            outputFile<<"Shelf: "<<i.newBook.pos.Shelf<<endl;
            outputFile<<"Row: "<<i.newBook.pos.row<<endl;
            outputFile<<"Book Number: "<<i.newBook.pos.bookNumber<<endl;
            outputFile<<"-----------------------------"<<endl; 
        }
    }
    outputFile.close();
    printCentered(Green "Book is Successfully Removed!!\n\n" Default);
    return;
}

void Librarian_Menu::UpdateBookPosition(const string& filename){
    BooksList = bookdetails.ReadBook_from_File(filename);
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    cin>>isbn;
    for(Book &i: BooksList){
        if(i.newBook.ISBN == isbn){
            printCentered(Green "Book Found!\n" Default);
            printCentered("New Book Shelf no: ");
            cin>>i.newBook.pos.Shelf;
            printCentered("New Row: ");
            cin>>i.newBook.pos.row;
            printCentered("New Book Position Number: ");
            cin>>i.newBook.pos.bookNumber;
        }
    }
    ofstream outputFile(filename,ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    for(Book i: BooksList){
            outputFile<<"Book Name: "<<i.newBook.Name<<endl;
            outputFile<<"ISBN: "<<i.newBook.ISBN<<endl;
            outputFile<<"Year: "<<i.newBook.Year<<endl;
            outputFile<<"Shelf: "<<i.newBook.pos.Shelf<<endl;
            outputFile<<"Row: "<<i.newBook.pos.row<<endl;
            outputFile<<"Book Number: "<<i.newBook.pos.bookNumber<<endl;
            outputFile<<"-----------------------------"<<endl; 
    }
    outputFile.close();
    printCentered(Green "Book Position is Updated Successfully!!\n\n" Default);
    return;
}

void Librarian_Menu::Login_to_AdminMenu(){
    string pass;
    printCentered(Blue "Enter Password: " Default);
    cin>>pass;
    cin.ignore();
    if(pass == password){
        bool exitStudentMenu = false;
        while (!exitStudentMenu) {
            system(CLEAR);
            addVerticalPadding(padding/5);
            printCentered(Green "Librarian Menu" Default);
            cout<<endl<<endl;
            printCentered("1. Add Book");
            cout<<endl;
            printCentered("2. Remove Book");
            cout<<endl;
            printCentered("3. Issue Book");
            cout<<endl;
            printCentered("4. Return Book");
            cout<<endl;
            printCentered("5. Update Book Position");
            cout<<endl;
            printCentered("6. Go to Previous Menu");
            cout<<endl;
            printCentered(Blue "Enter Option: " Default);
            int op;
            cin>>op;
            cin.ignore();
            switch (op) {
                case 1: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    AddNewBook();
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 2: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    RemoveBook();
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 3: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    IssueBook("Data/Issued_Books.txt");
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    ReturnBook("Data/Issued_Books.txt");
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 5: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    UpdateBookPosition("Data/Books.txt");
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 6: {
                    exitStudentMenu = true;
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
    }else{
        system(CLEAR);
        addVerticalPadding(padding/5);
        printCentered(Red "Invalid user or Password. Create New Profile." Default);
        cout<<endl;
        printCentered("Press Enter to continue...");
        cin.ignore();
        cin.get();
    }
}