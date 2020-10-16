/*
1. Topological sort + DFS
   Time complexity: O(n)
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph (numCourses, vector<int>());
        //[0, 1]: 1->0
        for (auto pair: prerequisites) {
            graph[pair[1]].push_back(pair[0]);
        }
        
        // -1: unknown; 0: visiting; 1: visited
        vector<int> visited (numCourses, -1);
        for (int i = 0; i < numCourses; i++) {
            if (dfs(graph, i, visited)) return false;
        }
        
        return true;
    }
    
    // return true (cycle) when a node is marked as visiting 
    bool dfs(vector<vector<int>> &graph, int curr, vector<int> &visited) {
        if (visited[curr] == 0) return true;
        if (visited[curr] == 1) return false;
        
        // mark node as visiting before each recursion
        visited[curr] = 0;
        
        for (int n: graph[curr]) {
            if (dfs(graph, n, visited))
                return true;
        }
        
        // mark as visited
        visited[curr] = 1;
        // means no cycle, ok
        return false;
    }
};

/*
2. BFS
   Time complexity = O(n)
*/
class Solution {
public:
    // bfs: push all the nodes whose indegree is 0 into queue
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph (numCourses, vector<int>());
        vector<int> indegree(numCourses);

        // [0, 1]: 1->0
        for (auto pair: prerequisites) {
            graph[pair[1]].push_back(pair[0]);
            indegree[pair[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (auto a: graph[curr]) {
                indegree[a]--;
                if (indegree[a] == 0) {
                    q.push(a);
                }
            }
        }
        
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] != 0) return false;
        }
        
        return true;
    }
};

/*
3. DFS finding cycles;
   Time complexity: O(n^2)
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, unordered_set<int>> graph;
        
        for (const auto& pair: prerequisites) {
            graph[pair[1]].insert(pair[0]);
        }
        
        for (int i = 0; i < numCourses; i++) {
            vector<int> visited (numCourses, 0);
            if (isCycle(graph, i, i, visited))
                 return false;
        }
        
        return true;
    }
    
    bool isCycle(unordered_map<int, unordered_set<int>>& graph, int start, int curr, vector<int>& visited) {
        if (curr == start && visited[curr]) return true;
        
        for (int next: graph[curr]) {
            if (visited[next]) continue;
            visited[next] = true;
            if (isCycle(graph, start, next, visited))
                return true;
        }
        return false;
    }
};
