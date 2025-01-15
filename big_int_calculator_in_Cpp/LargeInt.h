#include<iostream>
#include<string>
#include"List.h"


#ifndef LARGE_INTEGER_H_INCLUDE_
#define LARGE_INTEGER_H_INCLUDE_

// Exported type  -------------------------------------------------------------
class LargeInt{

private:

   // LargeInt Fields 
   int signum;    // +1 (positive), -1 (negative), 0 (zero)
   List digits;   // List of digits in this LargeInt

public:

   // Class Constructors & Destructors ----------------------------------------

   // LargeInt()
   // Constructor that creates a new LargeInt in the zero state: 
   // signum=0, digits=().
   LargeInt();

   // LargeInt()
   // Constructor that creates a new LargeInt from the long value x.
   LargeInt(long x);

   // LargeInt()
   // Constructor that creates a new LargeInt from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
   LargeInt(std::string s);

   // LargeInt()
   // Constructor that creates a copy of N.
   LargeInt(const LargeInt& N);

   // Optional Destuctor
   // ~LargeInt()
   // ~LargeInt();


   // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this LargeInt is positive, 
   // negative or 0, respectively.
   int sign() const;

   // compare()
   // Returns -1, 1 or 0 according to whether this LargeInt is less than N,
   // greater than N or equal to N, respectively.
   int compare(const LargeInt& N) const;


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this LargeInt to the zero state.
   void makeZero();

   // negate()
   // If this LargeInt is zero, does nothing, otherwise reverses the sign of 
   // this LargeInt positive <--> negative. 
   void negate();


   // LargeInt operations operations ----------------------------------------

   // add()
   // Returns a LargeInt representing the sum of this and N.
   LargeInt add(const LargeInt& N) const;

   // sub()
   // Returns a LargeInt representing the difference of this and N.
   LargeInt sub(const LargeInt& N) const;

   // mult()
   // Returns a LargeInt representing the product of this and N. 
   LargeInt mult(const LargeInt& N) const;


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this LargeInt consisting of its
   // base 10 digits. If this LargeInt is negative, the returned string 
   // will begin with a negative sign '-'. If this LargeInt is zero, the
   // returned string will consist of the character '0' only.
   std::string to_string();


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
   friend std::ostream& operator<<( std::ostream& stream, LargeInt N );

   // operator==()
   // Returns true if and only if A equals B. 
   friend bool operator==( const LargeInt& A, const LargeInt& B );

   // operator<()
   // Returns true if and only if A is less than B. 
   friend bool operator<( const LargeInt& A, const LargeInt& B );

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
   friend bool operator<=( const LargeInt& A, const LargeInt& B );

   // operator>()
   // Returns true if and only if A is greater than B. 
   friend bool operator>( const LargeInt& A, const LargeInt& B );

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
   friend bool operator>=( const LargeInt& A, const LargeInt& B );

   // operator+()
   // Returns the sum A+B. 
   friend LargeInt operator+( const LargeInt& A, const LargeInt& B );

   // operator+=()
   // Overwrites A with the sum A+B. 
   friend LargeInt operator+=( LargeInt& A, const LargeInt& B );

   // operator-()
   // Returns the difference A-B. 
   friend LargeInt operator-( const LargeInt& A, const LargeInt& B );

   // operator-=()
   // Overwrites A with the difference A-B. 
   friend LargeInt operator-=( LargeInt& A, const LargeInt& B );

   // operator*()
   // Returns the product A*B. 
   friend LargeInt operator*( const LargeInt& A, const LargeInt& B );

   // operator*=()
   // Overwrites A with the product A*B. 
   friend LargeInt operator*=( LargeInt& A, const LargeInt& B );


};


#endif