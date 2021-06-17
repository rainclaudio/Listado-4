#include <bits/stdc++.h>
/*
Problem Id: 12526 "Cellphone Typing"
page: www.onlinejudge.org
TRIE cortesía de geeks for geeks :D
Made By Claudio Rain
*/
using namespace std;

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
int main(){
    int n;

    std::string var;
    while(scanf("%d",&n)!= EOF){

      struct TrieNode *root = getNode();
      root->letter = '#';

      for(int i = 0; i < n; ++i){
        std::cin >> var;
        insert(root,var);
      }
    int sum = 0;
    getAverage(root,1,sum);
    double answer = (double)sum / n;
    printf("%.2f\n",answer);
    }
    return 0;
}
