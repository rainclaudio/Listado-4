#include <bits/stdc++.h>
/*
Problem Id: DICT "Search in the dictionary"
page: www.spoj.com
TRIE cortesía de geeks for geeks :D
Made By Claudio Rain
*/
using namespace std;
typedef std::string str;
const int ALPHABET_SIZE = 26;

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    char letter;
    bool isEndOfWord;
    int numChilds;
};
struct TrieNode *getNode(void){
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    pNode->numChilds = 0;
    return pNode;
}
void insert(struct TrieNode *root, string key){
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            pCrawl->children[index] = getNode();
            pCrawl->children[index]->letter = key[i];
            pCrawl->numChilds++;
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}
void getAverage(struct TrieNode*root,int counter,int& sum){
  if(root->isEndOfWord){
    sum += counter;
  }
  if((root->numChilds > 1 && root->letter != '#') || (root->isEndOfWord && root->numChilds > 0))counter++;
  for(int i = 0; i < ALPHABET_SIZE; ++i){
    if(root->children[i] != NULL){
      getAverage(root->children[i],counter,sum);
    }
  }
}
void destroyTree(struct TrieNode *root){
  for(int i = 0; i < ALPHABET_SIZE; ++i){
    if(root->children[i] != NULL){
      destroyTree(root->children[i]);
      root->children[i] = NULL;
    }
  }
}
void fill_vector(struct TrieNode *root,std::vector<str>& collector, str word,str v){
  if(root -> isEndOfWord && word != v){
    collector.push_back(word);
  }
  for (int i = 0; i < ALPHABET_SIZE; i++){
    if(root->children[i] != NULL){
      word.push_back(root->children[i]->letter);
      fill_vector(root->children[i],collector,word,v);
      word.pop_back();
    }
  }
}
std::vector<str> get_answer(struct TrieNode *root,str var){
  std::vector<str> answer;
  struct TrieNode *pCrawl = root;
  bool exists = true;

  for(int i = 0; i < var.size(); ++i){

    int index = var[i] - 'a';
    if(!pCrawl->children[index]){
      exists = false;
      break;
    }
    pCrawl = pCrawl->children[index];
  }

  if(exists)fill_vector(pCrawl,answer,var,var);
  return answer;
}


void printVector(std::vector<str> v){
  if(!v.empty()){
    for(auto it: v){
      std::cout<<'\n' << it << '\n';
    }
  } else printf("\nNo match.\n");
}
int main(){
    int n,k;
    std::cin >> n;
    str var;

    struct TrieNode *root = getNode();
    root->letter = '#';
    while(n--){
    // printf("\n");
      std::cin >> var;
      insert(root,var);
    }

    std::cin >> k;
    int case1 = 1;
    while (k--) {
      // printf("\n");
      std::cin >> var;
      std::vector<str>answer = get_answer(root,var);
      if(case1 != 1)printf("\n");
      printf("\nCase #%d:\n",case1);
      printVector(answer);
      case1++;
    }
    return 0;
}
