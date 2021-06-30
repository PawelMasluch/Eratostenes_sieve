#include<cstdio>
#include<vector>
#include<bitset>


typedef std::vector <int> VI;


#define REP(i,a,b,skok) for(int i=a; i<=b; i+=skok)
#define FOR(i,a,b) for(int i=a; i*i<=b; ++i)


const int MAX_NUMBER = 1000000000; // maximum number to be checked for primeness 
const int SQRT_MAX_NUMBER = 31622; // floor( sqrt(MAX_NUMBER) )
const int MAX_N = 10000000; // maximum length of range of checked (for primeness) numbers 


// isSmallPrime[i] = 0 iff i is not prime
// isSmallPrime[i] = 1 iff i is     prime
std::bitset <SQRT_MAX_NUMBER+1> isSmallPrime;


// // We find smallest prime factors for all numbers i in {a..b} (a<=b).
// smallestFactors[k] = p (k=2,...,n) iff:
//		1. p | k+a and
//		2. p is the smallest possible prime such that p | k+a
VI smallestFactors(MAX_N+1);


// Finding small primes via Eratostenes sieve.
void findSmallPrimes(){
	REP(i,0,1,1){
		isSmallPrime[i] = 0; // 0 and 1 are not primes
	}
	
	REP(i,2,SQRT_MAX_NUMBER,1){
		isSmallPrime[i] = 1; // initially, we assume that all numbers i=2,...,SQRT_MAX_NUMBER are primes
	}
	
	FOR(i,2,SQRT_MAX_NUMBER){
		if( isSmallPrime[i] == 1 ){ // if i is prime
			REP(j,i*i,SQRT_MAX_NUMBER,i){
				isSmallPrime[j] = 0; // j is not prime because i | j and j > i >= 2
			}
		}
	}
}


// min k: k*b >= a
// 10^9 >= a,b > 0
int ceil(int a, int b){
	return (a + b - 1) / b;
}


// Eratostenes sieve in O(n*loglog(n)) time.
// 2 <= a <= b <= 10^9 = MAX_NUMBER
// |b-a| <= MAX_N
void EratostenesSieve(int a, int b){
	
	findSmallPrimes();
	
	REP(i,a,b,1){
		smallestFactors[i-a] = i; // initially, we assume that all numbers i=a,...,b are primes so i | i for i=a,...,b
	}
	
	FOR(i,2,b){
		if( isSmallPrime[i] == 1 ){ // if i is prime
			REP(j,ceil(a,i)*i,b,i){ // ceil(a,i*i)*i*i - minimal number x such that i|x and x >= a
				
				//printf( "%d -> %d\n", j, smallestFactors[j-a] );
				
				if( smallestFactors[j-a] == j ){ // if j hasn't been considered yet
					smallestFactors[j-a] = i;
					
					//printf( "%d -> %d\n", j, smallestFactors[j-a] );
					
				}
			}
		} // after this loop: i is prime (i=2,...,n) iff smallestFactors[i-a] = i
	}
}


int main(){
	
	int a, b;
	scanf( "%d %d", &a, &b );
	
	EratostenesSieve(a, b);
	
	REP(i,a,std::min(a+50,b),1){
		printf( "i = %d: smallest prime factor is %d\n", i, smallestFactors[i-a] );
	}
	
	return 0;
}
