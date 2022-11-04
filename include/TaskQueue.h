#pragma once
#include <pthread.h>
#include <queue>

using callback = void(*)(void* arg);
template<typename T>
struct Task
{
	Task<T>() {
		function = nullptr;
		arg = nullptr;
	}
	Task<T>(callback f, void* arg) {
		function = f;
		this->arg = (T*)arg;
	}
	~Task<T>() {}
	callback function;
	T* arg;
};

template<typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	void addTask(Task<T> task);//添加任务
	void addTask(callback cb, void* arg);
	Task<T> takeTask();//取任务
	inline size_t taskNumber()//获取当前任务的个数
	{
		return m_taskQ.size();
	}
private:
	std::queue<Task<T>> m_taskQ;
	pthread_mutex_t m_mutex;
};

