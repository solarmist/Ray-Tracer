//
//  RNG.h
//  RayTracer
//
//  Created by Joshua Olson on 3/15/11.
//  Copyright 2011 solarmist. All rights reserved.
//

#ifndef _RNG_H_
#define _RNG_H_ 1

#ifndef precision
    //Use double on 64-bit OSs, float otherwise
    #ifdef _64_BIT
        typedef double precision;
    #else
        typedef float precision;
    #endif
#endif


class RNG
{
public:

    RNG(unsigned long long _seed = 7563846514231ULL)
    {
        seed        = _seed;
        mult        = 620394626989911ULL;
        llongMax   = 18446744073709551615ULL;
        floatMax   = 18446744073709551615.0f;
        
        if (sizeof(precision) < 8) {
            llongMax = 4294967295ULL;
            floatMax = 4294967295.0f;
        }
        
    }
    precision operator()();
    
    unsigned long long seed;
    unsigned long long mult;
    unsigned long long llongMax;
    precision floatMax;
};

inline precision RNG::operator()(){
    seed = mult * seed;
    return precision(seed % llongMax) / floatMax;
}

#endif // _RNG_H_