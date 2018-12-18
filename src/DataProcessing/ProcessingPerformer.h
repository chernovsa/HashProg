/*
 * ProcessingPerformer.h
 *
 *  Created on: 18 дек. 2018 г.
 *      Author: chernov
 */

#ifndef DATAPROCESSING_PROCESSINGPERFORMER_H_
#define DATAPROCESSING_PROCESSINGPERFORMER_H_

#include "Types/Types.h"

class ProcessingPerformer {
public:
	ProcessingPerformer(ArrayData &input_data,ArrayData &output_data,int block_size);
	virtual ~ProcessingPerformer();
	void process();
private:
	ArrayData &input_data_;
	ArrayData &output_data_;
	int block_size_;
};

#endif /* DATAPROCESSING_PROCESSINGPERFORMER_H_ */
