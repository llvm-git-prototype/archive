/* APPLE LOCAL file radar 6185344 - updated for radar 6230297 */
/* Test for blocks with explicit return type specified. */
/* { dg-options "-mmacosx-version-min=10.6 -ObjC" { target *-*-darwin* } } */
/* { dg-do compile } */

typedef float * PF;
float gf;

@interface NSView
  - (id) some_method_that_returns_id;
@end

NSView *some_object;

void some_func (NSView * (^) (id));

typedef struct dispatch_item_s *dispatch_item_t;
typedef void (^completion_block_t)(void);

typedef double (^myblock)(int);
double test(myblock I);

int main()
{
	 __block int x = 1;
 	__block int y = 2;

	^void *{ return 0; };

	^float(float y){ return y; };

	^double (float y, double d)
           {
	      if (y)
	       return d;
	      else
	       return y;
	   };

	const char * (^chb) (int flag, const char *arg, char *arg1) = ^ const char * (int flag, const char *arg, char *arg1) {
	  if (flag)
	    return 0;
	  if (flag == 1)
	    return arg;
          else if (flag == 2)
	    return "";
	  return arg1; 
	};

	^PF { return &gf; };

	some_func(^ NSView * (id whatever) { return [some_object some_method_that_returns_id]; });

	double res = test(^(int z){x = y+z; return (double)z; });	
}

void func()
{
  completion_block_t X;

  completion_block_t (^blockx)(dispatch_item_t) = ^completion_block_t (dispatch_item_t item) {
    return X;
  };

  completion_block_t (^blocky)(dispatch_item_t) = ^(dispatch_item_t item) {
    return X;
  };

  blockx = blocky;

}


// intent: block taking int returning block that takes char,int and returns int
int (^(^block)(double x))(char, short);

void foo() {
   int one = 1;
   block = ^(double x){ return ^(char c, short y) { return one + c + y; };};  /* { dg-warning "returning block that lives on the local stack" } */
   // or:
   block = ^(double x){ return ^(char c, short y) { return one + (int)c + y; };};  /* { dg-warning "returning block that lives on the local stack" } */
}


