#include <lgraph/data_structures/svector.hpp>

namespace lgraph {
namespace utils {

// PUBLIC

template<class T, class Alloc>
svector<T, Alloc>::svector() {
	idx = 0;
	elems = vector<T, Alloc>();
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n) {
	idx = 0;
	elems = vector<T, Alloc>(n);
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n, const T& v) {
	idx = 0;
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
	assert(i < idx);
	std::swap( elems[i], elems[idx - 1] );
	--idx;

	if (idx < (elems.size() >> 1)) {
		elems.resize(idx);
	}
}

template<class T, class Alloc>
void svector<T, Alloc>::sort() {
	std::sort(elems.begin(), elems.begin() + idx);
}

// GETTERS

template<class T, class Alloc>
size_t svector<T, Alloc>::size() const {
	return idx;
}

template<class T, class Alloc>
bool svector<T, Alloc>::contains(const T& v) const {
	bool found = false;
	size_t i = 0;
	while (i < idx and not found) {
		if ( elems[i] == v ) {
			found = true;
		}
		++i;
	}
	return i - 1 < idx;
}

template<class T, class Alloc>
bool svector<T, Alloc>::position(const T& v, size_t& p) const {
	p = idx;
	size_t i = 0;
	while (i < idx and p == idx) {
		if ( elems[i] == v ) {
			p = i;
		}
		++i;
	}
	return p != idx;
}

template<class T, class Alloc>
void svector<T,Alloc>::as_vector(vector<T,Alloc>& v) const {
	v = vector<T,Alloc>(elems.begin(), elems.begin() + size() );
}

} // -- namespace utils
} // -- namespace lgraph

