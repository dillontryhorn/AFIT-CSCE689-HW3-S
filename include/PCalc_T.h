#ifndef PCALC_T_H
#define PCALC_T_H

#include <PCalc.h>

/************************************************
 *  PCalc_T - Child class of PCalc,             *
 *  Performs a multi-threaded implementation    *
 *  of the Sieve of Eratosthenes                *
 ************************************************/

class PCalc_T : public PCalc
{
    public:
        //Calls parent constructor and creates array, stores num_thread in private variable
        PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size), num_threads(num_threads) {}
        
        //Calls parent destructor
        virtual ~PCalc_T() {}

        //Marks non prime numbers using multi-threading
        virtual void markNonPrimes() override;
    private:
        unsigned int num_threads;
};

#endif
