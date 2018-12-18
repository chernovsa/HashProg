/*
 * ServiceTypes.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef WORKER_SERVICETYPES_H_
#define WORKER_SERVICETYPES_H_
#include <mutex>
#include <condition_variable>
class CVLock{
public:
	CVLock(std::condition_variable &cv):
		cv_(cv)
	{

	}
	~CVLock(){
		cv_.notify_all();
	}
private:
	std::condition_variable &cv_;
};

#endif /* WORKER_SERVICETYPES_H_ */
