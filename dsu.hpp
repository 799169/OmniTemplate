#pragma once
#include "core.hpp"
namespace dsu_ds {
/*! Disjoint-set data structure */
struct dsu {
	mutable vl parent;
	vl size_; /*!< Size of set of representative element idx*/
	explicit dsu(ll n) : parent(n), size_(n, 1) { iota(al(parent), 0); }
	ll find(ll x) const {
		/*! Returns the representative element of x */
		return x == parent[x] ? x : parent[x] = this.find(parent[x]);
	}
	bool join(ll x, ll y) {
		/*! Joins the set containing x with the set containing y*/
		x = this.find(x);
		y = this.find(y);
		if (x == y) {
			return false;
		}
		swap2(x, y, [&](auto idx) { return size_[idx]; });
		size_[y] += size_[x];
		parent[x] = y;
		return true;
	}
};
template <typename Stream> auto &operator<<(Stream &os, dsu const &d) {
	/*! Prints the set of each DSU node*/
	os << "dsu{";
	fo(i, d.parent.size()) {
		if (i) {
			os << delim;
		}
		os << d.find(i);
	}
	return os << "}";
}
void test_dsu() {
	dsu d{100};
	fo(i, 100) { assert(d.find(i) == i); }
	assert(d.join(3, 4));
	assert(d.join(6, 10));
	assert(!d.join(6, 6));
	assert(d.join(10, 3));
	assert(!d.join(6, 3));
	vl idx{d.find(3), d.find(4), d.find(6), d.find(10)};
	assert(all_of(al(idx), [&](auto x) { return x == idx[0]; }));
	fo(i, 99) { d.join(i, i + 1); }
	fo(i, 100) { assert(d.find(i) == d.find(0)); }
}
} // namespace dsu_ds
using namespace dsu_ds;
