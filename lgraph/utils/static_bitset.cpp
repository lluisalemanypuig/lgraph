#include <lgraph/utils/static_bitset.hpp>

// C includes
#include <stdlib.h>
#include <string.h>

// MACROS

#define __uns_char__ unsigned char

#define mod_8(i) (i & 0x07)
#define div_8(i) (i >> 3)
#define is_div_8(i) (mod_8(i) == 0x00)

// ordinary system: 0123 4567 89...
// binary system:   7654 3210 76..

// returns the byte where the i-th bit (in ordinary system) is located at
#define byte(i) div_8(i)

// returns the corresponding bit position (in ordinary system) of the
// corresponding byte in binary system
#define bit_pos(i) (7 - mod_8(i))

// returns the byte corresponding to the i-th bit (in ordinary system)
// with the corresponding bit b set to the specified value
#define   _set_bit(val, i) static_cast<__uns_char__>(val |  (1 << bit_pos(mod_8(i))))
#define _unset_bit(val, i) static_cast<__uns_char__>(val & ~(1 << bit_pos(mod_8(i))))

// returns the i-th bit's value
#define get_bit(val, i) ((val & (0x80 >> mod_8(i))) >> bit_pos(i))

// returns the last byte's bits: if we use this class to store eleven
// bits then the last byte's bits are:  111* **** and returns 0000 0111
#define last_byte(val, nbits) (val >> (8 - mod_8(nbits)))

// PRIVATE

// PUBLIC

namespace lgraph {
namespace utils {

static_bitset::static_bitset() {
	bytes = nullptr;
	n_bytes = n_bits = 0;
}

static_bitset::static_bitset(const std::string& bs) {
	bytes = nullptr;
	n_bytes = n_bits = 0;
	init_01(bs);
}

static_bitset::static_bitset(const std::vector<bool>& bits) {
	bytes = nullptr;
	n_bytes = n_bits = 0;
	init_01(bits);
}

static_bitset::static_bitset(const static_bitset& bs) {
	bytes = nullptr;
	n_bytes = n_bits = 0;
	*this = bs;
}

static_bitset::~static_bitset() {
	clear();
}

// INITIALIZERS

void static_bitset::init(size_t b) {
	// k_bytes = # bytes to be reserved
	size_t k_bytes = (is_div_8(b) ? div_8(b) : div_8(b) + 1);

	// if we already have as many bytes as k_bytes do nothing
	if (n_bytes == k_bytes) {
		n_bits = b;
	}
	else {
		// destroy the currently used memory if necessary ...
		if (bytes != nullptr) {
			clear();
		}

		// ... and reserve the new space
		n_bits = b;
		n_bytes = k_bytes;
		bytes = static_cast<__uns_char__ *>(malloc(n_bytes*sizeof(unsigned char)));
	}
}

void static_bitset::init_set(size_t n_bits) {
	init(n_bits);
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = 0xff;
	}
}

void static_bitset::init_unset(size_t n_bits) {
	init(n_bits);
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = 0;
	}
}

void static_bitset::init_01(const std::string& zerones) {
	init_unset(zerones.length());
	for (size_t i = 0; i < n_bits; ++i) {
		if (zerones[i] == '1') {
			bytes[byte(i)] = _set_bit(bytes[byte(i)], i);
		}
	}
}

void static_bitset::init_01(const std::vector<bool>& bits) {
	init_unset(bits.size());
	for (size_t i = 0; i < n_bits; ++i) {
		if (bits[i]) {
			bytes[byte(i)] = _set_bit(bytes[byte(i)], i);
		}
	}
}

void static_bitset::init_bytes(const std::vector<char>& bts) {
	init(8*bts.size());
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = static_cast<__uns_char__>(bts[i]);
	}
}

void static_bitset::init_bytes(const std::string& bts) {
	init(8*bts.length());
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = static_cast<__uns_char__>(bts[i]);
	}
}

void static_bitset::clear() {
	if (bytes != nullptr) {
		free(bytes);
		bytes = nullptr;
	}
}

// OPERATORS

static_bitset& static_bitset::operator= (const static_bitset& bs) {
	init(bs.n_bits);
	bytes = static_cast<__uns_char__ *>(
		memcpy(
			static_cast<void *>(bytes),
			static_cast<void *>(bs.bytes),
			n_bytes
		)
	);
	return *this;
}

bool static_bitset::operator[] (size_t i) const {
	return get_bit(bytes[byte(i)], i);
}

static_bitset static_bitset::operator<= (const static_bitset& bs) const {
	static_bitset copy = *this;
	for (size_t b = 0; b < n_bytes; ++b) {
		copy.bytes[b] = ~bytes[b] | bs.bytes[b];
	}
	return copy;
}

static_bitset static_bitset::operator~ () const {
	static_bitset copy = *this;
	copy.flip();
	return copy;
}

static_bitset static_bitset::operator- (const static_bitset& bs) const {
	static_bitset copy = *this;
	copy -= bs;
	return copy;
}

static_bitset static_bitset::operator& (const static_bitset& bs) const {
	static_bitset copy = *this;
	copy &= bs;
	return copy;
}

static_bitset static_bitset::operator| (const static_bitset& bs) const {
	static_bitset copy = *this;
	copy |= bs;
	return copy;
}
static_bitset static_bitset::operator^ (const static_bitset& bs) const {
	static_bitset copy = *this;
	copy ^= bs;
	return copy;
}

static_bitset static_bitset::operator== (const static_bitset& bs) const {
	static_bitset copy = *this;
	for (size_t b = 0; b < n_bytes; ++b) {
		copy.bytes[b] = ~(bytes[b]^bs.bytes[b]);
	}
	return copy;
}

static_bitset& static_bitset::operator-= (const static_bitset& bs) {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] &= ~bs.bytes[b];
	}
	return *this;
}

static_bitset& static_bitset::operator&= (const static_bitset& bs) {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] &= bs.bytes[b];
	}
	return *this;
}

static_bitset& static_bitset::operator|= (const static_bitset& bs) {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] |= bs.bytes[b];
	}
	return *this;
}

static_bitset& static_bitset::operator^= (const static_bitset& bs) {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] ^= bs.bytes[b];
	}
	return *this;
}

static_bitset& static_bitset::operator+= (char k) {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] += k;
	}
	return *this;
}

// SETTERS

void static_bitset::set_all() {
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = 0xff;
	}
}

void static_bitset::unset_all() {
	for (size_t i = 0; i < n_bytes; ++i) {
		bytes[i] = 0;
	}
}

void static_bitset::set_bit(size_t i) {
	bytes[byte(i)] = _set_bit(bytes[byte(i)], i);
}

void static_bitset::unset_bit(size_t i) {
	bytes[byte(i)] = _unset_bit(bytes[byte(i)], i);
}

void static_bitset::flip() {
	for (size_t b = 0; b < n_bytes; ++b) {
		bytes[b] = ~bytes[b];
	}
}

void static_bitset::swap(static_bitset& bs) {
	for (size_t b = 0; b < n_bytes; ++b) {
		std::swap(bytes[b], bs.bytes[b]);
	}
}

// GETTERS

size_t static_bitset::size() const {
	return n_bits;
}

bool static_bitset::equal(const static_bitset& bs) const {
	size_t b = 0;
	size_t check_last = mod_8(n_bits) != 0;

	while ((b < n_bytes - check_last) and bytes[b] == bs.bytes[b]) {
		++b;
	}

	if (check_last == 0) {
		//if (b < n_bytes) return false;
		//return true;
		return b >= n_bytes;
	}
	if (b < n_bytes - check_last) {
		return false;
	}

	unsigned char last_this = last_byte(bytes[n_bytes - 1], n_bits);
	unsigned char last_bs = last_byte(bs.bytes[bs.n_bytes - 1], n_bits);
	return last_this == last_bs;
}

bool static_bitset::included(const static_bitset& bs) const {
	unsigned char IN = 0xff;
	size_t b = 0;
	size_t check_last = mod_8(n_bits) != 0;

	while ((b < n_bytes - check_last) and IN == 0xff) {
		IN = (~bytes[b] | bs.bytes[b]);
		++b;
	}

	if (IN != 0xff) {
		return false;
	}
	if (check_last == 0) {
		return IN;
	}

	unsigned char last_this = last_byte(bytes[n_bytes - 1], n_bits);
	unsigned char last_bs = last_byte(bs.bytes[bs.n_bytes - 1], n_bits);
	unsigned char last_bits_mask = 0xff >> (8 - mod_8(n_bits));
	return ((~last_this | last_bs) & last_bits_mask) == last_bits_mask;
}

bool static_bitset::all() const {
	size_t b = 0;
	size_t check_last = mod_8(n_bits) != 0;

	while ((b < n_bytes - check_last) and bytes[b] == 0xff) {
		++b;
	}

	if (check_last == 0) {
		//if (b < n_bytes) return false;
		//return true;
		return b >= n_bytes;
	}
	if (b < n_bytes - check_last) {
		return false;
	}

	unsigned char last = last_byte(bytes[n_bytes - 1], n_bits);
	unsigned char sign = static_cast<__uns_char__>(1 << mod_8(n_bits)) - 1;
	return last == sign;
}

bool static_bitset::any() const {
	size_t b = 0;
	size_t check_last = size_t(mod_8(n_bits) != 0);

	while ((b < n_bytes - check_last) and bytes[b] == 0x00) {
		++b;
	}

	if (check_last == 0) {
		//if (b < n_bytes) return true;
		//return false;
		return b < n_bytes;
	}
	if (b < n_bytes - check_last) {
		return true;
	}

	// the last byte may no be complete: 9 bits are: 1 byte and 1 bit
	return last_byte(bytes[n_bytes - 1], n_bits) != 0x00;
}

bool static_bitset::none() const {
	size_t b = 0;
	size_t check_last = mod_8(n_bits) != 0;

	while ((b < n_bytes - check_last) and bytes[b] == 0x00) {
		++b;
	}

	if (check_last == 0) {
		//if (b < n_bytes) return false;
		//return true;
		return b == n_bytes;
	}
	if (b < n_bytes - check_last) {
		return false;
	}

	// the last byte may no be complete: 9 bits are: 1 byte and 1 bit
	return last_byte(bytes[n_bytes - 1], n_bits) == 0x00;
}

void static_bitset::which(std::vector<size_t>& w) const {
	w.resize(0);
	for (size_t b = 0; b < n_bits; ++b) {
		if (get_bit(bytes[byte(b)], b)) {
			w.push_back(b);
		}
	}
}

size_t static_bitset::count() const {
	const size_t rem = mod_8(n_bits);
	const size_t check_last = rem != 0;

	size_t c = 0;
	for (size_t b = 0; b < n_bytes - check_last; ++b) {
		c +=	((0x80 & bytes[b]) >> 7) +
				((0x40 & bytes[b]) >> 6) +
				((0x20 & bytes[b]) >> 5) +
				((0x10 & bytes[b]) >> 4) +
				((0x08 & bytes[b]) >> 3) +
				((0x04 & bytes[b]) >> 2) +
				((0x02 & bytes[b]) >> 1) +
				((0x01 & bytes[b]) >> 0);
	}

	unsigned char last = bytes[n_bytes - 1];

	switch (rem) {
		case 7: c += ((0x02 & last) >> 1); [[clang::fallthrough]];
		case 6: c += ((0x04 & last) >> 2); [[clang::fallthrough]];
		case 5: c += ((0x08 & last) >> 3); [[clang::fallthrough]];
		case 4: c += ((0x10 & last) >> 4); [[clang::fallthrough]];
		case 3: c += ((0x20 & last) >> 5); [[clang::fallthrough]];
		case 2: c += ((0x40 & last) >> 6); [[clang::fallthrough]];
		case 1: c += ((0x80 & last) >> 7); [[clang::fallthrough]];
		default: break;
	}
	return c;
}

void static_bitset::get_01(std::string& s, const std::string& sep) const {
	const size_t rem = mod_8(n_bits);
	const size_t check_last = rem != 0;

	s = "";
	for (size_t b = 0; b < n_bytes - check_last; ++b) {
		s += char('0' + ((0x80 & bytes[b]) >> 7));
		s += char('0' + ((0x40 & bytes[b]) >> 6));
		s += char('0' + ((0x20 & bytes[b]) >> 5));
		s += char('0' + ((0x10 & bytes[b]) >> 4));
		s += char('0' + ((0x08 & bytes[b]) >> 3));
		s += char('0' + ((0x04 & bytes[b]) >> 2));
		s += char('0' + ((0x02 & bytes[b]) >> 1));
		s += char('0' + ((0x01 & bytes[b]) >> 0));
		s += sep;
	}

	if (rem == 0) {
		// remove the last sep
		s.pop_back();
	}

	unsigned char last = bytes[n_bytes - 1];
	switch (rem) {
		case 7: s += char('0' + ((0x02 & last) >> 1)); [[clang::fallthrough]];
		case 6: s += char('0' + ((0x04 & last) >> 2)); [[clang::fallthrough]];
		case 5: s += char('0' + ((0x08 & last) >> 3)); [[clang::fallthrough]];
		case 4: s += char('0' + ((0x10 & last) >> 4)); [[clang::fallthrough]];
		case 3: s += char('0' + ((0x20 & last) >> 5)); [[clang::fallthrough]];
		case 2: s += char('0' + ((0x40 & last) >> 6)); [[clang::fallthrough]];
		case 1: s += char('0' + ((0x80 & last) >> 7)); [[clang::fallthrough]];
		default: break;
	}
}

std::string static_bitset::get_01(const std::string& sep) const {
	std::string s;
	get_01(s, sep);
	return s;
}

void static_bitset::get_01(std::vector<bool>& v) const {
	const size_t rem = mod_8(n_bits);
	const size_t check_last = rem != 0;
	size_t b8;

	v.resize(n_bits, false);
	for (size_t b = 0; b < n_bytes - check_last; ++b) {
		b8 = b << 3;

		v[b8    ] = ((0x80 & bytes[b]) >> 7);
		v[b8 + 1] = ((0x40 & bytes[b]) >> 6);
		v[b8 + 2] = ((0x20 & bytes[b]) >> 5);
		v[b8 + 3] = ((0x10 & bytes[b]) >> 4);
		v[b8 + 4] = ((0x08 & bytes[b]) >> 3);
		v[b8 + 5] = ((0x04 & bytes[b]) >> 2);
		v[b8 + 6] = ((0x02 & bytes[b]) >> 1);
		v[b8 + 7] = ((0x01 & bytes[b]) >> 0);
	}

	b8 = 8*(n_bytes - 1);
	unsigned char last = bytes[n_bytes - 1];
	switch (rem) {
		case 7: v[b8 + 6] = ((0x02 & last) >> 1); [[clang::fallthrough]];
		case 6: v[b8 + 5] = ((0x04 & last) >> 2); [[clang::fallthrough]];
		case 5: v[b8 + 4] = ((0x08 & last) >> 3); [[clang::fallthrough]];
		case 4: v[b8 + 3] = ((0x10 & last) >> 4); [[clang::fallthrough]];
		case 3: v[b8 + 2] = ((0x20 & last) >> 5); [[clang::fallthrough]];
		case 2: v[b8 + 1] = ((0x40 & last) >> 6); [[clang::fallthrough]];
		case 1: v[b8    ] = ((0x80 & last) >> 7); [[clang::fallthrough]];
		default: break;
	}
}

std::vector<bool> static_bitset::get_01() const {
	std::vector<bool> v;
	get_01(v);
	return v;
}

void static_bitset::append_bytes(std::string& s) const {
	for (size_t k = 0; k < n_bytes; ++k) {
		s += bytes[k];
	}
}

void static_bitset::get_bytes(std::string& s) const {
	s.resize(n_bytes);
	for (size_t k = 0; k < n_bytes; ++k) {
		s[k] = static_cast<char>(bytes[k]);
	}
}

std::string static_bitset::get_bytes() const {
	std::string s;
	get_bytes(s);
	return s;
}

} // -- namespace utils
} // -- namespace lgraph
