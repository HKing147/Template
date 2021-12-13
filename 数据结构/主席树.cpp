const int N=2e5+10;
int a[N],root[N],idx;
int n,m;
vector<int> v;
struct Node{
    int l,r,cnt;
}tr[4*N+N*16];
int get(int x){
    return lower_bound(v.begin(),v.end(),x)-v.begin();
}
void pushup(int u){
    tr[u].cnt=tr[tr[u].l].cnt+tr[tr[u].r].cnt;
}
int build(int l,int r){
    int p=idx++;
    tr[p].cnt=0;
    if(l==r)
        return p;
    int mid=l+r>>1;
    tr[p].l=build(l,mid);
    tr[p].r=build(mid+1,r);
    pushup(p);
    return p;
}
int insert(int p,int l,int r,int x){
    int q=idx++;
    tr[q]=tr[p];
    if(l==r){
        tr[q].cnt++;
        return q;
    }
    int mid=l+r>>1;
    if(x<=mid)
        tr[q].l=insert(tr[p].l,l,mid,x);
    else
        tr[q].r=insert(tr[p].r,mid+1,r,x);
    pushup(q);
    return q;
}
int query(int p,int q,int l,int r,int k){
    if(l==r)
        return l;
    int cnt=tr[tr[q].l].cnt-tr[tr[p].l].cnt;
    int mid=l+r>>1;
    if(cnt>=k)
        return query(tr[p].l,tr[q].l,l,mid,k);
    else
        return query(tr[p].r,tr[q].r,mid+1,r,k-cnt);
}
int main()
{
	IOS;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    root[0]=build(0,v.size()-1);
    for(int i=1;i<=n;++i)
        root[i]=insert(root[i-1],0,v.size()-1,get(a[i]));
    while(m--){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<v[query(root[l-1],root[r],0,v.size()-1,k)]<<'\n';
    }
	return 0;
}
