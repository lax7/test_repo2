#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

/*
	TODO: later
	calling functions with 1,2,3,4,5 parameters
 */
void f();

// write this in assembler! count from 0 to n-1
uint32_t a1(uint32_t n);

// write this in assembler! count from n down to 0
uint32_t a2(uint32_t n);



uint64_t b1(uint32_t n) {
	for (int i = 0; i < n; i++)
		f();
	return 0;
}

uint64_t b2(uint32_t n) {
	for (; n > 0; n--) {
		f();
	}
	return 0;
}

uint64_t b3(uint32_t n) {
	uint64_t sum = 0;
	for (int i = 0; i < n; i++)
		sum += i;
	return sum;
}

uint64_t b4(uint32_t n) {
	uint64_t sum = 0;
	for (; n > 0; n--)
		sum += n;
	return sum;
}

uint64_t b5(uint32_t x[], uint32_t n) {
	uint64_t sum = 0;
	for (int i = 0; i < n; i++)
		sum += x[i];
	return sum;
}

uint64_t b6(uint32_t x[], uint32_t n) {
	uint64_t sum = x[0];
	for (n--; n > 0; n--)
		sum += x[n];
	sum += x[0];
	return sum;
}

uint64_t b7(uint32_t x[], uint32_t n) {
	uint64_t sum = 0;
	for(int i=0;i<=n-1;i+=2)
	sum+=x[i];
	for(int i=1;i<=n-1;i+=2)
	sum+=x[i];

return sum;
}

/*
  write code to compute sum backwards, not in sequential order
     compute x[n-1] + x[n-3] + x[n-5] + ...
     +   x[n-2] + x[n-4] + ...

 */

uint64_t b8(uint32_t x[], uint32_t n) {
	uint64_t sum = 0;
	for(int i=n-1;i>=0;i-=2)
		sum+=x[i];
	for(int i=n-2;i>=0;i-=2)
		sum+=x[i];
return sum;
}


/*
	write a function that reads and sums
     elements mod 4 = 0: x[0], x[4], x[8] ... 
	then the elements mod 4 = 1: x[1], x[5], x[9] ... = 0
	then the elements mod 4 = 2: x[2], x[6], x[10] ... = 0
	last x[3], x[7], x[11] ... = 0
	compare the speed of sequential access to the speed of writing out of order
 */
uint64_t b9(uint32_t x[], uint32_t n) {
	uint64_t sum = 0;
	for(int i=0;i<=n-1;i+=4)
		sum+=x[i];
	for(int i=1;i<=n-1;i+=4)
		x[i]=0;
	for(int i=2;i<=n-1;i+=4)
		x[i]=0;
	for(int i=3;i<=n-1;i+=4)
		x[i]=0;
return sum;
}

uint64_t b10(uint32_t x[], uint32_t n) {
  uint64_t sum = 0;
	const uint32_t chunk = 32;
	for (uint32_t i = 0; i < chunk; i++) {
		for (uint32_t j = i; j < n; j += chunk)
      sum += x[j];
	}
	return sum;
}


uint64_t b11(uint32_t x[], uint32_t n) {
  uint64_t sum = 0;
	const uint32_t chunk = 1024;
	for (uint32_t i = 0; i < chunk; i++) {
		for (uint32_t j = i; j < n; j += chunk)
			sum += x[j];
	}
	return sum;
}


uint64_t b12(uint32_t x[], uint32_t n) {
	for (int i = 0; i < n; i++)
		x[i] = 0;
	return 0;
}

uint64_t b13(uint32_t x[], uint32_t n) {
	for ( ; n > 0; n--)
		x[n] = 0;
	x[0] = 0;
	return 0;
}


/*
	write a function that sets elements x[0], x[2], x[4] ... = 0
	then goes back and sets the odd elements x[1], x[3], x[5] .. = 0
	compare the speed of sequential access to the speed of writing out of order
*/
uint64_t b14(uint32_t x[], uint32_t n) {
	for(int i=0; i<n; i+=2){
		x[i]=0;
}
	for(int i=1;i<n;i+=2){
		x[i]=0;
}
	return 0;
}


uint32_t countPrimes1(uint32_t n) {
	uint32_t count = 0;
	for (uint32_t i = 2; i <= n; i++) {
		for (uint32_t j = 2; j < i; j++)
			if (i % j == 0)
				goto notPrime;
		count++;
	notPrime: ; // do nothing if not prime
	}
	return count;
}

// skip 2 for speed. Handle 2 as a special case, then all primes are odd
// go up to the square root of the number
int32_t countPrimes2(uint32_t n) {
	uint32_t count = 1; // special case for 2, the only even prime
	for (uint32_t i = 3; i <= n; i +=2) {
  		for (uint32_t j = 3; j >= sqrt(n) ; j+=2)
			if(i % j == 0)
				goto notPrime;
		count++;
	notPrime: ; // do nothing if not prime
	}
	return count;
}

/*
	   5   6   7   8   9  10
    11  12  13  14  15  16
    17  18  19  20  21  22
    23  24  25  26  27  28
    29  30  31  32  33  34
 */
int32_t countPrimes3(uint32_t n) {
	uint32_t count = 2; // special case for 2,3
	for (uint32_t i = 5; i <= n; i += 6) {
		for (uint32_t j = 5; j <= sqrt(i); j += 6) {
			if (i % j == 0)
				goto notPrime1;
			if (i % (j+2) == 0)
				goto notPrime1;
		}
		count++;
	notPrime1: ; // do nothing if not prime
		uint32_t i2 = i + 2;
		for (uint32_t j = 5; j <= sqrt(i2); j += 6) {
			if (i2 % j == 0)
				goto notPrime2;
			if (i2 % (j+2) == 0)
				goto notPrime2;
		}
		count++;
	notPrime2: ;
	}
	return count;
}

// benchmark adding an array of single precision floating point
float b15(float x[], uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += x[i];
	return sum;
}

// benchmark writing zeros to an array of single precision floating point
float b16(float x[], uint32_t n) {
	for (int i = 0; i < n; i++)
		x[i] = 0;
	return 0;
}

// benchmark multiplying an array of single precision floating point
float b17(float x[], uint32_t n) {
	float prod = 1;
	for (int i = 0; i < n; i++)
		prod *= x[i];
	return prod;
}

// benchmark sum of floating point reciprocals
// check your answer! SHOULD NOT BE 1.0!!!
// 1/1 + 1/2 + 1/3 + ... + 1/n
float b18(uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += 1.0/(i+1);
	return sum;
}


// benchmark sum of floating point square roots
// sqrt(1) + sqrt(2) + ... + sqrt(n)
float b19(uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += sqrt (i);
	return sum;
}


// benchmark sum of double precision floating point reciprocals
// 1/1 + 1/2 + 1/3 + ... + 1/n
double b20(uint32_t n) {
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += 1.0/(i+1);
	return sum;
}


// benchmark sum of double precision floating ppoint square roots
// sqrt(1) + sqrt(2) + ... + sqrt(n)
double b21(uint32_t n) {
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += sqrt(i+1);
	return sum;
}

// There are bugs in my fact function. Fix them and benchmark
double fact(uint32_t n) { /* this is a comment*/
	double prod;
	for (int i = 0; i < n; i++)
		prod *= i;
	return prod;
}

//Write a recursive factorial function
double fact2(int n) {
	if (n==0)
		return 1;
	else
	return n*fact2(n-1);
}




/*
	This is matrix multiplication for a matrix of size 10x10



    3  2  1        1  0  2      1   4   0
    1  0  -1   *   -1 1  -2 =   1
    2  1  1        0  2  1
 */

void matmult(float ans[10][10], float a[10][10], float b[10][10]) {
	const int n = 10;
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			ans[i][j] = 0;
			for (uint32_t k = 0; k < n; k++)
				ans[i][j] += a[i][k] * b[k][j];
		}
}

/*
	the following code is not legal because 2-D matrices must be fixed in size.
	Instead, write the code to index using the rule: a[i][k] = a[i*n+k]
	This is what the compiler actually does for 2d matrices when it knows the size
	of n in advance

int x[10][20];
x[i][j]= 99;

        j
  5  6  7  9
  1  2  3  4
i 9  1  x  -1                m[i*n+j]
  1  0  2  -2


 */

void matmult2(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			ans[i*n+j] = 0;
			for (uint32_t k = 0; k < n; k++)
				ans[i*n+j] += a[i*n+k] * b[k*n+j];
		}
}


/*
	matmult2 above is inefficient because you are repeatedly writing ans[i][j],
	then reading it in again, adding a new multiplication and writing again.
	Avoid this by using a scalar variable which can be in a register.
 */

void matmult3(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			double dot = 0;
			for (uint32_t k = 0; k < n; k++)
				dot += a[i*n+k] * b[k*n+j];
			ans[i*n+j] = dot;
		}
}


/*
	matmult3 above is inefficient because every time you look up a location:

	a[i][k] you are computing a[i*n+k] which uses a multiplication which takes a few extra clocks

	rewrite the function to take advantage of the fact that we just need to add
	not multiply.
 */

void matmult4(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0; i < n; i++)
		for (uint32_t j = 0, c=i*n+j; j < n; j++, c++) {
			double dot = 0;
			for (uint32_t k = 0, d =i*n+k, e=j+n*k; k < n; k++)
				dot += a[d] * b[e];
			ans[c] = dot;
		}
}

constexpr double PI = 3.14159265358979;
/*
	Second part, added March 20, 2020
*/

/* Compute the product of all these terms. Look at the assembly language. Can you come up with a more efficient way to get the same answer? Benchmark the original and your better version.
*/
double deg2rad(uint32_t n) {
	const double x = 0.001;
	double y = 1;
	for (uint32_t i = 0; i < n; i++) {
		y = y * x * PI / 180;
	}
	return y;
}

/* 
	 The force due to gravity is:

	 F = G*m1*m2 / (r*r)

	 The acceleration of mass 1 is

	 a =  F / m1
*/
double grav(uint32_t n) {
	constexpr double G =  6.6742E-11; // universal gravitational constant
	double x = 0; // one dimensional problem. Start at x = 0
	double v = 0; // velocity = 0 to start
	double r = 1.5e12; // distance apart
	const double m1 = 5.972e24;      // earth mass
	const double m2 = 7.34767309e22; // moon mass
	constexpr double dt = 0.1; // 0.1 second timestep
	for (uint32_t i = 0; i < n; i++) {
		double F = G * m1 * m2 / (r*r);
		double a = F / m1;
		x = x + v * dt + 0.5*a * dt * dt;
		v = v + a * dt;
	}
	return x;
}





/*
	benchmarking a few instructions almost never makes sense

	ldr r0, [r1]
	add r0, #4
  ...

	Q: what do you do about pipelining?
	in a modern CPU, benchmarking is HARD

	A: measure what you want in bulk and take the average value for a
	large number of trials. Recognize that it may be different.
 */
template<typename Func>
void benchmark1(const char msg[], Func f, uint32_t n) {
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		uint64_t res = f(n);
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
}

template<typename Func>
void benchmark2(const char msg[], Func f, uint32_t n) {
	uint32_t* p = new uint32_t[n]; // allocate a big chunk of memory
	for (int i =  0; i < n; i++)
		p[i] = 0;
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		uint64_t res = f(p, n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
	delete [] p;
}

// benchmark for floating point arrays
template<typename Func>
void benchmark3(const char msg[], Func f, uint32_t n) {
  float* p = new float[n];
  for (int i = 0; i < n; i++)
    p[i] = 0;
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		float res = f(p, n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
  delete [] p;
}

// benchmark for double arrays
template<typename Func>
void benchmark4(const char msg[], Func f, uint32_t n) {
  double* p = new double[n];
  for (int i = 0; i < n; i++)
    p[i] = 0;
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		double res = f(p, n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
  delete [] p;
}

// integer parameter returning float
template<typename Func>
void benchmark5(const char msg[], Func f, uint32_t n) {
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		float res = f(n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
}

// integer parameter returning double
template<typename Func>
void benchmark6(const char msg[], Func f, uint32_t n) {
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		double res = f(n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(18) << res << '\t' << (t1-t0) << '\n';
	}
}

// integer parameter returning double
template<typename Func>
void benchmark7(const char msg[], Func f, uint32_t n) {
  float* a = new float[n*n];
  for (int i = 0; i < n*n; i++)
    a[i] = 0;
  float* b = new float[n*n];
  for (int i = 0; i < n*n; i++)
    b[i] = 0;
  float* c = new float[n*n];
	for (uint32_t trials = 0; trials < 5; trials++) {
		clock_t t0 = clock();
		f(c, a, b, n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << '\t' << (t1-t0) << '\n';
	}
}

int main() {
	const uint32_t n = 100000000; // 100 million
	benchmark1("a1", a1, n);
	benchmark1("a2", a2, n);

	benchmark1("b1", b1, n);
	benchmark1("b2", b2, n); // compare b1 and b2. What can you conclude?
	benchmark1("b3", b3, n);
	benchmark1("b4", b4, n); // compare b3 and b4. What can you conclude?
/*	//what can you conclude from the difference between b1,b3 and b2,b4?

  const uint32_t n2 = 40000000; // 40 million
	benchmark2("b5", b5, n2);
	benchmark2("b6", b6, n2); // compare b5 and b6, what can you conclude?

	benchmark2("b7", b7, n2);
	benchmark2("b8", b8, n2); // compare b7 and b8, what can you conclude?
//	what can you conclude from the difference between b5,b7 and b6,b8?

//	compare the times for going increasingly non-sequential. What happens?
	benchmark2("b9", b9, n2);
	benchmark2("b10", b10, n2);
	benchmark2("b11", b11, n2);
	benchmark2("b12", b12, n2);
	benchmark2("b13", b13, n2);
	benchmark2("b14", b14, n2);

	constexpr uint32_t numPrimes = 100000;
	benchmark1("countPrimes1", countPrimes1, numPrimes);
  	benchmark1("countPrimes2", countPrimes2, numPrimes*10);
	benchmark1("countPrimes3", countPrimes3, numPrimes*10);


	benchmark3("b15", b15, n2);
	benchmark3("b16", b16, n2);
	benchmark3("b17", b17, n2);

	benchmark6("b18", b18, n2);
	benchmark6("b19", b19, n2);
	benchmark6("b20", b20, n2);
  	benchmark6("b21", b21, n2);
	benchmark6("fact", fact, 50);
	benchmark6("fact2", fact2, 50);

//  	matrix benchmarks with three arrays
  benchmark7("matmult2", matmult2, 1024);
  benchmark7("matmult3", matmult3, 256);
 benchmark7("matmult4", matmult4, 256);
benchmark6("deg2rad", deg2rad, n);
benchmark6("grav", grav, n);
*/
}

