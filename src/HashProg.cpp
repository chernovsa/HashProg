//============================================================================
// Name        : HashProg.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "File/FileReader.h"
#include "File/FileWriter.h"
#include "DataProcessing/ProcessingPerformer.h"
#include "Worker/ReadWorker.h"
#include "Worker/WriteWorker.h"
#include "Worker/ProcessingWorker.h"
#include <thread>
using namespace std;
using HashException = std::string;
int main() {
	std::ifstream input_file("out.pcap",std::ifstream::binary);
	std::ofstream output_file("wout.pcap",std::ifstream::binary);
	  if (!input_file)
		  throw HashException("Cant read file");
	  if (!output_file)
		  throw HashException("Cant write to file");
	    // get length of file:
	  input_file.seekg (0, input_file.end);
	  streampos length = input_file.tellg();
	    input_file.seekg (0, input_file.beg);
	std::cout<<" file size="<<length<<std::endl;
	ArrayData input_data;
	ArrayData output_data;
	int block_size=50;
	FileReader file_reader(input_data,input_file,block_size);
	FileWriter file_writer(output_data,output_file,block_size);
	ProcessingPerformer processing_performer(input_data,output_data,block_size);

	std::mutex mtx;
	std::condition_variable cv;
	bool read_finished=false;
	CriticalData master_data{mtx,cv,read_finished};
	std::mutex slave_mtx;
	std::condition_variable slave_cv;
	bool slave_read_finished=false;
	CriticalData slave_data{slave_mtx,slave_cv,slave_read_finished};


	ReadWorker read_worker(file_reader,mtx,cv,read_finished);
	WriteWorker write_worker(file_writer,slave_mtx,slave_cv,slave_read_finished);
	ProcessingWorker performer_worker(processing_performer,master_data,slave_data);

	std::thread th_read(
[&read_worker](){
		read_worker.run();
	}
	);
	std::thread th_performer(
		[&performer_worker](){
			performer_worker.run();
			}
			);
	std::thread th_write(
	[&write_worker](){
			write_worker.run();
		}
		);
	if (th_read.joinable())
		th_read.join();
	if (th_performer.joinable())
		th_performer.join();
	if (th_write.joinable())
		th_write.join();
	return 0;
}
