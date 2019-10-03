/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 * 
 ********************************************************************/

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

