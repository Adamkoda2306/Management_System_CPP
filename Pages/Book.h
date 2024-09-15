// Book.h Header
#ifndef BOOK_H
#define BOOK_H

#include<string> //for strings
#include <vector> //for vectors
#include <fstream> //for file management
#include <iostream>
using namespace std;

// Position structure
struct Position{
    int Shelf;
    int row;
    int bookNumber;
};

// Book structure
struct book{
    string Name;
    string ISBN;
    int Year;
    Position pos;
};

class Book{
public:
    book newBook;// creating book variable
    //Functions for book.h Header
    vector<Book> ReadBook_from_File(const string& filename);
    void WriteBook_to_File(const string& filename);
    void DisplayBook();
};

#endif
