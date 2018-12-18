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
	int block_size=10020;
	FileReader file_reader(input_data,input_file,block_size);
	file_reader.readFile();

	FileWriter file_writer(input_data,output_file,block_size);
	file_writer.writeFile();
	return 0;
}
