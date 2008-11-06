/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */
/* LLVM LOCAL test not applicable */
/* { dg-require-fdump "" } */

typedef struct  {
  int x;
  int z;
} Foo_t;

char *xm;
void bar(void);

void foo(void)
{
  Foo_t x;
  x.x = 1;
  x.z = 2;
  xm = (char *)&x;
  bar();
  /* We can't propagate x.z past bar, so this link_error should still be there.  */
  if (x.z != 2)
    link_error ();
}
/* { dg-final { scan-tree-dump-times "link_error" 1 "optimized"} } */
/* { dg-final { cleanup-tree-dump "optimized" } } */
