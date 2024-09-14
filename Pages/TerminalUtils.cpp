#include "TerminalUtils.h"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h> // Windows-specific
#else
    #include <sys/ioctl.h> // Unix-specific
    #include <unistd.h>
#endif

using namespace std;

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

int width = getTerminalWidth();
int padding = (width - (width/3)) / 2;

void printCentered(const string& text) {
    cout<<setw(padding)<<""<<text;
}

void addVerticalPadding(int lines) {
    for (int i = 0; i < lines; ++i) {
        cout<<endl;
    }
}
