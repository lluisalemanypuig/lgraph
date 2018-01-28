/// C includes
#include <string.h>

/// C++ includes
#include <iostream>
#include <map>
using namespace std;

/// Custom includes
#include "src/random_graphs/barabasi_albert.hpp"
#include "src/random_graphs/switching.hpp"
#include "src/random_generator.hpp"
#include "src/digraph.hpp"
using namespace dsa;
using namespace utils;

void print_usage() {
	cout << "Help of this program" << endl;
	cout << " [-h, --help]: show the usage of this program" << endl;
	cout << "    Model selection parameters:" << endl;
	cout << "        -pa: Generate Barabasi-Albert model with preferential attachment" << endl;
	cout << "        -ra: Generate Barabasi-Albert model with random attachment" << endl;
	cout << "        -ng: Generate Barabasi-Albert model without vertex growth" << endl;
	cout << "        -sw: Generate a switching model graph. This option requires" << endl;
	cout << "             the selection of one of these models this model will:" << endl;
	cout << "             be applied on:" << endl;
	cout << "             - Barabasi-Albert model (any of its variants)" << endl;
	cout << "    Barabasi-Albert model configuration parameters:" << endl;
	cout << "        -T:   Number of steps of the simulation" << endl;
	cout << "        --n0: Initial number of vertices" << endl;
	cout << "        --m0: Number of edges added at each step" << endl;
	cout << "    Switching model configuration parameters:" << endl;
	cout << "        -Q:   The switching model will run for Q*|E| steps." << endl;
	cout << "    Other options" << endl;
	cout << "        --seed: Seed the random number generator" << endl;
}

int main(int argc, char *argv[]) {
	
	string model = "none";
	
	size_t n0 = 10;
	size_t m0 = 5;
	size_t T = 7;

	bool seed = false;

	bool apply_switching = false;
	size_t Q = 0;
	
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 or strcmp(argv[i], "--help") == 0) {
			print_usage();
			return 1;
		}
		else if (strcmp(argv[i], "-pa") == 0) {
			model = "preferential";
		}
		else if (strcmp(argv[i], "-ra") == 0) {
			model = "random";
		}
		else if (strcmp(argv[i], "-ng") == 0) {
			model = "no-growth";
		}
		else if (strcmp(argv[i], "-sw") == 0) {
			apply_switching = true;
		}
		else if (strcmp(argv[i], "-T") == 0) {
			T = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--n0") == 0) {
			n0 = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--m0") == 0) {
			m0 = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--seed") == 0) {
			seed = true;
		}
		else if (strcmp(argv[i], "-Q") == 0) {
			Q = atoi(argv[i + 1]);
			++i;
		}
		else {
			cerr << "Warning: option '" << string(argv[i]) << "' not recognized" << endl;
			cerr << "    See usage with [-h, --help]" << endl;
			return 1;
		}
	}
	
	if (model == "none") {
		cerr << "Error: no model selected." << endl;
		cerr << "    Use [-h, --help] to see the usage" << endl;
		return 1;
	}
	
	drandom_generator<> *rg = new drandom_generator<>();
	if (seed) rg->seed_random_engine();
	
	graphs::digraph Gs;
	
	if (model == "preferential") {
		graphs::random::Barabasi_Albert::preferential_attachment(n0, m0, T, rg, Gs);
	}
	else if (model == "random") {
		graphs::random::Barabasi_Albert::random_attachment(n0, m0, T, rg, Gs);
	}
	else if (model == "no-growth") {
		graphs::random::Barabasi_Albert::no_vertex_growth(n0, m0, T, rg, Gs);
	}
	
	if (apply_switching) {
		graphs::random::switching::switching_model(Q, rg, Gs);
	}

	cout << Gs << endl;
	
	
	// free memory
	delete rg;
}

