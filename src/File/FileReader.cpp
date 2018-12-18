/*
 * FileReader.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include "FileReader.h"
#include <array>
#include <iostream>
#include <cstdio>
FileReader::FileReader(ArrayData& data,std::ifstream &ifs,int block_size):
	data_(data),
	ifs_(ifs),
	block_size_(block_size)
{
	// TODO Auto-generated constructor stub

}

FileReader::~FileReader() {
	// TODO Auto-generated destructor stub
}

bool FileReader::readData(std::streamsize &count_readen){
	char buffer[block_size_];
	ifs_.read(buffer,block_size_);
	count_readen=ifs_.gcount();
	if (count_readen>0)
	{
		data_.insert(data_.end(),buffer,buffer+count_readen);
		for(auto hex : buffer)
			printf("%x ",(unsigned char)hex);
		printf("\n");
	}
	if (!ifs_)
	{
		return false;
	}
	return true;
}
bool FileReader::readFile(bool blocking){
	std::streamsize count_readen=0;
	bool res=true;
	if (!blocking)
	{
		res=readData(count_readen);
	}
	else
	{
		while(readData(count_readen)){
			std::cout<<" count_readen="<<count_readen<<" total="<<data_.size()<<std::endl;
		}
	}
	std::cout<<"total="<<data_.size()<<std::endl;
	return res;
}
