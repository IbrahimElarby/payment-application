#include"App.h"
#include"../helper function/helper.h"
#include"../Server/Server.h"
#include"../Terminal/Terminal.h"
#include"../Card/Card.h"
#include<stdio.h>
#include<stdlib.h>
ST_cardData_t mycard;
ST_terminalData_t mytransaction;
ST_accountsDB_t myaccount ;
void appStart(void)
{
	if(getCardHolderName(&mycard) == WRONG_NAME)
    {
        printf("WORNG NAME FORMAT");
        return;
    }
	if(getCardExpiryDate(&mycard) == WRONG_EXP_DATE)
    {
        printf("WRONG EXP_DATE FORMAT");
	    return ;
    }
    if(getCardPAN(&mycard)== WRONG_PAN)
    {
        printf("WRONG PAN FORMAT");
	    return ;
    }
	if( getTransactionDate(&mytransaction) == WRONG_DATE)
    {
        printf("WRONG DATE FORMAT");
        return;
    }
	if (isCardExpired(mycard, mytransaction) == EXPIRED_CARD)
	{
		printf("EXPIRED CARD\n");
		return;
	}
	getTransactionAmount(&mytransaction);
	setMaxAmount(&mytransaction);
	if (isBelowMaxAmount(&mytransaction) == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEEDED MAX AMOUNT");
		return;
	}
	if (isValidAccount(&mycard, &myaccount) == ACCOUNT_NOT_FOUND)
	{
		printf("ACCOUNT NOT FOUND");
		return;
	}
	if (isAmountAvailable(&mytransaction, &myaccount) == LOW_BALANCE)
	{
		printf("LOW BALANCE");
		return;
	}
	recieveTransactionData(&mytransaction);
	saveTransaction(&mytransaction);

}
