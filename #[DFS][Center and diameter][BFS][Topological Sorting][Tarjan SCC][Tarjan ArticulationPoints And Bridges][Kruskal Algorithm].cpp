

vector <int> graph[1000000];

// [DFS]

int vis[1000000] = { 0 };
void dfs(int u){
    if (vis[u]) return; vis[u] = 1;
    int size = graph[u].size();
    for (int i = 0; i < size; i ++)
        dfs(graph[u][i]);
}





// [Center and diameter of unweighted Tree]

vector < int > graph[100100];
int parent[100100], dist[100100] = { 0 }, N; // -1, 0, nodes

// return (distance, node)
pair< int, int > furthest(int u, int p, int depth) {

    pair< int, int > res = mp(depth, u); dist[u] = depth;

    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (v != p) {
            parent[v] = u;
            res = max(res, furthest(graph[u][i], u, depth + 1));
        }
    }

    return res;
}

// return (centers, diameter)
pair < vector < int >, int > solve(){

    int start, end; pair < vector < int >, int > res;
    end = furthest(rand() % N, -1, 0).second;
    memset(parent, -1, sizeof(parent));
    memset(dist, 0, sizeof(dist));
    pair < int, int > ret = furthest(end, -1, 0);
    start = ret.second; res.second = ret.first;
    int u = start, di = ret.first, di2 = ret.first / 2;

    while (u != -1){
        if (res.first.size() == 2) break;
        if (di & 1){ if (dist[u] == di2 || dist[u] == di2+1) res.first.pp(u); }
        else { if (dist[u] == di2) { res.first.pp(u); break; } } u = parent[u];
    }

    return res;
}





// [BFS]

int d[1000000];
void bfs(int source){
    queue<int> q; q.push(source);
    mm(d, -1); d[source] = 0;

    while (!q.empty()){
        int u = q.front(); q.pop();
        int size = graph[u].size();

        for (int i = 0; i < size; i ++){
            int v = graph[u][i];

            if (d[v] == -1)
                d[v] = d[u] + 1, q.push(v);
        }
    }
}

// [Kahn's Topological Sorting]

int in[1000000] = { 0 };
vector <int> kahn_topological_sorting(){
    priority_queue < int, vector <int>, greater <int> > pq; vector <int> res;

    for (int i = 1; i <= n; i ++)
        if(in[i] == 0) pq.push(i);

    while (!pq.empty()){
        vector <int> temp;

        while(!pq.empty())
            temp.pp(pq.top()), pq.pop();

        for (int i = 0 ; i < temp.size(); i ++){
            int top = temp[i]; res.pp(top);
            int size = graph[top].size();

            for (int ii = 0 ; ii < size; ii ++)
                if (--in[graph[top][ii]] == 0)
                    pq.push(graph[top][ii]);
        }
    }

    return res;
}

// [Tarjan SCC]

vector <int> st;
vector <int> comps[1000];
int inst[1000], dfn[1000], low[1000]; //assign them to 0,-1,random
int SCCs = 0, Time = 0;

void tarjan_scc(int u) {
    low[u] = dfn[u] = Time++;
    st.push_back(u);
    inst[u] = 1;

    int size = graph[u].size();
    for (int i = 0; i < size; i++) {
        int v = graph[u][i];
        if (dfn[v] == -1) tarjan_scc(v);
        if (inst[v]) low[u] = min(low[u], low[v]);
    }

    if (low[u] == dfn[u]) {
        while (1) {
            int v = st.back(); comps[SCCs].pp(v);
            st.pop_back(); inst[v] = 0;
            if (u == v) { SCCs++; break; }
        }
    }
}


// [Tarjan ArticulationPoints And Bridges]

vector < int > graph[1000];
int artic[1000], dfn[1000], low[1000], parent[1000]; //0,-1,random,-1
int Time = 0, root, rootchi = 0; //artic[root] if rootchi > 1
vector < pair < int, int > > bridges;

void Tarjan_ArticulationPoints_And_Bridges(int u) {
    low[u] = dfn[u] = Time++;

    int size = graph[u].size();
    for (int i = 0; i < size; i++) {
        int v = graph[u][i];

        if (dfn[v] == -1) {
            parent[v] = u; if (u == root) rootchi++;
            Tarjan_ArticulationPoints_And_Bridges(v);
            if (low[v] >= dfn[u]) artic[u] = 1;
            if (low[v] > dfn[u]) bridges.pp(mp(u, v));
            low[u] = min(low[u], low[v]);
        }

        else if (parent[u] != v) low[u] = min(low[u], dfn[v]);
    }
}



// [Kruskal's Algorithm]

int p[1000001], Rank[1000001]; // p[i] = i, Rank[i] = 0;
int get_father(int i) { return (p[i] == i) ? i : p[i] = get_father(p[i]); }
int is_connected(int i, int j) { return (get_father(i) == get_father(j)); }
void connect(int i, int j) {
    if (!is_connected(i, j)){
        int x = get_father(i), y = get_father(j);
        if (Rank[x] < Rank[y]) p[x] = y;
        else { p[y] = x;
            if (Rank[x] == Rank[y]) Rank[x] ++;
        }
    }
}

vector < pair < int, II > > edge;

int kruskal_algorithm(int res = 0){
    for (int i = 0 ; i < 1000000 ; i ++)
        p[i] = i, Rank[i] = 0; sort(ALL(edge));
    for (int i = 0 ; i < edge.size() ; i ++){
        int u = edge[i].se.fi, v = edge[i].se.se, cost = edge[i].fi;
        if (!is_connected(u, v)) connect(u, v), res += cost;
    }
    return res;
}
