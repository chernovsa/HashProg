/*
 * ReadWorker.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <Worker/ReadWorker.h>
#include "ServiceTypes.h"
#include <cstdio>
ReadWorker::ReadWorker(FileReader &file_reader,std::mutex &mtx,std::condition_variable &cv,bool &read_finished):
	file_reader_(file_reader),
	mtx_(mtx),
	cv_(cv),
	read_finished_(read_finished),
	alive_(true)
{
	// TODO Auto-generated constructor stub

}

ReadWorker::~ReadWorker() {
	// TODO Auto-generated destructor stub
}
void ReadWorker::run(){
	while(alive_){
		printf("readworker _before mtx\n");
		std::unique_lock<std::mutex> lck(mtx_);
		printf("readworker _get mtx\n");
		if (!file_reader_.readFile(false))
		{
			read_finished_=true;
			cv_.notify_one();
			break;
		}
		printf("readworker_before notify\n");
		cv_.notify_one();
		printf("readworker notify\n");
	}
}
void ReadWorker::stop(){
	alive_= false;
}
