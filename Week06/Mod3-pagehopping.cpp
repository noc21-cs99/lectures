#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define vi verticestor<int>
#define vll verticestor<long long int>

#define N 101
#define INF 1e9

static int dist[N][N];

int main()
{

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	std::ios::sync_with_stdio(false);

	std::cout << std::fixed;
	std::cout << std::setprecision(3);

	int cases = 0;
	int u, v;

	// Page Hopping Solution 
	// Adapted from:
	// https://quickgrid.blogspot.com/2016/12/Cpp-Solution-UVA-821-Page-Hopping-Floyd-Warshall-Simulation-Explanation-and-stl-set.html

	// Scan source node u and its adjacent node v
	// When both u and v zero then exit
	while ((cin >> u >> v) && (u || v))
	{

		// Use a set to track the vertices we have in the graph.
		set<int> vertices;

		// Since the constraints are simple a 2D matrix will work here
		// Reset all the previously calculated value for new graph
		// Set distances infinite to mark all nodes unreachable from any other node
		// dist[i][j] holds the distance from node i to node j
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dist[i][j] = INF;
			}
		}
		// Set the self distances as zero
		for (int i = 0; i < N; ++i)
		{
			dist[i][i] = 0;
		}

		// Subtracting one for indexing in the distance array:
		dist[u - 1][v - 1] = 1;
		vertices.insert(u);
		vertices.insert(v);

		// Input a graph if both u and v
		while ((cin >> u >> v) && (u || v))
		{
			// Subtracting one for indexing in the distance array:
			// Set the edge weight as 1 since no edge weights will be given
			dist[u - 1][v - 1] = 1;
			// Insert both nodes into set so that repeating nodes are there only once
			vertices.insert(u);
			vertices.insert(v);
		}

		// Floyd Warshall algorithm, time complexity: O(N^3)
		for (int k = 0; k < N; ++k)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					// Check to see if the path can be improved by going through
					// intermediate node k. Going from i -> .. -> k then k -> .. -> j
					// Otherwise that previously calculated path
					// i -> .. -> j without taking k is shorter
					if (dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		// For each node just calculate the shortest path to every other node
		// The shortest paths are calculated and stored now on graph matrix
		int sum = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i != j && dist[i][j] != INF)
				{
					sum = sum + dist[i][j];
				}
			}
		}

		// Just divide the total distance by edge count to get the answer
		int setSize = vertices.size();
		cases++;
		cout << "Case " << cases << ": average length between pages = " << (float)sum / (setSize * (setSize - 1)) << " clicks\n";
	}

	return 0;
}
