#ifndef helper_h
#define helper_h

#include"../Server/Server.h"

void copystrr(unsigned char* old , unsigned char* neww);


int hashfunction(uint8_t* str, uint32_t size);
void insert_hashtable(ST_accountsDB_t member);
int lookup_table(uint8_t* pan);
int lookup_table1(uint8_t* pan);
int binarysearch(uint32_t transactionNumber, uint32_t a, uint32_t b);
#endif // !helper.h

