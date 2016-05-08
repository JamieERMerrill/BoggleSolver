#pragma once
#include<mutex>
#include <stack>

template<typename T>
class ThreadsafeStack
{
private:
	std::stack<T> mInternalStack;
	std::mutex mMutex;
public:
	ThreadsafeStack();
	~ThreadsafeStack();

	void push(T item);
	T pop();
	bool empty();
	int size();
	void Lock();
	void Unlock();
};

template <typename T>
ThreadsafeStack<T>::ThreadsafeStack():
	mMutex()
{
}

template <typename T>
ThreadsafeStack<T>::~ThreadsafeStack()
{
}

template <typename T>
void ThreadsafeStack<T>::push(T item)
{
	mInternalStack.push(item);
}

template <typename T>
bool ThreadsafeStack<T>::empty()
{
	return mInternalStack.empty();
}

template <typename T>
T ThreadsafeStack<T>::pop()
{
	T item = mInternalStack.top();
	mInternalStack.pop();
	return item;
}

template <typename T>
int ThreadsafeStack<T>::size()
{
	return mInternalStack.size();
}

template <typename T>
void ThreadsafeStack<T>::Lock()
{
	mMutex.lock();
}

template <typename T>
void ThreadsafeStack<T>::Unlock()
{
	mMutex.unlock();
}


