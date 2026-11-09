#ifndef ISSUE_H
#define ISSUE_H

#define NAME_LEN    50
#define MAX_ISSUES  500
#define LOAN_DAYS   14   /* days a book may be kept before it is due */

typedef struct {
    int  issueId;
    int  bookId;
    char borrowerName[NAME_LEN];
    int  issueDay, issueMonth, issueYear;
    int  dueDay,   dueMonth,   dueYear;
    int  returned;   /* 0 = still out, 1 = returned */
} IssueRecord;

extern IssueRecord issueList[MAX_ISSUES];
extern int         issueCount;

void issueBook(void);
void returnBook(void);

/* Shared date helpers (all dates are day, month, year). */
void getCurrentDate(int *day, int *month, int *year);
int  isDateBefore(int d1, int m1, int y1, int d2, int m2, int y2);

#endif
