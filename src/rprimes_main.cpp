#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Rcpp.h>

using namespace std;
using namespace Rcpp;


// [[Rcpp::export]]
bool isPrime(unsigned long int n)
{
    if(n==1)
        return false;
    if(n<=3)
        return true;
    if(n%2 == 0 || n%3 == 0)
        return false;
    unsigned long int i = 5;
    
    while(i*i <= n)
    {
        if(n%i == 0 || n%(i+2)==0)
            return false;
        i += 6;
    }
    return true;
}

std::vector<bool> sieve(unsigned long int max, int n)
{
    std::vector<bool> isPrimeVec;
    isPrimeVec.assign(max, true);
    isPrimeVec[0] = false;
    isPrimeVec[1] = false;

    int count = 0;
    for(unsigned long int i = 2; i < max; i++)
    {
        if(isPrimeVec[i])
        {
            count ++;
            if(count >= n)
                break;
            for(unsigned long int j = 2; (i*j) < max; j++)
                isPrimeVec[i*j] = false;
        }
    }

    return isPrimeVec;
}

// [[Rcpp::export]]
unsigned long int nthPrime(int n)
{
    unsigned long int max;
    if(n>100)
        max = round(n*(log(n) + log(log(n)) - 1 + 1.8*log(log(n))/log(n)) + 5);
    else
        max = 1000;
    std::vector<bool> primeSieve = sieve(max, n);
    int count = 0;
    unsigned long int i;
    for(i=0; i<primeSieve.size(); i++)
    {
        if(primeSieve[i])
            count ++;
        if(count >= n)
            break;
    }
    return i;
}

// [[Rcpp::export]]
std::vector<unsigned long int> genPrimes(unsigned long int max)
{
    std::vector<bool> primeSieve = sieve(max, max);
    std::vector<unsigned long int> primes;
    for(unsigned long int i=2; i<primeSieve.size(); i++)
        if(primeSieve[i])
            primes.push_back(i);
    return primes;
}

/*
int main(int argc, char *argv[])
{
    unsigned long int max = stounsigned long int(string(argv[1]));
    vector<unsigned long int> primes = genPrimes(max);
    for(int i=0; i<primes.size(); i++)
        cout<<primes[i]<<" ";
    cout<<endl;
    return 0;
}
 */
 
               
