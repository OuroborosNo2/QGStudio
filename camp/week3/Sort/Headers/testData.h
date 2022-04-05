#ifndef TESTDATA_H_INCLUDED
#define TESTDATA_H_INCLUDED


/**
 * @name           :int createData(int min,int max,unsigned int quantity,char *dataIndex);
 * @description    :To create and save the data for test
 * @param          :dataIndex-文件编号
 * @return         :0-error,1-success
*/
int createData(int min,int max,unsigned int quantity,char *dataIndex);

/**
 * @name            :int* readData(char *dataIndex);
 * @description     :To read the data from file.
 * @param           :dataIndex-文件编号
 * @return          :0-error,1-success
*/
void readData(char *dataIndex,int *arr);

/**
 * @name            :int* readData(char *dataIndex);
 * @description     :To read the data from file.
 * @param           :dataIndex-文件编号
 * @return          :0-error,1-success
*/
void testTime(int quantity,int times);
#endif
