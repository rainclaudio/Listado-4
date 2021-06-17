#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)n;++i)
#define invrep(i,n) for(int i=n-1;i>=0;--i)
/*
Problem Id: PLD Palindromes
page: www.spoj.com
#Rolling Hash
Made By Claudio Rain
*/

using namespace std;
typedef unsigned long long ull;
ull mod[] = {(int)1e9+7, (int)1e9+9};
//largo máximo que puede tener un string
int maxstrlen = 1e6;

std::string S;
std::string Sinverted;
int k;
class RH {
	static vector<ull> x[2];
	vector<ull> h[2];
	string str;
	int n;

	//private: usar el método público para obtener el hash
	ull hash(int a, int start, int len) {
		ull ans = 0, end = start + len;
		//descomentar si se consideran substrings cíclicos
		//if (end > n) {end -= n; ans = h[a][0]*x[a][n-start] %mod[a];}
		ans += h[a][start] - h[a][end]*x[a][len] %mod[a] + mod[a];
		return ans %mod[a];
	}

public: RH() {}
	//str: string del cual se producen substrings a hashear
	RH(const string &str) { // complejidad: O(n)
		this->str = str;
		n = str.size();
		if (x[0].empty()) rep(a, 2) {
			x[a].assign(maxstrlen+1, 1);
			rep(i, maxstrlen) x[a][i+1] = x[a][i]*127 %mod[a];
		}
		rep(a, 2) {
			h[a].assign(n+1, 0);
			invrep(i, n) h[a][i] = (h[a][i+1]*127 + str[i]) %mod[a];
		}
	}

	//obtiene el hash de un substring que comienza en el índice “start”
	//y tiene largo “len”.
	ull hash(int start, int len) { // complejidad: O(1)
		return hash(0, start, len) << 32 | hash(1, start, len);
	}

	//si se usan, insertar aquí los métodos opcionales 1 o 2.
};
//esta línea es importante para que el código compile
vector<ull> RH::x[2];

int main(int argc, char const *argv[]) {
  std::cin >> k;
  std::cin >> S;
  int counterPalindromes = 0;
  // O(n)
  for(int i = 1; i <= S.length(); ++i){
    Sinverted.push_back(S[S.length()-i]);
  }
  RH rh(S);
  RH rh2(Sinverted);
  // O(n)
  for(int i = 0; i < S.length() - k + 1; ++i){
    if(rh.hash(i,k) == rh2.hash(S.length() - k - i,k))counterPalindromes++;
  }
  std::cout << counterPalindromes << '\n';
  return 0;
}
