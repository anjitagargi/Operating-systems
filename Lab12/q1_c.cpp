#include<bits/stdc++.h>

using namespace std;

int main()
{
	vector<pair<int, int>>processes(5, {-1, -1});
	vector<pair<int, int>>blocks(5, {-1, 50});

	cout << "Enter the processes index and their size: \n";
	for(int i = 0; i < 5; i++)
	{
		cin >> processes[i].first >> processes[i].second;
	}

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if(blocks[j].first == -1 && processes[i].second <= blocks[j].second)
			{
				blocks[j].first = processes[i].first;
				break;
			}
		}
	}

	for(auto val:blocks)
		cout << val.first << " ";

	cout << endl;



	return 0;
}
