/*
 * ProcessingWorker.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <Worker/ProcessingWorker.h>
#include "ServiceTypes.h"
#include <cstdio>
ProcessingWorker::ProcessingWorker(ProcessingPerformer& performer,CriticalData &master_data,CriticalData &slave_data):
	performer_(performer),
	master_data_(master_data),
	slave_data_(slave_data),
	alive_(true)

{
	// TODO Auto-generated constructor stub

}

ProcessingWorker::~ProcessingWorker() {
	// TODO Auto-generated destructor stub
}

void ProcessingWorker::run(){
	printf("performer_before mtx\n");
	std::unique_lock<std::mutex> lck(master_data_.mtx_);
	printf("performer_get mtx\n");
	while(alive_){
		std::unique_lock<std::mutex> slave_lck(slave_data_.mtx_);
		while(!master_data_.master_finished_)
		{
			printf("performer_wait\n");
			master_data_.cv_.wait(lck);
			printf("performer_process\n");
			if (performer_.process())
			{
				slave_data_.cv_.notify_one();
				break;
			}
		}
		if (master_data_.master_finished_)
		{
			//write last part of file
			performer_.process();
			slave_data_.master_finished_=true;
			slave_data_.cv_.notify_one();
			break;
		}
	}
}


void ProcessingWorker::stop(){
	alive_= false;
}
