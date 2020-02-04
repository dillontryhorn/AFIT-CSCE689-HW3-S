#include <PCalc_T.h>
#include <atomic>
#include <cmath>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mutex;
std::atomic<unsigned int> nextbase(3);

/*  Inspiration for this code taken from 
 *  http://heather.cs.ucdavis.edu/~matloff/50/Hwk/Primes.c
 *  Repurposed using STL and this project's control flow
 */

void PCalc_T::markNonPrimes()
{
    //Non-prime 0 and 1 removed
    PCalc_T::at( 0 ) = false;
    PCalc_T::at( 1 ) = false;

    //Faster to perform this if 1 thread is specified
    if( num_threads == 1 )
    {
        for( unsigned int i = 2; i*i <= PCalc_T::array_size(); i++ )
        {
        if( PCalc_T::at(i) )
            {
            for( unsigned int j = i*i; j <= PCalc_T::array_size(); j += i )
                PCalc_T::at( j ) = false; //Non-prime numbers
            }
        }
    }
    //Multi-threaded (2 or more)
    else
    {
        //Takes a baseline prime number and eliminates all of its multiples
        auto clrPrime = [&]( unsigned int base )
        {
            for( int i = 3; i*base <= array_size(); i++ )
                PCalc_T::at( i*base ) = false;
        };
        
        //Use mutex locks to increment to the next base prime number and eliminate its multiples
        auto worker = [&]( unsigned int worker_id )
        {
            unsigned int limit = sqrt( array_size() );
            unsigned int base = nextbase;
            while( true )
            {
                mutex.lock();
                base = nextbase;
                nextbase += 2;
                mutex.unlock();
                if( base <= limit )
                {
                    if( PCalc_T::at( base ) )
                        clrPrime( base );
                }
                else
                    return worker_id; //verifies thread that finishes
            }
        };

        //Get rid of all even numbers past 2, they are all non-prime (multiple of 2)
        for( unsigned int i = 3; i <= array_size(); i++ )  
        {
            if ( i % 2 == 0 ) 
                PCalc_T::at( i ) = false;
        }

        //Use multi-threading to accomplish the rest of the bases 3, 5, 7, ...
        std::vector<std::thread> threads;
        for( unsigned int i = 0; i < num_threads; i++ )
            threads.emplace_back( worker, i );

        //Return value from threads verifies the worker_id
        for( auto &thread : threads )
            thread.join();
    }
}
