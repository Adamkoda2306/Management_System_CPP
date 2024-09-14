#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Book.h"
#include "TerminalUtils.h"
using namespace std;

#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define Blue "\033[34m"

vector<Book> Book::ReadBook_from_File(const string& filename) {
    ifstream inputFile(filename);
    vector<Book> books;
    if (!inputFile.is_open()) {
        cerr<<"Error opening file for reading!"<<endl;
        return books;
    }

    string line;
    Book newBook;
    while (getline(inputFile, line)) {
        if (line.find("Book Name:") != string::npos) {
            newBook.newBook.Name = line.substr(line.find(":") + 2);  // Extract book name
        } else if (line.find("ISBN:") != string::npos) {
            newBook.newBook.ISBN = line.substr(line.find(":") + 2);  // Extract ISBN
        } else if (line.find("Year:") != string::npos) {
            newBook.newBook.Year = stoi(line.substr(line.find(":") + 2));  // Extract Year
        } else if (line.find("Shelf:") != string::npos) {
            newBook.newBook.pos.Shelf = stoi(line.substr(line.find(":") + 2));  // Extract Shelf
        } else if (line.find("Row:") != string::npos) {
            newBook.newBook.pos.row = stoi(line.substr(line.find(":") + 2));  // Extract Row
        } else if (line.find("Book Number:") != string::npos) {
            newBook.newBook.pos.bookNumber = stoi(line.substr(line.find(":") + 2));  // Extract Book Number
        }

        if (line.find("-----------------------------") != string::npos) {
            books.push_back(newBook);  // Add book to vector
            newBook = Book();  // Reset newBook for next book
        }
    }

    inputFile.close();
    return books;
}


void Book::WriteBook_to_File(const string& filename){
    ofstream outputFile(filename,ios::app);  // Append mode to add new books

    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing!"<<endl;
        return;
    }

    outputFile<<"Book Name: "<<newBook.Name<<endl;
    outputFile<<"ISBN: "<<newBook.ISBN<<endl;
    outputFile<<"Year: "<<newBook.Year<<endl;
    outputFile<<"Shelf: "<<newBook.pos.Shelf<<endl;
    outputFile<<"Row: "<<newBook.pos.row<<endl;
    outputFile<<"Book Number: "<<newBook.pos.bookNumber<<endl;
    outputFile<<"-----------------------------"<<endl;  // Separator between entries

    outputFile.close();
    printCentered(Blue "Book Added!!!\n\n" Default);
}

void Book::DisplayBook(){
    printCentered("Book Name: ");
    cout<<Blue<<newBook.Name<<Default<<endl;
    printCentered("ISBN: ");
    cout<<Blue<<newBook.ISBN<<Default<<endl;
    printCentered("Year: ");
    cout<<Blue<<newBook.Year<<Default<<endl;
    printCentered("Book Position: ");
    cout<<Blue<<"Shelf: "<<Default<<Green<<newBook.pos.Shelf<<Default<<" | "<<Blue<<"Row: "<<Default<<Green<<newBook.pos.row<<Default<<" | "<<Blue<<"book Number: "<<Default<<Green<<newBook.pos.bookNumber<<Default<<endl;
}