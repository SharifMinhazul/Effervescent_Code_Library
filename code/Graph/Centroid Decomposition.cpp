ll n,subsize[mx];
vector<int>adj[mx];
bool b[mx];
int cpar[mx];
vector<int>ctree[mx];

void calculatesize(ll u,ll par){
	subsize[u]=1;
	for(ll i=0;i<(ll)adj[u].size();i++){
		ll v=adj[u][i];
		if(v==par or b[v]==true)continue;
		calculatesize(v,u);
		subsize[u]+=subsize[v];
	}
}
ll getcentroid(ll u,ll par,ll n){
	ll ret=u;
	for(ll i=0;i<(ll)adj[u].size();i++){
		ll v=adj[u][i];
		if(v==par or b[v]==true)continue;
		if(subsize[v]>(n/2)){
			ret=getcentroid(v,u,n);
			break;
		}
	}
	return ret;
}
void decompose(ll u, int p){
	calculatesize(u,-1);
	ll c=getcentroid(u,-1,subsize[u]);
	b[c]=true;
	cpar[c] = p;
	//if(p != -1)ctree[p].push_back(c);
	for(ll i=0;i<(ll)adj[c].size();i++){
		ll v=adj[c][i];
		if(b[v]==true)continue;
		decompose(v, c);
	}
}
