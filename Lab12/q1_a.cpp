#include<bits/stdc++.h>

using namespace std;


bool cmp(pair<int, int>p1, pair<int, int>p2)
	{
		return p1.second < p2.second;
	}


int main()
{
	vector<pair<int, int>>processes(5, {-1, -1});
	vector<pair<int, int>>blocks(5, {-1, 50});
	
	
	
	cout << "Enter the processes index and their size: \n";
	for(int i = 0; i < 5; i++)
	{
		cin >> processes[i].first >> processes[i].second;
	}
	
	
	cout << "Enter the blocks and their size: \n";
	for(int i = 0; i < 5; i++)
	{
		cin >> blocks[i].first >> blocks[i].second;
	}
	
	for(int i = 0; i < 5; i++)
	{
		int index = 0;
		int sz = INT_MIN;
		int j = 0;
		for(; j < 5; j++)
		{
			if(blocks[j].first == -1 && processes[i].second <= blocks[j].second)
			{
				if(blocks[j].second >= sz)
				{
					index = j;
					sz = blocks[j].second;
				}
			}
		}
		
		blocks[index].first = processes[i].first;
	}
	
	for(auto val:blocks)
		cout << val.first << " ";
		
	cout << endl;
	
	
	
	return 0;
}
