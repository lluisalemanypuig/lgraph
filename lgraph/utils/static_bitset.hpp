#pragma once

// C includes
#include <stdlib.h>
#include <string.h>

// C++ includes
#include <fstream>
#include <string>
#include <vector>

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
		static_bitset(const std::string& bs);
		/**
		 * @brief Construct a bitset from a list of Boolean values.
		 * @ref bytes[i] = @e bits[i].
		 */
		static_bitset(const std::vector<bool>& bits);
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
		 * Each character of the string is interpreted as a single bit.
		 *
		 * @ref bytes[i] = @e zerones[i].
		 */
		void init_01(const std::string& zerones);
		/**
		 * @brief Initialise the bitset from a list of Boolean values.
		 *
		 * @ref bytes[i] = @e bits[i].
		 */
		void init_01(const std::vector<bool>& bits);
		/**
		 * @brief Initialise the bitset from a string of bytes.
		 *
		 * Each character of the vector is interpreted as a byte.
		 *
		 * @ref bytes[0..7] = @e bytes[0].
		 *
		 * @ref bytes[8..15] = @e bytes[1].
		 */
		void init_bytes(const std::vector<char>& bytes);
		/**
		 * @brief Initialise the bitset from a string of bytes.
		 *
		 * Each character of the string is interpreted as a byte.
		 *
		 * @ref bytes[0..7] = @e bytes[0].
		 *
		 * @ref bytes[8..15] = @e bytes[1].
		 */
		void init_bytes(const std::string& bytes);

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
		 *		s[i] := ~(this[i]^bs[i])
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

		/**
		 * @brief Adds a value to every group of 8 bits.
		 *
		 * Interpreting this bitset as a list of groups of 8 bits,
		 * adds to each one of them the value @e k.
		 *
		 * That is, to each of the groups of bits 0..7, 8..15, 16..23, ...
		 * adds to them the value @e k using the regular addition operation.
		 *
		 * The result is left in this bitset.
		 * @param k Value between 0 and 255, both included.
		 */
		static_bitset& operator+= (char k);

		/// Outputs this bitset formatted in a string.
		inline friend
		std::ostream& operator<< (std::ostream& os, const static_bitset& bitset) {
			for (size_t i = 0; i < bitset.n_bits; ++i) {
				os << static_cast<char>(bitset[i]);
			}
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
		void which(std::vector<size_t>& w) const;

		/// Returns the number of bits set to 1.
		size_t count() const;

		/**
		 * @brief Returns this bitset as a string.
		 * @param[out] s This bitset as a string of zeros and ones.
		 * @param sep A string used as spacing between each byte.
		 */
		void get_01(std::string& s, const std::string& sep = "") const;
		/**
		 * @brief Returns this bitset as a string.
		 * @param sep A string used as spacing between each byte.
		 */
		std::string get_01(const std::string& sep = "") const;

		/**
		 * @brief Returns this bitset as a vector of Boolean values.
		 * @param[out] v This bitset as vector of Boolean values.
		 * The @e i-th value in @e v equals the @e i-th bit.
		 */
		void get_01(std::vector<bool>& v) const;
		/**
		 * @brief Returns this bitset as a vector of Boolean values.
		 * @returns Returns this bitset as vector of Boolean values.
		 * The @e i-th value in @e v equals the @e i-th bit.
		 */
		std::vector<bool> get_01() const;

		/**
		 * @brief Append the contents of this bitset to the end
		 * of a string.
		 *
		 * The last byte may contain rubbish. The number of valid bits
		 * in the last byte is equal to the remainder of the division
		 * of the number of bytes by 8.
		 *
		 * @param[out] s Let @e k be a string such that
		 * k[0..7] = @ref bytes[0], k[8..15] = @ref bytes[1], ...
		 * The string k is appended at the end of @e s.
		 */
		void append_bytes(std::string& s) const;
		/**
		 * @brief Returns a string whose characters are the bytes of
		 * this bitset.
		 *
		 * The last byte may contain rubbish. The number of valid bits
		 * in the last byte is equal to the remainder of the division
		 * of the number of bytes by 8.
		 *
		 * @param[out] s A string 's' such that
		 * s[0..7] = @ref bytes[0], s[8..15] = @ref bytes[1], ...
		 */
		void get_bytes(std::string& s) const;

		/**
		 * @brief Returns a string whose characters are the bytes of
		 * this bitset.
		 *
		 * The last byte may contain rubbish. The number of valid bits
		 * in the last byte is equal to the remainder of the division
		 * of the number of bytes by 8.
		 *
		 * @returns Returns a string 's' such that
		 * s[0..7] = @ref bytes[0], s[8..15] = @ref bytes[1], ...
		 */
		std::string get_bytes() const;

};

} // -- namespace utils
} // -- namespace lgraph

