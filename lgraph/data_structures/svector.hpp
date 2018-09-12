#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <set>
using namespace std;

namespace lgraph {
namespace utils {

/**
 * @brief Shortened vector
 *
 * This class implements a container that is, basically, a little
 * shortcut in vectors for the ease of inserting/deleting elements
 * without having to use iterators. It also avoids all the work that
 * erasing an element from a STL's vector requires (moving all the
 * memory in the positions after the removed element to the end).
 *
 * A pointer determines the position next to the last element of the
 * container. Any element added to the container is placed where
 * @ref idx points at and then @ref idx is incremented. Any element
 * removed is moved at the position before @ref idx and then @ref idx
 * is decremented.
 *
 * @param T The type of the elements stored. Must allow the use of '='
 * and '<' operators.
 * 
 * @param Alloc The allocator for the elements of type @e T. See the
 * documentation for C++'s vectors for more details
 * (http://en.cppreference.com/w/cpp/container/vector).
 */
template<class T, class Alloc = allocator<T> >
class svector {
	private:
		/**
		 * @brief Pointer to the next position available in the container
		 *
		 * For example:
		 * \verbatim
		 *                   \/
		 * contents: 0 1 2 3 __
		 * \endverbatim
		 * @ref idx points at the position after element 3.
		 * The next new element added will be stored in the position
		 * pointed by @ref idx.
		 */
		size_t idx;

		/**
		 * @brief Container used to allocate the elements
		 *
		 * The valid elements in this container are found within range
		 * of indices [0,@ref idx).
		 *
		 * The new element added to this container will be placed in
		 * the position elems[@ref idx].
		 */
		vector<T,Alloc> elems;

		/**
		 * @brief Removes the element in the i-th position of this container
		 *
		 * Swaps the element in the @e i-th position with the element in the
		 * previous position pointed by @ref idx. Then decrements the value
		 * of @ref idx.
		 *
		 * @param i The index of the element to be removed.
		 * @pre @e i < @ref idx
		 * @post The destructor of the element is not called. Therefore,
		 * the memory will have to be explicitly freed by the caller,
		 * unless the allocator already implements their destruction.
		 */
		void only_remove(size_t i);

		/**
		 * @brief Shrinks the underlying container.
		 *
		 * In case the effective amount of elements in the container
		 * (value of @ref idx) is smaller than the vector's size (size
		 * of @ref elems) then @ref elems is resized to fit only
		 * @ref idx elements.
		 */
		void shrink_if();

	public:
		/// Definition of the iterator of svector class
		typedef T* iterator;
		/// Definition of the const iterator of svector class
		typedef const T* const_iterator;
		
	public:
		/// Empty constructor
		svector();

		/// Construct a shortened vector that holds @e n elements
		svector(size_t n);
		/// Construct a shortened vector that holds @e n elements, all of them being @e v
		svector(size_t n, const T& v);
		/// Destructor
		~svector();

		// ITERATORS

		/**
		 * @brief Iterator at the beginning of the container
		 *
		 * This is not actually an iterator, but a pointer to the elements
		 * of the vector @ref elems.
		 * @return Returns a pointer to the first element of @ref elems.
		 */
		iterator begin();
		/**
		 * @brief Const iterator at the beginning of the container
		 *
		 * This is not actually an iterator, but a pointer to the elements
		 * of the vector @ref elems.
		 * @return Returns a constant pointer to the first element of @ref elems.
		 */
		const_iterator begin() const;
		/**
		 * @brief Iterator at the end of the container
		 *
		 * This is not actually an iterator, but a pointer to the elements
		 * of the vector @ref elems.
		 * @return Returns a pointer to the last valid element of @ref elems.
		 */
		iterator end();
		/**
		 * @brief Const iterator at the end of the container.
		 *
		 * This is not actually an iterator, but a pointer to the elements
		 * of the vector @ref elems.
		 * @return Returns a constant pointer to the last valid element of @ref elems.
		 */
		const_iterator end() const;

		// OPERATORS

		/**
		 * @brief Outputs in an ostream object the contents of this container
		 *
		 * The contents passed to the ostream object are all those elements
		 * whose index is strictly below @ref idx.
		 */
		inline friend
		ostream& operator<< (ostream& os, const svector<T,Alloc>& v) {
			if (v.size() > 0) {
				os << v[0];
				for (size_t i = 1; i < v.size(); ++i) {
					os << " " << v[i];
				}
			}
			return os;
		}

		/// Assignment operator
		svector<T,Alloc>& operator= (const svector<T,Alloc>& s);

		/**
		 * @brief Returns a reference to the i-th element
		 * @pre @e i < @ref idx
		 */
		T& operator[] (size_t i);
		/**
		 * @brief Returns a constant reference to the i-th element
		 * @pre @e i < @ref idx
		 */
		const T& operator[] (size_t i) const;

		// MODIFIERS

		/**
		 * @brief Adds an element to this container
		 *
		 * If @ref idx is equal to size() then the method push_back() is called.
		 * Otherwise, element @e v is copied to the position pointed by @ref idx.
		 * In both cases @ref idx is incremented.
		 *
		 * @param v Value to be added
		 */
		void add(const T& v);

		/**
		 * @brief Removes the element in the i-th position of this container
		 *
		 * Swaps the element in the @e i-th position with the element in the
		 * previous position pointed by @ref idx. Then decrements the value
		 * of @ref idx.
		 *
		 * @param i The index of the element to be removed.
		 * @pre @e i < @ref idx
		 * @post The destructor of the element is not called. Therefore,
		 * the memory will have to be explicitly freed by the caller,
		 * unless the allocator already implements their destruction.
		 * 
		 * When @ref idx has reached half the total size of the container
		 * @ref elems the container is resized to a size equal to @ref idx.
		 */
		void remove(size_t i);

		/**
		 * @brief Removes the elements in the range [b,e) of this container
		 *
		 * It copies the elements in [@e e,@ref idx) to the (@ref idx - @e e)
		 * positions starting at @e b.
		 *
		 * @param b The index of the first element to be removed.
		 * @param e The index of the last element to be removed plus 1.
		 * @pre @e b < @e e <= @ref idx
		 * @post The destructor of the elements in the range [b,e) is not
		 * called. Therefore, the memory will have to be explicitly
		 * freed by the caller, unless the allocator already implements
		 * their destruction.
		 * 
		 * If @ref idx has reached half the total size of the container
		 * @ref elems the container is resized to a size equal to @ref idx.
		 */
		void remove(size_t b, size_t e);

		/**
		 * @brief Sorts the elements of this vector.
		 *
		 * Sorts the elements in positions [0,..,@ref idx)
		 */
		void sort();

		/**
		 * @brief Find and remove an element from the container
		 *
		 * Function that serves as a macro of finding the position of an
		 * element in the container and deleting the element in that
		 * position.
		 *
		 * @param v The element to search and delete
		 * @post The first occurrence of element @e v is removed from
		 * the container if it exists.
		 * 
		 * The destructor of the element is not called. Therefore, the
		 * memory will have to be explicitly freed by the caller, unless
		 * the allocator already implements their destruction.
		 */
		void find_remove(const T& v);

		/**
		 * @brief Removes the contents of several positions from the container.
		 *
		 * Consider the contents of the container at the state prior the
		 * deletion. After the deletion the contents of the container are
		 * all the elements except those pointed by the positions in @e poss
		 * at the previous state.
		 *
		 * @param poss Set of positions to be removed.
		 * @pre All elements in @e poss must be strictly smaller than the
		 * size of the container (see @ref size()) at the state prior the deletion.
		 * @post The contents of the container need not preserve the original
		 * order.
		 */
		void remove_several(const set<size_t>& poss);

		/**
		 * @brief Removes the contents of several positions from the container.
		 *
		 * Consider the contents of the container at the state prior the
		 * deletion. After the deletion the contents of the container are
		 * all the elements except those pointed by the positions in @e poss
		 * at the previous state.
		 *
		 * @param poss List of positions to be removed.
		 * @pre All elements in @e poss must be strictly smaller than the
		 * size of the container (see @ref size()) at the state prior the deletion.
		 * The elements in @e poss must be increasingly sorted.
		 * @post The contents of the container do not necessarily preserve the
		 * original order.
		 */
		void remove_several_s(const vector<size_t>& poss);

		/**
		 * @brief Removes the contents of several positions from the container.
		 *
		 * Consider the contents of the container at the state prior the
		 * deletion. After the deletion the contents of the container are
		 * all the elements except those pointed by the positions in @e poss
		 * at the previous state.
		 *
		 * This method requires linear space in the number of elements of
		 * this container (value of @ref idx).
		 *
		 * In case the size of @e poss is small then it may be better to sort
		 * its contents and use method @ref remove_several_s(const vector<size_t>&).
		 *
		 * @param poss List of positions to be removed.
		 * @pre All elements in @e poss must be strictly smaller than the
		 * size of the container (see @ref size()) at the state prior the deletion.
		 * @post The contents of the container need not preserve the original
		 * order.
		 */
		//void remove_several(const vector<size_t>& poss);

		// GETTERS

		/**
		 * @brief Returns the number of elements in this vector
		 * @return Returns the value of @ref idx
		 */
		size_t size() const;

		/**
		 * @brief Looks for an element equal to @e v in the container.
		 *
		 * Performs a linear search on the contents of the container.
		 *
		 * @param v THe element to be searched
		 * @return Returns true if there is an element equal to @e v in the container.
		 */
		bool contains(const T& v) const;

		/**
		 * @brief Looks for an element @e v in the vector and stores its position in @e pos
		 * @param v The element to be searched
		 * @return Returns a value smaller than @ref idx if v is in the
		 * container. Returns a value equal to @ref idx if otherwise.
		 */
		size_t position(const T& v) const;

		/**
		 * @brief Converts this shortened container into a regular C++'s vector.
		 *
		 * Makes a vector<T> with all the elements in this shortened vector
		 * in the positions [0,..,@ref idx).
		 */
		void as_vector(vector<T,Alloc>& v) const;
};

} // -- namespace utils
} // -- namespace lgraph

#include <lgraph/data_structures/svector.cpp>
