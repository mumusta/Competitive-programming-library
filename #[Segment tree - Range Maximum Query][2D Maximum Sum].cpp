
// [Segment tree - Range Maximum Query]

ll seq[100100], st[4*100100+5], n;

void pre(int id = 1, int l = 0, int r = n-1){
    if (l == r) { st[id] = l; return; }
    int mid = ((l + r) >> 1), ID = (id << 1);
    pre(ID, l, mid); pre(ID+1, mid+1, r);
    if (seq[st[ID]] == seq[st[ID+1]]) st[id] = min(st[ID], st[ID+1]);
    else st[id] = (seq[st[ID]] > seq[st[ID+1]]) ? st[ID] : st[ID+1];
}

ll RMQ(int x, int y, int id = 1, int l = 0, int r = n-1){
    if (y < l || r < x) return -1;
    if (x <= l && r <= y) return st[id];
    ll p1, p2, mid = ((l + r) >> 1), ID = (id << 1);
    p1 = RMQ(x, y, ID, l, mid); p2 = RMQ(x, y, ID+1, mid+1, r);
    if (p1 == -1) return p2; if (p2 == -1) return p1;
    if (seq[p1] == seq[p2]) return min(p1, p2);
    else return (seq[p1] > seq[p2]) ? p1 : p2;
}

ll update(int x, int v, int id = 1, int l = 0, int r = n-1){
    if (x < l || r < x) return st[id];
    if (l == r) { seq[l] = v; return st[id]; }
    ll mid = ((l + r) >> 1), ID = (id << 1), p1, p2;
    p1 = update(x, v, ID, l, mid); p2 = update(x, v, ID+1, mid+1, r);
    if (seq[p1] == seq[p2]) return st[id] = min(p1, p2);
    else return st[id] = (seq[p1] > seq[p2]) ? p1 : p2;
}



// [2D Maximum Sum]

int n, A[101][101], maxSubRect, subRect;
int main() {     // O(n^3) 1D DP + greedy (Kadane's) solution, 0.008 s in UVa
  scanf("%d", &n);                    // the dimension of input square matrix
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    scanf("%d", &A[i][j]);
    if (j > 0) A[i][j] += A[i][j - 1];      // only add columns of this row i
  }

  maxSubRect = -127*100*100;    // the lowest possible value for this problem
  for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
    subRect = 0;
    for (int row = 0; row < n; row++) {
      // Max 1D Range Sum on columns of this row i
      if (l > 0) subRect += A[row][r] - A[row][l - 1];
      else       subRect += A[row][r];

      // Kadane's algorithm on rows
      if (subRect < 0) subRect = 0;     // greedy, restart if running sum < 0
      maxSubRect = max(maxSubRect, subRect);
  } }
  printf("%d\n", maxSubRect);
}


