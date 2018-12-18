/*
 * ReadWorker.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef WORKER_READWORKER_H_
#define WORKER_READWORKER_H_
#include "File/FileReader.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

class ReadWorker {
public:
	ReadWorker(FileReader &file_reader,std::mutex &mtx,std::condition_variable &cv,bool &read_finished);
	virtual ~ReadWorker();
	void run();
	void stop();
private:
	FileReader &file_reader_;
	std::mutex &mtx_;
	std::condition_variable &cv_;
	bool &read_finished_;
	std::atomic<bool> alive_;
};

#endif /* WORKER_READWORKER_H_ */
