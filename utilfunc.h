//
//  utilfunc.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-15.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef ROBDD_utilfunc_h
#define ROBDD_utilfunc_h

//typedef int int;
//typedef int int;

struct bddNode
{
    bddNode():var(0),low(0),high(0)
    {
    }
    
    bddNode(int _var, int _low, int _high)
    {
        var = _var;
        low = _low;
        high = _high;
    }
    
    int var;
    int low;
    int high;
};


class applyMem
{
public:
    applyMem():u1(0),u2(0),u12(0)
    {
    }
    
    applyMem(int _u1, int _u2, int _u12)
    {
        u1 = _u1; u2 = _u2; u12 = _u12;
    }

    int u1;
    int u2;
    int u12;
};


/* hash function */
/* uses pseudo-random number generation */
/* use unsigned int in C to guarantee modular arithmetic */
int hash(bddNode *k, int m)
{
    REQUIRES(m > 1);
    unsigned int x = 1664525;
    unsigned int y = 1013904223;	/* inlined random number generator */
    unsigned int r = 0xdeadbeef;	/* initial seed */
    unsigned int h = (unsigned)k->var;
    r = r*x + y;		 /* mod 2^32, linear congruential random num */
    h = r*h + (unsigned)k->low;
    r = r*x + y;		 /* mod 2^32, linear congruential random num */
    h = r*h + (unsigned)k->high;
    h = h % (unsigned)m;		/* reduce to range */
    ENSURES(0 <= (int)h && (int)h < m);
    return (int)h;
}

/* key comparison = node comparison */
bool equal(bddNode *k1, bddNode *k2) {
    return k1->var == k2->var
    && k1->low == k2->low
    && k1->high == k2->high;
}

/* key equality compares inputs, ignore output */
bool apply_equal(applyMem *ap1, applyMem *ap2) {
    return ap1->u1 == ap2->u1 && ap1->u2 == ap2->u2;
}

/* hash functions uses pseudorandom numbers */
int apply_hash(applyMem *ap, int m) {
    REQUIRES(m > 0);
    unsigned int x = 1664525;
    unsigned int y = 1013904223;
    unsigned int r = 0xdeadbeef;
    unsigned int h = (unsigned) ap->u1;
    r = r*x + y;
    h = r*h + (unsigned) ap->u2;
    h = h % (unsigned)m;
    return (int)h;
}

bool sat_equal(int *k1, int *k2)
{
    return *k1 == *k2;
}

int sat_hash(int *k, int m)
{
    REQUIRES(*k >=0 && m>0);
    return *(int *)k % m;
}

int safe_shiftl(int n, int k) {
    REQUIRES(n >= 0 && k >= 0);
    if ((n > 0 && k >= (int)sizeof(int)*8)
        || n > (INT_MAX>>k)) {
        fprintf(stderr, "integer overflow %d << %d\n", n, k);
        abort();
    }
    return n<<k;
}

int safe_plus(int m, int n) {
    REQUIRES(m >= 0 && n >= 0);
    if (n > INT_MAX-m) {
        fprintf(stderr, "integer overflow %d + %d\n", m, n);
        abort();
    }
    return m+n;
}

#endif
