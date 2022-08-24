#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include"helper.h"
#include"../Server/Server.h"

void intialize_table()
{
	for (int i = 0; i < 255; i++)
	{
		account_database[i].balance = 0;
	}
}
void intialize_table_transaction()
{
	for (int i = 0; i < 255; i++)
	{
		side_transaction_database[i].transactionSequenceNumber = 0;
	}
}
int hashfunction(char* str, int size)
{
	int sum = 0;
	for (int i = 0; str[i] != 0; i++)
	{
		sum += str[i];
	}
	return sum % size;
}
void insert_hashtable(ST_accountsDB_t member)
{
	int index = hashfunction(member.primaryAccountNumber, 255);
	for (int i = 0; i < 255; i++)
	{
		int newindex = (i + index) % 255;
		if (account_database[newindex].state == NULL)
		{
			account_database[newindex] = member;
			return;
		}
	}
}
int lookup_table(char* pan)
{
	int index = hashfunction(pan, 255);
	for (int i = 0; i < 255; i++)
	{
		int newindex = (i + index) % 255;
		if (account_database[newindex].state != NULL && strcmp(account_database[newindex].primaryAccountNumber, pan) == 0)
		{
			return 0;
		}
	}
	return 1;
}
ST_accountsDB_t* lookup_table1(char* pan)
{
	int index = hashfunction(pan, 255);
	for (int i = 0; i < 255; i++)
	{
		int newindex = (i + index) % 255;
		if (account_database[newindex].state != NULL && strcmp(account_database[newindex].primaryAccountNumber, pan) == 0)
		{
			return &account_database[newindex];
		}
	}
	return NULL;
}
ST_transaction_t* binarysearch(int transactionNumber, int a, int b)
{
	if (a == b) return NULL;
	if (side_transaction_database[(a + b) / 2].transactionSequenceNumber == transactionNumber) return &side_transaction_database[(a + b) / 2];
	else if (side_transaction_database[(a + b) / 2].transactionSequenceNumber > transactionNumber) return binarysearch(transactionNumber, (a + b) / 2, b);
	else if (side_transaction_database[(a + b) / 2].transactionSequenceNumber < transactionNumber) return binarysearch(transactionNumber, a, (a + b) / 2);

}
