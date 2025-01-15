#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

#include "LargeInt.h"

using namespace std;
const int power = 9;              
const long base = pow(10, power); 

//* CONSTRUCTORS *//

// Constructor that creates a new LargeInt in the zero state:
// signum=0, digits=().
LargeInt::LargeInt() : signum(0)
{
}

// Constructor that creates a new LargeInt from the long value x.
LargeInt::LargeInt(long x)
{
    if (x == 0)
    {
        signum = 0;
    }
    else
    {
        signum = (x > 0) ? 1 : -1; 
        x = std::abs(x);
        digits.moveFront();
        while (x > 0)
        {
            int digit = x % 10;
            digits.insertAfter(digit); 
            x /= 10;                   
        }
    }
}

// Constructor that creates a new LargeInt from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
LargeInt::LargeInt(std::string s)
{
    if (s.empty())
    {
        // handle the case of an empty string here
    }

    // check if the string contains non-numeric characters
    for (char c : s)
    {
        if (!isdigit(c) && c != '-')
        {
            // handle the case of non-numeric characters here
        }
    }

    signum = 1;
    // ignore leading '+' sign and set startPos accordingly
    size_t startPos = 0;
    if (s[0] == '-')
    {
        signum = -1;
        startPos = 1;
    }
    else if (s[0] == '+')
    {
        startPos = 1;
    }

    // find the position of the first non-zero digit
    size_t nonZeroPos = s.find_first_not_of('0', startPos);

    // extract the substring starting from the non-zero digit
    std::string numStr = (nonZeroPos == std::string::npos) ? "0" : s.substr(nonZeroPos);

    for (char digit : numStr)
    {
        digits.insertBefore(digit - '0'); 
    }
}

// Constructor that creates a copy of N.
LargeInt::LargeInt(const LargeInt &N) : signum(N.signum), digits(N.digits)
{
}


//* ACCESS FUNCTIONS *//

// Returns -1, 1 or 0 according to whether this LargeInt is positive,
// negative or 0, respectively.
int LargeInt::sign() const
{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this LargeInt is less than N,
// greater than N or equal to N, respectively.
int LargeInt::compare(const LargeInt &N) const
{
    List thisDigitsCopy = this->digits;
    List nDigitsCopy = N.digits;

    // compare signums first
    if (this->signum != N.signum)
    {
        return (this->signum > N.signum) ? 1 : -1;
    }

    // compare lengths next
    int thisLength = thisDigitsCopy.length();
    int nLength = nDigitsCopy.length();
    if (thisLength != nLength)
    {
        return (thisLength > nLength) ? 1 : -1;
    }

    // if lengths are equal, compare digits from left to right
    thisDigitsCopy.moveFront();
    nDigitsCopy.moveFront();
    for (int i = 0; i < thisLength; ++i)
    {
        int thisDigit = thisDigitsCopy.peekNext();
        int nDigit = nDigitsCopy.peekNext();
        if (thisDigit != nDigit)
        {
            return (thisDigit > nDigit) ? 1 : -1;
        }
        thisDigitsCopy.moveNext();
        nDigitsCopy.moveNext();
    }

    return 0; // the numbers are equal
}

// makeZero()
// Resets this LargeInt to the zero state.
void LargeInt::makeZero()
{
    signum = 0;
    digits.clear();
}

// negate()
// If this LargeInt is zero, does nothing, otherwise reverses the sign of
// this LargeInt positive <--> negative.
void LargeInt::negate()
{
    if (signum != 0)
    {
        signum = -signum;
    }
}

// helper function to be used by sub() : negates every element in List L
void negateList(List &L)
{
    L.moveFront(); 
    while (L.position() != L.length())
    {                                    
        int currentValue = L.peekNext(); 
        L.setAfter(-currentValue);       
        L.moveNext();                    
    }
}

// helper function to determine if each element in list is 0 (thus the big int = 0)
bool isListZero(const List &L)
{
    List LCopy = L; 
    LCopy.moveFront();
    while (LCopy.position() < LCopy.length())
    {
        if (LCopy.peekNext() != 0)
        {
            return false;
        }
        LCopy.moveNext();
    }
    return true;
}

// subList definition later 
void subList(List &S, List A, List B);

// helper function that sums the pairs of elements in Lists A and B
// Overwrites the state of S with A + sgn*B (considered as vectors).
void sumList(List &S, List A, List B)
{
    S.clear(); 
    A.moveBack();
    B.moveBack();
    int carry = 0;

    while (A.position() > 0 || B.position() > 0 || carry != 0)
    {
        int aValue = (A.position() > 0) ? A.peekPrev() : 0;
        int bValue = (B.position() > 0) ? B.peekPrev() : 0;

        int sum = aValue + bValue + carry;
        carry = sum / 10;
        sum %= 10;

        S.insertAfter(sum);

        if (A.position() > 0)
            A.movePrev();
        if (B.position() > 0)
            B.movePrev();
    }

    S.moveBack();
}

// helper func that erforms carries from right to left (least to most 
// significant digits), then returns the sign of the resulting integer. 
// Used by add(), sub() and mult().
void normalizeList(List &L)
{
    // check if normalization is needed
    bool needsNormalization = false;
    L.moveFront();
    while (L.position() >= 0 && L.position() < L.length())
    {
        if (L.peekNext() >= 10 || L.peekNext() < 0)
        {
            needsNormalization = true;
            break;
        }
        L.moveNext();
    }

    if (!needsNormalization)
    {
        return; // no need to normalize
    }

    int carry = 0;

    L.moveBack();

    // handle the case where the cursor is at the front
    if (L.position() == 0)
    {
        L.setBefore(0); // insert a leading zero
        L.movePrev();
    }

    while (L.position() > 0)
    {
        int value = L.peekPrev() + carry;

        if (value < 0)
        {
            carry = -1;
            value += 10;
        }
        else
        {
            carry = value / 10;
        }

        int newValue = value % 10;
        L.setBefore(newValue);

        if (carry < 0)
        {
            carry++;
        }

        L.movePrev();
    }

    if (carry != 0)
    {
        L.insertBefore(abs(carry));
    }
}

// helper function to compare the magnitudes of two LargeInts
int compareMagnitudes(const LargeInt &a, const LargeInt &b)
{
    LargeInt negatedA = a;
    LargeInt negatedB = b;

    if (a.sign() < 0)
    {
        negatedA.negate(); // negate a if it's negative
    }
    if (b.sign() < 0)
    {
        negatedB.negate(); // negate b if it's negative
    }

    if (negatedA < negatedB)
    {
        return -1; // a has smaller magnitude than b
    }
    else if (negatedA > negatedB)
    {
        return 1; // a has larger magnitude than b
    }
    else
    {
        return 0; // magnitudes are equal
    }
}

// helper func that pads the digit lists with zeros to ensure equal length
void padDigitLists(List &aDigits, List &nDigits)
{
    // calculate the length difference between the digit lists
    int diff = aDigits.length() - nDigits.length();

    // pad the shorter list with zeros
    if (diff > 0)
    {
        // prepend zeros to nDigits
        for (int i = 0; i < diff; ++i)
        {
            nDigits.moveFront();
            nDigits.insertBefore(0);
        }
    }
    else if (diff < 0)
    {
        // prepend zeros to aDigits
        for (int i = 0; i < -diff; ++i)
        {
            aDigits.moveFront();
            aDigits.insertBefore(0);
        }
    }
}

// helper func to handle addition when 'this' is negative and 'N' is positive
void handleNegativePositive(const LargeInt &aCopy, const LargeInt &nCopy, const List &aDigits, const List &nDigits, List &resultDigits, int &resultSignum)
{
    int comparisonResult = compareMagnitudes(aCopy, nCopy);
    if (comparisonResult < 0)
    {
        // aCopy's magnitude is less than nCopy's
        subList(resultDigits, nDigits, aDigits);
        resultSignum = 1; // so result is pos
    }
    else if (comparisonResult > 0)
    {
        // aCopy's magnitude is greater than nCopy's
        subList(resultDigits, aDigits, nDigits);
        resultSignum = -1; // so result is neg
    }
    else
    {
        // magnitudes are equal
        resultSignum = 0;
    }
}

// helper func to handle addition when 'this' is positive and 'N' is negative
void handlePositiveNegative(const LargeInt &aCopy, const LargeInt &nCopy, const List &aDigits, const List &nDigits, List &resultDigits, int &resultSignum)
{
    int comparisonResult = compareMagnitudes(aCopy, nCopy);
    if (comparisonResult < 0)
    {
        // aCopy's magnitude is less than nCopy's
        subList(resultDigits, nDigits, aDigits);
        resultSignum = -1; // so result is pos
    }
    else if (comparisonResult > 0)
    {
        // aCopy's magnitude is greater than nCopy's
        subList(resultDigits, aDigits, nDigits);
        resultSignum = 1; // so result is neg
    }
    else
    {
        // magnitudes are equal
        resultSignum = 0;
    }
}

// helper func to handle addition when both 'this' and 'N' are negative
void handleBothNegative(const LargeInt &aCopy, const LargeInt &nCopy, const List &aDigits, const List &nDigits, List &resultDigits, int &resultSignum)
{
    // both numbers negative so add normally then make signum neg
    sumList(resultDigits, aDigits, nDigits);
    resultSignum = -1; 
}

// helper func to handle addition when 'this' and 'N' are positive or zero
void handlePositiveOrZero(const LargeInt &aCopy, const LargeInt &nCopy, const List &aDigits, const List &nDigits, List &resultDigits, int &resultSignum)
{
    // N is positive or zero, perform addition normally
    sumList(resultDigits, aDigits, nDigits); 

    // normalize the result list to remove any leading zeros
    normalizeList(resultDigits);

    // check if the result is zero
    if (isListZero(resultDigits))
    {
        resultSignum = 0; 
    }
    else
    {
        resultSignum = 1; 
    }
}

// Returns a LargeInt representing the sum of this and N.
LargeInt LargeInt::add(const LargeInt &N) const
{
    LargeInt aCopy = *this; 
    LargeInt nCopy = N;    

    padDigitLists(aCopy.digits, nCopy.digits);

    LargeInt result;
    int resultSignum;  
    List resultDigits; 

    // Perform addition based on the signs of the numbers
    if (aCopy.signum < 0 && nCopy.signum >= 0)
    {
        // this is negative, N is positive
        handleNegativePositive(aCopy, nCopy, aCopy.digits, nCopy.digits, resultDigits, resultSignum);
    }
    else if (nCopy.signum < 0 && aCopy.signum >= 0)
    {
        // this is positive, N is negative
        handlePositiveNegative(aCopy, nCopy, aCopy.digits, nCopy.digits, resultDigits, resultSignum);
    }
    else if (nCopy.signum < 0 && aCopy.signum < 0)
    {
        // both are negative
        handleBothNegative(aCopy, nCopy, aCopy.digits, nCopy.digits, resultDigits, resultSignum);
    }
    else
    {
        // N is positive or zero, perform addition normally
        handlePositiveOrZero(aCopy, nCopy, aCopy.digits, nCopy.digits, resultDigits, resultSignum);
    }

    // Check the sign of the result and construct the resulting LargeInt
    result.digits = resultDigits;
    result.signum = resultSignum;
    return result;
}

// helper func like sumList but used for subtraction
void subList(List &S, List A, List B)
{
    S.clear();
    A.moveBack();
    B.moveBack();
    int borrow = 0;

    while (A.position() > 0 || B.position() > 0)
    {
        int aValue = (A.position() > 0) ? A.peekPrev() : 0;
        int bValue = (B.position() > 0) ? B.peekPrev() : 0;
        int diff = aValue - bValue - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        S.insertAfter(diff); 

        if (A.position() > 0)
            A.movePrev();
        if (B.position() > 0)
            B.movePrev();
    }

    // make sure leading zeros are not included in the final result
    S.moveFront();
    while (S.front() == 0 && S.length() > 1)
    {
        S.eraseAfter();
    }
    S.moveBack();
}

// Returns a LargeInt representing the difference of this and N.
LargeInt LargeInt::sub(const LargeInt &N) const
{
    LargeInt aCopy = *this; 
    LargeInt nCopy = N;    

    padDigitLists(aCopy.digits, nCopy.digits);

    LargeInt result;
    int resultSignum;
    List resultDigits;

    // Perform subtraction based on the signs of the numbers

    if (aCopy.signum < 0 && nCopy.signum >= 0)
    {    // this is negative, N is positive
        sumList(resultDigits, aCopy.digits, nCopy.digits); // all you gotta do is add normally then put a neg sign on it
        resultSignum = -1;
    }
    else if (nCopy.signum < 0 && aCopy.signum >= 0)
    {    // this is positive, N is negative
        sumList(resultDigits, aCopy.digits, nCopy.digits); // all you gotta do is add normally and make positive
        resultSignum = 1;
    }
    else if (nCopy.signum < 0 && aCopy.signum < 0)
    {   // both are negative

        int comparisonResult = compareMagnitudes(aCopy, nCopy);
        // compare magnitudes to figure out which order to call subList + to determine sign

        if (comparisonResult < 0)
        {   // aCopy's magnitude is less than nCopy's
            subList(resultDigits, nCopy.digits, aCopy.digits); 
            resultSignum = 1; // swap a with n and make positive                                
        }
        else if (comparisonResult > 0)
        {   // aCopy's magnitude is greater than nCopy's
            subList(resultDigits, aCopy.digits, nCopy.digits); 
            resultSignum = -1;  // subtract normally and keep negative sign                               
        }
        else
        {   // magnitudes are equal
            resultSignum = 0;
        }
        normalizeList(resultDigits);
    }
    else
    {    // both are positive or zero

        // compare magnitudes to figure out which order to call subList + to determine sign
        int comparisonResult = compareMagnitudes(aCopy, nCopy);

        if (comparisonResult < 0)
        {
            // aCopy's magnitude is less than nCopy's
            subList(resultDigits, nCopy.digits, aCopy.digits);
            resultSignum = -1; // swap a with n and add negative sign
        }
        else if (comparisonResult > 0)
        {   // aCopy's magnitude is greater than nCopy's
            subList(resultDigits, aCopy.digits, nCopy.digits);
            resultSignum = 1; // subtract normally
        }
        else
        {   // magnitudes are equal
            resultSignum = 0;
        }
        normalizeList(resultDigits);
    }

    bool resultIsZero = isListZero(resultDigits);
    if (resultIsZero)
    {
        resultSignum = 0;
    }

    result.digits = resultDigits;
    result.signum = resultSignum;
    return result;
}

// helper function to append p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List &L, int shiftAmount)
{
    L.moveBack();
    for (int i = 0; i < shiftAmount; ++i)
    {
        L.insertAfter(0); 
    }
}

// helper func that multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List &L, int m)
{
    L.moveBack(); 
    long long carry = 0; 

    while (L.position() >= 1)
    {
        long digit = L.peekPrev();                                     
        long long product = static_cast<long long>(digit) * m + carry;
        carry = product / base;
        int newDigit = product % base;
        L.setBefore(newDigit); 
        L.movePrev();         
    }

    while (carry > 0)
    {
        L.moveFront();
        L.insertBefore(carry % base); 
        carry /= base;               
    }
}

// Returns a LargeInt representing the product of this and N. 
LargeInt LargeInt::mult(const LargeInt &N) const
{

    if (isListZero(this->digits) || isListZero(N.digits))
    {
        LargeInt zero("0");
        zero.signum = 0;
        return zero; // early return if either number is zero
    }

    LargeInt result;
    int originalSignum = this->signum * N.signum; 
    result.signum = 1;                            

    List nDigitsCopy = N.digits; 
    int shiftAmount = 0;

    nDigitsCopy.moveBack();
    while (nDigitsCopy.position() >= 1)
    {
        int nDigit = nDigitsCopy.peekPrev();
        List thisDigitsCopy = this->digits; 

        scalarMultList(thisDigitsCopy, nDigit); 
        normalizeList(thisDigitsCopy);          
        shiftList(thisDigitsCopy, shiftAmount); 
      
        LargeInt partialResult;
        partialResult.digits = thisDigitsCopy; 
        partialResult.signum = result.signum;

        result = result.add(partialResult); 
        normalizeList(result.digits);     

        nDigitsCopy.movePrev(); 
        shiftAmount++;        
    }

    result.signum = originalSignum;
    return result;
}


//* OTHER FUNCTIONS *//

// Returns a string representation of this LargeInt consisting of its
// base 10 digits. If this LargeInt is negative, the returned string
// will begin with a negative sign '-'. If this LargeInt is zero, the
// returned string will consist of the character '0' only.
std::string LargeInt::to_string()
{
    std::string result;
    if (signum == -1)
        result += "-";
    else if (signum == 0)
        return "0"; 

    digits.moveFront(); 
    while (digits.position() < digits.length())
    {
        int digit = digits.peekNext();
        result += std::to_string(digit);
        digits.moveNext();
    }
    return result;
}


//* OVERRIDEN OPERATORS *//

// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, LargeInt N)
{
    return stream << N.to_string();
}

// Returns true if and only if A equals B.
bool operator==(const LargeInt &A, const LargeInt &B)
{
    return A.sign() == B.sign() && A.digits == B.digits;
}

// Returns true if and only if A is less than B.
bool operator<(const LargeInt &A, const LargeInt &B)
{
    if (A.sign() != B.sign())
        return A.sign() < B.sign();
    if (A.sign() == 0)
        return false; 
    if (A.sign() == 1)
        return A.compare(B) < 0; 
    return A.compare(B) > 0;     
}

// Returns true if and only if A is less than or equal to B.
bool operator<=(const LargeInt &A, const LargeInt &B)
{
    return A == B || A < B;
}

// Returns true if and only if A is greater than B.
bool operator>(const LargeInt &A, const LargeInt &B)
{
    return !(A <= B);
}

// Returns true if and only if A is greater than or equal to B.
bool operator>=(const LargeInt &A, const LargeInt &B)
{
    return A > B || A == B;
}

// Returns the sum A+B.
LargeInt operator+(const LargeInt &A, const LargeInt &B)
{
    return A.add(B);
}

// Overwrites A with the sum A+B.
LargeInt operator+=(LargeInt &A, const LargeInt &B)
{
    A = A.add(B);
    return A;
}

// Returns the difference A-B.
LargeInt operator-(const LargeInt &A, const LargeInt &B)
{
    return A.sub(B);
}

// Overwrites A with the difference A-B.
LargeInt operator-=(LargeInt &A, const LargeInt &B)
{
    A = A.sub(B);
    return A;
}

// Returns the product A*B.
LargeInt operator*(const LargeInt &A, const LargeInt &B)
{
    return A.mult(B);
}

// Overwrites A with the product A*B.
LargeInt operator*=(LargeInt &A, const LargeInt &B)
{
    A = A.mult(B);
    return A;
}

