#include<bits/stdc++.h>

using namespace std;

#define endl "\n"
#define mod 1000000007

typedef long long ll;

class graph
{
	ll no_vertices, no_edges;
	bool weighted;
	vector<vector<pair<ll, ll>>> adj;
public:
	graph(ll n, ll m, bool weight_chk)
	{
		weighted = weight_chk;
		no_vertices = n;
		no_edges = m;
		vector<pair<ll, ll>> emp;
		for(ll i = 0; i < n; i++)
			adj.push_back(emp);
		if(weight_chk)
		{
			 ll x, y, w;
			for(ll i = 0; i < m; i++)
			{
				cin>>x>>y>>w;
				addedge({x, y}, w);
			}
		}
		else
		{
			ll x, y;
			for(ll i = 0; i < m; i++)
			{
				cin>>x>>y;
				addedge({x, y});
			}
		}
	}
	void addedge(pair<ll, ll> edge, ll weight = 1)
	{
		adj[edge.first].push_back({edge.second, weight});
		adj[edge.second].push_back({edge.first, weight});
	}
	void dfs(ll, ll);
	void bfs(ll, vector<ll> &);
	void dijkstra(ll s, vector<ll> &);
};

void graph::dfs(ll p, ll c)
{
	for(ll i = 0; i < adj[c].size(); i++)
	{
		if(adj[c][i].first != p)
		{
			dfs(c, adj[c][i].first);
		}
	}
	return;
}

void graph::bfs(ll s, vector<ll> &dist)
{
	vector<bool> used(no_vertices, false);
	queue<ll> visit;
	visit.push(s);
	used[s] = true;
	dist[s] = 0;
	while(visit.size() > 0)
	{
		ll top = visit.front();
		ll u;
		for(ll i = 0; i < adj[top].size(); i++)
		{
			u = adj[top][i].first;
			if(!used[u])
			{
				dist[u] = dist[top]+1;
				used[u] = true;
				visit.push(u);
			}
		}
		visit.pop();
	}
	return;
}

void graph::dijkstra(ll s, vector<ll> &dist)
{
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> nodes;
	for(ll i = 0; i < no_vertices; i++)
		dist[i] = 1e18;
	dist[s] = 0;
	nodes.push({0, s});
	while(nodes.size() > 0)
	{
		ll top = nodes.top().second;
		nodes.pop();
		pair<ll, ll> u;
		for(ll i = 0; i < adj[top].size(); i++)
		{
			u = adj[top][i];
			if(dist[top] + u.second < dist[u.first])
			{
				dist[u.first] = dist[top] + u.second;
				nodes.push({dist[u.first], u.first});
			}
		}
	}
	return;
}

int main()
{
	ll n, m;
	cin>>n>>m;
	graph a = graph(n, m, 1);
	vector<ll> dist(n);
	a.dijkstra(2, dist);
	for(ll x:dist)
		cout<<x<<" ";
    return 0;
}
