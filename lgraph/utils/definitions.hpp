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

#pragma once

// C++ includes
#include <cstdint>
#include <limits>
#include <vector>

// lgraph includes
#include <lgraph/utils/svector.hpp>

namespace lgraph {

/// Typedef for a graph node's index.
typedef uint64_t node;
/// Typedef for a list of nodes.
typedef utils::svector<node> neighbourhood;
/// Typedef for a list of weights.
template<class T>
using weight_list = utils::svector<T>;
/// Typedef for a constant iterator through a @ref neighbourhood.
typedef neighbourhood::const_iterator ncit;
/// Typedef for a non-constant iterator through a @ref neighbourhood.
typedef neighbourhood::iterator nit;
/// Typedef for an edge of a graph.
typedef std::pair<node, node> edge;

/// Function to avoid 'Unused parameter' warnings.
template<class T> inline void UNUSED(const T& t) { (void)t; }

/// Shorthand for the maximum value of any type.
template<typename T> inline T inf_t() { return std::numeric_limits<T>::max(); }

/**
 * @brief Typedef for the type of weight in unweighted graphs.
 *
 * _new_ stands for Null Edge Weight.
 */
typedef uint64_t _new_;

} // -- namespace lgraph
