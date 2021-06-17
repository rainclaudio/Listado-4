#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
/*
Problem Id: Needle in the Haystack
page: www.spoj.com
KMP cortesía de geeks for geeks :D
Made By Claudio Rain
*/

void computeLPSArray(std::string needle, int M, int* lps){
    int len = 0;

    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (needle[i] == needle[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(std::string needle, std::string Haystack){
    int M = needle.size();
    int N = Haystack.size();
    int lps[M];
    computeLPSArray(needle, M, lps);
    int i = 0;
    int j = 0;
    while (i < N) {
        if (needle[j] == Haystack[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("%d\n", i - j);
            j = lps[j - 1];
        }else if (i < N && needle[j] != Haystack[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}


int main(int argc, char const *argv[]) {
  int size;
  bool first = true;
  while(scanf("%d",&size)!= EOF){
    if(!first)std::cout << '\n';
    first = false;
    std::string needle,Haystack;
    getchar();
    std::getline(std::cin,needle);
    std::getline(std::cin,Haystack);
    KMPSearch(needle,Haystack);

  }
  return 0;
}
