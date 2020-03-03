/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 *
 ********************************************************************/

// C includes
#include <string.h>

// C++ includes
#include <iostream>
using namespace std;

// Custom includes
#include "driver.hpp"

#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/wxgraph.hpp>
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/data_structures/uxgraph.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>

int main(int argc, char *argv[]) {
	cout << "lgraph Copyright (C) 2018-2019 Lluís Alemany Puig" << endl;
	cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'." << endl;
	cout << "This is free software, and you are welcome to redistribute it" << endl;
	cout << "under certain conditions; type `show c' for details." << endl;

	bool directed = false;
	bool weighted = false;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--weighted") == 0) {
			weighted = true;
		}
		else if (strcmp(argv[i], "--unweighted") == 0) {
			weighted = false;
		}
		else if (strcmp(argv[i], "--directed") == 0) {
			directed = true;
		}
		else if (strcmp(argv[i], "--undirected") == 0) {
			directed = false;
		}
		else {
			cerr << "Error: option not recognised" << endl;
			return 1;
		}
	}

	if (weighted) {
		cout << "Execute driver for weighted graphs" << endl;
		graph_driver::driver_weighted(directed);
	}
	else {
		cout << "Execute driver for unweighted graphs" << endl;
		graph_driver::driver_unweighted(directed);
	}
}
