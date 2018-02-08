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
		G.dist_all_to_all(ds);
		return closeness(G, ds, cc);
	}

	void closeness(const graph& G, const vector<vector<size_t> >& ds, vector<double>& cc) {
		const size_t N = G.n_nodes();
		cc = vector<double>(N);

		for (size_t i = 0; i < N; ++i) {
			cc[i] = std::accumulate
			(
				ds[i].begin(), ds[i].end(), 0.0,
				[](size_t acc, size_t d) {
					if (d != utils::inf) {
						acc += 1.0/d;
					}
					return acc;
				}
			);

			cc[i] /= (N - 1);
		}
	}
	
	void betweenness(const graph& G, vector<double>& bc) {
	}
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

