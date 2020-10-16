/*
DFS Topological Sort
Time complexity: O(V+E) ~ O(V^2)
*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>());
        
        for (auto pair: prerequisites) {
            graph[pair[1]].push_back(pair[0]);
        }
        
        // -1: unknown, 0: visiting, 1: visited 
        vector<int> visited (numCourses, -1);
        vector<int> result;
        
        for (int i = 0; i < numCourses; i++) {
            if (dfsCycle(graph, i, visited, result)) return {};
        }
        
        // reverse the result list
        reverse(result.begin(), result.end());
        return result;
    }
    
    // return true (cycle) when a node is marked as visiting 
    bool dfsCycle(vector<vector<int>>& graph, int curr, vector<int>& visited, vector<int>& result) {
        if (visited[curr] == 0) return true;
        if (visited[curr] == 1) return false;
        
        // mark as visiting at beginning
        visited[curr] = 0;
        for (int n: graph[curr]) {
            if (dfsCycle(graph, n, visited, result)) return true;
        }
        
        // mark as visited
        visited[curr] = 1;
        result.push_back(curr);
        
        // ok
        return false;
        
    }
};
