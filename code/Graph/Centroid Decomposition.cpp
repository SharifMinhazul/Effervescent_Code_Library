ll n,subsize[mx];
vector<ll>adj[mx];
char ans[mx];
bool brk[mx];
void calculatesize(ll u,ll par){
	subsize[u]=1;
	for(ll i=0;i<(ll)adj[u].size();i++){
		ll v=adj[u][i];
		if(v==par or brk[v]==true)continue;
		calculatesize(v,u);
		subsize[u]+=subsize[v];
	}
}
ll getcentroid(ll u,ll par,ll n){
	ll ret=u;
	for(ll i=0;i<(ll)adj[u].size();i++){
		ll v=adj[u][i];
		if(v==par or brk[v]==true)continue;
		if(subsize[v]>(n/2)){
			ret=getcentroid(v,u,n);
			break;
		}
	}
	return ret;
}
void decompose(ll u,char rank){
	calculatesize(u,-1);
	ll c=getcentroid(u,-1,subsize[u]);
	brk[c]=true;
	ans[c]=rank;
	for(ll i=0;i<(ll)adj[c].size();i++){
		ll v=adj[c][i];
		if(brk[v]==true)continue;
		decompose(v,rank+1);
	}
}
int main(){
	scanf("%lld",&n);
	for(ll i=0;i<n-1;i++){
		ll a,b;
		scanf("%lld %lld",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	decompose(1,'A');
	for(ll i=1;i<=n;i++){
		printf("%c",ans[i]);
	}
}
