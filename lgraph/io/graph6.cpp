#include <lgraph/io/gsd6.hpp>

namespace lgraph {
namespace io {
namespace graph6 {

	void graph_from_g6_string(const string& s, uugraph& g) {

	}

	void graph_to_g6_string(const uugraph& g, string& s) {

	}

	// -- READING --

	bool read(const string& filename, uugraph& g) {
		return read(filename.c_str(), g);
	}

	bool read(const char *filename, uugraph& g) {
		ifstream fin;
		fin.open(filename);
		if (not fin.is_open()) {
			return false;
		}

		// Bear in mind that the file may contain
		// several lines, but only one will be read.

		string data = "";
		while (data == "" or data == ">>graph6<<") {
			fin >> data;
		}

		// ignore the other lines
		fin.close();

		// parse the graph
		graph_from_g6_string(data, g);
		return true;
	}

	bool read(const string& filename, vector<uugraph>& gs) {
		return read(filename.c_str(), gs);
	}

	bool read(const char *filename, vector<uugraph>& gs) {
		ifstream fin;
		fin.open(filename);
		if (not fin.is_open()) {
			return false;
		}

		// Bear in mind that the file may contain
		// several lines, but only one will be read.

		string data = "";
		while (data == "" or data == ">>graph6<<") {
			fin >> data;
		}

		do {
			uugraph g;
			graph_from_g6_string(data, g);
			gs.push_back(g);
		}
		while (fin >> data);

		fin.close();
		return true;
	}

	// -- WRITING --

	bool write(const string& filename, const uugraph& g) {
		return write(filename.c_str(), g);
	}

	bool write(const char *filename, const uugraph& g) {
		ofstream fout;
		fout.open(filename, ios_base::app);
		if (not fout.is_open()) {
			return false;
		}

		// convert
		string data;
		graph_to_g6_string(g, data);

		// write
		fout << data << endl;
		fout.close();

		return true;
	}

} // -- namespace graph6
} // -- namespace io
} // -- namespace lgraph
