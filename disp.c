#include <ncurses.h>
#include "hash.h"
#include "disp.h"

#define DISP 8

void init() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mvprintw(0, 0, "(i)nsert, (d)elete, or (g)et?");
    mvprintw(1, 0, "Key: ");
    mvprintw(2, 0, "Value: ");
    noecho();
}

void end() {
    clear();
    endwin();
}

char in() {
    curs_set(0);
    noecho();
    char c = getch();
    move(1, 5);
    clrtoeol();
    move(2, 7);
    clrtoeol();
    return c;
}

void display(Table *t) {
    unsigned int i, j;
    char *key, *val, *col;
    Entry *e;
    move(3, 0);
    clrtobot();
    for(i = 0; i < t->size / DISP; ++i) {
        for(j = 0; j < (DISP / t->size ? t->size : DISP); ++j) {
            mvprintw(j*2+4, i*20, "%d", i*DISP+j);
            if((e = t->e[i*DISP+j])) {
                mvprintw(j*2+4, i*20+3, "%-15s", e->key);
                mvprintw(j*2+5, i*20+1, "%s", e->col ? "t" : "f");
                switch(e->type) {
                    case NIL:
                        mvprintw(j*2+5, i*20+3, "NIL");
                        break;
                    case INTEGER:
                        mvprintw(j*2+5, i*20+3, "%d", *(int *)e->val);
                        break;
                    case STRING:
                        mvprintw(j*2+5, i*20+3, "\"%s\"", (char *)e->val);
                        break;
                }
            } else {
                mvprintw(j*2+4, 1*20+3, "E");
                mvprintw(j*2+5, i*20+3, "-");
            }
        }
    }
    mvprintw(21, 0, "size: %d", t->size);
    mvprintw(21, 10, "entries: %d", t->entries);
}

void dispval(void *val, Type t) {
    switch(t) {
        case NIL:
            mvprintw(2, 7, "NIL");
            break;
        case INTEGER:
            mvprintw(2, 7, "%d", *(int *)val);
            break;
        case STRING:
            mvprintw(2, 7, "%s", (char *)val);
            break;
    }
}

void getkeyval(char *key, char *val) {
    echo();
    curs_set(1);
    move(1, 5);
    getstr(key);
    move(2, 7);
    getstr(val);
}

void getkey(char *key) {
    echo();
    curs_set(1);
    move(1, 5);
    getstr(key);
}
