#include <lgraph/utils/random_generator.hpp>

namespace lgraph {
namespace utils {

template<class G, typename cT>
crandom_generator<G,cT>::crandom_generator() : random_generator<G,cT>() {
	U = nullptr;
}

template<class G, typename cT>
crandom_generator<G,cT>::~crandom_generator() {
	if (U != nullptr) {
		delete U;
	}
}

/* Initialisers of the distributions */

template<class G, typename cT>
void crandom_generator<G,cT>::init_uniform(cT a, cT b) {
	if (U != nullptr) {
		delete U;
		U = nullptr;
	}
	U = new std::uniform_real_distribution<cT>(a, b);
}

template<class G, typename cT>
void crandom_generator<G,cT>::init_binomial(cT, double) {
	// do nothing
}

/* Get pseudo-random numbers */

template<class G, typename cT>
cT crandom_generator<G,cT>::get_uniform() {
	assert(U != nullptr);

	cT r = (*U)(random_generator<G,cT>::gen);
	return r;
}

template<class G, typename cT>
cT crandom_generator<G,cT>::get_binomial() {
	return 0.0;
}
	
} // -- namespace utils
} // -- namespace lgraph

