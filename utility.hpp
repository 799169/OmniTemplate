#pragma once
#include "core.hpp"
// TODO templatize this
struct with {
	/*! Sets v to new_ temporary while with object is alive */
	ll old; //!< Original value of the variable
	ll &v;	//!< Reference to variable
	[[nodiscard]] with(ll new_, ll &v_) : old(v_), v(v_) { v = new_; }
	~with() { v = old; }
};
void test_with() {
	ll var = 12;
	auto inner_func = [&]() {
		with _w(23, var);
		assert(var == 23);
		var = 45;
	};
	inner_func();
	assert(var == 12);
}
template <typename Func> struct fix {
	/*! Helper for lambda recursive functions. The recursive function is
	 * passed to Func as the first argument.*/
	Func func;
	fix(const Func &func_) : func(func_) {}
	template <typename... Ts> auto operator()(Ts &&... args) const {
		return func(this, forward<decltype(args)>(args)...);
	}
};
#define lambda(f) [&](auto... args) { return f(args...); }
template <typename T> auto maxeq(T &&x, const T &y) { x = max(x, y); }
template <typename T> auto mineq(T &&x, const T &y) { x = min(x, y); }
template <typename T> auto cache(const T &f) {
	/*! Cache calls to f using a map of type T*/
	T ch;
	return [=](const auto &arg) mutable {
		if (ch.find(arg) == end(ch)) {
			ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
// TODO why doesn't [[nodiscard]] generated a compiler warning?
template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
[[nodiscard]] auto uniq(Cont v, Eq const &up = Eq{}, T const &sp = T{}) {
	/*! Remove all duplicates element from v so that all elements in v are
	 * distinct and sorted */
	sort(al(v), sp);
	v.resize(unique(al(v), up) - begin(v));
	return v;
}
void test_uniq() {
	assert((uniq(vl{2, -1, 3, -1, 2, 3}) == vl{-1, 2, 3}));
	assert((uniq<equal_to<>, greater<>>(vl{1, -3, 5}) == vl{5, 1, -3}));
}
template <typename T = less<>, typename Func>
auto map_args(const Func &f, T g = T{}) {
	return [&](const auto &... args) { return g(f(args)...); };
}
void test_map_args() {
	vl a{24, 25};
	assert(map_args<greater<>>([&](ll i) { return a[i]; })(1, 0));
}
template <typename T> auto prev_less(const T &v) {
	ll n = v.size();
	vl l(n, -1);
	stack<ll> s;
	fo(i, n) {
		while (s.size() && !(s.top() < v[i])) {
			s.pop();
		}
		if (s.size()) {
			l[i] = s.top();
		}
		s.push(v[i]);
	}
	return l;
}
ll nx2(ll x) {
	/*! Return the smallest power of two at least x*/
	if (x == 0) {
		return 1;
	}
	return 1LL << ll(ceil(log2(lli(x))));
}
void test_nx2() {
	assert(nx2(0) == 1);
	assert(nx2(1) == 1);
	assert(nx2(2) == 2);
	assert(nx2(3) == 4);
	assert(nx2(4) == 4);
	assert(nx2(5) == 8);
	assert(nx2((1LL << 45) - 100) == 1LL << 45);
	assert(nx2((1LL << 45)) == 1LL << 45);
}
[[nodiscard]] ll next_comb(ll x) {
	/*! Formally, returns the smallest integer y > x such that popcount(y) =
	 * popcount(x). Note, such y must exist. */
	// Uses algorithm from some blog online, I think
	// TODO credit author
	ll tz = __builtin_ctzll(x);
	ll y = x + (ll{1} << tz);
	const auto ret = y | (y ^ x) >> (2 + tz);
	assert(ret > x);
	assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
	return ret;
}
void test_next_comb() {
	ll x = 0b111;
	x = next_comb(x);
	assert(x == 0b1011);
	x = next_comb(x);
	assert(x == 0b1101);
	x = next_comb(x);
	assert(x == 0b1110);
	x = 0b1;
	x = next_comb(x);
	assert(x == 0b10);
	x = next_comb(x);
	assert(x == 0b100);
}
tm() struct ar { using type = T; };
tm() using ar_t = typename ar<T>::type;
template <typename T, size_t n> struct ar<T[n]> {
	using type = array<ar_t<T>, n>;
};

void test_ar() {
	using std::is_same_v; // FIXME
	static_assert(is_same_v<ar_t<ll[2][3]>, array<array<ll, 3>, 2>>);
	static_assert(is_same_v<ar_t<array<ll, 200>[2][3]>,
				array<array<array<ll, 200>, 3>, 2>>);
}
struct random_device_patch {
	/*! Random device patch to fix libstdc++'s broken implementation on
	 * Windows*/
	unsigned int operator()() {
		return clock_::now()
		    .time_since_epoch()
		    .count(); // TODO Probably random enough, but could be
			      // improved?
	}
	double entropy() { return 0.0; }
};
// TODO activate only on windows
using default_random_device = random_device_patch;
default_random_engine reng{default_random_device{}()};
void test_utility() {
	test_with();
	test_uniq();
	test_next_comb();
	test_ar();
	test_nx2();
	test_map_args();
}
