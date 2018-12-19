/*
 * ProcessingPerformer.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <DataProcessing/ProcessingPerformer.h>
#include <cstdio>

ProcessingPerformer::ProcessingPerformer(ArrayData &input_data,ArrayData &output_data,int block_size):
	input_data_(input_data),
	output_data_(output_data),
	block_size_(block_size)
{
	// TODO Auto-generated constructor stub

}

ProcessingPerformer::~ProcessingPerformer() {
	// TODO Auto-generated destructor stub
}

bool ProcessingPerformer::process(){
	uint8_t crc=0;
	int count=0;
	if (!input_data_.size())
		return false;
	for(auto value:input_data_){
        if (count == (block_size_-1))
		{
			crc&=0x55;
			output_data_.push_back(crc);
			count=0;
			printf("crc=%x\n",crc);
			crc=0;
		}
		else
		{
			crc+=value;
			count++;
		}
	}
    input_data_.clear();
	//finish last part
	if (count && count<block_size_)
	{
		crc&=0x55;
		output_data_.push_back(crc);
		printf("last part crc=%x\n",crc);
		crc=0;
	}
	return true;
}
