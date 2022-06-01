int sz[maxn];
void getsz(int v,int p){
  sz[v]=1;
  for(auto u : g[v])
    if(u!=p){
      getsz(u,v);
      sz[v]+=sz[u];
    }
}
//SACK O(nlog^2n)
map<int,int>*cnt[maxn];
void dfs(int v,int p){
  int mx=-1,bigChild=-1;
  for(auto u : g[v])
   if(u!=p){
     dfs(u,v);
     if(sz[u]>mx)mx=sz[u],bigChild=u;
   }
  if(bigChild!=-1)cnt[v]=cnt[bigChild];
  else cnt[v]=new map<int,int>();
 (*cnt[v])[col[v]]++;
  for(auto u : g[v])
   if(u!=p && u!=bigChild){
     for(auto x :*cnt[u])
      (*cnt[v])[x.first]+=x.second;
   }
}
//SACK-O(nlogn)
vector<int>*vec[maxn];
int cnt[maxn];
void dfs(int v,int p,bool keep){
  int mx=-1,bigChild=-1;
  for(auto u : g[v])
   if(u!=p&&sz[u]>mx)mx=sz[u],bigChild=u;
  for(auto u : g[v])
   if(u!=p && u!=bigChild)dfs(u,v,0);
  if(bigChild!=-1)
    dfs(bigChild,v,1),vec[v]=vec[bigChild];
  else vec[v]=new vector<int>();
  vec[v]->push_back(v);cnt[col[v]]++;
  for(auto u : g[v])
   if(u!=p && u!=bigChild)
     for(auto x :*vec[u]){
       cnt[col[x]]++;
       vec[v]->push_back(x);
     }
/*in this step*vec[v]contains all of the subtree of vertex v.*/
  if(keep==0)
    for(auto u:*vec[v])cnt[col[u]]--;
}
