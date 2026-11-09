#include <stdio.h>
#include "book.h"
#include "issue.h"
#include "storage.h"
#include "report.h"
#include "input.h"

/* Global storage for the whole program, defined once here and declared
   'extern' in book.h / issue.h so every .c file shares the same arrays. */
Book bookList[MAX_BOOKS];
int  bookCount = 0;

IssueRecord issueList[MAX_ISSUES];
int         issueCount = 0;

static void printMenu(void) {
    printf("\n========= LIBRARY MANAGEMENT SYSTEM =========\n");
    printf(" 1. Add Book\n");
    printf(" 2. Display All Books\n");
    printf(" 3. Issue Book\n");
    printf(" 4. Return Book\n");
    printf(" 5. Report: All Books\n");
    printf(" 6. Report: Currently Issued Books\n");
    printf(" 7. Report: Overdue Books\n");
    printf(" 8. Save & Exit\n");
    printf("==============================================\n");
}

int main(void) {
    loadBooks();
    loadIssues();

    int choice = 0;
    do {
        printMenu();

        int inputClosed = !readInt("Enter your choice: ", 1, 8, &choice);
        if (inputClosed) {
            printf("\nInput closed - saving and exiting.\n");
            choice = 8;
        }

        switch (choice) {
            case 1: addBook();               break;
            case 2: displayAllBooks();       break;
            case 3: issueBook();             break;
            case 4: returnBook();            break;
            case 5: listAllBooksReport();    break;
            case 6: listIssuedBooksReport(); break;
            case 7: listOverdueBooksReport();break;
            case 8: {
                int booksOk  = saveBooks();
                int issuesOk = saveIssues();
                if (booksOk && issuesOk) {
                    printf("Data saved. Goodbye!\n");
                } else if (inputClosed) {
                    printf("WARNING: data could not be saved.\n");
                } else {
                    printf("Data was NOT saved, so the program is staying open.\n"
                           "Fix the problem, then choose 8 again.\n");
                    choice = 0;    /* stay in the menu instead of losing data */
                }
                break;
            }
        }
    } while (choice != 8);

    return 0;
}
