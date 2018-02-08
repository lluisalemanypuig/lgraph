#include "random_generator.hpp"

namespace dsa {
namespace utils {

template<class G, typename cT>
crandom_generator<G,cT>::crandom_generator() : random_generator<G,cT>() { }

template<class G, typename cT>
crandom_generator<G,cT>::~crandom_generator() { }

/* Initialisers of the distributions */

template<class G, typename cT>
void crandom_generator<G,cT>::init_uniform(cT a, cT b) {
	U = uniform_real_distribution<cT>(a, b);
}

/* Get pseudo-random numbers */

template<class G, typename cT>
cT crandom_generator<G,cT>::get_uniform() {
	cT r = U(random_generator<G,cT>::gen);
	return r;
}
	
} // -- namespace utils
} // -- namespace dsa

