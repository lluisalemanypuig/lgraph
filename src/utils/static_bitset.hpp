#pragma once

/// C includes
#include <stdlib.h>
#include <string.h>

/// C++ includes
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

// The order of bits of a byte is the following
// order: 7654 3210
// byte:  0110 1001

/*
Useful boolean operations used to implement methods
of this class:

* Difference of bitsets:
	a b | d(a, b) = a & (-b)
	-------------
	0 0 | 0
	0 1 | 0
	1 0 | 1
	1 1 | 0

* Inclusion of bitsets:
	a b | lt(a, b) = -a | b = -d(a, b)
	--------------
	0 0 | 1
	0 1 | 1
	1 0 | 0
	1 1 | 1
*/

class static_bitset {
	private:
		size_t n_bytes, n_bits;
		unsigned char *bytes;

	public:
		static_bitset();
		static_bitset(const string& bs);
		static_bitset(const vector<bool>& bits);
		static_bitset(const static_bitset& bs);
		~static_bitset();

		/// INITIALIZERS

		void init(size_t n_bits);
		void init_set(size_t n_bits);
		void init_unset(size_t n_bits);
		void init(const string& bits);
		void init(const vector<bool>& bits);

		void clear();

		/// OPERATORS

		// Assigns 'bs' to this bitset
		static_bitset& operator= (const static_bitset& bs);

		// Returns the value of the i-th bit
		bool operator[] (size_t i) const;

		static_bitset operator<= (const static_bitset& bs) const;	// bit-wise lt
		static_bitset operator~ () const;							// bit-wise negation
		static_bitset operator- (const static_bitset& bs) const;	// bit-wise d
		static_bitset operator& (const static_bitset& bs) const;	// bit-wise and
		static_bitset operator| (const static_bitset& bs) const;	// bit-wise or
		static_bitset operator^ (const static_bitset& bs) const;	// bit-wise exclusive or
		static_bitset operator== (const static_bitset& bs) const;	// bit-wise exclusive nor

		static_bitset& operator-= (const static_bitset& bs);	// bit-wise d
		static_bitset& operator&= (const static_bitset& bs);	// bit-wise and
		static_bitset& operator|= (const static_bitset& bs);	// bit-wise or
		static_bitset& operator^= (const static_bitset& bs);	// bit-wise exclusive or

		inline friend
		ostream& operator<< (ostream& os, const static_bitset& bitset) {
			for (size_t i = 0; i < bitset.n_bits; ++i) os << bitset[i];
			return os;
		}

		/// SETTERS

		void set_all();
		void unset_all();

		void set_bit(size_t i);
		void unset_bit(size_t i);

		// All 0 bits are set to 1, and all 1 bits are set to 0.
		void flip();

		// Stores 'bs' into this bitset, and this bitset into 'bs'
		void swap(static_bitset& bs);

		/// GETTERS

		// Returns the number of bits.
		size_t size() const;

		// Returns true if all bits in this bitset are the same as the bits in bs
		// Equivalent to (*this == bs).all() but faster
		bool equal(const static_bitset& bs) const;

		// Returns true if all set bits in this bitset are also set in 'bs'
		// Equivalent to (*this <= bs).all() but faster
		bool included(const static_bitset& bs) const;

		// Returns true if all bits in this bitset are 1.
		bool all() const;

		// Returns true if at least one bit in this bitset is 1.
		bool any() const;

		// Returns true if no bit is 1.
		bool none() const;

		// Returns the indexes of the bits set to 1
		void which(vector<size_t>& w) const;

		// Returns the number of bits set to 1.
		size_t count() const;

		// Returns this bitset as a string
		string to_string(const string& sep = " ") const;
};

