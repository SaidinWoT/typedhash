#ifndef __DISP
#define __DISP

void init();
void end();

void getkeyval(char *key, char *val);
void getkey(char *key);
void display(Table *t);
void dispval(void *val, Type t);

char in();

#endif /* !__DISP */
