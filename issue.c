#include <stdio.h>
#include <time.h>
#include "issue.h"
#include "book.h"
#include "input.h"

/* Fills day/month/year with today's date. */
void getCurrentDate(int *day, int *month, int *year) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    *day   = t->tm_mday;
    *month = t->tm_mon + 1;       /* tm_mon counts from 0 */
    *year  = t->tm_year + 1900;   /* tm_year counts from 1900 */
}

/* Adds daysToAdd days to a date; mktime handles month/year/leap-year rollover. */
static void addDaysToDate(int day, int month, int year, int daysToAdd,
                          int *outDay, int *outMonth, int *outYear) {
    struct tm t = {0};
    t.tm_mday  = day + daysToAdd;   /* mktime normalises out-of-range days */
    t.tm_mon   = month - 1;
    t.tm_year  = year - 1900;
    t.tm_hour  = 12;                /* midday avoids daylight-saving edge cases */
    t.tm_isdst = -1;
    mktime(&t);

    *outDay   = t.tm_mday;
    *outMonth = t.tm_mon + 1;
    *outYear  = t.tm_year + 1900;
}

/* Returns 1 if the first date is strictly earlier than the second. */
int isDateBefore(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 != y2) return y1 < y2;
    if (m1 != m2) return m1 < m2;
    return d1 < d2;
}

/* Lends one copy of a book: creates an IssueRecord (due in LOAN_DAYS days)
   and reduces the book's availableCopies. */
void issueBook(void) {
    if (issueCount >= MAX_ISSUES) {
        printf("Issue records are full. Cannot issue more books.\n");
        return;
    }

    int bookId;
    printf("\n--- Issue Book ---\n");
    if (!readInt("Enter Book ID to issue: ", 1, MAX_BOOKS, &bookId)) return;

    int index = findBookIndexById(bookId);
    if (index == -1) {
        printf("No book found with ID %d.\n", bookId);
        return;
    }
    if (bookList[index].availableCopies <= 0) {
        printf("\"%s\" is currently unavailable - all copies are issued.\n",
               bookList[index].title);
        return;
    }

    IssueRecord rec;
    rec.issueId  = issueCount + 1;
    rec.bookId   = bookId;
    rec.returned = 0;

    if (!readLine("Borrower name: ", rec.borrowerName, NAME_LEN)) return;

    getCurrentDate(&rec.issueDay, &rec.issueMonth, &rec.issueYear);
    addDaysToDate(rec.issueDay, rec.issueMonth, rec.issueYear, LOAN_DAYS,
                  &rec.dueDay, &rec.dueMonth, &rec.dueYear);

    issueList[issueCount++] = rec;
    bookList[index].availableCopies--;

    printf("Issued \"%s\" to %s. Due date: %02d-%02d-%04d\n",
           bookList[index].title, rec.borrowerName,
           rec.dueDay, rec.dueMonth, rec.dueYear);
}

/* Marks an issue as returned and gives the copy back to the catalog. */
void returnBook(void) {
    int issueId;
    printf("\n--- Return Book ---\n");
    if (!readInt("Enter Issue ID: ", 1, MAX_ISSUES, &issueId)) return;

    for (int i = 0; i < issueCount; i++) {
        if (issueList[i].issueId != issueId) continue;

        if (issueList[i].returned) {
            printf("This issue record is already marked as returned.\n");
            return;
        }
        issueList[i].returned = 1;

        int b = findBookIndexById(issueList[i].bookId);
        if (b != -1) {
            bookList[b].availableCopies++;
            printf("\"%s\" returned by %s. Thank you!\n",
                   bookList[b].title, issueList[i].borrowerName);
        } else {
            printf("Book returned (original book record no longer exists).\n");
        }
        return;
    }
    printf("No issue record found with Issue ID %d.\n", issueId);
}
