/*
 * FileWriter.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef FILE_FILEWRITER_H_
#define FILE_FILEWRITER_H_
#include "Types/Types.h"
#include <fstream>
class FileWriter {
public:
	FileWriter(ArrayData& data,std::ofstream &ofs,int block_size);
	virtual ~FileWriter();
	void writeFile();
private:
	bool writeData();
private:
	ArrayData &data_;
	std::ofstream &ofs_;
	int block_size_;
};

#endif /* FILE_FILEWRITER_H_ */
