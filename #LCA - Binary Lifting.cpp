// [Lowest Common Ancestor]

// You have to assign a value to n (number of nodes [0-n]),
// and to graph (adjacent list of the tree)

int n, l;
vector< int > graph[100010];

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p){

    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : graph[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancetor(int u, int v){

    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){

    if (is_ancetor(u, v))
        return u;
    if (is_ancetor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancetor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
	
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}