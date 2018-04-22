#include "node_path.hpp"

namespace dsa {
namespace utils {

/// PUBLIC

template<class T>
node_path<T>::node_path() {
	 nodes = vector<node>();
	 path_length = 0;
}

template<class T>
node_path<T>::node_path(node n) {
	nodes = vector<node>(1, n);
	path_length = 0;
}

template<class T>
node_path<T>::~node_path() { }

template<class T>
void node_path<T>::empty() {
	nodes = vector<node>();
	path_length = 0;
}

/// OPERATORS

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

/// MODIFIERS

template<class T>
void node_path<T>::concatenate(const node_path<T>& p) {
	nodes.insert(
		nodes.end(),
		p.nodes.begin() + 1, p.nodes.end()
	);
	path_length += p.path_length;
}

template<class T>
void node_path<T>::add_node(node u) {
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

/// GETTERS

template<class T>
size_t node_path<T>::size() const {
	return nodes.size();
}

template<class T>
T node_path<T>::get_length() const {
	return path_length;
}

template<class T>
size_t node_path<T>::last_node() const {
	return nodes.back();
}

template<class T>
const vector<node>& node_path<T>::get_nodes() const {
	return nodes;
}

} // -- namespace utils
} // -- namespace dsa