#include "functions.hpp"

namespace functions {

	template<class T>
	void print_distance_matrix(const vector<vector<T> >& dist, const vector<vector<size_t> >& n_paths) {
		const size_t N = dist.size();

		const size_t max_node_length = std::to_string(N - 1).length();
		vector<size_t> max_column(N, 0);
		size_t row_width = 1;
		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {
				size_t length_dist = std::to_string(dist[v][u]).length();
				if (dist[v][u] == utils::inf_t<T>()) {
					length_dist = 3; // use 'inf'
				}

				size_t n_paths_length = std::to_string(n_paths[v][u]).length();

				// '|' + ' ' + dist_length + ' ' + '(' + length_n_paths + ')'
				size_t cell_length = 1 + 1 + length_dist + 1 + 1 + n_paths_length + 1;

				max_column[u] = max(max_column[u], cell_length);
			}
			max_column[u] = max(max_column[u], 2 + std::to_string(u).length());
			row_width += max_column[u] + 1;
		}

		cout << setw(max_node_length) << " " << " ";
		for (size_t u = 0; u < N; ++u) {
			cout << left << setw(max_column[u]) << "| " + std::to_string(u) << " ";
		}
		cout << endl;

		cout << string(row_width, '-') << endl;

		setiosflags(ios::left);
		for (size_t u = 0; u < N; ++u) {
			cout << setw(max_node_length) << u << " ";
			for (size_t v = 0; v < N; ++v) {
				cout << setw(max_column[v]);

				if (dist[u][v] == utils::inf_t<T>()) {
					cout << "| inf (" + std::to_string(n_paths[u][v]) + ")";
				}
				else {
					cout << "| " + std::to_string(dist[u][v]) + " (" + std::to_string(n_paths[u][v]) + ")";
				}
				cout << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

}
