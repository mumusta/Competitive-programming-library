// Fibonacci Numbers
// 0,1,1,2,3,5,8,13,21,34,55,89,...
// F[0] = 0, F[1] = 1, F[n] = F[n−1] + F[n−2]
// O(log(n))
ull fast_fibonacci(ull n){
	ull i = 1, h = 1, j = 0, k = 0, t;
	while (n > 0) {
		if (n % 2 == 1)
			t = j*h, j = i*h + j*k + t, i = i*k + t;
		t = h*h, h = (ull)2*k*h + t, k = k*k + t, n = n/(ull)2;
	}
	return j;
}

// Catalan Numbers
// 1,1,2,5,14,42,132,429,1430,…
ull catalan(ull n) {
	return (n == (ull)1) ? 1 : 
		   (((ull)2 * (n - (ull)1) + (ull)2) * 
		   ((ull)2 * (n - (ull)1) + (ull)1) * 
		   catalan(n - (ull)1)) / ((n) * (n + (ull)1));
}


// Stirling of the second type

ull stirling2 (ull n, ull k){
	if (k == 1 || n == k) return 1;
	return k * stirling2(n - 1, k) + stirling2(n - 1, k - 1);
}


// Bell Numbers (Bell triangle O(n*(n+1)/2))
// 1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570, 4213597
// number of partitions of a set of size n

const ull MAX_BELL = 1001;
ull bell[MAX_BELL] = { 1 };
ull rows[2][MAX_BELL] = { 1 }, p = 0;

void build_bell_numbers() {
	for (int i = 1; i < MAX_BELL; i ++) {
		p = !p, bell[i] = rows[p][0] = rows[!p][i-1];
		for (int j = 1; j < i+1; j ++)
			rows[p][j] = rows[p][j-1] + rows[!p][j-1];
	}
}



// The index of the Permutation
// p should contain numbers (0)->(n-1)
// returns the permutation number of p (0 indexed)
int permToIndex(vector < int > p) {
    if (p.size() <= 1) return 0;
    if (p.size() == 2) return p[0]; int f = 1;
    for (int i = 1; i < p.size(); i++) f *= i;
    vector < int > r = p; r.erase(r.begin());
    for (int i = 0; i < r.size(); i++)
    	if (r[i] > p[0]) r[i]--;
    return f * p[0] + permToIndex(r);
}


// jth Permutaion
// j is the permutaion number
// d is the number of elements in the permutaion
// returns the jth permutaion
vector < int > indexToPerm(int j, int d) {
	if (d == 1) {
		vector < int > ret;
		ret.push_back(0);
		return ret;
	}
	int f = 1;
	for (int i = 2; i < d; i++) f *= i;
	vector < int > r(d); r[0] = j / f;
	vector < int > t = indexToPerm(j % f, d - 1);
	for (int i = 0; i < t.size(); i++)
		if (t[i] >= r[0]) t[i]++;
	int ff = 0, tt = 1;
	for (int i = 0; i < t.size(); i ++)
		r[tt++] = t[ff++];
	return r;
}
