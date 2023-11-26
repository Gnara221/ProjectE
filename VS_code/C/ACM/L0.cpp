/*
 * @description: 
 * @param: 
 * @return: 
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;



int n,cost = 0;


int main() {
    // ifstream fin("test.txt");
    // if (!fin) {
    //     cerr << "Failed to open file test.txt" << endl;
    //     return 1;
    // }
    // string line;

	// freopen("o_input.txt", "r", stdin);
	// freopen("o_output.txt", "w", stdout);
    // getline(fin, line);  // 读取一行数据
    cin >> n;
    int LL_Level[n + 1];
    int enemy[n + 1];
    int enemy_level = 0;
    

    // getline(fin, line);
    for (int i = 1; i <= n; i++) {
        cin >> enemy[i];
    }
//    fin.close();
    LL_Level[0] = 1;  // 初始等级为 1
//    int max_k = 0;  // 当前已经 找到的所有方案中，能够打败第 i 层敌人的最高等级
//    memset(f, 0x3f, sizeof(f));  // 初始化为正无穷

     for (int i = 1; i <= n; i++)
    {
          // 如果当前等级不能打败敌人,先计算代价为差值，默认升级到敌人的等级 + 原先的等级，
        while(LL_Level[i-1] < enemy[i])
        {
            LL_Level[i-1] += 1 + enemy_level;  // 升级一次
            cost += 1;  // 代价 + 1
            //           cost += (enemy[i] - LL_Level[i-1] + 1);  // 否则，计算代价
        }
        LL_Level[i] = enemy[i] + LL_Level[i-1];  // 升到敌人的等级 + 原先的等级
        enemy_level += enemy[i];  // 计算敌人的总等级
    }

    cout << cost << endl;
    return 0;
}
