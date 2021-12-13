const int N=2e5+10;
int idx,root[N];
struct Node{
    int l,r;
    LL v;
}tr[N];
void pushup(int u){
    tr[u].v=tr[tr[u].l].v+tr[tr[u].r].v;
}
void modify(int l,int r,int& u,int idx,int x){
    if(!u)u=++idx;
    tr[u].v+=x;
    if(l==r)return;
    int mid=l+r>>1;
    if(idx<=mid)modify(l,mid,tr[u].l,idx,x);
    else modify(mid+1,r,tr[u].r,idx,x);
    // if(l==r){
    //     tr[u].v+=x;
    //     return;
    // }
    // int mid=l+r>>1;
    // if(idx<=mid)modify(l,mid,tr[u].l,idx,x);
    // else modify(mid+1,r,tr[u].r,idx,x);
    // pushup(u);
}
// x与y合并==>x
void merge(int &x,int y){
    if(!x||!y)x|=y;
    else{
        tr[x].v+=tr[y].v;
        merge(tr[x].l,tr[y].l);
        merge(tr[x].r,tr[y].r);
    }
}
// 将k分裂出区间[x,y]
int split(int l,int r,int &k,int x,int y){
    int u=++idx;
    if(x<=l&&y>=r){
        tr[u]=tr[k];
        k=0;
    }else{
        int mid=l+r>>1;
        if(x<=mid)
            tr[u].l=split(l,mid,tr[k].l,x,y);
        if(y>r)
            tr[u].r=split(mid+1,r,tr[k].r,x,y);
        pushup(k),pushup(u);
    }
    return u;
}
LL query(int l,int r,int u,int x,int y){
    if(x<=l&&y>=r)
        return tr[u].v;
    int mid=l+r>>1;
    LL res=0;
    if(x<=mid)
        res+=query(l,mid,tr[u].l,x,y);
    if(y>mid)
        res+=query(mid+1,r,tr[u].r,x,y);
    return res;
}
LL kth(int l,int r,int u,int k){
    if(l==r)
        return u;
    int mid=l+r>>1;
    if(k<=tr[tr[u].l].v)
        return kth(l,mid,tr[u].l,k);
    else
        return kth(mid+1,r,tr[u].r,k-tr[tr[u].l].v);
}
int main()
{
	// IOS;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int x;
        cin>>x;
        modify(1,n,root[1],i,x);
    }
    int last=1;
    while(m--){
        int t,x,y,z;
        cin>>t>>x>>y;
        switch(t){
            case 0:
                cin>>z;
                root[++last]=split(1,n,root[x],y,z);
                break;
            case 1:
                merge(root[x],root[y]);
                break;
            case 2:
                cin>>z;
                modify(1,n,root[x],z,y);
                break;
            case 3:
                    cin>>z;
                    cout<<query(1,n,root[x],y,z)<<'\n';
                    break;
            case 4:
                    if(y>tr[root[x]].v)cout<<-1<<'\n';
                    else cout<<kth(1,n,root[x],y)<<'\n';
                    break;
        }
    }
	return 0;
}

