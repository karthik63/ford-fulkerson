#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> previous(100,0);

int vertices; int edges;

bool bfs(int start, int end, int graph[100][100])
{
    
    previous.clear();
    
    queue<int> toex; int i,j,k = 0;  bool success = false;
    
    vector<bool> visited(edges+1,false);
    
    toex.push(start);
    
    while(!toex.empty())
    {
        int curr = toex.front();
        
        if(curr == end)
        {
            success = true; return success;
        }
        
        visited[curr] = true;
        
        toex.pop();
        
        for(i=0;i<vertices;i++)
        {
            if(graph[curr][i]==0)
            continue;
            
            if(!visited[i])
            {
                toex.push(i);
                visited[i] = true;
                previous[i] = curr;
            }
        }
    }
    
    return success;
}

int fordFulkerson(int graph[100][100],int source, int sink)
{
	int maxflow  = 0,j,k; bool ifpos = false;
	
    while(1){
    
        ifpos = bfs(source, sink, graph);
    
        if(!ifpos)
        return maxflow;
        
        int temp, i = sink , minflow = 10000;
        
        while(1)
        {
            temp = previous[i];
            
            if(graph[temp][i]<minflow)
            minflow = graph[temp][i];
            
            i = temp;
                    
            if(temp==source)
            break;
        }
    
        i = sink;
    
        while(1)
        {
            temp = previous[i];
        
            graph[temp][i] -=minflow;
            graph[i][temp] += minflow;
            
            i = temp;
        
            if(temp == source)
            break;
        }
        
        maxflow+=minflow;
    }
}

int main()
{
    
    int graph[100][100] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
 
    vertices = 6; edges = 8;
 
    cout << "The maxflow is " << fordFulkerson(graph, 0, 5);
 
    return 0;
}
