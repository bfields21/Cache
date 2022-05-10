#include <iostream>
#include <string>
#include <assert.h>
#include "Line.h"
#include "Set.h"

// TO DO: lots of work to do in this file.
//        Look for TODO throughout the file

/*
 * initialize
 * Initialize the Set object.
 * A Set is a linked list of Line objects.  Up to associativity Line objects can
 * be in the linked list.
 */
void Set::initialize(int32_t index, int32_t associativity, bool verbose)
{
   this->index = index;                 // index of this set
   this->associativity = associativity; // way
   this->verbose = verbose;             // can be used to turn debugging prints on or off
   this->firstLine = NULL;              // pointer to the first Line object in the Set
}

/*
 * isHit
 * Looks in the Set for the tag. Returns true if found and false otherwise.
 */
bool Set::isHit(int64_t tag)
{
   // TODO
   Line *ptr = firstLine;

   // If set is empty return false
   if (firstLine == NULL)
   {
      return false;
   }
   // If the set is not empty loop through checking for tag match.
   else
   {
      while (ptr != NULL)
      {
         if (ptr->tag == tag)
         {
            return true;
         }
         else 
         {
            ptr = ptr->next;
         }
      }
      return false;
   }
}

/*
 * isFull
 * Returns true if the Set is full. The Set is full if the linked listed contains
 * associativity (way) Line objects. This is used to determine whether an eviction
 * is necessary.
 */
bool Set::isFull()
{

   // TODO
   //  Count starts at 1 because if .next == NULL then count won't be incremented.
   int count = 0;
   Line *ptr = firstLine;
   // Loop through the linked list, counting the number of objects
   if (firstLine == NULL)
   {
      return false;
   }
   while (ptr != NULL)
   {
         count++;
         
         if (count == associativity)
         {
            return true;
         }
         ptr = ptr->next;
   }
   return false;
   
}

/*
 * updateSet
 * Updates the Set with the provided tag.
 * The Line objects in the linked list encapsulated by the Set object need to be kept in
 * in the Set in LRU order so that the MRU Line object is in the front
 * of the linked list.
 *
 * Suppose tag is T and associativity is 4.
 * If the tags of the nodes in the linked list are: A B C D
 * then after the update, the tags are: T A B C
 * Notice that D (the LRU) got evicted.
 *
 * If the tags of the nodes in the linked list are: A B T D
 * then after the update, the tags are: T A B D
 * Notice that T was moved from where it was to the front of the linked list.
 *
 * If the tags of the nodes in the linked list are: A B
 * (only two nodes)
 * then after the update, the tags are: T A B
 * Notice nothing was evicted because the Set isn't full.
 *
 */
void Set::updateSet(int64_t tag)
{
   // TODO
   // Note: this work is completed by calling other methods in this
   //       class.
   //
   // If the tag is already in the set then remove the Line containing
   // the tag.
   //
   // Or, if the set is full then remove the LRU Line.
   //
   // After that, insert a new Line with this tag in the front of the
   // linked list.
   // ()

   // If empty
   if (firstLine == NULL)
   {
      insertInFront(tag);
   }
   // Non-empty set
   else
   {
      if (isHit(tag))
      {
         removeLine(tag);
      }
      else if (isFull())
      {
         removeLine(getLRUTag());
      }
      insertInFront(tag);
   }
}

/*
 * insertInFront
 * Create a new Line object and insert it in the front of the linked list.
 * This method is called by updateSet.
 */
void Set::insertInFront(int64_t tag)
{
   // TODO
   Line *ptr = firstLine;
   Line *newLine = new Line(tag);

   // If set is NOT empty
   if (ptr != NULL)
   {
      newLine->next = ptr;
      firstLine = newLine;
   }
   // If Set is empty set firstLine to newLine
   else
   {
      firstLine = newLine;
   }

}

/*
 * removeLine
 * Remove the Line object from the linked list with the specified tag.
 * This will update firstLine if the Line object is the first one in the
 * linked list; otherwise, it updates the next field of the previous
 * Line in the linked list.
 * This method is called by updateSet.
 */
void Set::removeLine(int64_t tag)
{
   // TODO
   Line *currPtr = firstLine;
   Line *prePtr = firstLine;

   // If firstline tag is a match
   if(firstLine->tag == tag)
   {
      currPtr = firstLine->next;
      delete firstLine;
      firstLine =currPtr;
      return;
   }

   // If tag doesn't match on the first line
   currPtr = currPtr->next;
   while(currPtr != NULL)
   {
      if(currPtr->tag == tag)
      {
         prePtr->next = currPtr->next;
         delete currPtr;
         break;
      }
      prePtr = currPtr;
      currPtr = currPtr->next;
   }

   
}

/*
 * getLRUTag
 * Returns the tag of the LRU Line in the set. This is the tag of the
 * last Line object in the linked list.
 * This method is called by updateSet.
 */
 int64_t Set::getLRUTag()
{
   // TODO
   Line *ptr = firstLine;

   while (ptr->next != NULL)
   {
      ptr = ptr->next;
   }

   return ptr->tag;

}

/*
 * Destructor for the dynamically allocated data.
 */
Set::~Set()
{
   // TODO
   Line * ptr = firstLine;

   while(ptr != NULL){
      Line * next = ptr->next;
      ptr = NULL;
      ptr = next;
   }
}

/*
 * print
 * Prints the tags in the Set if the set is non-empty. If the Set is empty
 * nothing is printed. This can be used for debugging.
 */
void Set::print()
{

   if (firstLine)
   {
      std::cout << "Set: " << index << " Tags: ";
      Line *ptr = firstLine; // initialize to point to first node in the linked list
      while (ptr != NULL)
      {
         std::cout << std::hex << ptr->tag << " ";
         ptr = ptr->next;
      }
      std::cout << "\n";
   }
}
