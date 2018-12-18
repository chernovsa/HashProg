/*
 * WriteWorker.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef WORKER_WRITEWORKER_H_
#define WORKER_WRITEWORKER_H_
#include "File/FileWriter.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

class WriteWorker {
public:
	WriteWorker(FileWriter &file_writer,std::mutex &mtx,std::condition_variable &cv,bool &master_finished);
	virtual ~WriteWorker();
	void stop();
	void run();
private:
	FileWriter &file_writer_;
	std::mutex &mtx_;
	std::condition_variable &cv_;
	std::atomic<bool> alive_;
	bool &master_finished_;
};

#endif /* WORKER_WRITEWORKER_H_ */
