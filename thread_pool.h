#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <atomic>
#include <mutex>
#include <functional>
#include <condition_variable>

//任务抽象基类
class Task
{
public:
	virtual void run() = 0; //用户可以自定义任何类型的任务，重写run方法
};

enum PoolMode
{
	MODE_FIXED, //固定数量的线程
	MODE_CACHED //线程可动态增长
};

//线程
class Thread
{

public:
	//线程函数对象类型
	using ThreadHandler = std::function<void()>;
	Thread(ThreadHandler handler);

	~Thread();
	//启动线程
	void start();

private:
	ThreadHandler handler_;
};

class threadPool
{
public:
	threadPool();
	~threadPool();
	void start(int initThreadSize = 4); //开启线程池
	void setMode(PoolMode mode);

	//设置初始线程数量
	void setInitThreadSize(int size);

	//设置task任务队列上线阈值
	void setTaskQueMaxThreshHold(int threshhold);

	//给线程池提交任务
	void submitTask(std::shared_ptr<Task> sp);
	threadPool(const threadPool &) = delete;			//禁止拷贝构造
	threadPool &operator=(const threadPool &) = delete; //禁止拷贝赋值

private:
	void threadHandler();

private:
	size_t initThreadSize_;
	std::vector<Thread *> threads_; //线程列表

	std::queue<std::shared_ptr<Task>> taskQueue_; //任务队列，使用基类指针，完成多态
	std::atomic_int taskSize_;					  //任务数量
	int taskQueMaxThresHold_;					  //任务队列数量的阈值

	//锁
	std::mutex taskQueMtx;
	//条件变量
	std::condition_variable notFull;
	std::condition_variable notEmpty;
	PoolMode poolMode_;
};
