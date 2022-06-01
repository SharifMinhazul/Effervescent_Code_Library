#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5+6;
const int INF = 0x3f3f3f3f;
struct edge{
    int u,v;
    int cost;
};
vector<edge>e;
vector<int>path(mx);
int dist[mx];
/*
    Time-complexity: O(|V|*|E|)
    Space-complexity: O(|V|)
    To find any negative cycle assign dist[i] = 0 for all.
    We can use floyd-warshall algorithm to find negative cycle too.
    *Handle LL carefully.
*/
void bellmanford(int s,int n){
    int m = e.size();
    memset(dist,0x3f3f3f3f,sizeof dist);
    dist[s] = 0;
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < m; ++j)
            if (dist[e[j].u] < INF)
                if (dist[e[j].v] > dist[e[j].u] + e[j].cost) {
                    dist[e[j].v] = max(-INF, dist[e[j].u] + e[j].cost);
                    path[e[j].v] = e[j].u;
                    x = e[j].v;
                }
    }

    if (x == -1)
        cout << "No negative cycle from " << s;
    else {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = path[y];

        vector<int> path;
        for (int cur = y; ; cur = path[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "Negative cycle: ";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] << ' ';
    }
}
int main(){

}