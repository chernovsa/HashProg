/*
 * ProcessingWorker.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <Worker/ProcessingWorker.h>
#include "ServiceTypes.h"
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
	while(alive_){
		std::unique_lock<std::mutex> lck(master_data_.mtx_);
		std::unique_lock<std::mutex> slave_lck(slave_data_.mtx_);
		if (master_data_.master_finished_)
		{
			//write last part of file
			performer_.process();
			CVLock slave_cv(slave_data_.cv_);
			slave_data_.master_finished_=true;
			break;
		}
        master_data_.cv_.wait(lck);
		performer_.process();
		CVLock slave_cv(slave_data_.cv_);
	}
}


void ProcessingWorker::stop(){
	alive_= false;
}
