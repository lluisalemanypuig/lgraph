#include <lgraph/metrics/centralities_ux.hpp>

// C++ includes
#include <iostream>
#include <numeric>
using namespace std;

// lgraph includes
#include <lgraph/graph_traversal/traversal_ux.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* CLOSENESS */

double closeness(const uxgraph *G, node u) {
	vector<_new_> ds;
	traversal::uxdistance(G, u, ds);
	double sum = accumulate
	(
		ds.begin(), ds.end(), 0.0,
		[](double acc, _new_ d) {
			// when d == inf, there is not path, so we
			// should not accumulate this distance
			if (d != inf_t<_new_>()) {
				acc += static_cast<double>(d);
			}
			return acc;
		}
	);
	return 1.0/(sum/(G->n_nodes() - 1));
}

void closeness(const uxgraph *G, std::vector<double>& cc) {
	vector<vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return closeness(G, ds, cc);
}

void closeness(
	const uxgraph *G,
	const std::vector<std::vector<_new_> >& ds,
	std::vector<double>& cc
)
{
	transform(
		// iterate through all nodes
		ds.begin(), ds.end(),

		// append value at the back of cc
		back_inserter(cc),

		// calculate closeness centrality
		[&](const vector<_new_>& ds_i) {
			double sum = accumulate
			(
				ds_i.begin(), ds_i.end(), 0.0,
				[](double acc, _new_ d) {
					// when d == inf, there is not path, so we
					// should not accumulate this distance
					if (d != inf_t<_new_>()) {
						acc += static_cast<double>(d);
					}
					return acc;
				}
			);
			return 1.0/(sum/(G->n_nodes() - 1));
		}
	);
}

double mcc(const uxgraph *G) {
	vector<vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	// compute sum of all the distance values.

	double sum = accumulate(
		ds.begin(), ds.end(), 0.0,
		[](double acc, const vector<_new_>& v) -> double {
			// sum of a row, accumulate values below infinte
			_new_ s = accumulate(
				v.begin(), v.end(), static_cast<_new_>(0),
				[](_new_ acc_inner, _new_ d) -> _new_ {
					if (d != inf_t<_new_>()) {
						acc_inner += d;
					}
					return acc_inner;
				}
			);
			// sum of inverse of distances
			return acc + 1.0/s;
		}
	);

	double n = static_cast<double>(G->n_nodes());
	return ((n - 1.0)/n)*sum;
}

double mcc(const uxgraph *G, const std::vector<double>& cc) {
	double S = accumulate(cc.begin(), cc.end(), 0.0);
	return S/G->n_nodes();
}

/* BETWEENNES */

double betweenness(const uxgraph *G, node u) {
	vector<vector<boolean_path_set<_new_> > > all_to_all_paths;
	traversal::uxpaths(G, all_to_all_paths);
	return betweenness(G, all_to_all_paths, u);
}

double betweenness(
	const uxgraph *G,
	const std::vector<std::vector<boolean_path_set<_new_> > >& paths,
	node u
)
{
	double B = 0.0;

	const size_t N = G->n_nodes();
	for (node s = 0; s < N; ++s) {
		for (node t = s + 1; t < N; ++t) {
			if (s == u or t == u) {
				// this should be obvious
				B += 1.0;
				continue;
			}

			// don't do anything if there are no paths from s to t
			if (paths[s][t].size() == 0) {
				continue;
			}

			// amount of shortest paths between s and t in which u lies on
			size_t g_st_i = 0;
			for (const boolean_path<_new_>& bp : paths[s][t]) {
				if (bp[u]) {
					++g_st_i;
				}
			}

			double g_st = paths[s][t].size();

			// calculate the "partial" centrality
			B += g_st_i/g_st;
		}
	}

	// normalise with "(n - 1) choose 2"
	const size_t n_minus_1__chose_2 = ((N - 1)*(N - 2))/2;
	B = B/n_minus_1__chose_2;
	return B;
}

void betweenness(const uxgraph *G, std::vector<double>& bc) {
	vector<vector<boolean_path_set<_new_> > > all_to_all_paths;
	traversal::uxpaths(G, all_to_all_paths);
	betweenness(G, all_to_all_paths, bc);
}

void betweenness(
	const uxgraph *G,
	const std::vector<std::vector<boolean_path_set<_new_> > >& paths,
	std::vector<double>& bc
)
{
	const size_t N = G->n_nodes();

	// amount of shortest paths between s and t in
	// which vertices of the graph lie on
	vector<size_t> g_st_i(N);
	// initialise data
	bc = vector<double>(N, 0);

	for (node s = 0; s < N; ++s) {
		for (node t = s + 1; t < N; ++t) {
			// don't do anything if there are no paths from s to t
			if (paths[s][t].size() == 0) {
				continue;
			}

			// set vector to 0
			fill(g_st_i.begin(), g_st_i.end(), 0);

			for (node u = 0; u < N; ++u) {
				for (const boolean_path<_new_>& bp : paths[s][t]) {
					if (bp[u]) {
						++g_st_i[u];
					}
				}
			}

			double g_st = paths[s][t].size();

			// calculate the "partial" centrality for each node
			for (node u = 0; u < N; ++u) {
				bc[u] += g_st_i[u]/g_st;
			}
		}
	}

	// normalise
	const size_t n_minus_1__chose_2 = ((N - 1)*(N - 2))/2;
	for (node u = 0; u < N; ++u) {
		bc[u] /= n_minus_1__chose_2;
	}
}
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

