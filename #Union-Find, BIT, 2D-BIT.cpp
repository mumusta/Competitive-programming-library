// [Union-Find]

int p[1000001], Rank[1000001]; // p[i] = i, rank[i] = 0.
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


// [BIT]
//insert 5 3 9, put 1 at 5, 3 and 9. add(5, 1), add(3, 1), add(9, 1);
//find(3) returns 9, find(2) returns 5, find(1) returns 3 //find is lower bound
//get(9) returns 3, get(5) returns 2, get(3) returns 1

int sum(int index){
    int res = 0;
    while (index > 0){
        res += fen[index];
        index -= (index & -index);
    } return res;
}

void add(int index, int value){
    while (index <= N){
        fen[index] += value;
        index += (index & -index);
    }
}


// [2D-BIT]

void add(int i, int ii, ll v){
    i++; ii++;
    while (i <= N){
        int j = ii;
        while (j <= N){
            BIT[i][j] += v; j += (j & -j);
        } i += (i & -i);
    }
}

ll sum(int i, int ii){
    ll ret = 0; i++; ii++;
    while (i > 0){
        int j = ii;
        while (j > 0){
            ret += BIT[i][j]; j -= (j & -j);
        } i -= (i & -i);
    } return ret;
} //sum(i,j) = sum of rectangle (0,0)(i,j)


