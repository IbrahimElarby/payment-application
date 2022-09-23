#include<stdio.h>
#include<stdlib.h>
#include"../App/App.h"


void printdata(ST_accountsDB_t mem)
{
    printf("%f  %s \n" , mem.balance, mem.primaryAccountNumber);

}

int main()
{
    ST_accountsDB_t person = { 2000.0 ,RUNNING,"8989374615436851"};
ST_accountsDB_t person1 = { 50000.0 ,RUNNING,"8989374615445861"};
ST_accountsDB_t person2 = { 26658.0 ,RUNNING,"4559374615436851"};
ST_accountsDB_t person3 = { 1255.0 ,RUNNING,"8456862615436851"};
ST_accountsDB_t person4 = { 248865.0 ,RUNNING,"8989396877412235"};
ST_accountsDB_t person5 = { 4000.0 ,BLOCKED,"4758628656322447"};
insert_hashtable(person);
insert_hashtable(person1);
insert_hashtable(person2);
insert_hashtable(person3);
insert_hashtable(person4);
insert_hashtable(person5);



	appStart();
}
