#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Server.h"
#include"../helper function/helper.h"




ST_accountsDB_t person = { 2000.0 ,RUNNING,"8989374615436851"};
void insert_hashtable(person);
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t* member = lookup_table1(transData->cardHolderData.primaryAccountNumber);
	if (lookup_table(transData->cardHolderData.primaryAccountNumber)) return FRAUD_CARD;
	if (transData->terminalData.transAmount > member->balance) return DECLINED_INSUFFECIENT_FUND;
	if (member->state == BLOCKED) return DECLINED_STOLEN_CARD;
	for (int i = 0; i < 255; i++)
	{
		if (side_transaction_database[i].transState == NULL)
		{
			side_transaction_database[i] = *transData;
			member->balance = member->balance - transData->terminalData.transAmount;
			return APPROVED;
		}
	}
	return INTERNAL_SERVER_ERROR;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	accountRefrence = lookup_table1(cardData->primaryAccountNumber);
	if (accountRefrence == NULL) return ACCOUNT_NOT_FOUND;
	return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance) return LOW_BALANCE;
	return SERVER_OK;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	for (int i = 0; i < 255; i++)
	{
		if (side_transaction_database[i].transState == NULL)
		{
			side_transaction_database[i] = *transData;
			if (i != 0)
			{
				side_transaction_database[i].transactionSequenceNumber = side_transaction_database[i - 1].transactionSequenceNumber + 1;
			}
			return SERVER_OK;
		}
	}
	return SAVING_FAILED;
}
EN_serverError_t getTransaction(int transactionSequenceNumber, ST_transaction_t* transData)
{
	if (binarysearch(transactionSequenceNumber, 0, 255) == NULL) return TRANSACTION_NOT_FOUND;
	return SERVER_OK;
}
