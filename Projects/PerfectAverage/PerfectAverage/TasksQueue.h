#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <math.h>
#include <string>
#include <time.h>
#include <random>
#include <memory.h>
#include <bitset>

#include <thread>
#include <mutex>
#include <atomic>

#include "ECG.h"
#include "Drawer.h"

using namespace std;

class TasksQueue
{
public:

	TasksQueue();

	~TasksQueue();

	void addTask(string name, vector <double> parameters);

	void run(int workersCount = 8);

	void stop();

	static pair<int, pair<int, int> > comparePeaksWithReference(vector <int> peaks, vector <int> reference);

	void worker();

	bool workDone() const;

	void showResults(string path);

public:

	map<string, vector <double> > filteredData; // name, ecg
	map<string, vector <int> > referencePeaks; // name, peaks

private:

	vector< pair<string, vector <double> > > m_workQueue; // name, parameters
	mutable mutex m_queueMutex;

	vector<thread> m_workers;
	
	vector < pair<string, pair<vector <double>, pair<int, pair<int, int> > > > > results; // {name, {parameters, {ok, {fp, fn} } } }
	mutable mutex g_resultMutex;
	
	atomic_bool m_cancel;
};