#ifndef __HASH
#define __HASH

#include <stdbool.h>

typedef enum _type {
    NIL,
    INTEGER,
    STRING
} Type;

typedef struct _entry {
    size_t siz;
    Type type;
    void *val;
    char *key;
    bool col;
} Entry;

typedef struct _table {
    unsigned int size, entries;
    float load;
    Entry **e;
} Table;

Table *makeTable();
void freeTable(Table *);

void hset(Table *t, char *key, void *val, Type type, size_t siz);
void hdel(Table *t, char *key);
Type hget(Table *t, char *key, void *val);

#ifdef TESTING
unsigned int hash(const char *k);
#endif /* !TESTING */
#endif /* !__HASH */
