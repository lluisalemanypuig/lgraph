#include "metrics/centralities.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace centralities {
	
	void degree(const graph& G, vector<double>& dc) {
		vector<node> nds;
		G.nodes(nds);
		
		// number of nodes minus 1
		const double nm1 = G.n_nodes() - 1;
		dc.clear();
		
		transform(
			// iterate through all nodes
			nds.begin(), nds.end(),
			
			// append value at the back of dc
			back_inserter(dc),
			
			// calculate degree centrality
			[&](node u) {
				return G.degree(u)/nm1;
			}
		);
	}
	
	void closeness(const graph& G, vector<double>& cc) {
		vector<vector<size_t> > ds;
		traversal::distances(G, ds);
		return closeness(G, ds, cc);
	}

	void closeness(const graph& G, const vector<vector<size_t> >& ds, vector<double>& cc) {
		const size_t N = G.n_nodes();

		transform(
			// iterate through all nodes
			ds.begin(), ds.end(),

			// append value at the back of cc
			back_inserter(cc),

			// calculate closeness centrality
			[&](const vector<size_t>& ds_i) {
				double sum = std::accumulate
				(
					ds_i.begin(), ds_i.end(), 0.0,
					[](double acc, size_t d) {
						if (d != utils::inf and d > 0) {
							acc += 1.0/d;
						}
						return acc;
					}
				);

				return sum/(N - 1);
			}
		);
	}
	
	void betweenness(const graph& G, vector<double>& bc) {
	}
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

