#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define mp make_pair
#define ft first
#define sd second

using namespace std;
typedef pair<int, int> PII;
typedef pair<int, PII >PIII;
//实验要求：
//创建图类，图的存储结构使用邻接矩阵或者链表。
//对图提供操作：遍历，BFS，DFS
//输出生成树
//输出最小生成树
class Diagraph{
public:
    Diagraph(int n){
        this->n = n;
        a = new int*[n+1];//使顶点的编号从1开始。
        for(int i=0; i<=n; i++){
            a[i] = new int[n+1];
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                a[i][j] = NO_EDGE;
            }
        }
        initEdge();
    }

    //初始化边的方法，要求用户输入图中的边，并对不合法输入进行排除。
    void initEdge(){
        //测试数据
        //bfs：125364
        //dfs：125346
        a[1][2] = 1;
        a[1][3] = 2;
        a[1][4] = 3;
        a[2][3] = 4;
        a[2][4] = 3;
        a[3][4] = 2;

        // for (int i=1; i<=n; i++) {
        //     for (int j=1; j<=n; j++) {
        //         if (a[i][j] > 0) a[j][i] = a[i][j];
        //     }
        // }
        //正常输入的流程
        // printf("Please input the edges: \n");
        // printf("TIP:Input two vertices and the weight per round, split them with a space.\"0 0 0\" to finish.\n");
        // int tmp1, tmp2, weight;
        // for(int i=0; i<n; i++){
        //     cin >> tmp1;
        //     cin >> tmp2;
        //     cin >> weight;
        //     if(tmp1==0 && tmp2==0 && weight ==0) return;
        //     if(tmp1>n || tmp1<1 || tmp2>n || tmp2<1){
        //         cout << "No such vertice!" << endl;
        //         i--;
        //         continue;
        //     }
        //     if(weight == NO_EDGE){
        //         cout << "Invalid weight!" << endl;
        //         i--;
        //         continue;
        //     }
        //     if(a[tmp1][tmp2] != NO_EDGE){
        //         cout << "Edge alredy exists between this pair of vertices, overwrite it?(\"1\" to overwrite, others to cancel)" <<  endl;
        //         int flag;
        //         cin >> flag;
        //         if (flag == 1){
        //             a[tmp1][tmp2] = weight;
        //         } else {
        //             i--;
        //             continue;
        //         }
        //     }
        //     a[tmp1][tmp2] = weight;
        //     cout << "succeed." << endl;
        // }
    }

    //是否存在某条边
    bool exists(int i, int j){
        if(a[i][j] != NO_EDGE){
            return true;
        } else return false;
    }

    //边数
    int edges(){
        return e;
    }

    //顶点数
    int vervices(){
        return n;
    }

    //添加一条边
    void addEdge(int i, int j, int weight){
        if(i>n || i<1 || j>n || j<1){
            cout << "No such vertice!" << endl;
            return;
        }
        if(weight == NO_EDGE){
            cout << "Invalid weight!" << endl;
            return;
        }
        if(a[i][j] != NO_EDGE){
            cout << "Edge alredy exists between this pair of vertices, overwrite it?(\"1\" to overwrite, others to cancel)" <<  endl;
            int flag;
            cin >> flag;
            if (flag == 1){
                a[i][j] = weight;
            } else {
                cout << "Operation \"add edge\" failed.";
                return;
            }

        }
        a[i][j] = weight;
    }

    //删除一条边
    void deleteEdge(int i, int j){
        if(i>n || i<1 || j>n || j<1){
            cout << "No such vertice!" << endl;
            return;
        }
        if(a[i][j] == NO_EDGE){
            cout << "No such edge!" << endl;
            return;
        }
        a[i][j] = NO_EDGE;
    }

    //计算某个顶点的出度
    int outDegree(int v){
        int counter = 0;
        for(int j=1; j<=n; j++){
            if(a[v][j] != NO_EDGE) counter++;
        }
        return counter;
    }

    //计算某个顶点的入度
    int inDegree(int v){
        int counter = 0;
        for(int i=1; i<=n; i++){
            if(a[i][v] != NO_EDGE) counter++;
        }
        return counter;
    }

    //返回某一边的权重
    int weight(int i, int j){
        return a[i][j]==NO_EDGE ? NO_EDGE : a[i][j];
    }

    void adjMatrix(){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(a[i][j] != NO_EDGE)
                    cout << a[i][j];
                else cout << 0;
            }
            cout << endl;
        }
    }

    //广搜
    void bfs(int num){
        bool *done = new bool[n+1];
        for(int i=1; i<=n; i++){
            done[i] = 0;
        }
        vector<int> v;
        queue<int> q;
        q.push(num);
        done[num] = 1;
        while(!q.empty()){
            for(int i=1; i<=n; i++){
                if(a[num][i] != NO_EDGE && done[i] == 0){
                    q.push(i);
                    done[i] = 1;
                }
            }
            v.push_back(num);
            q.pop();
            if(!q.empty())
                num = q.front();
        }
        for(vector<int>::iterator it = v.begin();
                it != v.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
        delete []done;
    }

    //深搜
    void dfs(int num){
        bool *done = new bool[n+1];
        for(int i=1; i<=n; i++){
            done[i] = 0;
        }
        vector<int> v;
        stack<int> s;
        s.push(num);
        v.push_back(num);
        done[num] = 1;
        while(!s.empty()){
            for(int i=1; i<=n; i++){
                if(a[num][i] != NO_EDGE && done[i] == 0){
                    s.push(i);
                    done[i] = 1;
                    num = i;
                    i = 1;
                    v.push_back(num);
                }
            }
            s.pop();
            if(!s.empty())
                num = s.top();

        }
        for(vector<int>::iterator it = v.begin();
                it != v.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
        delete []done;
    }
    //最小生成树
    void mst(int num){
        long long size = 0;
        priority_queue<PIII> q;
        while (!q.empty()) q.pop();
        int pre[n+1];
        bool vis[n+1];
        // int dis[n+1];
        // memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        memset(pre, 0, sizeof(pre));
        q.push(mp(0, mp(num, -1)));
        // dis[num] = 0;
        while (!q.empty()){
            while (!q.empty() && vis[q.top().sd.ft]) q.pop();
            if (q.empty()) break;
            PIII t = q.top(); q.pop();
            int i = t.sd.ft;
            vis[i] = true;
            size += (-t.ft);
            // dis[i] = -t.ft;
            pre[i] = t.sd.sd;
            for (int j=1; j<=n; j++){
                if (a[i][j]> 0 && !vis[j]){
                    q.push(mp(-(a[i][j]), mp(j, i)));
                }
            }
        }
        printf("The size of MST is %lld\n", size);
        for (int i=1; i<=n; i++) {
            if (i != num) {
                printf("%d -> %d\n", pre[i], i);
            }
        }
    }

private:
    const int NO_EDGE = -2376;//权重是这个表示没有边
    int n;//顶点数
    int e;//边数
    int **a;//邻接矩阵
};

int main() {
    Diagraph dg(4);
    cout << "===================================================" << endl;
    cout << "===Adjcent Matrix " << endl;//邻接矩阵
    dg.adjMatrix();
    cout << endl;
    cout << "===================================================" << endl;
    cout << "===Broadth First Search" << endl;//宽度优先搜索遍历图
    dg.bfs(1);
    cout << endl;
    cout << "===================================================" << endl;
    cout << "===Depth First Search " << endl;//深度优先搜索遍历图
    dg.dfs(1);
    cout << endl;
    cout << "===================================================" << endl;
    cout << "===Min Spinning Tree " << endl;//深度优先搜索遍历图
    dg.mst(1);

    return 0;
}
