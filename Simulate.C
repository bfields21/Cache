#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "Line.h"
#include "Set.h"
#include "Cache.h"
#include "Simulate.h"

//TO DO: implement run and accessCache functions
//Look for TODO 

/* Simulator constructor
 * Dynamically create a Cache object and initialize the Simulator object.
 */

Simulate::Simulate(int32_t associativity, int32_t blockOffsetBits, 
                   int32_t setIndexBits, bool verbose)
{
   hits = misses = evictions = 0;
   cacheP = new Cache(associativity, blockOffsetBits, setIndexBits, verbose);
   this->verbose = verbose;
}

/*
 * Destroy the Simulator object.
 */
Simulate::~Simulate()
{
   delete cacheP;
}

/* 
 *  Opens a file and reads it line by line.
 *  Each line is filtered and calls accessCache accordingly.
 *  Verbose prints out input lines with its outcome (hit, miss, and/or evict).
 */
void Simulate::run(std::string filename)
{
   std::fstream fs;
   fs.open(filename, std::fstream::in);
   
   //TODO
   //Loop, reading lines from the file.
   //From each line, get the type and the address.
   //Depending upon the type (L or S), you'll pass it to the
   //accessCache method. (See assignment.)
   //If the verbose flag is true, print out the input line (see csim-ref).

   if(fs.is_open()) 
   {   
      std::string stringLine;
      while(getline(fs, stringLine)) 
      { 
         if(verbose) 
         {
            if (stringLine[0] != 'I')
            {
               std::cout << stringLine; 
            }
         }

         std::string lineString;
         for(int i = 3; stringLine[i] != ','; i++) 
         {
            lineString = lineString + stringLine[i];
         }
         int64_t addressString = std::stol(lineString, nullptr, 16);
         if(stringLine[1] == 'M') 
         {
            accessCache(addressString);
            accessCache(addressString);
            printf("\n");
         }
         else if(stringLine[1] == 'S' || stringLine[1] == 'L') 
         {
            accessCache(addressString);
            printf("\n");
         }
      }
      fs.close(); 
   }
}

/* accessCache
 * Takes as input a 64 bit address.
 * Uses the address to access the cache pointed to by cacheP
 * and updates hits, misses, and evictions.
 */
void Simulate::accessCache(int64_t address)
{
   //TODO
   //cacheP contains a pointer to the cache object
   //Call the appropriate methods in the Cache class
   //to determine whether to increment hits, misses, and/or evictions
   //If verbose is true, output the verbose output (see assignment)

   
  if (cacheP->isHit(address)) 
   {
       printf("is Hit\n");
       hits = hits + 1;
   } 
   else 
   {
       printf("is Miss\n");
       misses = misses + 1;

       if (cacheP->isEvict(address)) 
      {
         printf("is Eviction\n");
         evictions = evictions + 1;
      }
   }

   cacheP->update(address);
}

/*
 * printSummary
 * Print the number of hits, misses, and evictions at the end of
 * the simulation.
 */
void Simulate::printSummary()
{
   std::fstream fs;
   printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
   fs.open(".csim_results", std::fstream::out);
   assert(fs.is_open());
   fs << hits << " " << misses << " " << evictions <<"\n";;
   fs.close();
}

