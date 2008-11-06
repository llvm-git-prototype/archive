/* APPLE LOCAL file radar 5832193 */
/* assigning a Block into a global should elicit a global write-barrier under GC */
/* { dg-do run } */
/* { dg-options "-mmacosx-version-min=10.5 -ObjC -fobjc-gc" { target *-*-darwin* } } */

#include <stdio.h>
void * _NSConcreteStackBlock;

int GlobalInt = 0;

id objc_assign_global(id val, id *dest) {
    GlobalInt = 1;
    return (id)0;
}

id objc_assign_ivar(id val, id dest, long offset) {
    GlobalInt = 1;
    return (id)0;
}

id objc_assign_strongCast(id val, id *dest) {
    GlobalInt = 1;
    return (id)0;
}


void (^GlobalVoidVoid)(void);


int main(char *argc, char *argv[]) {
   __block int i = 0;
   // assigning a Block into a global should elicit a global write-barrier under GC
   GlobalVoidVoid = ^ {  ++i; }; 
   return GlobalInt - 1;
}
