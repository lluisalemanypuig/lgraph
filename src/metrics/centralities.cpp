#include "src/metrics/centralities.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace centralities {
	
	void degree(const graph& G, vector<double>& dc) {
		vector<node> nds;
		G.nodes(nds);
		
		const double nm1 = G.n_nodes() - 1;
		dc.clear();
		
		transform(
			// iterate through all nodes
			nds.begin(), nds.end(),
			
			// append value at the back of dc
			back_inserter(dc),
			
			// calculate degree centrality
			[&](size_t u) {
				return G.degree(u)/nm1;
			}
		);
	}
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

