// [Hashing]

// To hash a string for each char from left to right,
// shift left, then add to index zero, and so on.

#define BASE (ll)128 // or 29, 31, 53, 1009
#define BASEINV (ll)1453125008 // e7sebha le nafsak lel b2yen :D
#define MOD (ll)2000000011 // 1e9+9, 1e9+7, 2000000063, 2000000087, 2000000089

ll fp(ll B , ll P, ll mod){
    ll res = 1 , pow = P , val = B;
    while (pow > 0){
        if (pow & 1){
            res *= val; res %= mod;
        } val *= val; val %= mod; pow >>= 1;
    } return res;
}

ll addCharAt(int ind, char v, ll pvHashV) {
    return ((fp(BASE, (ll) ind) * v) % MOD + pvHashV) % MOD;
}

ll removeCharAt(int ind, char v, ll pvHashV) {
    return (MOD - (((fp(BASE, (ll) ind) * v) % MOD)) % MOD + pvHashV) % MOD;
}

ll shiftL(ll pvHash) { return (pvHash * BASE) % MOD; }
ll shiftR(ll pvHash) { return (pvHash * BASEINV) % MOD; }



// [KMP and Prefix Function]

// vector < int > res = KMP("muhammadmustafadagamdfash5", "mu");
// then res equal { 0, 8 }

vector < int > PrefixFunction(string pat){
    int m = pat.size(); vector < int > longestPrefix(m, 0);
    for (int i = 1, k = 0; i < m ; i++){
        while (k > 0 && pat[k] != pat[i])
            k = longestPrefix[k - 1];
        if (pat[k] == pat[i]) longestPrefix[i] = ++k;
        else longestPrefix[i] = k;
    } return longestPrefix;
}

vector < int > KMP(string str, string pat){
    int n = str.size(), m = pat.size(); vector < int > res;
    vector < int > longestPrefix = PrefixFunction(pat);
    for (int i = 0, k = 0; i < n ; i++){
        while (k > 0 && pat[k] != str[i])
            k = longestPrefix[k - 1];
        if (pat[k] == str[i]) k++;
        if (k == m){
            res.push_back(i - m + 1);
            k = longestPrefix[k - 1];
        }
    } return res;
}



// [Z Algorithm]

// will contain the values of z function
// for string (pattern + "$" + text)

// z_algorithm("muhammadmustafa", "mu");

//     m u $ m u h a m m a d m u s t a f a
// z = 0 0 0 2 0 0 0 1 1 0 0 2 0 0 0 0 0 0

int z[1000000] = { 0 };

void z_algorithm(string text, string pattern){
    string str = pattern + "$" + text;
    int n = str.size(), l = -1, r = -1;
    for (int i = 1; i < n ; i ++){
        if (i > r){
            l = r = i;
            while (r < n && str[r] == str[r-l]) r++;
            z[i] = r-l; r--;
        }
        else {
            if (z[i-l] < (r-i)+1) z[i] = z[i-l];
            else {
                l = i;
                while (r < n && str[r] == str[r-l]) r++;
                z[i] = r-l; r--;
            }
        }
    }
}



// [Letter tree (Trie)]

// Trie t; t.insert("muhammad"); t.insert("mustafa");
/* cout << t.wordOccurrence("muhammad") << ' '
         << t.wordOccurrence("must") << ' '
         << t.prefixExist("must") << endl;    */
// 1 0 1

const int MAX_CHAR = 26;

struct Trie {
	Trie* child[MAX_CHAR]; int Stops;

	Trie() { memset(child, 0, sizeof(child)); Stops = 0; }

	void insert(char *str) {
		if(*str == '\0') Stops++;
		else {
			int cur = *str - 'a';
			if(child[cur] == 0) child[cur] = new Trie();
			child[cur]->insert(str+1);
		}
	}

	int wordOccurrence(char* str) {
		if(*str == '\0') return Stops;
        int cur = *str - 'a';
		if(child[cur] == 0) return 0;
		return child[cur]->wordOccurrence(str+1);
	}

	bool prefixExist(char* str) {
		if(*str == '\0') return true;
		int cur = *str - 'a';
		if(child[cur] == 0) return false;
		return child[cur]->prefixExist(str+1);
	}
};






// [Suffix Array] O(n log n)


/*

  [Notes]

    T is The main string, n is the length of it.
    SA is the suffix array, SA[0] = i,
    which T[i], ..., T[n-1] equal the smallest suffix of T


  [To construct SA]

	// T is "abracadabra"
    n = strlen(gets(T)); T[n++] = '$'; constructSA();


  [To print]

    for (int i = 0; i < n; i ++){
        for (int ii = SA[i]; ii < n; ii ++)
            cout << T[ii]; cout << endl;
    }

    $
	a$
	abra$
	abracadabra$
	acadabra$
	adabra$
	bra$
	bracadabra$
	cadabra$
	dabra$
	ra$
	racadabra$

*/

#define MAX_N 100010

char T[MAX_N];
int n, c[MAX_N];
int RA[MAX_N], tempRA[MAX_N];
int SA[MAX_N], tempSA[MAX_N];


void countingSort(int k) {
  int i, sum, maxi = max(300, n); memset(c, 0, sizeof c);
  for (i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t; }
  for (i = 0; i < n; i++)
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++) SA[i] = tempSA[i];
}

void constructSA() { int i, k, r;
  for (i = 0; i < n; i++) RA[i] = T[i];
  for (i = 0; i < n; i++) SA[i] = i;
  for (k = 1; k < n; k <<= 1){
    countingSort(k); countingSort(0);
    tempRA[SA[0]] = r = 0;
    for (i = 1; i < n; i++)
      tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]]
      && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++) RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;
  }
}



// [String Matching Using Suffix Array] O(m log n)

/*
  [To start searching for P]
    m = strlen(gets(P)); II pos = stringMatching();

  [To print]
    for (int i = pos.fi ; i <= pos.se; i ++)
        cout << SA[i] << endl;

  [Notes]
    P is The pattern string, m is the length of it.
    The answers are -1, -1 if not found or,
    SA[pos.fi], SA[pos.fi+1], ..., SA[pos.se].
    which means for each SA[i] in the answers,
    we found string P in T at SA[i].

*/

char P[MAX_N]; int m;

II stringMatching() {
  int lo = 0, hi = n-1, mid = lo;
  while (lo < hi) { mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res >= 0) hi = mid; else lo = mid + 1;
  }
  if (strncmp(T + SA[lo], P, m) != 0) return II(-1, -1);
  II ans; ans.first = lo; lo = 0; hi = n - 1; mid = lo;
  while (lo < hi) { mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res > 0) hi = mid; else lo = mid + 1;
  }
  if (strncmp(T + SA[hi], P, m) != 0) hi--;
  ans.second = hi; return ans;
}



//[LCP (longest common prefix) according to suffixes of T] O(n)

/*
    LCP[i] = The longest common prefix between
    previous suffix SA[i-1] and current suffix SA[i].

    [Note]
      LCP can solve,
      [Longest Repeated Substring](Overlapping allowed),
      [Longest Common Substring].
*/

int LCP[MAX_N], Phi[MAX_N], PLCP[MAX_N];

void computeLCP() {
  int i, L; Phi[SA[0]] = -1;
  for (i = 1; i < n; i++) Phi[SA[i]] = SA[i-1];
  for (i = L = 0; i < n; i++){
    if (Phi[i] == -1) { PLCP[i] = 0; continue; }
    while (T[i + L] == T[Phi[i] + L]) L++;
    PLCP[i] = L; L = max(L-1, 0);
  }
  for (i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
}

