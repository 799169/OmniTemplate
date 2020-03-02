#ifndef PRE
#include <bits/extc++.h>
#include <experimental/source_location>
#include <experimental/iterator>
#endif
#ifdef LOCAL
#define dbg(x) (++depth, debug(x, #x##s))
#else
#define NDEBUG
#define dbg(x) (x)
#endif
#if 1
#define BEGIN_NS namespace {
#define END_NS }
#else
#define BEGIN_NS
#define END_NS
#endif
#define fo(i,...) for([[maybe_unused]] auto i: ra{__VA_ARGS__ })
#define fr(i,...) for([[maybe_unused]] auto i: rev(ra{__VA_ARGS__ }))
#define tp decltype
#define tm(...) template<typename __VA_ARGS__  T>
#define this (*this)
#define al(v) begin(v),end(v)
#define I(x) ll x;cin>>x;
#define pb push_back
#define vc vector
bool debug_mode = false;
//#define rel_assert(msg) if constexpr(debug_mode){static_assert(false, msg);}
#define rel_assert(...)
#define WARN(msg) [[deprecated(msg)]] auto warn = [](){rel_assert(msg);}; warn();
//#define TODO(msg) WARN("TODO: " msg)
#define TODO(msg)
#define paste2(x,y) x##y
#define paste(x, y) paste2(x,y)
#define lets_count lets_add paste(_l, __COUNTER__)
#define let(a, ...) using a = __VA_ARGS__ ; lets_count{#__VA_ARGS__ , #a};
#define import(a) using namespace a; lets_count{#a "::", ""};
#define df(x, v) remove_const_t<tp(v)> x = v
using namespace std;
BEGIN_NS
#define ostream auto
vector<pair<string, string>> lets{{"__debug::", ""}, {"const ", ""}, {"__cxx11::basic_string<char>", "string"}};
struct lets_add {
	lets_add(const auto& a, const auto& b){
		lets.pb({a,b});
	}
};
import(__gnu_pbds);
using std::priority_queue;
using __gnu_cxx::power;
import(std);
import(experimental);
import(chrono);
import(literals);
import(placeholders)
let(lli,long long);
let(ull, unsigned long long);
#include "my_int.hpp"
let(vl,vector<ll>);
let(ld,long double)
let(pr,pair<ll, ll>);
let(com, complex<double>);
let(pt, complex<ll>);
using bt = bitset<numeric_limits<ll>::digits>;
tm() using pq = std::priority_queue<T, vector<T>, greater<>>;
let(clock_, high_resolution_clock);
import(this_thread);
let(um,unordered_map<ll, ll>);
tm() auto type_name([[maybe_unused]] T const& v){
	string s = __PRETTY_FUNCTION__, tar = "T = ";
	auto st = s.find(tar)+tar.size();
	return s.substr(st, s.find("]", st)-st);
}
auto replace(auto s, const auto& a, const auto& b){
	ll loc;
	while((loc = s.find(a)) !=string::npos){
		s = s.substr(0, loc) + b + s.substr(loc+a.size());
	}
	return s;
}
auto simple_tp([[maybe_unused]] const auto& v){
	auto s = type_name(v);
	for(const auto& p: lets){
		s = replace(s, p.first, p.second);
	}
	return s;
}
auto constexpr inf = ll(numeric_limits<ll>::max())/8;
auto const delim = ", "s;
auto constexpr tau = 2*3.1415926535897932384626433L;
#include "io.hpp"
BEGIN_NS
#include "range.hpp"
ll depth = -1;
auto debug(const auto& x, const auto& name, source_location const& loc = source_location::current()){
	if(debug_mode){
		fo(i,depth){cerr<<"\t";}
		cerr<<loc.function_name()<<":"<<loc.line()<<" "<<name<<" = "<<x<<endl;
	}
	--depth;
	return x;
}
#include "dsu.hpp"
#include "operations.hpp"
#include "utility.hpp"
#include "modulo.hpp"
#include "number_theory.hpp"
#include "linear_algebra.hpp"
tm() struct ar {using type = T;};
tm() using ar_t = typename ar<T>::type;
template<typename T, size_t n>
struct ar<T[n]>{using type = array<ar_t<T>,n>;};
#include "combinatorics.hpp"
#include "graph_theory.hpp"
tm() using bin_op = T(*)(T,T);
#define ret(x, id) if(f == static_cast<tp(f)>(x)){return id;}
constexpr ll identity(bin_op<ll const&> const& f){
	ret(max<ll>, -inf);
	ret(min<ll>, inf);
	abort();
}
constexpr ll identity(bin_op<ll> const& f){
	ret(gcd<ll>, 0);
	abort();
}
#include "persistent.hpp"
#include "time.hpp"
#include "fft.hpp"
#include "big_integer.hpp"
#include "coroutine.hpp"
#include "tree.hpp"
#include "geometry.hpp"
using ull = unsigned long long ;
#include "string.hpp"
END_NS
#include "main.hpp"
BEGIN_NS
template<typename T, typename V = null_type>
using omap = tree<T, V, less<>, rb_tree_tag, tree_order_statistics_node_update>;
END_NS
BEGIN_NS
#include "segment_tree.hpp"
#include "2sat.hpp"
END_NS
const bool multitest = false;
struct random_device_patch { // Random device patch to fix libstdc++'s broken implementation on Windows
	unsigned int operator()(){
		return clock_::now().time_since_epoch().count(); // Probably random enough
	}
	double entropy() {
		return 0.0;
	}
};
using default_random_device = random_device_patch;
default_random_engine reng{default_random_device{}()};
#include "treap.hpp"
#include "queue.hpp"