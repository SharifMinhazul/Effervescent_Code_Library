#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
const int mx = 1e5 + 5;
using ll = long long;
using pll = pair<ll, ll>;
vector<pll>adj[mx];
int dis[mx];
bool vis[mx];
//Complexity O(V+ElogV)
void Dijkstra(int src) {
    priority_queue<pll, vector<pll>, greater<pll> >pq;
    pq.push({ 0,src });
    memset(dis, 0x3f3f3f3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().ss;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto v : adj[u]) {
            if (dis[v.ss] > dis[u] + v.ff) {
                dis[v.ss] = dis[u] + v.ff;
                pq.push({ dis[v.ss],v.ss });
            }
        }
    }
}
int main() {

}