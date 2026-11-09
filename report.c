#include <stdio.h>
#include "report.h"
#include "book.h"
#include "issue.h"

/* Prints one issue record as a table row (shared by both issue reports). */
static void printIssueRow(const IssueRecord *r) {
    Book *b = findBookById(r->bookId);
    printf("%-4d %-30.30s %-20.20s %02d-%02d-%04d\n",
           r->issueId, b ? b->title : "(unknown)", r->borrowerName,
           r->dueDay, r->dueMonth, r->dueYear);
}

static void printIssueHeader(void) {
    printf("%-4s %-30s %-20s %-10s\n", "ID", "Book", "Borrower", "Due Date");
    printf("-------------------------------------------------------------------\n");
}

void listAllBooksReport(void) {
    printf("\n=== Full Book Catalog ===\n");
    displayAllBooks();
}

void listIssuedBooksReport(void) {
    printf("\n=== Currently Issued Books ===\n");
    printIssueHeader();

    int found = 0;
    for (int i = 0; i < issueCount; i++) {
        if (!issueList[i].returned) {
            printIssueRow(&issueList[i]);
            found = 1;
        }
    }
    if (!found) printf("No books are currently issued.\n");
}

void listOverdueBooksReport(void) {
    int day, month, year;
    getCurrentDate(&day, &month, &year);

    printf("\n=== Overdue Books (as of %02d-%02d-%04d) ===\n", day, month, year);
    printIssueHeader();

    int found = 0;
    for (int i = 0; i < issueCount; i++) {
        /* overdue = not returned AND due date is strictly before today */
        if (!issueList[i].returned &&
            isDateBefore(issueList[i].dueDay, issueList[i].dueMonth, issueList[i].dueYear,
                         day, month, year)) {
            printIssueRow(&issueList[i]);
            found = 1;
        }
    }
    if (!found) printf("No overdue books.\n");
}
