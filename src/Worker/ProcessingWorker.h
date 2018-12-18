/*
 * ProcessingWorker.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef WORKER_PROCESSINGWORKER_H_
#define WORKER_PROCESSINGWORKER_H_

#include "DataProcessing/ProcessingPerformer.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

struct CriticalData{
	std::mutex &mtx_;
	std::condition_variable &cv_;
	bool &master_finished_;
};
class ProcessingWorker {
public:
	ProcessingWorker(ProcessingPerformer& performer,CriticalData &master_data,CriticalData &slave_data);
	virtual ~ProcessingWorker();
	void run();
	void stop();
private:
	ProcessingPerformer& performer_;
	CriticalData master_data_;
	CriticalData slave_data_;
	std::atomic<bool> alive_;

};

#endif /* WORKER_PROCESSINGWORKER_H_ */
