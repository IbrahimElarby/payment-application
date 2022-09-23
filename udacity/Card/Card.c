#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("please enter your name ");
	gets(cardData->cardHolderName);
	int len = strlen(cardData->cardHolderName);
	if (len > 24 || len < 20)
	{
	    return WRONG_NAME;
	}
	for(int i = 0 ; i < len ; i++)
    {
        if(isalpha(cardData->cardHolderName[i])== 0 && cardData->cardHolderName[i] != ' ' )
        {
            return WRONG_NAME;
        }
    }
	return CARD_OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("what is card expiry date in 'MM/YY' format ");
	gets(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate[5] != '\0') return WRONG_EXP_DATE;
	if (cardData->cardExpirationDate[0] > '1' && cardData->cardExpirationDate[0] < '0') return WRONG_EXP_DATE;
	if (!(isdigit(cardData->cardExpirationDate[1])))return WRONG_EXP_DATE;
	else if(cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1]>'2')return WRONG_EXP_DATE;
	if (cardData->cardExpirationDate[2] != '/') return WRONG_EXP_DATE;
	if (!isdigit(cardData->cardExpirationDate[3]))return WRONG_EXP_DATE;
	if (!isdigit(cardData->cardExpirationDate[4]))return WRONG_EXP_DATE;
	return CARD_OK;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("please enter your PAN ");
	gets(cardData->primaryAccountNumber);
	int len = strlen(cardData->primaryAccountNumber);
	if (len > 19 || len < 16)
    {
        return WRONG_PAN;
    }
	for(int i = 0 ; i < len ; i++)
    {
        if (!isalnum(cardData->primaryAccountNumber[i]))
        return WRONG_PAN;
    }
	return CARD_OK;
}

