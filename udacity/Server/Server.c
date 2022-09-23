#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Server.h"
#include"../helper function/helper.h"





EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    int index = lookup_table1(transData->cardHolderData.primaryAccountNumber);
	ST_accountsDB_t * member = &account_database[index] ;

	if (lookup_table(transData->cardHolderData.primaryAccountNumber))
    {printf("fraud card\n");
        return FRAUD_CARD;}
	if (transData->terminalData.transAmount > member->balance)
    {printf("insuffecient fund\n");
        return DECLINED_INSUFFECIENT_FUND;}
	if (member->state == BLOCKED)
    { printf("decline stolen card\n");
        return DECLINED_STOLEN_CARD;}
	for (int i = 0; i < 255; i++)
	{
		if (side_transaction_database[i].transactionSequenceNumber == 0)
		{
			side_transaction_database[i] = *transData;
			printf("your account was  %f  \n",member->balance);
			member->balance = member->balance - transData->terminalData.transAmount;
			int index = hashfunction(transData->cardHolderData.primaryAccountNumber,255);
			//account_database[index].balance = member->balance;
			printf("now is %f \n",account_database[index].balance);
			printf("successful operation \n");

			return APPROVED;
		}
	}
	printf("internal server error");
	return INTERNAL_SERVER_ERROR;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{

	int index = lookup_table1(cardData->primaryAccountNumber);
	//printf("index is %d\n",index);
	*accountRefrence = account_database[index];
	//printf("%f   %s \n  %f   %s   ", accountRefrence->balance, accountRefrence->primaryAccountNumber, account_database[index].balance , account_database[index].primaryAccountNumber);
	if (accountRefrence->primaryAccountNumber[0] == 0) return ACCOUNT_NOT_FOUND;
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
		if (side_transaction_database[i].transactionSequenceNumber == 0)
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
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	if (binarysearch(transactionSequenceNumber, 0, 255) == -1) return TRANSACTION_NOT_FOUND;
	return SERVER_OK;
}
