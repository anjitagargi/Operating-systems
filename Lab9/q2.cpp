/*NAME: AHAN BANDYOPADHYAY
ROLL NO.: 211210008*/


#include <iostream>
#include <bits/stdc++.h>
#include <mutex>
#include <condition_variable>
#include <pthread.h>
#include <unistd.h>
#include <thread>

using namespace std;

class ReaderWriterMonitor {
	private:
		int activeReaders = 0;
		int waitingWriters = 0;
		int activeWriters = 0;
		
		std::mutex mutex;
		condition_variable readCV;
		condition_variable writeCV;
		
	public:
		void startRead() {
			unique_lock<std::mutex> lock(mutex);
			while (activeWriters > 0 || waitingWriters > 0) {
				readCV.wait(lock);
			}
			activeReaders++;
		}
		
		void endRead() {
			unique_lock<std::mutex> lock(mutex);
			activeReaders--;
			
			if (activeReaders == 0) {
				writeCV.notify_one();
			}
		}
		
		void startWrite() {
			unique_lock<std::mutex> lock(mutex);
			waitingWriters++;
			while (activeReaders > 0 || activeWriters > 0) {
				writeCV.wait(lock);
			}
		
			waitingWriters--;
			activeWriters++;
		}
		
		void endWrite() {
			unique_lock<std::mutex> lock(mutex);
			activeWriters--;
			if (waitingWriters > 0) {
				writeCV.notify_one();
			} else {
				readCV.notify_all();
			}
		}
};

int sharedData = 0;

ReaderWriterMonitor monitor;

void reader(int id) {
	monitor.startRead();
	cout << "Reader " << id << " reads data: " << sharedData << endl;
	monitor.endRead();
}

void writer(int id) {
	monitor.startWrite();
	sharedData++;
	cout << "Writer " << id << " writes data: " << sharedData << std::endl;
	monitor.endWrite();
}

int main() {
	const int numReaders = 3;
	const int numWriters = 2;
	
	for (int i = 0; i < numReaders; ++i) {
		thread(reader, i).detach();
	}
	
	for (int i = 0; i < numWriters; ++i) {
		thread(writer, i).detach();
	}
	
	cout << "timeout\n" << endl;
	this_thread::sleep_for(chrono::seconds(5));

	return 0;
}
