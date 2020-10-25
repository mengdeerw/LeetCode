// 1. bfs
class Solution {
public:
    vector<vector<int>> dirs {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int result = 0;
                
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    grid[i][j] = '0'; // mark as visited
                    queue<pair<int, int>> q; // {row, col}       
                    q.push({i, j});

                    while (!q.empty()) {
                        int r = q.front().first;
                        int c = q.front().second;
                        q.pop();
                        for (auto dir: dirs) {
                            int newR = r + dir[0];
                            int newC = c + dir[1];
                            if (newR >= 0 && newC >= 0 && newR < m && newC < n && grid[newR][newC] == '1') {
                                q.push({newR, newC});
                                grid[newR][newC] = '0';
                            }
                        }
                    }
                }
            }
        }
        return result;
    }  
};

// 2. dfs
// if don't want to change the original grid data

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited (m, vector<bool>(n, false));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfs(grid, i, j, m ,n, visited);
                    result++;
                }
            }
        }
        return result;
    }
    
    void dfs(vector<vector<char>>& grid, int i, int j, int& m, int& n, vector<vector<bool>>& visited) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(grid, i + 1, j, m, n, visited);
        dfs(grid, i - 1, j, m, n, visited);
        dfs(grid, i, j + 1, m, n, visited);
        dfs(grid, i, j - 1, m, n, visited);
    }
};
