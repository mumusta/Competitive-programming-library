

// [Floyd-Warshall algorithm]

ll graph[500][500]; // graph[i][j] = the cost of edge (i,j) i.e. adjacency matrix
// or INF if there is no such edge or zero if i = j
void floyd_warshall(){
    for (int k = 1; k <= N; k ++)
        for (int i = 1; i <= N; i ++)
            for (int j = 1; j <= N; j ++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

// [Floyd-Warshall, Printing the shortest paths]

int p[500][500];
void print_path(int i, int j){
    if (i != j) print_path(i, p[i][j]);
    printf(" %d", j);
}

void floyd_warshall_print_path(){
    for (int i = 1; i <= N; i ++)
        for (int j = 1; j <= N; j ++)
            p[i][j] = i;

    for (int k = 1; k <= N; k ++)
        for (int i = 1; i <= N; i ++)
            for (int j = 1; j <= N; j ++)
                if (graph[i][k] + graph[k][j] < graph[i][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                    p[i][j] = p[k][j];
                }
}

// [Dijkstra's algorithm]

vector < II > graph[500]; int d[500]; // graph[u][0] = mp(node v, edge uv weight)
void dijkstra(int source){
    priority_queue < II, vector < II >, greater < II > > pq;
    pq.push(mp(0, source)); fill(d, d+500, 1e9); d[source] = 0;
    while (!pq.empty()){
        II top = pq.top(); pq.pop();
        int ln = top.fi, u = top.se, size = graph[u].size();
        if (ln > d[u]) continue;
        for (II pr : graph[u]){
            int v = pr.fi, nextln = ln + pr.se;
            if (nextln < d[v])
                d[v] = nextln, pq.push(mp(nextln, v));
        }
    }
}

// [Bellman Ford's Algorithm]

vector < II > graph[500]; int d[500]; // d[N] assigned to OO
// graph[u][0] = mp(node v, edge uv weight)
int N, HasNegativeCycle = 0;

void bellman_ford(int source){

    d[source] = 0;
    for (int i = 0; i < N - 1; i ++)
        for (int u = 1; u <= N; u ++)
            for (II pr : graph[u]){
                int v = pr.fi, uv = pr.se;
                d[v] = min(d[v], d[u] + uv);
            }

    for (int u = 1; u <= N; u ++)
        for (II pr : graph[u]){
            int v = pr.fi, uv = pr.se;
            if (d[v] > d[u] + uv)
                HasNegativeCycle = 1;
        }
}



// [Max Flow][Edmonds-Karp Algorithm] O(VE^2)

vector <int> graph[150];
int vgraph[150][150];
int s, t, p[150], flow;

void augmenting_path(int u, int bottleneck){
    if (u == s) { flow = bottleneck; return; }
    else if (p[u] != -1){
        augmenting_path(p[u], min(bottleneck, vgraph[p[u]][u]));
        vgraph[p[u]][u] -= flow; vgraph[u][p[u]] += flow;
    }
}

int edmonds_karp_algorithm(int MaxFlow = 0){

    while (true){
        flow = 0; mm(p, -1);

        queue<int> q; q.push(s);
        int d[150]; mm(d, -1); d[s] = 0;

        while(!q.empty()){
            int u = q.front(); q.pop(); int size = graph[u].size();
            if (u == t) break;
            for (int i = 0; i < size; i ++){
                int v = graph[u][i];
                if (d[v] == -1 && vgraph[u][v] > 0)
                    d[v] = d[u] + 1, q.push(v), p[v] = u;
            }
        }

        augmenting_path(t, 1e9);
        if (flow == 0) break; else MaxFlow += flow;
    }

    return MaxFlow;
}
