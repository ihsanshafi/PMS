/*
#Library Management System

1.Nahome Teshome UGR/30997/15
2.Amanuel Aberie UGR/30137/15
3.Yosef Tewodros UGR/31453/15 
4.Nahom Mulushewa UGR/30999/15
5.Yeabsira Solomon UGR/31386/15
6.Aymen Nesredin UGR/30214/15

*/
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    char name[100];
    char author[100];
    int pages;
    char genre[50];
};

void addBook(Book library[], int& numBooks) {
    if (numBooks < MAX_BOOKS) {
        Book newBook;
        cout << "Enter book name: ";
        cin.ignore();
        cin.getline(newBook.name, sizeof(newBook.name));

        cout << "Enter author name: ";
        cin.getline(newBook.author, sizeof(newBook.author));

        cout << "Enter number of pages: ";
        cin >> newBook.pages;

        cout << "Enter genre: ";
        cin.ignore();
        cin.getline(newBook.genre, sizeof(newBook.genre));

        library[numBooks++] = newBook;
        cout << "Book added successfully.\n";
    } else {
        cout << "Library is full. Cannot add more books.\n";
    }
}

void displayLibrary(const Book library[], int numBooks) {
    if (numBooks > 0) {
        cout << "Library Contents:\n";
        for (int i = 0; i < numBooks; ++i) {
            cout << "Book " << (i + 1) << ":\n";
            cout << "Name: " << library[i].name << "\n";
            cout << "Author: " << library[i].author << "\n";
            cout << "Pages: " << library[i].pages << "\n";
            cout << "Genre: " << library[i].genre << "\n\n";
        }
    } else {
        cout << "Library is empty.\n";
    }
}

void editBook(Book library[], int numBooks) {
    if (numBooks > 0) {
        int bookIndex;
        cout << "Enter the index of the book to edit (1 to " << numBooks << "): ";
        cin >> bookIndex;

        if (bookIndex >= 1 && bookIndex <= numBooks) {
            cout << "Editing Book " << bookIndex << ":\n";
            cout << "Enter new book name: ";
            cin.ignore();
            cin.getline(library[bookIndex - 1].name, sizeof(library[bookIndex - 1].name));

            cout << "Enter new author name: ";
            cin.getline(library[bookIndex - 1].author, sizeof(library[bookIndex - 1].author));

            cout << "Enter new number of pages: ";
            cin >> library[bookIndex - 1].pages;

            cout << "Enter new genre: ";
            cin.ignore();
            cin.getline(library[bookIndex - 1].genre, sizeof(library[bookIndex - 1].genre));

            cout << "Book edited successfully.\n";
        } else {
            cout << "Invalid book index.\n";
        }
    } else {
        cout << "Library is empty. Cannot edit.\n";
    }
}

void deleteBook(Book library[], int& numBooks) {
    if (numBooks > 0) {
        int bookIndex;
        cout << "Enter the index of the book to delete (1 to " << numBooks << "): ";
        cin >> bookIndex;

        if (bookIndex >= 1 && bookIndex <= numBooks) {
            for (int i = bookIndex - 1; i < numBooks - 1; ++i) {
                library[i] = library[i + 1];
            }
            --numBooks;
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Invalid book index.\n";
        }
    } else {
        cout << "Library is empty. Cannot delete.\n";
    }
}

int main() {
    Book library[MAX_BOOKS];
    int numBooks = 0;
    int choice;

    do {
        cout << "\nASTU Library Management System Menu:\n";
        cout << "1. Add a book\n";
        cout << "2. Display library\n";
        cout << "3. Edit a book\n";
        cout << "4. Delete a book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library, numBooks);
                break;
            case 2:
                displayLibrary(library, numBooks);
                break;
            case 3:
                editBook(library, numBooks);
                break;
            case 4:
                deleteBook(library, numBooks);
                break;
            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}