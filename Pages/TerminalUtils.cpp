#include <iostream>
#include <iomanip> //for position

// Checks if the system is Window or Linux
#ifdef _WIN32
    #include <windows.h> // Windows-specific
#else
    #include <sys/ioctl.h> // Unix-specific
    #include <unistd.h>
#endif

//user defined Header Files
#include "TerminalUtils.h"
using namespace std;

// Checks if the system is Window or Linux
#ifndef _WIN32
int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
#else
int getTerminalWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}
#endif

int width = getTerminalWidth();// getting the width
int padding = (width - (width/3)) / 2; // adjusting the padding accoeding to the width

// User defined print function with left padding
void printCentered(const string& text) {
    cout<<setw(padding)<<""<<text;
}

// User defined function for top padding
void addVerticalPadding(int lines) {
    for (int i = 0; i < lines; ++i) {
        cout<<endl;
    }
}
