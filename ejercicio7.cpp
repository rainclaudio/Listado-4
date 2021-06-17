#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define dprint(v) cout << #v"=" << v << endl //;)
/*
Problem Id: Suffix Array
page: www.spoj.com
Suffix Array usado en clases, cortesía de profe Diego Gatica :D
Made By Claudio Rain
*/

const int MAXN=100100;
char T[MAXN];
int n;
#define MAX_N 100100
#define rBOUND(x) (x<n? r[x] : 0)
//sa will hold the suffixes in order.
int sa[MAXN], r[MAXN];
string s; //input string, n=sz(s)
string input1;
string input2;
int f[MAX_N], tmpsa[MAX_N];
void countingSort(int k){
        zero(f);
        forn(i, n) f[rBOUND(i+k)]++;
        int sum=0;
        forn(i, max(255, n)){
                int t=f[i]; f[i]=sum; sum+=t;}
        forn(i, n)
                tmpsa[f[rBOUND(sa[i]+k)]++]=sa[i];
        memcpy(sa, tmpsa, sizeof(sa));
}
void constructsa(){//O(n log n)
        n=sz(s);
        forn(i, n) sa[i]=i, r[i]=s[i];
        for(int k=1; k<n; k<<=1){
                countingSort(k), countingSort(0);
                int rank, tmpr[MAX_N];
                tmpr[sa[0]]=rank=0;
                forr(i, 1, n)
                        tmpr[sa[i]]=(r[sa[i]]==r[sa[i-1]] && r[sa[i]+k]==r[sa[i-1]+k] )? rank : ++rank;
                memcpy(r, tmpr, sizeof(r));
                if(r[sa[n-1]]==n-1) break;
        }
}
void print(){//for debug
        forn(i, n)
                cout << i << ' ' <<
                s.substr(sa[i], s.find( '$', sa[i])-sa[i]) << endl;}


//returns (lowerbound, upperbound) of the search
ii stringMatching(string P){ //O(sz(P)lgn)
        int lo=0, hi=n-1, mid=lo;
        while(lo<hi){
                mid=(lo+hi)/2;
                int res=s.compare(sa[mid], sz(P), P);
                if(res>=0) hi=mid;
                else lo=mid+1;
        }
        if(s.compare(sa[lo], sz(P), P)!=0) return ii(-1, -1);
        ii ans; ans.fst=lo;
        lo=0, hi=n-1, mid;
        while(lo<hi){
                mid=(lo+hi)/2;
                int res=s.compare(sa[mid], sz(P), P);
                if(res>0) hi=mid;
                else lo=mid+1;
        }
        if(s.compare(sa[hi], sz(P), P)!=0) hi--;
        ans.snd=hi;
        return ans;
}

//Calculates the LCP between consecutives suffixes in the Suffix Array.
//LCP[i] is the length of the LCP between sa[i] and sa[i-1]
int LCP[MAX_N], phi[MAX_N], PLCP[MAX_N];
void computeLCP(){//O(n)
        phi[sa[0]]=-1;
        forr(i, 1, n) phi[sa[i]]=sa[i-1];
        int L=0;
        forn(i, n){
                if(phi[i]==-1) {PLCP[i]=0; continue;}
                while(s[i+L]==s[phi[i]+L]) L++;
                PLCP[i]=L;
                L=max(L-1, 0);
        }
        forn(i, n) LCP[i]=PLCP[sa[i]];
}
void printLCP(){
  std::cout << "LCP" << '\n';
  for(int i = 0; i < n; ++i){
    std::cout << LCP[i] << ' ';
  }
  std::cout  << '\n';

}

int main() {
  std::cin >> s;

      n = (int)(s.size());
      s+= '#';
      constructsa();
      // computeLCP();
      // print();
      // printLCP();
      for (int i = 1; i < n; i++) printf("%d\n", sa[i]);

  return 0;
}
