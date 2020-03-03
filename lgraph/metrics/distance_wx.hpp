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
#include <vector>

// lgraph includes
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

/* ----------------------------- */
/* DISTANCES FOR WEIGHTED GRAPHS */

/**
 * @brief Diameter of a graph.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @return Returns the largest distance between all pairs of nodes.
 */
template<class T>
T max_distance(const wxgraph<T> *G);
/**
 * @brief Diameter of a graph.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the largest distance between all pairs of nodes.
 */
template<class T>
T max_distance(const wxgraph<T> *G, const std::vector<std::vector<T> >& ds);

/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @return Returns the average of the distance between all pairs of nodes.
 */
template<class T>
double mean_distance(const wxgraph<T> *G);
/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The weighted graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the average of the distance between all pairs of nodes.
 */
template<class T>
double mean_distance(const wxgraph<T> *G, const std::vector<std::vector<T> >& ds);

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/metrics/distance_wx.cpp>
