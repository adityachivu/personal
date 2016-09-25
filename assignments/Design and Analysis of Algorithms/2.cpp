#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

#define MAX 1100
#define INF 1e18


vector<pair<int, double> > graph[MAX];
vector<int> component[MAX];
stack<int> Stack;
bool visited[MAX];
int comp[MAX], cnt, block[MAX];

double minwt = -INF;

void dfs( int v )
{
	visited[v] = true;
	component[cnt].push_back(v);

	for(int i=0 ; i<graph[v].size() ; i++)
	{
		int u = graph[v][i].first;
		if(!visited[u])
			dfs(u);
	}
}

int find(int x)
{
	if(x != block[x])
		block[x] = find(block[x]);
	return block[x];
}

int main()
{
	ifstream infile;
	infile.open("data.txt");
	int r, c, m;
	infile>>r>>c>>m;

	for(int i=0 ; i<m ; i++)
	{
		int a, b;
		double w;
		infile>>a>>b>>w;

		graph[a].push_back(make_pair(b, w));
		graph[b].push_back(make_pair(a, w));
	}

	for(int i=1 ; i<=r ; i++)
	{
		if(!visited[i])
		{
			cnt++;
			dfs(i);
		}
	}

	int mx = 0;

	for(int i=0 ; i<MAX ; i++)
		mx = max(mx, (int)component[i].size()), block[i] = i;

	cout<<mx<<"\n";

	for(int i=1 ; i<MAX ; i++)
	{
		if(mx == (int)component[i].size())
		{
			double sum = 0;
			vector<pair<double, pair<int, int> > > edges; 
			for(int j=0 ; j<component[i].size() ; j++)
			{
				int u = component[i][j];
				for(int k=0 ; k<graph[u].size() ; k++)
				{
					int v = graph[u][k].first;
					edges.push_back(make_pair(graph[u][k].second, make_pair(v, u)));
				}
			}

			sort(edges.begin(), edges.end());

			for(int j=0 ; j<edges.size() ; j++)
			{
				double weight;
				int a, b;
				weight = edges[j].first;
				a = find(edges[j].second.first), b = find(edges[j].second.second);

				if(a == b)
					continue;

				block[b] = a;
				sum += weight;
			}

			minwt = max(minwt, sum);
		}
	}

	cout<<minwt<<"\n";

	return 0;
}
