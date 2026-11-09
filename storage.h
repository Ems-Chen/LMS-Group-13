#ifndef STORAGE_H
#define STORAGE_H

/* save* return 1 on success, 0 on failure (and print the reason).
   load* never crash: a missing file means "start empty", a damaged
   file prints a warning and also starts empty. */
int  saveBooks(void);
int  saveIssues(void);
void loadBooks(void);
void loadIssues(void);

#endif
