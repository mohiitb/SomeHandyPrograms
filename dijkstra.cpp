//Time Complexity for DFS and BFS: O(V+E)

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph{
	private: vector<vector<pair<int,int> > > V;
			 int Vs;
	public:
		Graph(int);
		bool addEdge(int,int,int);
		void simpleTraverse();
		void dijkstra(int);
};

Graph::Graph(int Vnums){
	V.resize(Vnums);
	Vs = Vnums;
}
bool Graph::addEdge(int v1, int v2, int w){
	if(v1<0||v1>=Vs||v2<0||v2>=Vs||v1==v2)
		return false;
	
	if(V[v1].size()!=0){
		for(int it = 0;it<V[v1].size();it++)
			if(V[v1][it].first==v2)
				return false;
	}
	if(V[v2].size()!=0){
		for(int it = 0;it<V[v2].size();it++)
			if(V[v2][it].first==v1)
				return false;
	}
	V[v1].push_back(make_pair(v2,w));
	V[v2].push_back(make_pair(v1,w));
	return true;
}

void Graph::simpleTraverse(){
	for(int i=0;i<Vs;i++){
		cout<<"Vertices connected with vertex "<<(i+1)<<": ";
		for(int it = 0;it<V[i].size();it++){
			cout<<"("<<V[i][it].first+1<<","<<V[i][it].second<<")";
		}
		cout<<endl;
	}
}

void Graph::dijkstra(int v1){
	vector<int> distances;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
	for(int i=0;i<Vs;i++) distances.push_back(INT_MAX);
	distances[v1] = 0;
	Q.push(make_pair(v1,0));
	while(!Q.empty()){
		pair<int,int> top = Q.top();
		Q.pop();
		int v = top.first,d = top.second;
		if(d<=distances[v]){
			for(vector<pair<int,int> >::iterator it=V[v].begin();it!=V[v].end();it++){
				if(distances[it->first]>(distances[v]+it->second)){
					distances[it->first] = distances[v] + it->second;
					Q.push(make_pair(it->first,distances[it->first]));
				}
			}
		}
	}
	for(int i=0;i<Vs;i++) cout<<i+1<<","<<distances[i]<<endl;
}

int main(){
	int choice,V,v1,v2,w;
	cout<<"Program to implement Dijkstra in weighted graph:\n\n";
	cout<<"Enter no. of vertices: ";
	cin>>V;
	Graph graph(V);
	while(1){
		cout<<"Select one of the below:\n1.Add Edge and Weight\n2.Show Graph\n3.Dijkstra\nAny other option to exit\nYour Choice: ";
		cin>>choice;
		switch(choice){
			case 1: cout<<"Enter first vertex: ";
					cin>>v1;
					cout<<"Enter second vertex: ";
					cin>>v2;
					cout<<"Enter edge weight: ";
					cin>>w;
					if(graph.addEdge(v1-1,v2-1,w)==false)
						cout<<"Edge cannot be added!\n";
					else
						cout<<"Edge successfully added.\n";
					break;
			case 2: cout<<"Traversing Graph from vertex 1(vertex_number,weight):\n";
					graph.simpleTraverse();
					cout<<endl;
					break; 							
			case 3: graph.dijkstra(0);
					break;
			default: exit(0);	
		}
	}
	return 0;
}
