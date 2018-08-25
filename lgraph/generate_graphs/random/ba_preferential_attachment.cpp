#include <lgraph/generate_graphs/social/barabasi_albert.hpp>

namespace lgraph {
namespace networks {
namespace random {
	
	// private namespace for the no growth variant
	namespace _pa {
		
		// function for debugging
		inline void print_stubs(const uugraph& G, const vector<size_t>& stubs, size_t max_idx, const string& tab = "") {
			logger<null_stream>& LOG = logger<null_stream>::get_logger();
			
			LOG.log() << tab << "max_idx= " << max_idx << endl;
			LOG.log() << tab;
			for (size_t i = 0; i < stubs.size(); ++i) {
				size_t pos_length = std::to_string(i).length();
				size_t stub_length = std::to_string(stubs[i]).length();
				size_t degree_length = std::to_string(G.degree(stubs[i])).length();
				size_t max_length = max(pos_length, max(stub_length, degree_length));
				
				LOG.log() << setw(max_length) << i << " ";
			}
			LOG.log() << endl;
			
			LOG.log() << tab;
			for (size_t i = 0; i < stubs.size(); ++i) {
				size_t pos_length = std::to_string(i).length();
				size_t stub_length = std::to_string(stubs[i]).length();
				size_t degree_length = std::to_string(G.degree(stubs[i])).length();
				size_t max_length = max(pos_length, max(stub_length, degree_length));
				
				LOG.log() << setw(max_length) << stubs[i] << " ";
			}
			LOG.log() << endl;
			
			LOG.log() << tab;
			for (size_t i = 0; i < stubs.size(); ++i) {
				size_t pos_length = std::to_string(i).length();
				size_t stub_length = std::to_string(stubs[i]).length();
				size_t degree_length = std::to_string(G.degree(stubs[i])).length();
				size_t max_length = max(pos_length, max(stub_length, degree_length));
				
				LOG.log() << setw(max_length) << G.degree(stubs[i]) << " ";
			}
			LOG.log() << endl;
			
			LOG.log() << tab;
			for (size_t i = 0; i < max_idx; ++i) {
				size_t pos_length = std::to_string(i).length();
				size_t stub_length = std::to_string(stubs[i]).length();
				size_t max_length = max(pos_length, stub_length);
				
				LOG.log() << setw(max_length) << " " << " ";
			}
			size_t pos_length = std::to_string(max_idx).length();
			size_t stub_length = std::to_string(stubs[max_idx]).length();
			size_t max_length = max(pos_length, stub_length);
			LOG.log() << setw(max_length) << "^" << endl;
		}
		
		// G: the graph
		// u: the new vertex added
		// stub_idx: the index of the vertex chosen
		// stubs: a reference to the vector of stubs
		// max_idx: upper bound of the range of the stubs vector
		inline
		void update_stubs(const uugraph& G, size_t stub_idx, vector<size_t>& stubs, size_t& max_idx) {
			const size_t v = stubs[stub_idx];
			
			if (G.degree(v) == 0) {
				// there is one stub for vertex 'v' but degree is 0. This
				// is a special case with which has to be dealt with care
				
				if (stub_idx == max_idx) {
					// easy case: move max_idx
					--max_idx;
					
					return;
				}
				
				size_t next_pos = stub_idx + 1;
				copy(
					stubs.begin() + next_pos, stubs.begin() + max_idx + 1,
					stubs.begin() + stub_idx
				);
				stubs[max_idx] = v;
				--max_idx;
				
				return;
			}
			
			// the chosen node goes at the end, where it will not be chosen again.
			
			if (v == stubs[max_idx]) {
				// connect the new vertex with a vertex pointed by max_idx
				// swap the regions corresponding to the stubs of v and
				// what comes after max_idx. Update max_idx
				
				copy(
					stubs.begin() + max_idx + 1, stubs.end(),
					stubs.begin() + max_idx - G.degree(v) + 1
				);
				
				fill(stubs.end() - G.degree(v), stubs.end(), v);
				
				stubs.push_back(v);
				max_idx = max_idx - G.degree(v);
				return;
			}
			
			// most dificult case: it is time to copy memory.. carefully!
			
			size_t next_pos = stub_idx;
			while (next_pos < max_idx and stubs[next_pos] == v) {
				++next_pos;
			}
			
			size_t last_pos = next_pos - G.degree(v);
			
			copy(
				stubs.begin() + next_pos, stubs.end(),
				stubs.begin() + last_pos
			);
			
			size_t q = stubs.size() - max_idx - 1;
			max_idx = max_idx - G.degree(v);
			size_t lim_inf = max_idx + q + 1;
			
			fill(stubs.begin() + lim_inf, stubs.end(), v);
			stubs.push_back(v);
		}
	}
	
	template<class G, typename dT>
	void BA_preferential_attachment
	(
		drandom_generator<G,dT> *rg,
		size_t n0, size_t m0, size_t T,
		uugraph& Gs
	)
	{
		// initialize sequences of graphs
		Gs.init(n0);
		
		// Initialize list of stubs to choose from. For every node, as
		// many stubs as the degree of the node. However, if the node
		// has degree 0, the list will have 1 stub for that node.
		vector<size_t> stubs(n0);
		for (size_t i = 0; i < stubs.size(); ++i) {
			stubs[i] = i;
		}
		
		// at each time step t (1 <= t <= T) add one vertex to G
		// connected to m0 vertices chosen following the preferential
		// attachment rule making sure that no vertex is chosen twice
		// in the same time step.
		for (size_t t = 1; t <= T; ++t) {
			
			// define the upper bound of the interval within which
			// the random numbers will be generated
			size_t max_idx = stubs.size() - 1;
			
			// add a new vertex to the graph
			size_t u = Gs.add_node();
			
			// connect the new vertex to m0 vertices in the graph
			for (size_t m = 0; m < m0; ++m) {
				// reset the uniform random generator
				rg->init_uniform(0, max_idx);
				
				// choose stub and make edge
				size_t stub_idx = rg->get_uniform();
				size_t v = stubs[stub_idx];
				
				// rearrange the vector stubs for next iteration
				_pa::update_stubs(Gs, stub_idx, stubs, max_idx);
				
				Gs.add_edge(u, v);
			}
			
			// insert m0 stubs for new vertex
			stubs.insert(stubs.end(), m0, u);
		}
	}

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

