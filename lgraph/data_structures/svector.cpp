#include <lgraph/data_structures/svector.hpp>

namespace lgraph {
namespace utils {

// PRIVATE

template<class T, class Alloc>
void svector<T, Alloc>::only_remove(size_t i) {
	assert(i < idx);

	std::swap( elems[i], elems[idx - 1] );
	--idx;
}

template<class T, class Alloc>
void svector<T, Alloc>::shrink_if() {
	// if idx is smaller than half the vector's size
	// then resize the vector to save some memory
	if (idx < (elems.size() >> 1)) {
		elems.resize(idx);
	}
}

// PUBLIC

template<class T, class Alloc>
svector<T, Alloc>::svector() {
	idx = 0;
	elems = vector<T, Alloc>();
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n) {
	idx = n;
	elems = vector<T, Alloc>(n);
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n, const T& v) {
	idx = n;
	elems = vector<T, Alloc>(n,v);
}

template<class T, class Alloc>
svector<T, Alloc>::~svector() { }

// ITERATORS

template<class T, class Alloc>
typename svector<T, Alloc>::iterator svector<T, Alloc>::begin() {
	return &elems[0];
}

template<class T, class Alloc>
typename svector<T, Alloc>::const_iterator svector<T, Alloc>::begin() const {
	return &elems[0];
}

template<class T, class Alloc>
typename svector<T, Alloc>::iterator svector<T, Alloc>::end() {
	iterator e = nullptr;
	if (idx < elems.size()) {
		e = &elems[idx];
	}
	else {
		e = &elems[idx - 1];
		++e;
	}
	return e;
}

template<class T, class Alloc>
typename svector<T, Alloc>::const_iterator svector<T, Alloc>::end() const {
	const_iterator e = nullptr;
	if (idx < elems.size()) {
		e = &elems[idx];
	}
	else {
		e = &elems[idx - 1];
		++e;
	}
	return e;
}

// OPERATORS

template<class T, class Alloc>
svector<T,Alloc>& svector<T, Alloc>::operator= (const svector<T,Alloc>& s) {
	idx = s.idx;
	elems = s.elems;
	return *this;
}

template<class T, class Alloc>
T& svector<T, Alloc>::operator[] (size_t i) {
	assert(i < idx);
	return elems[i];
}

template<class T, class Alloc>
const T& svector<T, Alloc>::operator[] (size_t i) const {
	assert(i < idx);
	return elems[i];
}

// MODIFIERS

template<class T, class Alloc>
void svector<T, Alloc>::add(const T& v) {
	if (idx == elems.size()) {
		elems.push_back(v);
		++idx;
	}
	else {
		(*this)[idx++] = v;
	}
}

template<class T, class Alloc>
void svector<T, Alloc>::remove(size_t i) {
	only_remove(i);

	// if idx is smaller than half the vector's size
	// then resize the vector to save some memory
	shrink_if();
}

template<class T, class Alloc>
void svector<T, Alloc>::remove(size_t b, size_t e) {
	assert(b < e);
	assert(e <= idx);

	// copy the elements from [e, idx) to
	// the positions starting at b
	copy(
		elems.begin() + e, elems.begin() + idx,
		elems.begin() + b
	);

	idx -= (e - b);

	// save memory
	shrink_if();
}

template<class T, class Alloc>
void svector<T, Alloc>::sort() {
	std::sort(elems.begin(), elems.begin() + idx);
}

template<class T, class Alloc>
void svector<T, Alloc>::find_remove(const T& v) {
	size_t pos = position(v);
	if (pos < idx) {
		remove(pos);
	}
}

template<class T, class Alloc>
void svector<T, Alloc>::remove_several(const set<size_t>& v) {
	// traverse the set to the end (in reverse order)
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		only_remove( *it );
	}

	// save memory
	shrink_if();
}

template<class T, class Alloc>
void svector<T, Alloc>::remove_several_s(const vector<size_t>& v) {
#if not defined (NDEBUG)
	// variables used to make sure the
	// vector is increasingly sorted
	size_t prev_elem = v[0];
	size_t k = 0;
#endif

	// traverse the set to the end (in reverse order)
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
#if not defined (NDEBUG)
		if (k > 0) {
			// if k points at the second
			// element or beyond
			assert( prev_elem < v[k] );
			prev_elem = v[k];
		}

		++k;
#endif

		only_remove( *it );
	}

	// save memory
	shrink_if();
}

template<class T, class Alloc>
void svector<T, Alloc>::remove_several(const vector<size_t>& v) {
#if not defined (NDEBUG)
	const size_t old_idx = idx;
#endif

	// initial position of each element
	map<T, size_t> initial_pos;
	for (size_t i = 0; i < idx; ++i) {
		initial_pos[elems[i]] = i;
	}

	// translation table:
	// tr[i] = j --> "the contents of position 'i' are
	// NOW found at position 'j'"
	vector<size_t> tr(idx);
	iota(tr.begin(), tr.end(), 0);

	// traverse the set to the end (in reverse order)
	for (auto it = v.begin(); it != v.end(); ++it) {
		assert(*it < old_idx);

		// remove contents at initial position *it
		// now at position tr[*it]
		size_t i = tr[*it];

		// remove element at position i
		std::swap( elems[i], elems[idx - 1] );

		// update translation table:
		// -> last element was at position idx - 1.
		// Now it is at position i.
		size_t old_pos = initial_pos[elems[i]];
		tr[old_pos] = i;
		// -> the element just removed is moved to
		// position idx - 1
		tr[*it] = idx - 1;

		--idx;
	}

	// save memory
	shrink_if();
}

// GETTERS

template<class T, class Alloc>
size_t svector<T, Alloc>::size() const {
	return idx;
}

template<class T, class Alloc>
bool svector<T, Alloc>::contains(const T& v) const {
	return position(v) != idx;
}

template<class T, class Alloc>
size_t svector<T, Alloc>::position(const T& v) const {
	size_t i = 0;
	while (i < idx) {
		if (elems[i] == v) {
			return i;
		}
		++i;
	}
	return idx;
}

template<class T, class Alloc>
void svector<T,Alloc>::as_vector(vector<T,Alloc>& v) const {
	v = vector<T,Alloc>(elems.begin(), elems.begin() + size() );
}

} // -- namespace utils
} // -- namespace lgraph

