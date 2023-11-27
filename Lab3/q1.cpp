#include<bits/stdc++.h>

using namespace std;

void findCompletionTime(int processes[], int n, int bt[], int ct[])
{
	ct[0] = bt[0];

	for (int i = 1; i < n ; i++ )
		ct[i] = bt[i] + bt[i-1] ;
}

void findWaitingTime(int processes[], int n, int at[], int bt[], int wt[])
{
	// waiting time for first process is 0
	wt[0] = 0;

	// calculating waiting time
	for (int i = 1; i < n ; i++ )
		wt[i] =  (at[i - 1] + bt[i - 1] + wt[i - 1] ) - at[i];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int at[], int bt[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0, ct[n];

	findCompletionTime(processes, n, bt, ct);
	findWaitingTime(processes, n, at, bt, wt);
	findTurnAroundTime(processes, n, bt, wt, tat);

	cout << "Processes: "<< "Arrival time " << " Burst time " << "Completion time " << " Waiting time " << " Turn around time\n";

	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
	
		cout << " " << i+1 << "\t\t " << at[i] << "\t    " << bt[i] << "\t\t " << ct[i] << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
	}

	cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
	cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
}


int main()
{
	//process id's
	int processes[] = {1,2,3,4,5,6};
	int n = sizeof processes / sizeof processes[0];

	int arr_time[] = {};
	//Burst time of all processes
	int burst_time[] = {};

	for(int i = 0; i < n; i++)
	{
		cin >> arr_time[i] >> burst_time[i];
	}
	
	findavgTime(processes, n, arr_time, burst_time);
	
	return 0;
}

