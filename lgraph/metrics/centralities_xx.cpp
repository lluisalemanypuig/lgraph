#include <lgraph/metrics/centralities_xx.hpp>

// C++ includes
using namespace std;

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* DEGREE */

double degree(const xxgraph *G, node u) {
	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	return G->degree(u)/nm1;
}

void degree(const xxgraph *G, std::vector<double>& dc) {
	vector<node> nds;
	G->nodes(nds);

	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	dc.clear();

	transform(
		// iterate through all nodes
		nds.begin(), nds.end(),

		// append value at the back of dc
		back_inserter(dc),

		// calculate degree centrality
		[&](node u) {
			return G->degree(u)/nm1;
		}
	);
}

} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph
