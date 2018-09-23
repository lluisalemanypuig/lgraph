#pragma once

// C includes
#include <stdlib.h>
#include <string.h>

// C++ includes
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

// The order of bits of a byte is the following
// order: 7654 3210
// byte:  0110 1001

namespace lgraph {
namespace utils {

/**
 * @brief Bitset class.
 *
 * Alternative to the bitset<T> class from the C++'s Standard Library,
 * whose size must be known at compilation time.
 *
 * Basically, allows to store as many bits as indicated in one of the
 * @ref init methods. These bits are stored in a C array of elements
 * of type 'char'. For b bits
 *	* b <= 8, the bitset allocates 1 char,
 *	* 8 < b <= 16, the bitset allocates 2 chars,
 *	* 16 < b <= 24, the bitset allocates 3 chars,
 *	* ...
 *
 * This class implements logical operations between two bitsets, like
 * the bit-wise and, or, xor, difference, equality, negation, ...
 *
 * This class must be first initialised before its use, using one of
 * the @ref init methods.
 *
 * Assuming the bits store are 0110 1001, the
 *	* 0th bit is 0
 *	* 1st bit is 1
 *	* 2nd bit is 1
 *	* 3rd bit is 0
 *	* 4th bit is 1
 *	* 5th bit is 0
 *	* 6th bit is 0
 *	* 7th bit is 1
 *
 * If we interpreted '0110 1001' as a number in binary, then
 * there is a fundamental difference between this way of accessing the
 * bits and the way we would do it in base-2 numbers: the order is
 * reversed:
 *	* 0th bit is 1
 *	* 1st bit is 0
 *	* 2nd bit is 0
 *	* 3rd bit is 1
 *	* 4th bit is 0
 *	* 5th bit is 1
 *	* 6th bit is 1
 *	* 7th bit is 0
 *
 * However, a bitset is not a number in base 2.
 *
 * In the following methods, it will be assumed that:
 *	* ~ represents the unary NOT operator
 *	* |,&,^ represent the logical operations or,and,exclusive-or, respectively
 */
class static_bitset {
	private:
		/// The number of bytes (or of chars) of this bitset.
		size_t n_bytes;
		/// The number of bits this bitset stores.
		size_t n_bits;
		/// The bits of this bitset, grouped by bytes (chars).
		unsigned char *bytes;

	public:
		/// Empty constructor.
		static_bitset();
		/**
		 * @brief Construct a bitset from a string of zeros and ones.
		 * @ref bytes[i] = @e bs[i].
		 */
		static_bitset(const string& bs);
		/**
		 * @brief Construct a bitset from a list of Boolean values.
		 * @ref bytes[i] = @e bits[i].
		 */
		static_bitset(const vector<bool>& bits);
		/// Copy-constructor.
		static_bitset(const static_bitset& bs);
		/// Destructor.
		~static_bitset();

		// INITIALIZERS

		/**
		 * @brief Initialise the bitset with @e n_bits bits.
		 *
		 * Initialises this bitset so that it allocates enough space for @e n_bits bits.
		 *
		 * @param n_bits The number of bits to allocate.
		 */
		void init(size_t n_bits);
		/**
		 * @brief Initialise the bitset with @e n_bits bits all of them set to 1.
		 *
		 * Initialises this bitset so that it allocates enough space for @e n_bits bits
		 * all of them set to 1.
		 *
		 * @param n_bits The number of bits to allocate.
		 */
		void init_set(size_t n_bits);
		/**
		 * @brief Initialise the bitset with @e n_bits bits all of them set to 0.
		 *
		 * Initialises this bitset so that it allocates enough space for @e n_bits bits
		 * all of them set to 0.
		 *
		 * @param n_bits The number of bits to allocate.
		 */
		void init_unset(size_t n_bits);
		/**
		 * @brief Initialise the bitset from a string of zeros and ones.
		 *
		 *		@ref bytes[i] = @e bits[i].
		 */
		void init(const string& bits);
		/**
		 * @brief Initialise the bitset from a list of Boolean values.
		 * @ref bytes[i] = @e bits[i].
		 */
		void init(const vector<bool>& bits);

		/**
		 * @brief Frees the memory occupied by the bitset.
		 *
		 * The values @ref n_bytes and @ref n_bits are set to 0, and
		 * the pointer @ref bytes to null.
		 */
		void clear();

		// OPERATORS

		/**
		 * @brief Asigns the contents of @e bs to this bitset.
		 *
		 * In case this bitset has different size from @e bs's then
		 * its memory is freed and reallocated. In case the sizes are
		 * equal then the contents are overriden with @e bs's.
		 *
		 * @param bs The bitset to be copied.
		 * @return Returns a reference to this bitset.
		 */
		static_bitset& operator= (const static_bitset& bs);

		/// Returns the value of the i-th bit.
		bool operator[] (size_t i) const;

		/**
		 * @brief Inclusion operator.
		 *
		 * Applies an element-wise implication operation.
		 *
		 * @param bs Bitset to be compared again.
		 * @return Returns a bitset s where the i-th bit of s, s[i], is
		 *
		 *		s[i] = ~(this[i]) | bs[i] = this[i] -> bs[i]
		 *
		 *  * 0 <= 0: 1
		 *  * 0 <= 1: 1
		 *  * 1 <= 0: 0
		 *  * 1 <= 1: 1
		 */
		static_bitset operator<= (const static_bitset& bs) const; // bit-wise lt
		/**
		 * @brief Unary not operator.
		 * @return Returns the bits of this bitset flipped (what was a 1
		 * is now a 0, and viceversa).
		 */
		static_bitset operator~ () const; // bit-wise negation
		/**
		 * @brief Bitset difference operator.
		 * @param bs Bitset to be operated with.
		 * @return Returns a bitset s where the i-th bit of s, s[i], is
		 * s[i] = this[i] & ~bs[i]:
		 *
		 *  * 1 - 0 = 1
		 *  * 1 - 1 = 1
		 *  * 0 - . = 0
		 */
		static_bitset operator- (const static_bitset& bs) const; // bit-wise d
		/**
		 * @brief And operator.
		 * @return Returns a bitset s where the i-th bit of s, s[i], is
		 *
		 *		s[i] := this[i] & bs[i]:
		 */
		static_bitset operator& (const static_bitset& bs) const; // bit-wise and
		/**
		 * @brief Or operator.
		 * @return Returns a bitset s where the i-th bit of s, s[i], is
		 *
		 *		s[i] := this[i] | bs[i]:
		 */
		static_bitset operator| (const static_bitset& bs) const; // bit-wise or
		/**
		 * @brief Exclusive-or operator.
		 * @return Returns a bitset s where the i-th bit of s, s[i], is
		 *
		 *		s[i] := this[i] ^ bs[i]:
		 */
		static_bitset operator^ (const static_bitset& bs) const; // bit-wise exclusive or
		/**
		 * @brief Equality operator.
		 * @return Returns a bitset s where the i-th bit of s is set to 1
		 * if, and only if, the i-th bit of this bitset and the i-th of @e bs
		 * are equal.
		 *
		 *		s[i] := ~(this[i]^bs[i]
		 */
		static_bitset operator== (const static_bitset& bs) const; // bit-wise exclusive nor

		/**
		 * @brief Difference operator.
		 *
		 * See @ref operator-(const static_bitset&)const
		 * for details.
		 *
		 * * The operation performed is:
		 \verbatim
		 *this = *this - bs
		 \endverbatim
		 */
		static_bitset& operator-= (const static_bitset& bs); // bit-wise d
		/**
		 * @brief And operator.
		 *
		 * See @ref operator&(const static_bitset&)const
		 * for details.
		 *
		 * * The operation performed is:
		 \verbatim
		 *this = *this & bs
		 \endverbatim
		 */
		static_bitset& operator&= (const static_bitset& bs); // bit-wise and
		/**
		 * @brief Or operator.
		 *
		 * See @ref operator|(const static_bitset&)const
		 * for details.
		 *
		 * The operation performed is:
		 \verbatim
		 *this = *this | bs
		 \endverbatim
		 */
		static_bitset& operator|= (const static_bitset& bs); // bit-wise or
		/**
		 * @brief Exclusive-or operator.
		 *
		 * See @ref operator^(const static_bitset&)const
		 * for details.
		 *
		 * * The operation performed is:
		 \verbatim
		 *this = *this ^ bs
		 \endverbatim
		 */
		static_bitset& operator^= (const static_bitset& bs); // bit-wise exclusive or

		/// Outputs this bitset formatted in a string.
		inline friend
		ostream& operator<< (ostream& os, const static_bitset& bitset) {
			for (size_t i = 0; i < bitset.n_bits; ++i) os << bitset[i];
			return os;
		}

		// SETTERS

		/// Sets all bits to 1.
		void set_all();
		/// Sets all bits to 0.
		void unset_all();

		/// Sets the @e i-th bit to 1.
		void set_bit(size_t i);
		/// Sets the @e i-th bit to 0.
		void unset_bit(size_t i);

		/**
		 * @brief Flips the values of the bits.
		 *
		 * All 0 bits are set to 1, and all 1 bits are set to 0.
		 */
		void flip();

		/**
		 * @brief Swaps the contents of this bitset and @e bs's.
		 * @pre Both bitsets must have been initialised.
		 */
		void swap(static_bitset& bs);

		// GETTERS

		/**
		 * @brief Returns the number of bits.
		 * @return Returns the value of @ref n_bits.
		 */
		size_t size() const;

		/**
		 * @brief Returns whether the two bitsets are equal.
		 *
		 * Equivalent to using the @ref all() method on the result
		 * of the '==' operator (see @ref operator==(const static_bitset&)const)
		 * between @e *this and @e bs.
		 *
		 * @param bs The bitset to be compared against.
		 * @return Returns true if all bits in this bitset are the
		 * same as the bits in @e bs.
		 */
		bool equal(const static_bitset& bs) const;

		/**
		 * @brief Returns true if this bitset is included in @e bs.
		 *
		 * Equivalent to using the @ref all() method on the result
		 * of the '<=' operator (see @ref operator<=(const static_bitset&)const)
		 * between @e *this and @e bs.
		 *
		 * @param bs The bitset to be compared against.
		 * @return Returns true if all set bits in this bitset are also
		 * set in @e bs.
		 */
		bool included(const static_bitset& bs) const;

		/// Returns true if all bits in this bitset are 1.
		bool all() const;

		/// Returns true if at least one bit in this bitset is 1.
		bool any() const;

		/// Returns true if no bit is 1.
		bool none() const;

		/**
		 * @brief Returns the indexes of the bits set to 1.
		 * @param[out] w A vector where w[i] = j if, and only if,
		 * the j-th bit of the bitset is set to 1.
		 */
		void which(vector<size_t>& w) const;

		/// Returns the number of bits set to 1.
		size_t count() const;

		/**
		 * @brief Returns this bitset as a string.
		 * @param sep A string used as spacing between the bits.
		 */
		string to_string(const string& sep = " ") const;
};

} // -- namespace utils
} // -- namespace lgraph

