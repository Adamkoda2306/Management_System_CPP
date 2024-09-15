#include<iostream>
#include<cstdlib> // for using system()

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
#define lightGreen "\033[32m"
#define Blue "\033[34m"

//user defined Header Files
#include "TerminalUtils.h"
#include "Librarian_MainMenu.h"
#include "Book.h"
#include "Students_MainMenu.h"
using namespace std;

// Constructor for defining the admin password
Librarian_Menu::Librarian_Menu(){
    password = "admin123";
}

// Function for adding the book with the help of write_to_file function defined in book.h header
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
    //goes to the writebook_to_file function which is defined in the book.h header file and stores the book details in the file
    bookdetails.WriteBook_to_File("Data/Books.txt");
}

// Function for issuing the book
void Librarian_Menu::IssueBook(const string& filename){
    ofstream UpdateFile(filename,ios::app);  // Append mode to add new issued books
    if (!UpdateFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return;
    }
    //take the isbn for searching the book
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
        // if the book not found it stops here
        printCentered(Red "Book Not Found!!!\n\n" Default);
        return;
    }
    //take the userID for searching the Student user
    string user;
    printCentered(Blue "Enter Student UserID: " Default);
    cin>>user;
    Student_Menu menu;
    Profile Student;
    Student = menu.SearchProfile(user);
    if(Student.Username != user){
        // if the user not found it stops here
        return;
    }
    //if the all the details are found then it takes the values in the issuebook structure
    issue.Name = bookdetails.newBook.Name;
    issue.ISBN = bookdetails.newBook.ISBN;
    issue.StudentUserID = Student.Username;
    issue.email = Student.Email;
    issue.PhoneNumber = Student.PhoneNumber;
    // writes the issuebook details to the file
    UpdateFile<<"Issued Book Name: "<<issue.Name<<endl;
    UpdateFile<<"Issued Book ISBN: "<<issue.ISBN<<endl;
    UpdateFile<<"Student UserID: "<<issue.StudentUserID<<endl;
    UpdateFile<<"Student Email: "<<issue.email<<endl;
    UpdateFile<<"Student PhoneNumber: "<<issue.PhoneNumber<<endl;
    UpdateFile<<"-----------------------------"<<endl;
    UpdateFile.close();
    // Updates the student profile of bookrented which is defined in the student menu
    menu.UpdateProfile_BookRented(Student, true);
    printCentered(Green "Issued Book Updated Successfully!!\n\n" Default);
    return;
}

// This function returns the Vector of issuebook format which are read from the file
vector<Issued_Book> Librarian_Menu::StoreIssuedBook(const string& filename){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return IssuedBookList;
    }
    string line;
    Issued_Book issuedbook;
    // Reads specific data from the file like it takes the values from the file
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
            // it push the data into the vector if it find this line
            IssuedBookList.push_back(issuedbook); // Add book to vector
            issuedbook = Issued_Book(); // Reset newBook for next book
        }
    }

    inputFile.close();
    return IssuedBookList;
}

// Function is used for updating the book which are returned
void Librarian_Menu::ReturnBook(const string& filename){
    IssuedBookList = StoreIssuedBook(filename);//accessing the all issued book
    if(IssuedBookList.empty()){
        printCentered(Red "No Books are Issued!!!\n\n" Default);
        return;
    }
    //take the isbn for searching the book
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    cin>>isbn;
    for(Issued_Book i: IssuedBookList){
        if(i.ISBN == isbn){
            printCentered(Green "Book Found!" Default);
            //if found taking the value into the issue variable
            issue = i;
        }
    }
    if(issue.ISBN != isbn){
        // if the book not found it stops here
        printCentered(Red "Book Not Found!!!\n\n" Default);
        return;
    }
    Student_Menu menu;
    Profile Student;
    Student = menu.SearchProfile(issue.StudentUserID);// Storing the User profile into the Student variable
    menu.UpdateProfile_BookRented(Student, false);// updating the book rented variable in the student profile
    ofstream outputFile(filename,ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    // Updating the file => removing the book which is returned from the file
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
    //Clearing the vector data and shrinking it's size
    IssuedBookList.clear();
    IssuedBookList.shrink_to_fit();
    outputFile.close();
}

// this function is for Updating the file => removing the book which is not required by librarian from the file
void Librarian_Menu::RemoveBook(){
    BooksList = bookdetails.ReadBook_from_File("Data/Books.txt");
    ofstream outputFile("Data/Books.txt",ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    //Taking the isbn value for removing the book
    string bookISBN;
    printCentered("Enter Book ISBN: ");
    cin>>bookISBN;
    for(Book i: BooksList){
        if(i.newBook.ISBN == bookISBN){
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

// This function for updating the book position as the book is kept in new position
void Librarian_Menu::UpdateBookPosition(const string& filename){
    BooksList = bookdetails.ReadBook_from_File(filename);// Storing the book details in the book vector
    //taking the isbn for searching the book
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    cin>>isbn;
    for(Book &i: BooksList){
        if(i.newBook.ISBN == isbn){
            // changing the position
            printCentered(Green "Book Found!\n" Default);
            printCentered("New Book Shelf no: ");
            cin>>i.newBook.pos.Shelf;
            printCentered("New Row: ");
            cin>>i.newBook.pos.row;
            printCentered("New Book Position Number: ");
            cin>>i.newBook.pos.bookNumber;
        }
    }
    ofstream outputFile(filename,ios::out | ios::trunc);// for overwriting the file
    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    // Writing the data to the file
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

// Main Screen Of the Librarian
void Librarian_Menu::Login_to_AdminMenu(){
    string pass;
    printCentered(Blue "Enter Password: " Default);
    cin>>pass;
    cin.ignore();
    // only Opens when you give the correct password
    if(pass == password){
        bool exitStudentMenu = false;
        while (!exitStudentMenu) {
            system(CLEAR);
            addVerticalPadding(padding/5);
            // Menu of Librarian
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
                    //add new book function
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
                    //remove book function
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
                    //issue book function
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
                    //return book function
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
                    //update book position function
                    UpdateBookPosition("Data/Books.txt");
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 6: {
                    // Exits the Librarian Menu and goes to the login screen of Librarian
                    exitStudentMenu = true;
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
    }else{
        system(CLEAR);
        addVerticalPadding(padding/5);
        // goes to the login page of Librarian
        printCentered(Red "Invalid Password." Default);
        cout<<endl;
        printCentered("Press Enter to continue...");
        cin.ignore();
        cin.get();
    }
}