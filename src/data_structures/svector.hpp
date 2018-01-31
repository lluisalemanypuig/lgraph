#pragma once

/// C includes
#include <assert.h>

/// C++ includes
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

namespace dsa {
namespace utils {

/*
This class implements a little shortcut in vectors for the ease
of inserting/deleting elements without having to use iterators.

A pointer (idx) points at the next available position. Any element
added to the vector is placed where 'idx' points at. Any element
removed is moved at the position before 'idx' and then 'idx' is
decremented. Adding elements should be done through the method add().

The interval of valid indexes is defined as: [0, 1, ..., idx).
The value of 'idx' can be retrieved through method get_size().

The name 'svector' stands for 'set-like vector'. However, the data
stored in this container is not sorted at all.
*/
template<class T, class Alloc = allocator<T> >
class svector : public vector<T, Alloc> {
	private:
		// a pointer to the next position available in the vector
		// for example:
		//                   \/
		// contents: 0 1 2 3 __
		// 'idx' points at the position after 3
		// any new element added will be stored in the position
		// pointing by 'idx'.
		size_t idx;
		
	public:
		svector();
		
		/* When this vector is first initialised, the method get_size
		 * will return 0 because no elements were inserted using add.
		 * However, the size() method will return n, because that is
		 * the actual size of the vector.
		*/
		svector(size_t n);
		svector(size_t n, const T& v);
		~svector();
		
		/// OPERATORS
		
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
		
		/// Modifiers
		
		void add(const T& v);
		void remove(size_t i);
		void sort();
		
		/// Getters
		
		// Returns the number of elements inserted using add() minus
		// the amount of elements erased using remove
		size_t n_elems() const;
		
		// Returns true if value 'v' is in this container. Linear search.
		bool contains(const T& v) const;
		
		// Stores the position of value 'v' if it exists and returns true
		// or stores 'n_elems() + 1' and returns false if otherwise.
		bool position(const T& v, size_t& pos) const;
		
};

} // -- namespace utils
} // -- namespace dsa

#include "svector.cpp"
