#ifndef DBIGUINT_H
#define DBIGUINT_H
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;


//Changes made to file for git minilab testing branch1

//Change on branch to get merge error

//change 2 ob branch

//Change made on Github
class dbiguint
{
public:
    // pre: none
    // post: creates a dynamic bigint value 0
    dbiguint();
    // pre: s[0], ..., s[s.size()-1] are digits
    // post: creates a dbiguint whose digits are given in s
    dbiguint(const string & s);
/*We aren't implementing this constructor yet
    // pre:  none    //NEW
    // post: copy constructor: creates a new dynamic bigint which is
    //                         a copy of given dynamic bigint
    dbiguint(const dbiguint & b);
*/
    // pre: none    //NEW
    // post: returns dynamically allocated memory to heap
    ~dbiguint();
    // pre: none    //NEW
    // post: makes this dynamic bigint a copy of given dynamic bigint
    void operator =(const dbiguint & b);
    // pre: none    //NEW
    // post: returns the size of the memory block of this dbiguint
    int size() const;
    // pre: none
    // post: returns the digit at given pos (0 if does not exist)
    //       pos 0 is the least significant (units) digit
    unsigned short operator [](int pos) const;
    // pre: none
    // post: returns 0 if this dbiguint equals given dbiguint
    //               1 if this dbiguint >      given dbiguint
    //              -1 otherwise
    int compare(const dbiguint & b) const;
    // pre: none
    // post: returns a string containing the digits and sign of this dbiguint
    string toStdString() const;
    // pre: none
    // post: adds/subtracts given dbiguint to this dbiguint
    void operator +=(const dbiguint & b);
    void operator -=(const dbiguint & b);
    void operator *=(const dbiguint & b);
    // pre: none
    // post: if newcapacity_ <= capacity_ then do nothing (cannot shrink)
    //       else allocate a new block with size newcapacity_
    //       copy existing digits and fill the rest with 0
    void reserve(int newcapacity);
    void clean();
private:
    unsigned short *data_;
    int capacity_;
    // INVARIANTS:
    //    data_ points to (has the address of) a dynamic array
    //    of capacity_ digits
    //    data_[0] = least significant (units) digits
    //    data_[k] = digit at position k (or 0 if not used)
};
// nonmember functions
dbiguint operator +(const dbiguint & a, const dbiguint & b);
dbiguint operator -(const dbiguint & a, const dbiguint & b);
dbiguint operator *(const dbiguint & a, const dbiguint & b);
bool operator < (const dbiguint & a, const dbiguint & b);
bool operator <= (const dbiguint & a, const dbiguint & b);
bool operator == (const dbiguint & a, const dbiguint & b);
bool operator != (const dbiguint & a, const dbiguint & b);
bool operator >= (const dbiguint & a, const dbiguint & b);
bool operator > (const dbiguint & a, const dbiguint & b);
ostream & operator << (ostream & out, const dbiguint & b);
istream & operator >> (istream & out, dbiguint & b);
#endif // DBIGUINT_H
