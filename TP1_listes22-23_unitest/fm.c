#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 100

FILE *fmemopen(void *buf, size_t size, const char *mode) {
    FILE *fp;

    if (strcmp(mode, "w") != 0) {
        return NULL;
    }

    if (size > MAX_BUF_SIZE) {
        size = MAX_BUF_SIZE;
    }

    fp = fopen("fmemopen.tmp", mode);
    if (fp == NULL) {
        return NULL;
    }

    setbuf(fp, buf);
    return fp;
}