#include"App.h"
#include"../helper function/helper.h"
#include"../Server/Server.h"
#include<stdio.h>
#include<stdlib.h>
ST_transaction_t mytransaction;
ST_accountsDB_t myaccount ;

void appStart(void)
{
	if(getCardHolderName(&(mytransaction.cardHolderData)) == WRONG_NAME)
    {
        printf("WORNG NAME FORMAT");
        return;
    }
	if(getCardExpiryDate(&(mytransaction.cardHolderData)) == WRONG_EXP_DATE)
    {
        printf("WRONG EXP_DATE FORMAT");
	    return ;
    }
    if(getCardPAN(&(mytransaction.cardHolderData))== WRONG_PAN)
    {
        printf("WRONG PAN FORMAT");
	    return ;
    }
	if( getTransactionDate(&(mytransaction.terminalData)) == WRONG_DATE)
    {
        printf("WRONG DATE FORMAT");
        return;
    }
	if (isCardExpired(&(mytransaction.cardHolderData),&(mytransaction.terminalData)) == EXPIRED_CARD)
	{
		printf("EXPIRED CARD\n");
		return;
	}
	getTransactionAmount(&(mytransaction.terminalData));
	setMaxAmount(&(mytransaction.terminalData));
	if (isBelowMaxAmount(&(mytransaction.terminalData)) == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEEDED MAX AMOUNT");
		return;
	}
	if (isValidAccount(&(mytransaction.cardHolderData), &myaccount) == ACCOUNT_NOT_FOUND)
	{
		printf("ACCOUNT NOT FOUND");
		return;
	}
	if (isAmountAvailable(&(mytransaction.terminalData), &myaccount) == LOW_BALANCE)
	{
		printf("LOW BALANCE");
		return;
	}
	recieveTransactionData(&mytransaction);
	saveTransaction(&mytransaction);

}
