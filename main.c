#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "disp.h"

Table *t;
char *key, *val;

int main(int argc, char **argv) {
    char opt;
    int *tmp;
    void *v;
    Type type;
    t = makeTable();
    key = calloc(1024, sizeof(char));
    val = calloc(1024, sizeof(char));
    init();
    while((opt = in()) != 'q') {
        switch(opt) {
            case 'i':
                getkeyval(key, val);
                if(val[0] == '\0') {
                    hset(t, key, NULL, NIL, sizeof(void *));
                } else if(val[0] >= '0' && val[0] <= '9') {
                    *tmp = atoi(val);
                    hset(t, key, tmp, INTEGER, sizeof(int));
                } else {
                    hset(t, key, val, STRING, sizeof(char) * strlen(val));
                }
                display(t);
                break;
            case 'd':
                getkey(key);
                hdel(t, key);
                display(t);
                break;
            case 'g':
                getkey(key);
                type = hget(t, key, v);
                dispval(v, type);
                break;
            default:
                continue;
        }
    }
    freeTable(t);
    free(key);
    free(val);
    end();
    return 0;
}
