#include <stdio.h>
#include "book.h"
#include "input.h"

/* Returns the array index of the book with this id, or -1. */
int findBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookList[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Same search, but returns a pointer to the book (or NULL). */
Book *findBookById(int id) {
    int index = findBookIndexById(id);
    return (index == -1) ? NULL : &bookList[index];
}

/* Asks for a title, author and copy count, then appends the book.
   The ID is assigned automatically (books are never deleted, so
   "count + 1" can never collide). */
void addBook(void) {
    if (bookCount >= MAX_BOOKS) {
        printf("Catalog is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    printf("\n--- Add New Book ---\n");
    printf("Book ID assigned: %d\n", newBook.id);

    if (!readLine("Title: ", newBook.title, TITLE_LEN))       return;
    if (!readLine("Author: ", newBook.author, AUTHOR_LEN))    return;
    if (!readInt("Number of copies (1-1000): ", 1, MAX_COPIES,
                 &newBook.totalCopies))                       return;
    newBook.availableCopies = newBook.totalCopies;

    bookList[bookCount++] = newBook;
    printf("Book \"%s\" added successfully.\n", newBook.title);
}

/* Prints every book as a table. Read-only. */
void displayAllBooks(void) {
    if (bookCount == 0) {
        printf("No books in the catalog yet.\n");
        return;
    }

    printf("%-4s %-30s %-20s %-8s %-10s\n",
           "ID", "Title", "Author", "Total", "Available");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-4d %-30.30s %-20.20s %-8d %-10d\n",
               bookList[i].id, bookList[i].title, bookList[i].author,
               bookList[i].totalCopies, bookList[i].availableCopies);
    }
}
