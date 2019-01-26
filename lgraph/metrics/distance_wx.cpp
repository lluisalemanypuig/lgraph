#include <lgraph/metrics/distance_wx.hpp>

// lgraph includes
#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/metrics/centralities_wx.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

template<class T>
T max_distance(const wxgraph<T> *G) {
	std::vector<std::vector<T> > ds;
	traversal::wxdistances(G, ds);
	return max_distance(G, ds);
}

template<class T>
T max_distance(const wxgraph<T> *G, const std::vector<std::vector<T> >& ds) {
	const size_t N = G->n_nodes();
	T D = 0;
	for (size_t i = 0; i < N; ++i) {
		D = accumulate
		(
			ds[i].begin() + i + 1, ds[i].end(), D,
			[](T M, T d) {
				if (d != inf_t<T>()) {
					M = std::max(M, d);
				}
				return M;
			}
		);
	}
	return D;
}

template<class T>
double mean_distance(const wxgraph<T> *G) {
	std::vector<std::vector<T> > ds;
	traversal::wxdistances(G, ds);
	return mean_distance(G, ds);
}

template<class T>
double mean_distance(const wxgraph<T> *G, const std::vector<std::vector<T> >& ds) {
	const size_t N = G->n_nodes();
	double m = 0;
	for (size_t i = 0; i < N; ++i) {

		// sum values only if they are not infinite
		double li = accumulate
		(
			ds[i].begin(), ds[i].end(), 0.0,
			[](double acc, T d) {
				if (d != inf_t<T>()) {
					acc += d;
				}
				return acc;
			}
		);
		// divide by (N - 1) because ds[i][i] = 0
		li /= (N - 1);

		m += li;
	}
	return m/N;
}

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks
} // -- namespace lgraph

