#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include"helper.h"
#include"../Server/Server.h"


void copystrr (unsigned char * old , unsigned char* neww)
{
    for(int i = 0 ; old[i] != 0 ; i++)
    {
        neww[i] = old[i];
    }
}

int hashfunction(uint8_t* str, uint32_t size)
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
		if (account_database[newindex].primaryAccountNumber[0] == 0)
		{
			account_database[newindex] = member;
			return;
		}
	}
}
int lookup_table(uint8_t* pan)
{
	int index = hashfunction(pan, 255);
	for (int i = 0; i < 255; i++)
	{
		int newindex = (i + index) % 255;
		if (account_database[newindex].primaryAccountNumber[0] != 0 && strcmp(account_database[newindex].primaryAccountNumber, pan) == 0)
		{
			return 0;
		}
	}
	return 1;
}
int lookup_table1(uint8_t* pan)
{
	int index = hashfunction(pan, 255);
	for (int i = 0; i < 255; i++)
	{
		int newindex = (i + index) % 255;
		if (account_database[newindex].primaryAccountNumber[0] != NULL && strcmp(account_database[newindex].primaryAccountNumber, pan) == 0)
		{
			return newindex;
		}
	}
	return NULL;
}
int binarysearch(uint32_t transactionNumber, uint32_t a, uint32_t b)
{
	if (a == b) return -1;
	if (side_transaction_database[(a + b) / 2].transactionSequenceNumber == transactionNumber) return (a + b) / 2;
	else if (side_transaction_database[(a + b) / 2].transactionSequenceNumber > transactionNumber) return binarysearch(transactionNumber, (a + b) / 2, b);
	else if (side_transaction_database[(a + b) / 2].transactionSequenceNumber < transactionNumber) return binarysearch(transactionNumber, a, (a + b) / 2);

}

