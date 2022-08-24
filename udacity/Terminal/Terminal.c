#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("enter the transaction date in DD/MM/YYYY format ");
	scanf("%s", termData->transactionDate);
	if (strlen(termData->transactionDate) != 10)
	{
		return WRONG_DATE;
	}
	if (!(termData->transactionDate[2] == '/') || !(termData->transactionDate[5] == '/')) return WRONG_DATE;
	if (!isdigit(termData->transactionDate[1]))return WRONG_DATE;
	if (!isdigit(termData->transactionDate[4]))return WRONG_DATE;
	else if(termData->transactionDate[3] == '1' && termData->transactionDate[4]>'2')return WRONG_DATE;
	if (!isdigit(termData->transactionDate[6]))return WRONG_DATE;
	if (!isdigit(termData->transactionDate[7]))return WRONG_DATE;
	if (!isdigit(termData->transactionDate[8]))return WRONG_DATE;
	if (!isdigit(termData->transactionDate[9]))return WRONG_DATE;
	if (!(termData->transactionDate[0] > '0') || !(termData->transactionDate[0] <= '3'))return WRONG_DATE;
	if (!(termData->transactionDate[3] > '0') || !(termData->transactionDate[3] <= '1'))return WRONG_DATE;
	return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (termData.transactionDate[8] > cardData.cardExpirationDate[3])return EXPIRED_CARD;
	if (termData.transactionDate[9] > cardData.cardExpirationDate[4])return EXPIRED_CARD;
	if (termData.transactionDate[3] > cardData.cardExpirationDate[0])return EXPIRED_CARD;
	if (termData.transactionDate[4] > cardData.cardExpirationDate[1])return EXPIRED_CARD;
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("enter the transaction amount ");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0) return INVALID_AMOUNT;
	return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("enter the max transaction amount ");
	scanf("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) return INVALID_MAX_AMOUNT;
	return TERMINAL_OK;
}
