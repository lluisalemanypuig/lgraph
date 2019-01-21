#include <lgraph/data_structures/node_path.hpp>

namespace lgraph {

// PUBLIC

template<class T>
node_path<T>::node_path() {
	 nodes = std::vector<node>();
	 path_length = 0;
}

template<class T>
node_path<T>::node_path(node n) {
	nodes = std::vector<node>(1, n);
	path_length = 0;
}

template<class T>
node_path<T>::~node_path() { }

template<class T>
void node_path<T>::empty() {
	nodes = std::vector<node>();
	path_length = 0;
}

// OPERATORS

template<class T>
node node_path<T>::operator[] (size_t i) const {
	return nodes[i];
}

template<class T>
node& node_path<T>::operator[] (size_t i) {
	return nodes[i];
}

template<class T>
bool node_path<T>::operator< (const node_path<T>& p) const {
	return path_length < p.path_length;
}

template<class T>
bool node_path<T>::operator> (const node_path<T>& p) const {
	return path_length > p.path_length;
}

template<class T>
node_path<T>& node_path<T>::operator= (const node_path<T>& np) {
	nodes = np.nodes;
	path_length = np.path_length;
	return *this;
}

// MODIFIERS

template<class T>
void node_path<T>::concatenate(const node_path<T>& p) {
	if (p.size() > 1) {
		nodes.insert(
			nodes.end(),
			p.nodes.begin() + 1, p.nodes.end()
		);
		path_length += p.path_length;
	}
}

template<class T>
void node_path<T>::add_node(node u) {
	assert(u >= 0);
	nodes.push_back(u);
}

template<class T>
void node_path<T>::add_length(const T& l) {
	path_length += l;
}

template<class T>
void node_path<T>::set_length(const T& l) {
	path_length = l;
}

template<class T>
void node_path<T>::reverse() {
	std::reverse(nodes.begin(), nodes.end());
}

template<class T>
void node_path<T>::delete_last() {
	nodes.pop_back();
}

// GETTERS

template<class T>
size_t node_path<T>::size() const {
	return nodes.size();
}

template<class T>
T node_path<T>::get_length() const {
	return path_length;
}

template<class T>
node node_path<T>::last_node() const {
	return nodes.back();
}

template<class T>
const std::vector<node>& node_path<T>::get_nodes() const {
	return nodes;
}

template<class T>
std::string node_path<T>::to_string() const {
	std::string s;
	to_string(s);
	return s;
}

template<class T>
void node_path<T>::to_string(std::string& s) const {
	if (nodes.size() > 0) {
		s = std::to_string(nodes[0]);
		for (size_t i = 1; i < nodes.size(); ++i) {
			s += " -> " + std::to_string(nodes[i]);
		}
	}
}

} // -- namespace lgraph
