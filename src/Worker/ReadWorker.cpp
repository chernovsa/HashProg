/*
 * ReadWorker.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <Worker/ReadWorker.h>
#include "ServiceTypes.h"
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
		std::unique_lock<std::mutex> lck(mtx_);
		CVLock cv_lck(cv_);
		if (!file_reader_.readFile(false))
		{
			read_finished_=true;
			break;
		}
	}
}
void ReadWorker::stop(){
	alive_= false;
}
