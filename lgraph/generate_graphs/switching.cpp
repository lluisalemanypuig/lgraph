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

#include <lgraph/generate_graphs/switching.hpp>

// C++ includes
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>

// lgraph includes
#include <lgraph/utils/logger.hpp>

namespace lgraph {
namespace networks {
namespace modify {

// private namespace for the switching model
namespace _switching {

	inline std::string edge_to_string(const edge& e) {
		return "(" + std::to_string(e.first) + "," + std::to_string(e.second) + ")";
	}

	inline void print_edges
	(const std::vector<edge>& edges, size_t max_idx, const std::string& tab = "")
	{
		utils::logger<utils::null_stream>& LOG =
			utils::logger<utils::null_stream>::get_logger();

		LOG.log() << tab;
		for (size_t i = 0; i < edges.size(); ++i) {
			std::string str_edge = edge_to_string(edges[i]);
			std::string str_idx = std::to_string(i);
			size_t max_len = std::max(str_edge.length(), str_idx.length());

			if (i == max_idx) {
				LOG.log() << std::setw(max_len + 1) << str_idx + "* ";
			}
			else {
				LOG.log() << std::setw(max_len) << str_idx << " ";
			}
		}
		LOG.log() << std::endl;

		LOG.log() << tab;
		for (size_t i = 0; i < edges.size(); ++i) {
			std::string str_edge = edge_to_string(edges[i]);
			std::string str_idx = std::to_string(i);
			size_t max_len = std::max(str_edge.length(), str_idx.length());

			LOG.log() << std::setw(max_len) << str_edge << " ";
		}
		LOG.log() << std::endl;
	}

	// Resorts the edges so that all edges that share and enpoint with e1
	// are placed behind max_idx. The edge e1 is also put behind max_idx.
	// Returns true if max_idx >= 0.
	// Returns false if otherwise.
	// The event of 'false' happens when all edges in the set share an
	// endpoint with e1 (think of a star tree)
	bool resort_edges(size_t e_idx, std::vector<edge>& all_edges, size_t& max_idx) {
		utils::logger<utils::null_stream>& LOG =
			utils::logger<utils::null_stream>::get_logger();

		edge e = all_edges[e_idx];

		// place e at the end only if necessary
		if (e_idx != max_idx) {
			std::swap(all_edges[e_idx], all_edges[max_idx]);
		}
		// reduce the interval:
		//               max_idx
		// [e0, e1, ...,  ek,    e_idx]
		--max_idx;

		LOG.log() << "    After first swap:" << std::endl;
		_switching::print_edges(all_edges, max_idx, "        ");

		size_t i = 0;
		while (i <= max_idx and max_idx > 0) {

			size_t s = all_edges[i].first;
			size_t t = all_edges[i].second;
			LOG.log() << "    Does edge " << _switching::edge_to_string(all_edges[i])
					  << " share an endpoint with "
					  << _switching::edge_to_string(e) << "?" << std::endl;

			if (s == e.first or s == e.second or t == e.first or t == e.second) {
				// the i-th edge and 'e' share an endpoint
				// put the i-th edge at the end, reduce interval

				std::swap(all_edges[i], all_edges[max_idx]);
				--max_idx;

				LOG.log() << "        Yes" << std::endl;
				LOG.log() << "        After swapping:" << std::endl;
				_switching::print_edges(all_edges, max_idx, "            ");

				// do not increment 'i' so that we can process the
				// edge that was at the end of the interval and now
				// placed at the i-th position
			}
			else {
				LOG.log() << "        No" << std::endl;

				// the i-th edge and 'e' do not share any endpoint
				// continue to the next edge.
				++i;
			}
		}

		// there may be one more edge to process...
		bool max_idx_0_or_more = true;
		if (max_idx == 0) {
			// ... there is
			size_t s = all_edges[0].first;
			size_t t = all_edges[0].second;
			if (s == e.first or e.second or t == e.first or t == e.second) {
				max_idx_0_or_more = false;
			}
		}

		return max_idx_0_or_more;
	}
} // -- namespace _switching

template<class G, typename dT> void switching_model
(utils::drandom_generator<G,dT>& rg, size_t Q, uugraph& Gs)
{
	utils::logger<utils::null_stream>& LOG =
			utils::logger<utils::null_stream>::get_logger();

	std::vector<edge> all_edges;
	Gs.edges(all_edges);

	assert(all_edges.size() >= 2);

	size_t max_idx = all_edges.size() - 1;

	size_t T = Q*Gs.n_edges();
	for (size_t i = 1; i <= T; ++i) {

		LOG.log() << "Step i= " << i << std::endl;

		rg.init_uniform(0, max_idx);
		size_t e1_idx = rg.get_uniform();

		LOG.log() << "    First edge chosen: "
				  << _switching::edge_to_string(all_edges[e1_idx]) << std::endl;

		// make sure that the next edge chosen is different
		// from e1, shares no endpoint with it, so that it
		// can be chosen in constant time
		bool r = _switching::resort_edges(e1_idx, all_edges, max_idx);

		if (r) {
			rg.init_uniform(0, max_idx);
			size_t e2_idx = rg.get_uniform();

			LOG.log() << "    Second edge chosen: "
					  << _switching::edge_to_string(all_edges[e2_idx])
					  << std::endl;

			// delete edges e1 and e2 from the graph and
			// make two new ones, swapping the endpoints
			// of e1 and e2.

			// e1 is always placed at the end
			e1_idx = all_edges.size() - 1;

			// Exchange endpoints:
			// from ((s,t),(u,v)) to ((s,v),(u,t))
			std::swap(all_edges[e1_idx].second, all_edges[e2_idx].second);

			LOG.log() << "    Edges switched!" << std::endl;
		}

		max_idx = all_edges.size() - 1;
	}

	LOG.log() << "Building the resulting graph..." << std::endl;

	// clear the current graph and build a new one
	// with the switched edges
	const size_t N = Gs.n_nodes();
	Gs.init(N);
	for (const edge& e : all_edges) {
		Gs.add_edge(e);
	}

	LOG.log() << "Built!" << std::endl;
}

} // -- namespace modify
} // -- namespace networks
} // -- namespace lgraph
