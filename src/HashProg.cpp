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
#include <exception>
using namespace std;
class HashException :public std::runtime_error{
    using std::runtime_error::runtime_error;
};
const char* INPUT_NAME="out.pcap";
const char* OUTPUT_NAME="wout.pcap";
int main() {
    std::ifstream input_file(INPUT_NAME,std::ifstream::binary);
    std::ofstream output_file(OUTPUT_NAME,std::ifstream::binary);
	  if (!input_file)
          throw HashException("Cant read file "+std::string(INPUT_NAME));
	  if (!output_file)
          throw HashException("Cant write to file "+std::string(OUTPUT_NAME));
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


	std::thread th_performer(
		[&performer_worker](){
			performer_worker.run();
			}
            );
	std::thread th_read(
	[&read_worker](){
			read_worker.run();
		}
		);
	std::thread th_write(
    [&write_worker](){
           // write_worker.run();
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
