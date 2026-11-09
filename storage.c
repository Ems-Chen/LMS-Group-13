#include <stdio.h>
#include "storage.h"
#include "book.h"
#include "issue.h"

#define BOOKS_FILE  "data/books.dat"
#define ISSUES_FILE "data/issues.dat"

/* Writes the count, then the whole array, as raw binary. Returns 1 only if
   every write (and the final close) succeeded. */
static int saveArray(const char *path, const void *items, size_t itemSize, int count) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        printf("Error: cannot write %s (does the 'data' folder exist?).\n", path);
        return 0;
    }
    int ok = fwrite(&count, sizeof(int), 1, fp) == 1 &&
             fwrite(items, itemSize, (size_t)count, fp) == (size_t)count;
    if (fclose(fp) != 0) ok = 0;
    if (!ok) printf("Error: writing %s failed.\n", path);
    return ok;
}

/* Reads the count and the array. The count is checked against maxItems
   BEFORE reading, so a damaged file cannot overflow the array.
   Returns the number of items loaded (0 if missing or damaged). */
static int loadArray(const char *path, void *items, size_t itemSize, int maxItems) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) return 0;                      /* first run: nothing saved yet */

    int count = 0;
    int ok = fread(&count, sizeof(int), 1, fp) == 1 &&
             count >= 0 && count <= maxItems &&
             fread(items, itemSize, (size_t)count, fp) == (size_t)count;
    fclose(fp);

    if (!ok) {
        printf("Warning: %s is damaged; starting with no records from it.\n", path);
        return 0;
    }
    return count;
}

int  saveBooks(void)  { return saveArray(BOOKS_FILE,  bookList,  sizeof(Book),        bookCount);  }
int  saveIssues(void) { return saveArray(ISSUES_FILE, issueList, sizeof(IssueRecord), issueCount); }
void loadBooks(void)  { bookCount  = loadArray(BOOKS_FILE,  bookList,  sizeof(Book),        MAX_BOOKS);  }
void loadIssues(void) { issueCount = loadArray(ISSUES_FILE, issueList, sizeof(IssueRecord), MAX_ISSUES); }
