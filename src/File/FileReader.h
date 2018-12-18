/*
 * FileReader.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef FILE_FILEREADER_H_
#define FILE_FILEREADER_H_
#include "Types/Types.h"
#include <fstream>

class FileReader {
public:
	FileReader(ArrayData& data,std::ifstream &ifs,int block_size);
	virtual ~FileReader();
	void readFile();
private:
	bool readData(std::streamsize &count_readen);
private:
	ArrayData &data_;
	std::ifstream &ifs_;
	int block_size_;
};

#endif /* FILE_FILEREADER_H_ */
