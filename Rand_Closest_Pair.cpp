#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
using namespace std;


struct point
{
    double x;
    double y;
};

void Data_input(point p[], int n);
void Permute_in_Place(point p[], int n);
double distance(point a, point b);
void point_print(point p);

int main()
{
    double delta, delta_half, delta_new;
    int N, n = 1000, s, t, key, p_1, p_2, start_x, start_y, end_x, end_y;
    bool flag;
    point p[1000];
    // 输入点的坐标
    Data_input(p, n);
    // 随机排序所有点
    Permute_in_Place(p, n);
    // 第1、2两点的距离作为δ
    delta = distance(p[0],p[1]);
    // δ的一半作为网格间隙
    delta_half = delta/2;
    // 网格的格数（一行）
    N = int(10 / delta_half);
    // 构造哈希表
    unordered_map<int, int> HashMap;
    // 依次处理n个点
    for(int i = 0; i < n; i++)
    {
        // 计算p[i]点所在的网格
        s = int(p[i].x / delta_half);
        t = int(p[i].y / delta_half);
        // 计算25个（可能不到）网格的起始和终止位置
        start_x = s - 2;    if(start_x < 0) start_x = 0;
        start_y = t - 2;    if(start_y < 0) start_y = 0;
        end_x = s + 2;      if(end_x > N)   end_x = N;
        end_y = t + 2;      if(end_y > N)   end_y = N;
        // 计算所要搜索的网格宽度、高度、和数目
        int x_width = end_x - start_x + 1;
        int y_width = end_y - start_y + 1;
        int num = x_width * y_width;
        int key_start = start_x * N + start_y;
        // 搜索25（num）个网格中的点
        int j = 0;
        while(j < num)
        {
            // 计算当前格子的key值
            key = key_start + j/y_width * N + j%y_width;
            // 如果当前格子有点存在
            if(HashMap.count(key) != 0)
            {
                // 找到点的下标
                int p_num = HashMap.at(key);
                // 计算两点间的距离
                delta_new = distance(p[i], p[p_num]);
                // 如果新的距离δ’更小
                if(delta > delta_new)
                {
                    // 将δ‘作为新的δ
                    delta = delta_new;
                    // 存储距离最近的两个点的下标
                    p_1 = i;
                    p_2 = p_num;
                    // 置位标志位且退出循环
                    flag = true;
                    break;
                }
            }
            j++;
        }
        // 如果标志位为1（δ有被更新过）
        if(flag)
        {
            // 计算新的网格
            delta_half = delta/2;
            N = int(10 / delta_half);
            // 清空哈希表
            HashMap.clear();
            // 将前i+1个点重新计算网格并放入哈希表中
            for(int j = 0; j <= i; j++)
            {
                int s_now = int(p[j].x / delta_half);
                int t_now = int(p[j].y / delta_half); 
                int key_now = s_now * N + t_now;
                HashMap[key_now] = j;
            }
            // 标志位置位0
            flag = false;
        }
        // 如果标志位为0（δ没有被更新过）
        else
            HashMap[s * N + t] = i;
    }
    // 输出结果
    printf("The min distance = %.14f\n", delta);
    printf("第%d个点\tP = ", p_1); point_print(p[p_1]);
    printf("第%d个点\tP = ", p_2); point_print(p[p_2]);
    return 0;
}

/*********读取点坐标文件*********/
void Data_input(point p[], int n)
{
    ifstream Point_data("data1000 copy.txt", ios::in);
    if(!Point_data)
    {
        cout << "unable to open" << endl;
        return;
    }
    int i = 0;
    for (i; i < n; i++)
    {
        Point_data >> p[i].x;
        Point_data >> p[i].y;
    }
    return;
}

/*********在位随机排列数组*********/
void Permute_in_Place(point p[], int n)
{
    // 初始化随机数
    srand(unsigned(time(NULL)));
    int r, base = n;
    point p_change;
    for (int i = 0; i < n; i++)
    {
        r = rand()%base + i;        //在i~n范围内(共base个数)获得随机数r
        // 交换p[i]和p[r]
        p_change = p[i];
        p[i] = p[r];
        p[r] = p_change;
        base--;
    }
}

/*********计算两点间距离*********/
double distance(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/*********输出点坐标*********/
void point_print(point p)
{
    printf("(%.14f, %.14f)\n",p.x,p.y);
}
