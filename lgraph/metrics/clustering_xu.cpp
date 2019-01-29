#include <lgraph/metrics/clustering_xu.hpp>

// C includes
#include <assert.h>

namespace lgraph {
namespace networks {
namespace metrics {
namespace clustering {

double gcc(const xxgraph *G) {
	assert(not G->is_directed());

	size_t T = 0;
	size_t connected_triples = 0;
	const size_t N = G->n_nodes();

	// for each vertex u ...
	for (size_t u = 0; u < N; ++u) {

		const neighbourhood& nu = G->get_neighbours(u);
		for (size_t v_it = 0; v_it < nu.size(); ++v_it) {
			node v = nu[v_it];

			for (size_t w_it = v_it + 1; w_it < nu.size(); ++w_it) {
				node w = nu[w_it];
				// ... get two different neighbours of u (v, w) and
				// check if they are connected. If so, we found a triangle
				if (v != w and G->has_edge(v, w)) {
					++T;
				}
			}

			// ... and count the connected triples as the number of
			// neighbours minus one (because one vertex is u)
			connected_triples += G->degree(v) - 1;
		}
	}

	// each triplet is counted twice!
	connected_triples /= 2;

	// this formula does not need a leading 3* because triangles are
	// counted three times each already!
	return (1.0*T)/(connected_triples);
}

double mlcc(const xxgraph *G) {
	assert(not G->is_directed());

	double Cws = 0.0;
	const size_t N = G->n_nodes();

	// for each vertex u ...
	for (size_t u = 0; u < N; ++u) {

		// The contribution of those nodes with degree less than 2 to
		// the coefficient is for sure 0 because we can be certain that
		// they cannot form a triangle. Besides, the number of pairs
		// will be equal to 0 (division by zero!)
		size_t du = G->degree(u);
		if (du < 2) {
			continue;
		}

		size_t T = 0;

		const neighbourhood& nu = G->get_neighbours(u);
		for (size_t v_it = 0; v_it < nu.size(); ++v_it) {
			node v = nu[v_it];

			for (size_t w_it = v_it + 1; w_it < nu.size(); ++w_it) {
				node w = nu[w_it];

				// ... get two different neighbours of u (v, w) and
				// check if there is a connection.
				if (v != w and G->has_edge(v, w)) {
					++T;
				}
			}
		}

		// double n_pairs = nu*(nu - 1)/2.0;
		// Cws += T/n_pairs;
		// we know that n_pairs > 0 because nu >= 2
		Cws += (2.0*T)/(du*(du - 1));
	}

	return Cws/N;
}

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

