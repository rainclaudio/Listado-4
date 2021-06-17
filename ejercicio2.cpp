#include <iostream>
#include <vector>
/*
Problem ID: The hunt for Gollum
Page: www.spoj.com
KMP cortesía de geeks for geeks :D
Solved by Claudio Rain
*/
typedef std::vector<int> v;
typedef std::string st;
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

v KMPSearch(std::string needle, std::string Haystack){
  v answer;
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
          answer.push_back(i-j + 1);
            // printf("%d\n", i - j);
            j = lps[j - 1];
        }else if (i < N && needle[j] != Haystack[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
  return answer;
}

void printGraph(std::vector<std::vector<int>> vector){
  std::cout << "VECTOR: " << '\n';
  for(int i = 0; i < vector.size(); ++i){
    for(int j = 0; j < vector[i].size(); ++j){
      std::cout << vector[i][j] << ' ';
    }
    std::cout  << '\n';
  }
}

int main(int argc, char const *argv[]) {
  int n1,n2;
  std::cin >> n1 >> n2;
  std::cout  << '\n';
  int m1,m2;
  char GollumPlaces[n1 + 1][n2+1];
  for(int i = 1; i <= n1; ++i){
    scanf("%s\n",GollumPlaces[i]);
  }
  // std::cout << "gollumPlaces" << '\n';
  // for (size_t i = 1; i <= n1; i++) {
  //   std::cout << GollumPlaces[i] << '\n';
  // }
  std::cin >> m1 >> m2;
  std::cout << '\n';
  // std::cout << "ok" << '\n';
  // std::cout << m1<<' '<<m2<< '\n';
  int first = true;
  char map[m1][m2+1];
  for(int i = 0; i < m1; ++i){
      scanf("%s",map[i]);
  }
  // for (size_t i = 0; i < m1; i++) {
  //   std::cout << map[i] << '\n';
  // }
  bool nothingFound = true;
  for(int i = 0; i <= (m1 - n1); ++i){

      std::string patttern(GollumPlaces[1]);
      std::string text(map[i]);

      v var = KMPSearch(patttern,text);
      if(!var.empty()){
        std::vector<std::vector<int>> vector(n1-1);

        bool isValid = false;
        // std::cout << "FILA: "<<i << '\n';
        // for(auto it: var)std::cout << it << ' ';
        // std::cout  << '\n';
        // std::cout << "Procesando: " << '\n';
        for(int k = i+1,num = 2; num <= n1; k++,num++){
          // std::cout<<'\t' << "K fila: "<<k << '\n';
          std::string p1(GollumPlaces[num]);
          std::string t1(map[k]);
          // std::cout << '\t'<<p1 << '\n';
          // std::cout << '\t'<<t1 << '\n';
          vector[num - 2] = KMPSearch(p1,t1);
        }
        // printGraph(vector);

        // recorre el arreglo de las primeras ocurrencias
        for(int l = 0; l < var.size(); ++l){
          int currentValue = var[l];
          // comprueba que se repiten para las otras
          // debemos encontrar cada coincidencia
          int counterOcurrences = 1;
          for(int m = 0; m < vector.size(); ++m){
            // encontramos una coincidencia particular
            for(int o = 0; o < vector[m].size(); ++o){
              if(vector[m][o] == currentValue){
                counterOcurrences++;
                isValid = true;
                break;
              }
              else if(vector[m][o] > currentValue){
                isValid = false;
                break;
              }
            }
          }
          if(isValid && counterOcurrences == n1){
            nothingFound = false;
            if(!first)printf("\n");
            printf("(%d,%d)\n",i+1,currentValue);
            first = false;
          }
          counterOcurrences = 1;
        }
      }
  }
  if(nothingFound)std::cout << "NO MATCH FOUND..." << '\n';
  return 0;
}
