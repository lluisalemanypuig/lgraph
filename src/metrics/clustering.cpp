#include "src/metrics/clustering.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace clustering {

	double gcc(const graph& G) {
		size_t T = 0;
		size_t connected_triples = 0;
		const size_t N = G.n_nodes();
		
		// for each vertex u ...
		for (size_t u = 0; u < N; ++u) {
			
			const neighbourhood& neigh_u = G.get_neighbours(u);
			for (lcit v = neigh_u.begin(); v != neigh_u.end(); ++v) {
				
				lcit w = v; ++w;
				for (; w != neigh_u.end(); ++w) {
					// ... get two different neighbours of u (v, w) and
					// check if they are connected. If so, we found a triangle
					if (v != w and G.has_edge(*v, *w)) ++T;
				}
				
				// ... and count the connected triples as the number of
				// neighbours minus one (because one vertex is u)
				connected_triples += G.degree(*v) - 1;
			}
		}
		
		// each triplet is counted twice!
		connected_triples /= 2;
		
		// this formula does not need a leading 3* because triangles are
		// counted three times each already!
		return (1.0*T)/(connected_triples);
	}
	
	double mlcc(const graph& G) {
		double Cws = 0.0;
		const size_t N = G.n_nodes();
		
		// for each vertex u ...
		for (size_t u = 0; u < N; ++u) {
			
			// The contribution of those nodes with degree less than 2
			// to to coefficient is for sure 0 because it is sure that
			// they cannot form a triangle. Besides, the number of pairs
			// will be equal to 0 (division by zero!)
			size_t nu = G.degree(u);
			if (nu >= 2) {
				size_t T = 0;
				
				const neighbourhood& neigh_u = G.get_neighbours(u);
				for (lcit v = neigh_u.begin(); v != neigh_u.end(); ++v) {
					
					lcit w = v; ++w;
					for (; w != neigh_u.end(); ++w) {
						// ... get two different neighbours of u (v, w) and
						// check if there is a connection.
						if (*v != *w and G.has_edge(*v, *w)) ++T;
					}
				}
				
				// double n_pairs = nu*(nu - 1)/2.0;
				// Cws += T/n_pairs;
				// we know that n_pairs > 0 because nu >= 2
				Cws += (2.0*T)/(nu*(nu - 1));
			}
		}
		
		return Cws/N;
	}

} // -- namespace clustering
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

