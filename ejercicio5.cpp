
// C++ program for building suffix array of a given text
#include <bits/stdc++.h>
using namespace std;
// Structure to store information of a suffix

// const int MAXN=100100;
char T[MAXN];
#define MAX_N 100100

struct suffix
{
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
};

// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b)
{
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
               (a.rank[0] < b.rank[0] ?1: 0);
}

// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
int *buildSuffixArray(char *txt, int n)
{
    // A structure to store suffixes and their indexes
    struct suffix suffixes[n];

    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabatically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }

    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);

    // At this point, all suffixes are sorted according to first
    // 2 characters.  Let us sort suffixes according to first 4
    // characters, then first 8 and so on
    int ind[n];  // This array is needed to get the index in suffixes[]
                 // from original index.  This mapping is needed to get
                 // next suffix.
    for (int k = 4; k < 2*n; k = k*2)
    {
        // Assigning rank and index values to first suffix
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        // Assigning rank to suffixes
        for (int i = 1; i < n; i++)
        {
            // If first rank and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else // Otherwise increment rank and assign
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        // Assign next rank to every suffix
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                  suffixes[ind[nextindex]].rank[0]: -1;
        }

        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+n, cmp);
    }

    // Store indexes of all sorted suffixes in the suffix array
    int *suffixArr = new int[n];
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    // Return the suffix array
    return  suffixArr;
}
string get_Color(int pos,int LIMIT1){
  if(pos >= LIMIT1) return "RED";
  // else if(pos >= 5) return "BLUE";
  return "GREEN";
}
// A utility function to print an array of given size
void printArr(int arr[], int n,string str1,int LIMIT1)
{
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
        std::cout << str1.substr(arr[i])<<" "<<get_Color(arr[i],LIMIT1) << '\n';
      }
    cout << endl;
}
int LCP[MAX_N], phi[MAX_N], PLCP[MAX_N];
void computeLCP(int *sa,int n,char *s){//O(n)
        phi[sa[0]]=-1;
        for(int i = 1; i < n; ++i){
          phi[sa[i]]=sa[i-1];
        }
        int L=0;
        for(int i = 0; i < n; ++i){
          if(phi[i]==-1) {PLCP[i]=0; continue;}
          while(s[i+L]==s[phi[i]+L]) L++;
          PLCP[i]=L;
          L=max(L-1, 0);
        }
        for(int i = 0; i < n; ++i){
           LCP[i]=PLCP[sa[i]];
        }
}
/*
el kilometraje del auto es 58 mil km
tenemos que cambiar la correa la cual se va desgastando
para los autos es 50k y para los camiones es 100k
el repuesto de consique mediante el : AAAH se me olvidió
no te olvides de pasar la cuota actual
*/
void printLCP(int n,string str1){
  std::cout << "LCP  n equal to: " << n << '\n';
  for(int i = 0; i < n; ++i){
    std::cout << LCP[i] << ' ';
  }
  std::cout  << '\n';

}
int get_answer(int arr[],int n,string str1, int LIMIT1){
  int answer = 0;
  for(int i = n - 1; i >= 4; --i){
    if(LCP[i] > answer && (get_Color(arr[i],LIMIT1) != get_Color(arr[i - 1],LIMIT1))){
      // printf("current answer: LCP:  %d and  arr: %d\n",LCP[i],arr[i] );
      // std::cout << "substr.arr[i-1]: "<<str1.substr(arr[i-1]) << '\n';
      // std::cout << "substr.arr[i]: "<<str1.substr(arr[i])<< '\n';
      answer = LCP[i];
    }
  }
  return answer;
}
int setup(std::string str1, std::string str2){
  int answer = 0;
  // char txt[str1.size() + str2.size()] = str1 + str2;
  int sizeS1 = str1.size();
  int sizeS2 = str2.size();
  str1.push_back('!');
    // str1 +='!';
    // // string n3("bcad#daca%");
    // str1.append(n3);
    str1.append(str2);
    // str1 +='#';
    str1.push_back('#');
    // str1.append("daca/");
    // int n = str1.size() + str2.size();
    int n = str1.size();
    int *suffixArr = buildSuffixArray(&str1[0],  n);
    // cout << "Following is suffix array for " << str1 << endl;
    // printArr(suffixArr, n,str1,sizeS1);
    computeLCP(suffixArr,n,&str1[0]);
    // printLCP(n,str1);
    answer = get_answer(suffixArr,n,str1,sizeS1);
  return answer;
}
int main(int argc, char const *argv[]) {
  std::string str1;
  std::string str2;
  std::cin >> str1;
  std::cin >> str2;
  // scanf("%s",str1 );
  // scanf("%s",str2 );
  std::cout << setup(str1,str2) << '\n';
  return 0;
}
