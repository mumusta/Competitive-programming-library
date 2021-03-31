//[Fraction stuff]

/*

a1    a2   a1*b2+a2*b1
--  + -- = -----------  Then we divide both by the GCD of both.
b1    b2      b1*b2

a1    a2   a1*b2-a2*b1
--  - -- = -----------  Then we divide both by the GCD of both.
b1    b2      b1*b2

2    3
-- < -- Because (2 * 4) < (3 * 5) //Cross stuff
5    4

*/

// Facts Primes
// int primelst[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
//									53, 59, 61, 67, 71, 73, 79, 83, 89, 97 }; // [1-100]
// (2^31)-1 is a prime number with value 2147483647
// (2^61)-1 is a prime number with value 2305843009213693951
// primesRangeCnt 10^i (4, 25, 168, 1229, 9592, 78498, 664579, 5761455) [e.g. 4 primes <= 10^1] ~= n / log(n)
// 257, 263, 269, 271 -> 4 primes their multiplication > 2^32
// Wilson's theorem: (p-1)!%p = p-1 IFF p is prime

//[GCD and LCM]

ll gcd(ll a, ll b) { return b == 0?a:gcd(b,a%b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }



// [Is Prime]

int is_prime(int n){
    if (n == 2) return 1;
    if (n < 2 || n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2){
        if (n % i == 0) return 0;
    } return 1;
}

// [Sieve]

vector <int> isprime(N + 1, 1);
void sieve(){
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i * i <= N; i ++){
        if (isprime[i]){
            for (int ii = i * 2; ii <= N; ii += i){
                isprime[ii] = 0;
            }
        }
    }
}


// [Generate Divisors]
// The result is not sorted!

vector <int> divisors;
void generate_divisors(int n, int i = 1){
    for (i = 1; i * i < n; i++)
        if (n % i == 0) divisors.pp(i), divisors.pp(n/i);
    if (i * i == n) divisors.pp(i);
}

// [Generate Prime Factors]

vector <int> factors;
void generate_prime_factors(int n){
    for (int i = 2; i * i <= n; i ++)
        while (n % i == 0) factors.pp(i), n /= i;
    if (n > 1) factors.pp(n);
}


#define MOD 1000000007
using namespace std;
long long fast_power(long long base, long long power) {
    long long result = 1;
    while(power > 0) {

        if(power & 1) { 
            result = (result*base) % MOD;
        }
        base = (base * base) % MOD;
        power >>= 1;
    }
    return result;
}

// [Fast Power]

ll fp(ll B , ll P, ll mod){
    ll res = 1 , pow = P , val = B;
    while (pow > 0){
        if (pow & 1){
            res *= val; res %= mod;
        } val *= val; val %= mod; pow >>= 1;
    } return res;
}


// Facts factorial
// Fact(n) = 1 * 2 .... n
// Fact(0) = Fact(1) = 1
// Implemented iteratively and recursively
// Factorial is exponential: so be careful either in: computation or algorithm order
// n! % x	where x <= n	-> 0
// Wilson's theorem: (p-1)!%p = p-1 IFF p is prime
// 2! is the only prime factorial



// [How many prime p in the prime factors of n!]
/*
			  1				 	  2
	  1	  	  2		   3		  2
  1	  2   3	  2   5	   2    7	  2
1 2	3 2 5 2 7 2 9 2 11 2  13 2 15 2				[Exploring 16! with p=2]
*/

ll p_in_factorial_n(ll n, ll p){
    ll res = 0;
    for (ll i = p; i <= n; i *= p)
        res += n / i;
    return res;
}



// The length of a number base 10
int lengthOfNumber(ull n){ return floor( log10(n) ) + 1; }



// [Extended GCD]

//	ax + by = gcd(a,b)
int eGCD(int a, int b, int &x, int &y) {
	x = 1;
	y = 0;
	int nx = 0, ny = 1;
	int t, r;
	while (b) {
		r = a / b;
		t = a - r * b;
		a = b;
		b = t;
		t = x - r * nx;
		x = nx;
		nx = t;
		t = y - r * ny;
		y = ny;
		ny = t;
	}
	return a;
}

//ax + by = c
bool solveLDE(int a, int b, int c, int &x, int &y, int &g) {
	g = eGCD(a, b, x, y);
	x *= c / g;
	y *= c / g;
	return (c % g) == 0;
}

//(a * mi) % m = 1
int modInv(int a, int m) {
	int mi, r;
	eGCD(a, m, mi, r);
	return (mi + m) % m;
}

//(a * x) % b = c
bool solve(ll a, ll b, ll c, ll &x) {
	ll y, g;
	if (solveLDE(a, b, c, x, y, g) && a * x + b * y == c) {
		if (x < 0) {
			x += (abs(x) / b) * b;
			if (x < 0) x += b;
		}
		return 1;
	}
	return 0;
}
