#ifndef BOOK_H
#define BOOK_H

#include<string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

struct Position{
    int Shelf;
    int row;
    int bookNumber;
};

struct book{
    string Name;
    string ISBN;
    int Year;
    Position pos;
};

class Book{
public:
    book newBook;
    vector<Book> ReadBook_from_File(const string& filename);
    void WriteBook_to_File(const string& filename);
    void DisplayBook();
};

#endif
