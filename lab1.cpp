#include<iostream>

using namespace std;

int M = 10000000;                                                               //经费
int n = 10;                                                                     //广告牌类型数量
int v[11] = {0, 271, 299, 431, 471, 831, 1111, 1499, 2048, 3051, 4999};     //价格
int w[11] = {0, 8, 7, 9, 11, 12, 19, 13, 23, 57, 87};                       //广告效果
int P[10000001];                                                           //动态规划备忘录
int num[11];                                                                    //存储数量
bool flag[10000001][11];                                                    //判断是否采用当前广告牌

int main()
{
    //动态规划求最好的广告效果
    for(int i = 1; i <= n; i++)
    {
        for(int j = v[i]; j <= M; j++)
        {
            if (P[j] < P[j - v[i]] + w[i])
            {
                P[j] = P[j - v[i]] + w[i];
                flag[j][i] = true;                                          //标记当前广告牌有选择使用
            }
        }
    }
    
    //从尾到头逆推各个广告牌使用的情况
    int i = n, j = M;
    while(i > 0 && j > 0)
	{
		if(flag[j][i])
		{
			num[i] += 1;
			j -= v[i];
		}
		else i--;
	}

    cout << "Max P = " << P[M] << "\tremain = " << j << endl;
    
    for(int i = 1; i <= n; i++)
    {
        cout << char('A' +  i - 1) << " : ";
        cout << "v = " << v[i];
        cout << "\tw = " << w[i];
        cout << "\tw/v = " << double(w[i])/v[i];
        cout << " \tnum = " << num[i] << endl;
    }
    
    return 0;
}