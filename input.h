#ifndef INPUT_H
#define INPUT_H

/* Safe keyboard input. Both functions return 1 on success and
   0 if the input stream has closed (Ctrl+D / end of piped input). */

/* Reads one non-empty line into buf (at most size-1 characters).
   Extra characters beyond that are discarded, never left behind. */
int readLine(const char *prompt, char *buf, int size);

/* Reads a whole number between min and max, asking again until valid. */
int readInt(const char *prompt, int min, int max, int *out);

#endif
