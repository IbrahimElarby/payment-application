#ifndef helper_h
#define helper_h

#include"../Server/Server.h"
void intialize_table();
void intialize_table_transaction();
int hashfunction(char* str, int size);
void insert_hashtable(ST_accountsDB_t member);
int lookup_table(char* pan);
ST_accountsDB_t* lookup_table1(char* pan);
ST_transaction_t* binarysearch(int transactionNumber, int a, int b);
#endif // !helper.h

