/*
 * @description: 
 * @param: 
 * @return: 
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MIN 0
#define MAX (ll)1e9
#define HEIGHT (ll)1e5
int main()
{
	// freopen("o_input.txt", "r", stdin);
	freopen("o_input.txt", "w", stdout);
	srand(time(NULL));
	for(int i=1; i<=1; i++)
	{
		int height = (rand() % (HEIGHT - MIN + 1)) + MIN;
		cout<<height<<endl;
		for(int j=1; j<=height; j++){
			cout << (rand() % (MAX - MIN + 1)) + MIN<<" ";
		}
		cout<<endl;
	}
	fclose(stdout);
	return 0;
}
