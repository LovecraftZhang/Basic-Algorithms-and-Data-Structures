#include "Hashtable.h"
#include <cstdlib>
#include <iostream>
#include <cassert> 

using namespace std; 

Hashtable::Hashtable(int size) {
    //constructor
    int prime = nextPrime( size ); 
    _size = size;
    if (prime != size) { 
      cout << "Warning: size = " << size << " is not a prime number." << endl; 
/* uncomment these if you want */ 
//    cout << "Using " << prime << " instead." << endl; 
//    _size = prime; 
    }
    _totalProbes = 0;
    _numInserts = 0;
    _numFailures = 0; 
    _table = new int [ _size ];
    for (int ii=0; ii < _size; ii++) {
        _table[ ii ] = EMPTY;
    }
}
void Hashtable::clear(void) {
    _totalProbes = 0;
    _numInserts = 0;
    _numFailures = 0; 
    for (int ii=0; ii < _size; ii++) {
        _table[ ii ] = EMPTY;
    }
}    
    

Hashtable::~Hashtable() {
    //deconstructor
    delete[] _table;
}

void Hashtable::tallyProbes(int p) {
    // Add the number of probes, p, for one insert operation to the tally.
    _totalProbes += p;
    _numInserts += 1;
}

void Hashtable::printStats() {
    float l =_totalProbes / _size;
    cout << "Average probes/insert = " <<
            probeRate() << " = " <<
            _totalProbes << "/" << _numInserts;
    cout << " Load factor = " << l;
    cout <<", size = "<< _size;
    cout <<", failures = " << _numFailures << endl;
}

float Hashtable::probeRate() {
    return (float)_totalProbes / (float)_numInserts;
}

int Hashtable::hash(int k) {
    return k % _size;
}

void Hashtable::qinsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with quadratic probing and hash(k) = k % _size.

    // Tips:
    // - Look at the lecture slides if you don't remember how to implement these.
    // - You need to prevent against infinite loops. You should limit the number
    // of times you probe and print an error message upon exceeding this limit.
    // - You're welcome to add new declarations to hash.h, add to the constructor,
    // include libraries, or anything else you need. 
    // - You're also welcome to modify the main() method to automate your testing.

    // ************* ADD YOUR CODE HERE *******************
    int index = 0;
    int p = 0;
    do {
        index = (hash(k) + p^2) % _size;
        if (_table[index] == EMPTY) {
            _table[index] = k;
            tallyProbes(p + 1);
            return;
        }
        p++;
    } while (_table[index] != EMPTY && p != _size && p < (_size / 2));

    _numFailures += 1;
    cout << "Warning: qinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;

    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 

}

void Hashtable::linsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with linear probing and hash(k) = k % _size.

    // ************* ADD YOUR CODE HERE *******************
    int index = 0;
    int p = 0;
    do {
        index = (hash(k) + p) % _size;
        if (_table[index] == EMPTY) {
            _table[index] = k;
            tallyProbes(p + 1);
            return;
        }
        p++;
    } while (_table[index] != EMPTY && p <= _size);

    _numFailures += 1;
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;

    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot
}

void Hashtable::dinsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with double hashing. Use the existing hash function
    // and also implement a second hash function.

    // ************* ADD YOUR CODE HERE *******************
    int index = 0, hash2 = 7 - (k % 7);
    int p = 0;
    do {
            index = (hash(k)+ p * hash2) % _size;
            if (_table[index] == EMPTY) {
                _table[index] = k;
                tallyProbes(p + 1);
                return;
            }
            p++;
        } while (_table[index] != EMPTY && p != _size);

    _numFailures += 1;
    cout << "Warning: dinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;

    
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot
}

void Hashtable::print() {
    // Print the content of the hash table.

    for (int i=0; i<_size; i++) {
        cout<<"["<<i<<"] ";
        if (_table[i] != EMPTY)
            cout << _table[i];
        cout << endl;
    }
}

bool Hashtable::checkValue(int k, int i) {
    // Check if value k is at index i. Use this to help you with testing.

    return (_table[i] == k);
}

int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if (n == 2) return true;
    if (n % 2 == 0) return false;  
    return isPrime( n, 3 ); 
}
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    return isPrime( n, divisor + 2 ); 
}

