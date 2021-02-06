#include "TasksQueue.h"

TasksQueue::TasksQueue()
{
	m_cancel = false;
}

TasksQueue::~TasksQueue()
{
	stop();
}

void TasksQueue::addTask(string name, vector <double> parameters)
{
	lock_guard<mutex> lock(m_queueMutex);
	m_workQueue.push_back({ name, parameters });
}

void TasksQueue::run(int workersCount)
{
	stop();

	m_cancel = false;

	for (int i = 0; i < workersCount; i++)
	{
		m_workers.push_back(thread(&TasksQueue::worker, this));
	}
}

void TasksQueue::stop()
{
	m_cancel = true;

	for (size_t i = 0; i < m_workers.size(); i++)
	{
		if (m_workers[i].joinable())
			m_workers[i].join();
	}

	m_workers.clear();
}

pair<int, pair<int, int> > TasksQueue::comparePeaksWithReference(vector <int> peaks, vector <int> reference)
{
	set<int> peaksS, referenceS;
	for (auto it : peaks)
	{
		peaksS.insert(it);
	}
	for (auto it : reference)
	{
		referenceS.insert(it);
	}

	const int maxR = 60;
	int val;

	int ok = 0, fp = 0, fn = 0;

	// compute ok
	for (auto it : peaks)
	{
		val = it - maxR;

		auto iter = referenceS.lower_bound(val);

		if (iter != referenceS.end())
		{
			if (abs(it - *iter) <= maxR)
			{
				ok++;

				peaksS.erase(it);
				referenceS.erase(iter);
			}
		}
	}

	// erase peaks at start and at end
	while (peaks.size() != 0 && *peaks.begin() < 360)
	{
		peaks.erase(peaks.begin());
	}
	while (peaks.size() != 0 && *(--peaks.end()) > 650000 - 360)
	{
		peaks.erase(--peaks.end());
	}
	while (reference.size() != 0 && *reference.begin() < 360)
	{
		reference.erase(reference.begin());
	}
	while (reference.size() != 0 && *(--reference.end()) > 650000 - 360)
	{
		reference.erase(--reference.end());
	}

	// compute false-positive and false-negative
	fp = peaksS.size();
	fn = referenceS.size();

	return { ok, {fp, fn} };
}

void TasksQueue::worker()
{
	while (!m_cancel)
	{
		ECG ecg(360);

		string name;
		vector <double> parameters;
		vector <int> referenceRPeaks;

		{
			std::lock_guard<std::mutex> lock(m_queueMutex);
			if (m_workQueue.empty())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				continue;
			}

			name = m_workQueue.back().first;
			parameters = m_workQueue.back().second;

			ecg.data = filteredData[name];
			referenceRPeaks = referencePeaks[name];

			m_workQueue.pop_back();
		}

		// Work using data

		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size(), parameters[0], parameters[1],
			parameters[2], parameters[3], parameters[4]);

		pair<int, pair<int, int> > stats = comparePeaksWithReference(rPeaks, referenceRPeaks);

		// add results
		std::lock_guard<std::mutex> lock(g_resultMutex);
		cout << name << " " << parameters[0] << " " << parameters[1] << " " << parameters[2] << " "
			<< parameters[3] << " " << parameters[4] << " " << stats.first << " " << stats.second.first << " "
			<< stats.second.second << "\n";
		cout.flush();
		results.push_back({ name, {parameters, stats} });
	}
}

bool TasksQueue::workDone() const
{
	lock_guard<std::mutex> lock(m_queueMutex);
	return m_workQueue.empty();
}

void TasksQueue::showResults(string path)
{
	ofstream out(path);

	for (auto it : results)
	{
		auto pars = it.second.first;
		auto res = it.second.second;

		out << it.first << " " << pars[0] << " " << pars[1] << " " << pars[2] << " " << pars[3] << " " << pars[4]
			<< " " << res.first << " " << res.second.first << " " << res.second.second << "\n";

		out.flush();
	}

	out.close();
}