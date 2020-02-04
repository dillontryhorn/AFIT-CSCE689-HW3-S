#include <PCalc_SP.h>

/************************************************
 *  markNonPrimes                               *
 *  Implements the Sieve of Eratosthenes using  *
 *  two for-loops, no multi-threading           *
 ************************************************/

void PCalc_SP::markNonPrimes()
{
    PCalc_SP::at( 0 ) = false;
    PCalc_SP::at( 1 ) = false;

    //Start at two
    for( unsigned int i = 2; i*i <= PCalc_SP::array_size(); i++ )
    {
        if( PCalc_SP::at(i) )
        {
            for( unsigned int j = i*i; j <= PCalc_SP::array_size(); j += i )
                PCalc_SP::at( j ) = false; //Non-prime numbers
        }
    }
}