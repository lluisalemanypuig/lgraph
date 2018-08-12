#include "svector.hpp"

namespace lgraph {
namespace utils {

// PUBLIC

template<class T, class Alloc>
svector<T, Alloc>::svector() : vector<T, Alloc>() {
	idx = 0;
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n) : vector<T, Alloc>(n) {
	idx = 0;
}

template<class T, class Alloc>
svector<T, Alloc>::svector(size_t n, const T& v) : vector<T, Alloc>(n, v) {
	idx = 0;
}

template<class T, class Alloc>
svector<T, Alloc>::~svector() { }

// MODIFIERS

template<class T, class Alloc>
void svector<T, Alloc>::add(const T& v) {
	if (idx == this->size()) {
		this->push_back(v);
		++idx;
	}
	else {
		(*this)[idx++] = v;
	}
}

template<class T, class Alloc>
void svector<T, Alloc>::remove(size_t i) {
	std::swap( (*this)[i], (*this)[idx - 1] );
	--idx;
}

template<class T, class Alloc>
void svector<T, Alloc>::sort() {
	std::sort(this->begin(), this->begin() + idx);
}

// GETTERS

template<class T, class Alloc>
size_t svector<T, Alloc>::n_elems() const {
	return idx;
}

template<class T, class Alloc>
bool svector<T, Alloc>::contains(const T& v) const {
	bool found = false;
	size_t i = 0;
	while (i < idx and not found) {
		if ( (*this)[i] == v ) {
			found = true;
		}
		++i;
	}
	return i;
}

template<class T, class Alloc>
bool svector<T, Alloc>::position(const T& v, size_t& p) const {
	p = idx + 1;
	size_t i = 0;
	while (i < idx and p == idx + 1) {
		if ( (*this)[i] == v ) {
			p = i;
		}
		++i;
	}
	return p != idx + 1;
}

template<class T, class Alloc>
void svector<T,Alloc>::as_vector(vector<T,Alloc>& v) const {
	v = vector<T,Alloc>(this->begin(), this->begin() + n_elems() );
}

} // -- namespace utils
} // -- namespace lgraph

