
#ifndef _MACROS_H
#define _MACROS_H

#define BITFIELD2(t,a,b)		t b; t a;
#define BITFIELD3(t,a,b,c)		t c; t b; t a;
#define BITFIELD4(t,a,b,c,d)		t d; t c; t b; t a;
#define BITFIELD5(t,a,b,c,d,e)		t e; t d; t c; t b; t a;
#define BITFIELD6(t,a,b,c,d,e,f)	t f; t e; t d; t c; t b; t a;
#define BITFIELD7(t,a,b,c,d,e,f,g)	t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD8(t,a,b,c,d,e,f,g,h)	t h; t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD9(t,a,b,c,d,e,f,g,h,i)	t i; t h; t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD10(t,a,b,c,d,e,f,g,h,i,j) t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD11(t,a,b,c,d,e,f,g,h,i,j,k) t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD12(t,a,b,c,d,e,f,g,h,i,j,k,l) t l; t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
#define BITFIELD13(t,a,b,c,d,e,f,g,h,i,j,k,l,m) t m; t l; t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;

#define BITFIELD17(t,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) t q; t p; t o; t n; t m; t l; t k; t j;t i; t h; t g; t f; t e; t d; t c; t b; t a;

#endif /* !_MACROS_H */