#ifndef PCALC_SP_H
#define PCALC_SP_H

#include <PCalc.h>

/************************************************
 *  PCalc_SP - Child class of PCalc,            *
 *  Performs a single process, single threaded  *
 *  implementation of the Sieve of Eratosthenes *
 ************************************************/

class PCalc_SP : public PCalc
{
    public:
        //Calls parent constructor to create an array of numbers from 0 to array_size
        PCalc_SP(unsigned int array_size) : PCalc(array_size) {}

        //Calls parent destructor
        virtual ~PCalc_SP() {}

        //Marks non prime numbers so they are not included in the final list
        virtual void markNonPrimes() override; 
};

#endif
