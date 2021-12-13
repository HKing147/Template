const int N=1e5+10;
int root,idx;
struct Node{
    int l,r;
    int v,key;
    int size;
    void init(int _v){
        v=_v,key=rand();
        size=1;
    }
}tr[N];
void pushup(int u){
    tr[u].size=tr[tr[u].l].size+tr[tr[u].r].size+1;
}
// 按值分裂(x中的节点的值都<=v)
void split(int u,int v,int &x,int &y){
    if(!u)x=y=0;
    else{
        if(tr[u].v<=v){
            x=u;
            split(tr[u].r,v,tr[u].r,y);
        }else{
            y=u;
            split(tr[u].l,v,x,tr[u].l);
        }
        pushup(u);
    }
}
// 合并x与y
int merge(int x,int y){
    if(!x||!y)return x+y;
    if(tr[x].key>tr[y].key){ //这里条件可以随便写，只要是随机就行
        tr[x].r=merge(tr[x].r,y);
        pushup(x);
        return x;
    }else{
        tr[y].l=merge(x,tr[y].l);
        pushup(y);
        return y;
    }
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
int main()
{
	IOS;
    int m;
    W(m){
        int t,x;
        cin>>t>>x;
        switch(t){
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                cout<<get_rk(x)<<'\n';
                break;
            case 4:
                cout<<tr[get_val(x)].v<<'\n';
                break;
            case 5:
                cout<<tr[pre(x)].v<<'\n';
                break;
            case 6:
                cout<<tr[nxt(x)].v<<'\n';
                break;
        }
    }
	return 0;
}

