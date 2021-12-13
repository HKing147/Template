const int N=1e5+10;
int root,idx;
struct Node{
    int l,r;
    int v,key;
    int size;
    int rev;// 区间操作的懒标记
    void init(int _v){
        v=_v,key=rand();
        size=1;
    }
}tr[N];
void pushup(int u){
    tr[u].size=tr[tr[u].l].size+tr[tr[u].r].size+1;
}
void pushdown(int u){
    if(tr[u].rev){
        tr[tr[u].l].rev^=1;
        swap(tr[tr[u].l].l,tr[tr[u].l].r);
        tr[tr[u].r].rev^=1;
        swap(tr[tr[u].r].l,tr[tr[u].r].r);
        tr[u].rev=0;
    }
}
// 按大小size分裂(x中包含前size个节点)
void split(int u,int size,int &x,int &y){
    if(!u)x=y=0;
    else{
        pushdown(u);// 分裂前下传懒标记
        if(tr[tr[u].l].size<size){
            x=u;
            split(tr[u].r,size-tr[tr[u].l].size-1,tr[u].r,y);
        }else{
            y=u;
            split(tr[u].l,size,x,tr[u].l);
        }
        pushup(u);
    }
}
// 合并x与y
int merge(int x,int y){
    if(!x||!y)return x+y;
    if(tr[x].key>tr[y].key){ //这里条件可以随便写，只要是随机就行
        pushdown(x);// 合并前下传懒标记
        tr[x].r=merge(tr[x].r,y);
        pushup(x);
        return x;
    }else{
        pushdown(y);// 合并前下传懒标记
        tr[y].l=merge(x,tr[y].l);
        pushup(y);
        return y;
    }
}
// 翻转区间[l,r]
void reverse(int l,int r){
    int x,y,z;
    split(root,l-1,x,y);// root按大小l-1分裂为x与y
    split(y,r-l+1,y,z);// y按大小r-l+1分裂为y与z ==> y就是所要操作的区间
    tr[y].rev^=1;
    swap(tr[y].l,tr[y].r);
    root=merge(merge(x,y),z);
}
// 插入值为v的节点
void insert(int v){
    int x,y;
    split(root,v,x,y);//按值v分裂为x、y两棵树
    tr[++idx].init(v);//新节点
    root=merge(merge(x,idx),y);//x与新节点合并，再与y合并
}
// 删除值为v的一个节点
void del(int v){
    int x,y,z;
    split(root,v,x,z);//先按值v分裂为x与z
    split(x,v-1,x,y);//再将x按值v-1分裂为x与y(y上节点值都为v)
    y=merge(tr[y].l,tr[y].r);//合并y的左右子树=>删除y这个节点
    root=merge(merge(x,y),z);
}
// 查询值为v的节点的排名
int get_rk(int v){
    int rk,x,y;
    split(root,v-1,x,y);
    rk=tr[x].size+1;
    root=merge(x,y);
    return rk;
}
// 查询排名为k的节点的编号
int get_val(int k){
    int u=root;
    while(u){
        if(tr[tr[u].l].size>=k)u=tr[u].l;
        else if(tr[tr[u].l].size+1==k)return u;
        else k-=tr[tr[u].l].size+1,u=tr[u].r;
    }
    return -1;
}
// 查询值为v的节点的前驱(编号)
int pre(int v){
    int u,x,y;
    split(root,v-1,x,y);
    u=x;
    while(tr[u].r)u=tr[u].r;
    root=merge(x,y);
    return u;
}
// 查询值为v的节点的后继(编号)
int nxt(int v){
    int u,x,y;
    split(root,v,x,y);
    u=y;
    while(tr[u].l)u=tr[u].l;
    root=merge(x,y);
    return u;
}
void output(int u){
    pushdown(u);
    if(tr[u].l)output(tr[u].l);
    cout<<tr[u].v<<" ";
    if(tr[u].r)output(tr[u].r);
}
int main()
{
	IOS;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        insert(i);
    while(m--){
        int l,r;
        cin>>l>>r;
        reverse(l,r);
    }
    output(root);
    cout<<'\n';
	return 0;
}

