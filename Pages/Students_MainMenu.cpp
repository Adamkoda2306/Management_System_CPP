#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>

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
#include "Students_MainMenu.h"
#include "Book.h"
using namespace std;


void Student_Menu::CreateProfile(const string& filename){
    ofstream outputFile(filename,ios::app);  // Append mode to add new books

    if (!outputFile.is_open()) {
        cerr<<"Error opening file for writing!"<<endl;
        return;
    }
    Profile profile;
    printCentered(Blue "Enter Username: " Default);
    cin>>profile.Username;
    printCentered(Blue "Enter Password: " Default);
    cin>>profile.Password;
    profile.Books_rented = 0;
    outputFile<<"Username: "<<profile.Username<<endl;
    outputFile<<"Password: "<<profile.Password<<endl;
    outputFile<<"Books Rented: "<<profile.Books_rented<<endl;
    outputFile<<"-----------------------------"<<endl;  // Separator between entries

    outputFile.close();
}

vector<Profile> Student_Menu::StoreProfiles(const string& filename){
    ifstream inputFile(filename);
    vector<Profile> profiles_list;
    if (!inputFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return profiles_list;
    }

    string line;
    Profile newProfile;
    while (getline(inputFile, line)) {
        if (line.find("Username:") != string::npos) {
            newProfile.Username = line.substr(line.find(":") + 2);  // Extract book name
        } else if (line.find("Password:") != string::npos) {
            newProfile.Password = line.substr(line.find(":") + 2);  // Extract ISBN
        } else if (line.find("Books Rented:") != string::npos) {
            newProfile.Books_rented = stoi(line.substr(line.find(":") + 2));  // Extract Year
        }

        if (line.find("-----------------------------") != string::npos) {
            profiles_list.push_back(newProfile);
            newProfile= Profile();
        }
    }

    inputFile.close();
    return profiles_list;
}

void Student_Menu::DisplayProfile(Profile user){
    printCentered(Green "Student Profile: " Default);
    cout<<endl<<endl;
    printCentered("UserName: ");
    cout<<Blue<<user.Username<<Default<<endl;
    printCentered("Books Rented: ");
    cout<<Blue<<user.Books_rented<<Default<<endl;
    printCentered("________________________________________");
}

void Student_Menu::Display_Books(){
    vector<Book> BooksList;
    if(BooksList.empty()){
        Book books;
        BooksList = books.ReadBook_from_File("Books.txt");
    }
    int j=0;
    addVerticalPadding(padding/5);
    printCentered(Green "All Books List: " Default);
    cout<<endl<<endl;
    for(Book i: BooksList){
        printCentered("Book No: ");
        cout<<Blue<<++j<<Default<<endl;
        i.DisplayBook();
        printCentered("____________________________________________");
        cout<<endl<<endl;
    }
}

void Student_Menu::Search_Book_Name(){
    vector<Book> BooksList;
    string name;
    printCentered(Blue "Enter Book Name: " Default);
    getline(cin, name);
    if(BooksList.empty()){
        Book books;
        BooksList = books.ReadBook_from_File("Books.txt");
    }
    system(CLEAR);
    addVerticalPadding(padding/5);
    for(Book i: BooksList){
        if(i.newBook.Name == name){
            printCentered(Green "Book Found!" Default);
            cout<<endl<<endl;
            i.DisplayBook();
            cout<<endl;
            return;
        }
    }
    printCentered(Red "Book Not Found!!!" Default);
    cout<<endl;
}

void Student_Menu::Search_Book_ISBN(){
    vector<Book> BooksList;
    string isbn;
    printCentered(Blue "Enter Book ISBN: " Default);
    getline(cin, isbn);
    if(BooksList.empty()){
        Book books;
        BooksList = books.ReadBook_from_File("Books.txt");
    }
    system(CLEAR);
    addVerticalPadding(padding/5);
    for(Book i: BooksList){
        if(i.newBook.ISBN == isbn){
            printCentered(Green "Book Found!" Default);
            cout<<endl<<endl;
            i.DisplayBook();
            cout<<endl;
            return;
        }
    }
    printCentered(Red "Book Not Found!!!" Default);
    cout<<endl;
}

void Student_Menu::Login_to_Menu(){
    string username;
    vector<Profile> profilesList;
    string password;
    printCentered(Blue "Enter UserName: " Default);
    cin>>username;
    printCentered(Blue "Enter Password: " Default);
    cin>>password;
    cin.ignore(); 
    profilesList = StoreProfiles("Student_Profiles.txt");
    int i=0;
    while(profilesList[i].Username != username && profilesList[i].Password != password){
        i++;
    }
    if(profilesList[i].Username == username && profilesList[i].Password == password){
        bool exitStudentMenu = false;
        while (!exitStudentMenu) {
            system(CLEAR);
            addVerticalPadding(padding/5);
            printCentered(Green "Student Menu" Default);
            cout<<endl<<endl;
            printCentered("1. Display Profile");
            cout<<endl;
            printCentered("2. Display all Books");
            cout<<endl;
            printCentered("3. Search Book by Name");
            cout<<endl;
            printCentered("4. Search Book by ISBN");
            cout<<endl;
            printCentered("5. Go to Student Login Menu");
            cout<<endl;
            printCentered(Blue "Enter Option: " Default);
            int op;
            cin>>op;
            cin.ignore();
            switch (op) {
                case 1: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    DisplayProfile(profilesList[i]);
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 2: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    Display_Books();
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 3: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    Search_Book_Name();
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4: {
                    system(CLEAR);
                    addVerticalPadding(padding/5);
                    Search_Book_ISBN();
                    cout<<endl;
                    printCentered("Press Enter to continue...");
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 5: {
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