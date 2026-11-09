#ifndef BOOK_H
#define BOOK_H

#define TITLE_LEN   100
#define AUTHOR_LEN  50
#define MAX_BOOKS   200
#define MAX_COPIES  1000

typedef struct {
    int  id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int  totalCopies;
    int  availableCopies;
} Book;

/* Shared global state: defined once in main.c, used everywhere else */
extern Book bookList[MAX_BOOKS];
extern int  bookCount;

void  addBook(void);
void  displayAllBooks(void);
Book *findBookById(int id);
int   findBookIndexById(int id);

#endif
