#include "thread_pool.h"
#include <iostream>
#include <functional>
#include <thread>

const int TASK_MAX_THRESHHOLD = 1024;

threadPool::threadPool() : initThreadSize_(4),
						   taskSize_(0),
						   taskQueMaxThresHold_(TASK_MAX_THRESHHOLD),
						   poolMode_(PoolMode::MODE_FIXED)
{
}

threadPool::~threadPool() {}

void threadPool::setMode(PoolMode mode)
{
	poolMode_ = mode;
}

void threadPool::setInitThreadSize(int size)
{
	initThreadSize_ = size;
}

void threadPool::setTaskQueMaxThreshHold(int threshhold)
{
	taskQueMaxThresHold_ = threshhold;
}

void threadPool::submitTask(std::shared_ptr<Task> sp)
{

	// taskQueue_.push(sp);
}

//*****************************thread_之所有能够调用Thread的函数，是因为通过function绑定threadPool到Thread中***************************************************

// start开启线程
void threadPool::start(int initThreadSize)
{
	//初始线程个数
	initThreadSize_ = initThreadSize;

	//创建线程对象
	for (int i = 0; i < initThreadSize_; i++)
	{

		//创建Thread对象的时候，把线程含本数给到thread对象
		threads_.emplace_back(new Thread(std::bind(&threadPool::threadHandler, this))); //
	}
	//启动所有线程 std::vector<Thread*>threads_;//线程列表
	for (int i = 0; i < initThreadSize_; i++)
	{
		threads_[i]->start(); //启动所有线程
	}
}

void threadPool::threadHandler()
{
	std::cout << "thread handler" << std::endl;
	std::cout << std::this_thread::get_id() << std::endl;
}

//*******************线程方法实现****************************************
Thread::Thread(ThreadHandler handler)
{

	handler_ = handler;
}

Thread::~Thread()
{
}

//启动线程
void Thread::start()
{
	//创建线程并启动
	std::thread t(handler_);
	t.detach(); //设置成分离模式
}
