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

// lgraph includes
#include <lgraph/data_structures/xxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace clustering {

/* -------------------------------- */
/* CLUSTERING FOR UNWEIGHTED GRAPHS */

/**
 * @brief Global Clustering Coefficient of an undirected unweighted graph.
 *
 * Computes the global clustering coefficient of this graph:
 *
 * \f$C = \frac{\# triangles}{\# \ connected \ triples}\f$
 *
 * The global clustering coefficient of a graph is defined in
 \verbatim
 Newman, M. E. J. (2010). Networks. An introduction. Oxford
 University Press, Oxford.
 \endverbatim
 *
 * @param G The unweighted graph to be evaluated.
 * @return Returns the global clustering coefficient of G.
 * @pre The graph is undirected.
 */
double gcc(const xxgraph *G);

/**
 * @brief Mean Local Clustering Coefficient of an undirected unweighted graph.
 *
 * First, define a clustering coefficient for each vertex \f$i\f$:
 *
 * \f$C_i = \frac{\# \ connected \ neighbours \ of \ i}{\# \ pairs \ of \ neighbours \ of \ i}\f$
 *
 * The Mean Local CLustering Coefficient is thus evaluated as:
 *
 * \f$C = \frac{1}{n} \sum_{i=1}^n C_i\f$.
 *
 * The local clustering coefficient of a graph is defined in
 \verbatim
 Watts, D. J. and Strogatz, S. H. (1998). Collective
 dynamics of ’small-world’ networks. Nature, 393:440–442.
 \endverbatim
 *
 * @param G The unweighted graph to be evaluated.
 * @return Returns the local clustering coefficient of G.
 * @pre The graph is undirected.
 */
double mlcc(const xxgraph *G);

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph
