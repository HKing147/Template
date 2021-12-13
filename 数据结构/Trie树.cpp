int son[N][26], cnt[N], idx;
// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以每个节点结尾的单词数量

// 插入一个字符串
void insert(char *str) {
  int p = 0;
  for (int i = 0; str[i]; i++) {
    int u = str[i] - 'a';
    if (!son[p][u])
      son[p][u] = ++idx;
    p = son[p][u];
  }
  cnt[p]++;
}

// 查询字符串出现的次数
int query(char *str) {
  int p = 0;
  for (int i = 0; str[i]; i++) {
    int u = str[i] - 'a';
    if (!son[p][u])
      return 0;
    p = son[p][u];
  }
  return cnt[p];
}

/* --------------------------------------- */
const int N=1e5+10;
struct Node{
    int ne[26];
    int cnt;
}node[N];
int idx;
// 插入字符串s
void Insert(string s){
    int p=0,i=0;
    while(i<s.length()){
        if(!node[p].ne[s[i]-'a'])
            node[p].ne[s[i]-'a']=++idx;
        p=node[p].ne[s[i]-'a'];
        ++i;
    }
    node[p].cnt++;
}
// 查询字符串s出现的次数
int query(string s){
    int p=0,i=0;
    while(i<s.length()){
        if(node[p].ne[s[i]-'a']==0)
            return 0;
        p=node[p].ne[s[i]-'a'];
        ++i;
    }
    return node[p].cnt;
}
