#ifndef Card_h
#define Card_h

#include<stdio.h>
#include<stdlib.h>

typedef struct ST_cardData_t
{
	char cardHolderName[25];
	char primaryAccountNumber[20];
	char cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif // !Card.h
