#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

#define MAX 1100
#define INF 1e18


vector<pair<int, double> > graph[MAX], rgraph[MAX];
stack<int> Stack;
bool visited[MAX];
int comp[MAX], cnt;
vector<int> cmp[MAX];
double diameter = -INF, dist[MAX], shortestPath[MAX][MAX];

void rdfs(int v){
	visited[v] = true;
	cmp[cnt].push_back(v);
	comp[v] = cnt;

	for(int i=0 ; i<rgraph[v].size() ; i++){
		int u = rgraph[v][i].first;
		if(!visited[u])
			rdfs(u);
	}
}

void dfs(int v){
	visited[v] = true;

	for(int i=0 ; i<graph[v].size() ; i++){
		int u = graph[v][i].first;
		if(!visited[u])
			dfs(u);
	}

	Stack.push(v);
}

int main(){
	ifstream infile;
	infile.open("data.txt");
	int r, c, m;
	infile>>r>>c>>m;

	for(int i=0 ; i<m ; i++){
		int a, b;
		double w;
		infile>>a>>b>>w;

		graph[a].push_back(make_pair(b, w));
		rgraph[b].push_back(make_pair(a, w));
	}

	for(int i=1 ; i<=r ; i++){
		if(!visited[i])
			dfs(i);
	}

	for(int i=0 ; i<MAX ; i++)
		visited[i] = false;

	while(!Stack.empty()){
		int v = Stack.top();
		Stack.pop();

		if(!visited[v]){
			cnt++;
			rdfs(v);
		}
	}

	int mx = 0;

	for(int i=1 ; i<MAX ; i++)
		mx = max(mx, (int)cmp[i].size());

	for(int i=0 ; i<MAX ; i++)
		dist[i] = INF;
		
    for(int i=0 ; i<MAX ; i++)
        for(int j=0 ; j<MAX ; j++)
            if(i != j)
                shortestPath[i][j] = INF;
	
	for(int i=0 ; i<MAX ; i++)
	    shortestPath[i][i] = 0;

	if(mx>1)
	{
		for(int i=1 ; i<MAX ; i++)
		{
			if(mx == (int)cmp[i].size())
			{
				vector<pair<pair<int, int>, double> > edges;
				for(int j=0 ; j<cmp[i].size() ; j++)
				{
					int u = cmp[i][j];
					for(int k=0 ; k<graph[u].size() ; k++)
					{
						int v = graph[u][k].first;
						if(comp[v] != comp[u])
						    continue;
						edges.push_back(make_pair(make_pair(u, v), graph[u][k].second));
					}
				}

				for(int j=1 ; j<cmp[i].size() ; j++)
				{
					for(int k=0 ; k<edges.size() ; k++)
					{
						int u = edges[k].first.first, v = edges[k].first.second;
						double weight = edges[k].second;
						if(dist[u] != INF && dist[u] + weight < dist[v])
							dist[v] = dist[u] + weight;
					}
				}

				int flag = 0;

				for(int j=0 ; j<edges.size() ; j++)
				{
					int u = edges[j].first.first, v = edges[j].first.second;
					double weight = edges[j].second;
					if(dist[u] != INF && dist[u] + weight < dist[v])
					{
						cout<<"Graph contains negative cycle!!!\n";
						flag = 1;
						break;
					}
				}

				if(!flag){
					for(int j=0 ; j<cmp[i].size() ; j++)
					{
					    for(int k=0 ; k<cmp[i].size() ; k++)
					    {
					        for(int l=0 ; l<cmp[i].size() ; l++)
					        {
					            int a, b, c;
					            a = cmp[i][j], b = cmp[i][k], c = cmp[i][l];
					            shortestPath[b][c] = min(shortestPath[b][c], shortestPath[b][a] + shortestPath[a][c]);
					        }
					    }
					}
					
					for(int j=0 ; j<cmp[i].size() ; j++)
					{
					    for(int k=0 ; k<cmp[i].size() ; k++)
					    {
					        int a, b;
					        a = cmp[i][j], b = cmp[i][k];
					        diameter = max(diameter, shortestPath[a][b]);
					    }
					}
                }
   			}
		}
	} else 
		diameter = 0;

	cout<<diameter<<"\n";

	return 0;
}
