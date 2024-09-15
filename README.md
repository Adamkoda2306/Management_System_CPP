# Library Management System

A simple **Library Management System** built using **C++**. This project helps manage the essential functions of a library, allowing students to borrow and return books, and librarians to manage the collection and issue books.

Librarian Login pass: admin123

## Features

### 1. Student Functionality:
- **Login**: Students can log in using their credentials.
- **Book Search**: Browse or search for available books in the library.
- **Display Profile**: See Their Own Profile Details.
- **CreateUser**: New Login Details can be Created by the student.
- **Display All Books**: Students can See all books details which are in the library.

### 2. Librarian Functionality:
- **Login**: Librarians have access to the admin panel.
- **Add Books**: Add new books to the library database.
- **Issue Books**: Issue books to students by entering the student's ID and book details.
- **Return Books**: Process book returns and update the library inventory.
- **Update Book Position**: Modify the physical location of books in the library.
- **Remove Books**: Delete outdated or unavailable books from the system.

### 3. Application Features:
- **Cross-Platform Terminal Control**: The system supports clearing the console screen on both Windows and Unix-like systems.
- **File-based Persistence**: Data such as book details and issued books are stored in text files for future use.
- **User-Friendly Interface**: Easy-to-navigate menus for both students and librarians, with clear prompts and feedback.

## Structure of the Project

```
/LibraryManagementSystem
│
├── Pages/
│   ├── TerminalUtils.h        # Utilities for handling terminal actions
|   ├── TerminalUtils.cpp
│   ├── Students_MainMenu.h    # Main menu logic for students
|   ├── Students_MainMenu.cpp
│   ├── Librarian_MainMenu.h   # Main menu logic for librarians
|   ├── Librarian_MainMenu.cpp
│   ├── Menu.h                 # Main entry point for login options
|   ├── Menu.cpp
|   ├── Book.h                     # Book class and related operations
|   ├── Book.cpp
│
├── Data/
|   ├── Books.txt                  # Persistent storage for book details
|   ├── Issued_Books.txt            # Persistent storage for issued book records
|   ├── Student_Profiles.txt                  # Persistent storage for book details
|
└── Management_System.cpp                   # Main program file
```

## Getting Started

### Prerequisites

- A working **C++ compiler** (e.g., g++, clang++).
- Basic knowledge of C++, OOPs and file handling.

### Installation & Compilation

1. **Clone the repository**:
   ```bash
   https://github.com/Adamkoda2306/Management_System_CPP.git
   cd Management_System_CPP
   ```

2. **Compile the project**:
   You can compile the project using a C++ compiler. For example, with `g++`:
   ```bash
   g++ *.cpp Pages/*.cpp -o Management_System
   ```

3. **Run the program**:
   After compilation, you can execute the application:
   ```bash
   ./Management_System
   ```

### Usage

- The application starts with a **menu** allowing the user to choose between **student** and **librarian** login or to exit the program.
- Follow the on-screen prompts to navigate through the menus.
- Librarians can manage the library's inventory, while students can See their Profile and Search books.

## Important Functions

### 1. `Librarian_Menu` Class
Handles all librarian-related operations such as adding books, issuing/returning books, and managing the book inventory.

- `AddNewBook()`: Adds a new book to the library.
- `IssueBook()`: Issues a book to a student.
- `ReturnBook()`: Handles the return process for books.
- `UpdateBookPosition()`: Updates the physical location of books.
- `RemoveBook()`: Removes a book from the library's database.

### 2. `Student_Menu` Class
Handles all Students-related operations such as Search books and Create user.

- `BookSearch_ISBN()`: Adds a new book to the library.
- `Display Profile()`: Issues a book to a student.
- `CreateUser()`: Handles the return process for books.
- `BookSearch_Name()`: Updates the physical location of books.
- `Display_all_Books()`: Removes a book from the library's database.

## Future Enhancements

Here are some possible future improvements:
- **Authentication**: Add authentication for both students and librarians.
- **Fine Management**: Add functionality for calculating and tracking overdue fines.
- **Search Books**: Implement advanced search options based on author, genre, and other criteria.
- **Notifications**: Add email or SMS notifications for students about due dates and fines.
- **Graphical User Interface (GUI)**: Upgrade to a GUI using libraries like **Qt** or **wxWidgets** for a more intuitive interface.

## Contact

If you have any questions or suggestions, feel free to reach out to me via:
- **Email**: adam.koda2306@gmail.com
- **GitHub**: [AdamKoda](https://github.com/Adamkoda2306)
