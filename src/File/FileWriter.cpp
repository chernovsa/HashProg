/*
 * FileWriter.cpp
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#include <File/FileWriter.h>

FileWriter::FileWriter(ArrayData& data,std::ofstream &ofs,int block_size):
	data_(data),
	ofs_(ofs),
	block_size_(block_size)
{
	// TODO Auto-generated constructor stub

}

FileWriter::~FileWriter() {
	// TODO Auto-generated destructor stub
}

bool FileWriter::writeData(){

	if (data_.size()<0)
		return false;

	ofs_.write((char*)data_.data(),data_.size());
	data_.clear();

	if (!ofs_)
	{
		return false;
	}
	return true;
}
bool FileWriter::writeFile(){

	return writeData();
}
