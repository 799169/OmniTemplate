template <typename T> struct SplayTree {
  public:
  struct Node {
	  public:
		// Constructor?
		T value;
		array<Node *, 2> child{};
		Node *parent{};
	};
	struct iterator: public it_base<T> {
	  public:
		void operator++() {
      for(;node && side(node); node = node->parent){}
    }
    T& operator*(){
      return node->value;
    }
		Node *node;
    iterator(Node* node_arg): node(node_arg) {}
	};
	Node *root{};
	size_t sz{};
	SplayTree() {}
	static void attach(Node *&old, Node *const new_) {
		new_->parent = old->parent;
		old = new_;
	}
	static bool side(Node *const child) {
		return child->parent->child[1] == child;
	}
	static void rotate(Node *const x) {
		const auto p = x->parent;

		const bool i = side(x);

		if(x->child[!i]){
      attach(p->child[i], x->child[!i]);
      attach(x->child[!i], p);
    }
    else {
      x->child[!i] = p;
      p->parent = x;
    }
	}
	static void splay(Node *const x) {
		while (x->parent) {
			if (!x->parent->parent) {
				// Zig step
				rotate(x);
				return;
			}
			if (side(x) == side(x->parent)) {
				// Zig-zig step
				rotate(x->parent);
				rotate(x);
			} else {
				// Zig-zag step
				rotate(x);
				rotate(x);
			}
		}
	}
	void insert(Node *const x) {
		++sz;
		if (!root) {
			root = x;
			return;
		}
		auto y = root;
		while (true) {
			auto &nw = y->child[x->value > y->value];
			if (!nw) {
				nw = x;
				nw->parent = y;
				splay(nw);
				return;
			}
			y = nw;
		}
		return;
	}
	void insert(const T &key) { insert(new Node{key}); }
	void erase(Node *const x) {
		assert(x);
		splay(x);
		root = join(x->child[0], x->child[1]);
		delete x;
		--sz;
	}
	void erase(const T &key) { erase(find(key)); }
	static Node *extremum(Node *const x, const bool i) {
		assert(x);
		return x->child[i] ? extremum(x->child[i], i) : x;
	}
	static Node *join(Node *const a, Node *const b) {
		if (!a) {
			return b;
		}
		Node *const mx = extremum(a, true);
		splay(mx);
		assert(mx->child[1] == nullptr);
		mx->child[1] = b;
		return mx;
	}
	array<Node *, 2> split(Node *const x) {
		splay(x);
		// TODO use detach function
		if (x->child[1]) {
			x->child[1]->parent = nullptr;
		}
		return {x, x->child[1]};
	}
	Node *find(const T &key) {
		auto x = root;
		for (; x && key != x->value; x = x->child[key > x->value]) {
		}
		return x;
	}
	size_t size() { return sz; }
	bool empty() { return size() == 0; }
	iterator begin(){
    return iterator{extremum(root, false)};
  }
  iterator end(){
    return iterator{nullptr};
  }
};
void test_splay_tree() {
	SplayTree<int> sp;
	sp.insert(4);
	sp.insert(3);
	sp.insert(5);
	assert(sp.size() == 3);
	assert(!sp.empty());
	assert(sp.find(4)->value == 4);
	assert(sp.find(3)->value == 3);
	assert(sp.find(5)->value == 5);
	assert(sp.find(2) == nullptr);
	assert(sp.find(6) == nullptr);
	sp.erase(3);
	assert(sp.size() == 2);
	assert(sp.find(3) == nullptr);
	assert(sp.find(5)->value == 5);
	assert(sp.find(4)->value == 4);
	sp.insert(20);
	sp.insert(-2);
	sp.insert(6);
	for (auto x : {-2, 6, 20}) {
		assert(sp.find(x)->value == x);
	}
	vl vec;
  SplayTree<int>::iterator::value_type x1{};
	//copy(sp.begin(), sp.end(), back_inserter(vec));
  dbg(vec);
	cout << "\e[0;32mAccepted\e[0m" << endl;
}
