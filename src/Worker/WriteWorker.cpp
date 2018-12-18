/*
 * WriteWorker.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <Worker/WriteWorker.h>

WriteWorker::WriteWorker(FileWriter &file_writer,std::mutex &mtx,std::condition_variable &cv,bool &master_finished):
file_writer_(file_writer),
mtx_(mtx),
cv_(cv),
master_finished_(master_finished),
alive_(true)
{
	// TODO Auto-generated constructor stub

}

WriteWorker::~WriteWorker() {
	// TODO Auto-generated destructor stub
}

void WriteWorker::stop(){
	alive_= false;
}

void WriteWorker::run(){
	while(alive_){
		std::unique_lock<std::mutex> lck(mtx_);
		if (master_finished_)
		{
			//write last part of file
			file_writer_.writeFile();
			break;
		}
		cv_.wait(lck);
		if (file_writer_.writeFile())
		{

		}
	}
}
