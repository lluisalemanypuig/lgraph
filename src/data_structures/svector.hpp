#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

namespace lgraph {
namespace utils {

/**
 * @brief Shortened vector
 *
 * This class implements a little shortcut in vectors for the ease of
 * inserting/deleting elements without having to use iterators.
 *
 * A pointer determines the position next to the last element of the vector.
 * Any element added to the vector is placed where @ref idx points at and then
 * @ref idx is incremented.
 * Any element removed is moved at the position before @ref idx and then
 * @ref idx is decremented.
 *
 * @param T The type of the elements stored. Must implement the '=' operator.
 * @param Alloc The allocator for the elements of type @e T. See the
 * documentation for C++'s vectors for more details
 * (http://en.cppreference.com/w/cpp/container/vector)
 */
template<class T, class Alloc = allocator<T> >
class svector : public vector<T, Alloc> {
	private:
		/**
		 * @brief Pointer to the next position available in the vector
		 *
		 * For example:
		 *                   \/
		 * contents: 0 1 2 3 __
		 * @ref idx points at the position after element 3
		 * any new element added will be stored in the position
		 * pointed by @ref idx
		 */
		size_t idx;
		
	public:
		/// Empty constructor
		svector();

		/// Construct a shortened vector that holds @e n elements
		svector(size_t n);
		/// Construct a shortened vector that holds @e n elements, all of them being @e v
		svector(size_t n, const T& v);
		/// Destructor
		~svector();

		/**
		 * @brief Outputs in an ostream object the contents of this vector.
		 *
		 * The contents passed to the ostream object are all those elements
		 * whose index is strictly below @ref idx.
		 */
		inline friend
		ostream& operator<< (ostream& os, const svector& v) {
			if (v.n_elems() > 0) {
				os << v[0];
				for (size_t i = 1; i < v.n_elems(); ++i) {
					os << " " << v[i];
				}
			}
			return os;
		}

		/**
		 * @brief Adds an element to this vector
		 *
		 * If @ref idx is equal to size() then the method push_back() is called.
		 * Otherwise, element @e v is copied to the position pointed by @ref idx
		 * and then @ref idx is incremented.
		 * @param v Value to be added
		 */
		void add(const T& v);

		/**
		 * @brief Removes the element in the i-th position of this vector.
		 *
		 * Places the element in the @e i-th position of this vector and then
		 * decrements the value of @ref idx.
		 * @param i The index of the element to be removed.
		 */
		void remove(size_t i);
		/**
		 * @brief Sorts the elements of this vector.
		 *
		 * Sorts the elements in positions [0,..,@ref idx)
		 */
		void sort();

		/**
		 * @brief Returns the number of elements in this vector
		 * @return Returns the value of @ref idx
		 */
		size_t n_elems() const;
		
		// Returns true if value 'v' is in this container. Linear search.
		/**
		 * @brief Looks for an element equal to @e v in the vector.
		 *
		 * Performs a linear search on the contents of the vector.
		 * @param v THe element to be searched
		 * @return Returns true if there is an element equal to @e v in the vector.
		 */
		bool contains(const T& v) const;
		
		// Stores the position of value 'v' if it exists and returns true
		// or stores 'n_elems() + 1' and returns false if otherwise.
		/**
		 * @brief Looks for an element @e v in the vector and stores its position in @e pos
		 * @param[in]	v The element to be searched
		 * @param[out]	pos The position of @e v in the vector.
		 * @return Returns true if @e v is in the vector.
		 */
		bool position(const T& v, size_t& pos) const;
};

} // -- namespace utils
} // -- namespace lgraph

#include "svector.cpp"
