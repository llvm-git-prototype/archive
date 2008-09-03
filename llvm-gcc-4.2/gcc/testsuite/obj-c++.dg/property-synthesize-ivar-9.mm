/* APPLE LOCAL file radar 5435299 */
/* The ivar's C scope extends from the @synthesize statement to the end of the file */
/* { dg-options "-fnew-property-ivar-synthesis -mmacosx-version-min=10.5 -m64" { target powerpc*-*-darwin* i?86*-*-darwin* } } */
/* { dg-options "-fnew-property-ivar-synthesis -fobjc-new-property" { target arm*-*-darwin* } } */
/* { dg-do compile { target *-*-darwin* } } */

#ifdef __OBJC2__
#import <objc/Object.h>

@interface Test9_1 : Object
@property int prop;
@end

@implementation Test9_1
-(int) method1 { return prop; }  /* { dg-error "\\'prop\\' was not declared in this scope" } */
@synthesize prop;
-(int) method2 { return prop; }
@end

@implementation Test9_1 (Category)
-(int) method3 { return prop; }
@end

@interface Test9_2 : Object
@property int prop;
@end

@implementation Test9_2
-(int) method1 { return prop_ivar; }  /* { dg-error "\\'prop_ivar\\' was not declared in this scope" } */
-(int) method2 { return prop; }       /* { dg-error "\\'prop\\' was not declared in this scope" } */
@synthesize prop = prop_ivar;
-(int) method3 { return prop_ivar; }
-(int) method4 { return prop; }       /* { dg-error "\\'prop\\' was not declared in this scope" } */
@end

@implementation Test9_2 (Category)
-(int) method5 { return prop_ivar; }  
-(int) method6 { return prop; }       /* { dg-error "\\'prop\\' was not declared in this scope" } */
@end

#endif
