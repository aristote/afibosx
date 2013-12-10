///////////////////////////////////////////////////////////////////////////////////////////////////
//  afibosx.cpp
//  Ok kids. This was written in 30 mins for April's fool day. Don't try write code like this.
///////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
//#include <malloc.h> // for _msize on windows
#include <malloc/malloc.h> // for os x

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////
//    size_t *should* be an unsigned int >> max malloc *should* be 4 294 967 295 bytes
//    closest fibo is 4 807 526 976 so max iteration should be at 47
//
static const int        MAX_ITERATIONS = 47;
//
///////////////////////////////////////////////////////////////////////////////////////////////////


size_t         fibonacciArray[MAX_ITERATIONS];     // Array init
const int                  bufferSize = 32;


static bool initFibonacci()            // this is not a perfect fibonacci serie since we are
                                       // skipping the firsts 0 & 1.
{
    size_t     fibOne(0);  // fib1
    size_t     fibTwo(1);  // fib2 init at 1 (sneak trick to start the serie)
    size_t     Sum(1);     // Sum
    for (int i = 0; i <= MAX_ITERATIONS; i++)
    {
        fibonacciArray[i] = Sum ;                 //
        Sum = fibOne + fibTwo;                    //
        fibOne = fibTwo;                          // We swap the values
        fibTwo = Sum;                             //
    } //for
    return 0;
} //initFibonacci




size_t returnFibChunkLenght(size_t memoryLenght)
{
    size_t possibleChunk = 0;
    for (int i = 0; i <= MAX_ITERATIONS-1; i++)
    {
        if (fibonacciArray[i] >= memoryLenght)
        {
            possibleChunk = fibonacciArray[i];
            break;
        } //if
    } //for
    return possibleChunk;
}//returnFibChunkLenght




size_t randLong(bool useLong=1)   // size_t is a unsigned int but rand() is short int (0x7FFF)
{
    if (useLong)
    {
        return (rand() % 0x7fff) * (rand() % 0x7fff); // close enough.. Better than 9 9 9 9 anyways..
    }
    else
    {
        return ((rand() % 0x7fff)*2); // fallback to int
    }
    
    
} //randLong


int main()
{
    size_t memoryChunk;  // random generated memory size for allocation
    size_t fibChunk;     // fibonacci returned value for the memoryChunk
    size_t actualChunk;  // returned value of memory allocation via malloc_usable_size
    char * buffer;                  //
    initFibonacci();                // fibonacci array initialisation
    srand(time(0));                 // srand init
    
    
    cout << "/////////////////////////////////////////////////////" << endl;
    cout << " Test suite of malloc through the fibonacci sequence " << endl;
    cout << "/////////////////////////////////////////////////////" << endl;
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    
    
    for(int counter = 0; counter <= 5; counter++)
    {
        memoryChunk = randLong(0) ; // Damn you RAND_MAX at 0x7FFF
        
        
        fibChunk = returnFibChunkLenght(memoryChunk);
        buffer = (char*) malloc (fibChunk);
        
        
        if (buffer == NULL)
        {
            cout << endl << "Malloc error :(" << endl;
            break;
        }
        else
        {
            memset (buffer, 'A', fibChunk);
            //actualChunk = _msize( buffer ); // Windows
            //actualChunk = malloc_usable_size(buffer); // Linux
            actualChunk = malloc_size(buffer); // Os X
            free (buffer);
            
            
            cout << "Chunk " << counter << " is: " << memoryChunk << " bytes." << endl;
            cout << "FiboChunk:  " << fibChunk << " bytes " << "(verified via malloc_usable_size is " << actualChunk << " bytes)."<< endl;
            signed long int diff(fibChunk-memoryChunk);
            cout << "Difference: " << diff << " bytes." <<endl;
        }//else if
        cout << "-----------------------------------------------" << endl;
    }//for
    //system("pause");
    return 0;
} //main
