int id[N],idx;
int fa[N],sz[N],dep[N],son[N],tp[N];
LL p[N],cnt[N],np[N],ncnt[N];
void dfs1(int u,int d){
    if(ne[u].size()==0)
        leaf.push_back({0,u});
    dep[u]=d,sz[u]=1;
    for(auto s: ne[u]){
        dfs1(s,d+1);
        sz[u]+=sz[s];
        if(sz[son[u]]<sz[s])son[u]=s;
    }
}
void dfs2(int u,int t){
    tp[u]=t,id[u]=++idx,ncnt[idx]=cnt[u],np[idx]=p[u];
    if(son[u])dfs2(son[u],t);
    for(auto s: ne[u]){
        if(s!=son[u])
            dfs2(s,s);
    }
}
LL query_path_sum(int u,int v){
    LL res=0;
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]])swap(u,v);
        res+=query_s(1,id[tp[u]],id[u]);
        u=fa[tp[u]];
    }
    if(u!=v){
        if(dep[u]<dep[v])swap(u,v);
        res+=query_s(1,id[v]+1,id[u]);
    }
    return res;
}

