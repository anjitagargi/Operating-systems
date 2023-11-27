#include<bits/stdc++.h>

// using 5 processes
#define n 5

using namespace std;

class Process
{
	public:
		int arr_time;
		int burst_time;
		int priority;
		int process_ID;
};

//create a matrix of processes of class Process
Process proc_mtx[5];

//first sort as per arrival time, if arrival time is same then arrange as per priority
bool cmp(Process p1, Process p2)
{
/*
	if(p1.arr_time == p2.arr_time)
	{
		return p1.priority < p2.priority;
	}
	else
	{
		return p1.arr_time < p2.arr_time;
	}
*/	
	return p1.priority < p2.priority;
}

//implementing first come first serve by calculation of waiting time
void calculateWaitingTime(int wt[])
{
	//array storing cumulative burst time
	int cbt[5];
	
	//first cumulative frequncy is same as the frequency of first process arrival time
	cbt[0] = proc_mtx[0].arr_time;
	
	//waiting time of first process is zero
	wt[0] = 0;

	for(int i = 1; i < n; i++)
	{
		//calculate the cumulative burst time
		cbt[i] = proc_mtx[i-1].burst_time + cbt[i-1];
		
		//waiting time is cumulative burst time minus arrival time
		wt[i] = (cbt[i] - proc_mtx[i].arr_time);
		
		if(wt[i] < 0)
			wt[i] = 0;
	}	
}

//function to calculate turn around time
void calculateTurnAroundTime(int tat[], int wt[])
{
	for(int i = 0; i < n; i++)
	{
		tat[i] = proc_mtx[i].burst_time + wt[i];
	}
}


void createGanttChart()
{
	//initialising waiting time and turnaround time array
	int wt[5], tat[5];

	int total_avgwt = 0, total_avgtat = 0;

	// Function call to find waiting time array
	calculateWaitingTime(wt);
	
	//Function call to find turnaround time
	calculateTurnAroundTime(tat, wt);
		
	//initialising start time and completion time
	int st[5], ct[5];

	
	st[0] = proc_mtx[0].arr_time;
	
	ct[0] = st[0] + tat[0];

	// calculating starting and completion time
	for(int i = 1; i < n; i++)
	{
		st[i] = ct[i-1];
		ct[i] = st[i] + tat[i] - wt[i];
	}
		
	cout << "Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time" << endl;		
	for(int i = 0; i < n; i++)
	{
		total_avgwt += wt[i];
		total_avgtat += tat[i];
			
		cout << "       " <<  i+1 << "\t\t" << st[i] << "\t\t" << ct[i] <<"\t\t"<< tat[i] << "\t\t" << wt[i] <<endl;
	}
		
		
	cout << "Average waiting time is : ";
	cout << total_avgwt/(float)n <<endl;
	cout << "Average turnaround time : ";
	cout << total_avgtat/(float)n <<endl;
}

int main()
{	
	//input arrival times
	cout << "\nInput the arrival times: \n";
	fflush(stdin);
	int at[n] = {0};
	for(int i = 0; i < n; i++)
	{
		cin >> at[i];	
	}
	
	//input burst times
	cout << "\nInput the burst times: \n";
	fflush(stdin);	
	int bt[n] = {0};
	for(int i = 0; i < n; i++)
	{
		cin >> bt[i];	
	}

	//input priorities
	cout << "\nInput the priorities: \n";
	fflush(stdin);
	int priority[n] = {0};
	for(int i = 0; i < n; i++)
	{
		cin >> priority[i];	
	}
	
	//copy the values in the priority matrix to be able to implement funcdamentals of priority queue
	for(int i = 0; i < n; i++)
	{
		proc_mtx[i].arr_time = at[i];
		
		proc_mtx[i].burst_time = bt[i];
		
		proc_mtx[i].priority = priority[i];
		
		proc_mtx[i].process_ID = i+1;
	}
	
	cout << endl;
	cout << "\nProcess ID\t" << "Arrival Time\t" << "Burst Time\t" << "Priority\n";
	for(int i = 0; i < n; i++)
	{
		cout << "        " << proc_mtx[i].process_ID << "\t\t" << proc_mtx[i].arr_time << "\t\t" << proc_mtx[i].burst_time << "\t\t" << proc_mtx[i].priority << "\n"; 
	}
	
		
	//SORT priority matrix on the basis of priority
	sort(proc_mtx, proc_mtx + n, cmp);
	
	//function call to create Gantt chart of input CPU Priority scheduling info
	createGanttChart();
	
	return 0;
}
