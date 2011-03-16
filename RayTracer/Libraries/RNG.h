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
    RNG(unsigned long long _seed = 7564231ULL)
    {
        seed        = _seed;
        mult        = 62089911ULL;
        llong_max   = 4294967295ULL;
        float_max   = 4294967295.0f;
        
    }
    precision operator()();
    
    unsigned long long seed;
    unsigned long long mult;
    unsigned long long llong_max;
    precision float_max
};

inline precision RNG::operator()(){
    seed = mult * seed;
    return precision(seed % llong_max) / float_max;
}

#endif // _RNG_H_