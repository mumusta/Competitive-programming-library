

// [Important]


#include <bits/stdc++.h>

using namespace std;

typedef long double LD;
typedef long long int ll;
typedef unsigned long long int ull;

#define pp push_back
#define mp make_pair

// ----------------------------------------------------

ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define fi first
#define se second
#define len length
#define mp make_pair
#define pp push_back
#define pf push_front
#define V(a) vector <a>
#define P(a,b) pair <a,b>
#define II pair <int, int>
#define sp(a) setprecision(a)
#define ALL(a) a.begin(),a.end()
#define mm(a,b) memset(a , b , sizeof a)
#define cwbits(a) __builtin_popcountll(a)

typedef long long int ll;
typedef unsigned long long int ull;

const double PI = acos(-1.0);
ll  sqdist (ll  p1x , ll  p1y , ll  p2x , ll  p2y)
{ return(p2x-p1x)*(p2x-p1x)+(p2y-p1y)*(p2y-p1y); }
ll gcd(ll a, ll b) { return b == 0?a:gcd(b,a%b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }
int oned(int row, int col, int totalcol) { return row * totalcol + col; }
ll MOD(ll a, ll b) { return a >= 0 ? a % b : (b - abs(a % b)) % b; }
int X[] = { 1, 0, -1, 0, 1, -1, -1, 1 };
int Y[] = { 0, 1, 0, -1, 1, 1, -1, -1 };



// [Red-Black Trees]

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define at(a) find_by_order(a)       // if needed
#define less_than(a) order_of_key(a) // if needed

using namespace std; using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T,
null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {

    ordered_set<int> s;
    s.insert(2); s.insert(1); s.insert(3); s.insert(4); s.insert(4); s.insert(5);
    // s = {1, 2, 3, 4, 5}

    cout << s.order_of_key(3) << endl; // output: 2
    // the number of elements in the s less than 3
    // (we can say the index of 3 if it is in s)

    cout << *s.find_by_order(3) << endl; // output: 4
    // print the 3-th smallest number in s(0-based)
    // (we can say that we access the 3th(0-based) place in s)
}

