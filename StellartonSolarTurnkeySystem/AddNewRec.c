/*Program File: AddNewRec.c
Author: Shaonan Hu & Jiaohao Chen
Last Modified Date: Nov 15th 2021
Function: 
	-Add new record to the exist record
*/
#include "SSSTurnkeySys.h"
//Update Rec
//Orders
//PayDue
//BackOrder
//Table Driven

//Function Defination to add Customer
void AddCust(FILE* cfile)
{
	chead chrec;
	long cid;

	//Put the file pointer to the position 0
	fseek(cfile, 0, SEEK_SET);
	//Read the header record at the position 0
	fread(&chrec, sizeof(chead), 1, cfile);
	//Prompt the user to enter the Customer ID
	printf("Customer ID is : %d\n", chrec.cnextid);
	//Assign the record ID
	cid = chrec.cnextid;

	//the position of the next record at the file pointer is valid
	//since the customer start from 1000, the record number should be
	//cid-999 ex: (1000-999)-1st Customer Record
	if (fseek(cfile, (cid-IDconstant) * sizeof(CREC), SEEK_SET) < 0)
	{
		printf("Invalid Customer ID: %u\n", cid);
		(void)getchar();
		return;
	}
	//For loop stop until reach to the MAXCUSTFILED (7)
	//Write date to the arrey which has the address of the Customer Field
	for (int field = 0; field < MAXCUSTFIELD;field++) {
		printf("%s\n", AddCustProm[field]);
		fgets(CustFieldPtr[field], CustFieldSize[field], stdin);
		TRUNCATE(CustFieldPtr[field]);
	}

	//Assign the customer id to the input customer id
	customer.crec.cid = cid;
	//Initial the CustStatus to Active
	customer.crec.CustStatus = Active;
	//Inital the Customer next deleted ID field to -1
	//-1 indicate that there is no next deleted ID linked
	customer.crec.nextDelCustID = -1;
	//write the record to the position that pointed by the file pointer
	fwrite(&customer, sizeof(CREC), 1, cfile);

	//move the file pointer to the header record
	fseek(cfile, 0, SEEK_SET);
	//increment the customer id to the next customer id
	chrec.cnextid = chrec.cnextid + 1;
	//update the next customer id
	fwrite(&chrec, sizeof(chead), 1, cfile);
	//Prompt the Customer has Added
	printf("\n/*Customer Added*/\n");
	
}

//Function Defination to add supplier
//Same Construction as above
void AddSup(FILE* sfile)
{
	
	shead shrec;
	long sid;

	//Put the fiel pointer of supplier rec to the 0 position
	fseek(sfile, 0, SEEK_SET);
	//read the header record
	fread(&shrec, sizeof(shead), 1, sfile);
	//prompt the user to enter the data
	printf("Supplier ID is : %u\n", shrec.snextid);
	sid = shrec.snextid;

	//Move the file pointer to the next supplier
	//check if it is a valid 
	if (fseek(sfile, (sid - IDconstant) * sizeof(SREC), SEEK_SET) < 0)
	{
		printf("Invalid Supplier ID: %u\n", sid);
		(void)getchar();
		return;
	}
	
	//Write the record to the array assigned to each field of the Supplier
	for (int field = 0; field < MAXSUPFIELD; field++) {
		printf("%s\n", AddSupProm[field]);
		fgets(SupFieldPtr[field], SupFieldSize[field], stdin);
		TRUNCATE(SupFieldPtr[field]);
	}
	//Update the supplier ID to a new ID
	supplier.srec.sid = sid;
	//Initial the Supplier Status to Active
	supplier.srec.SupStatus = Active;

	supplier.srec.nextDelSupID = -1;
	//write the record to the file
	fwrite(&supplier, sizeof(SREC), 1, sfile);
	//move file pointer to the position 0
	fseek(sfile, 0, SEEK_SET);
	//increment the nextid
	shrec.snextid = shrec.snextid + 1;
	//write the record to assigned file pointer
	fwrite(&shrec, sizeof(shead), 1, sfile);
	printf("\n/*Supplier Added*/\n");
	
}

//Function Defination to add Product
//Samiler Construction as above
void AddProd(FILE* pfile)
{
	phead phrec;
	long pid;
	char* UnitCost;
	char temp[NumLen];
	int money = 0;


	//put the file pointer to the 0 position
	fseek(pfile, 0, SEEK_SET);
	//read the record at the assigned position
	fread(&phrec, sizeof(phead), 1, pfile);

	printf("Product ID is : %u\n", phrec.pnextid);
	pid = phrec.pnextid;
	//Move the file pointer to the next file rec position
	//check if it is able to write
	if (fseek(pfile, pid * sizeof(PREC), SEEK_SET) < 0)
	{
		printf("Invalid Product ID: %u\n", pid);
		(void)getchar();
		return;
	}

	for (int field = 0; field < MAXPRODFIELD; field++) {
		printf("%s\n", AddProdProm[field]);

		switch (ProdFiledType[field]) {
		case CharType:
			fgets(ProdFieldPtr[field], ProdFieldSize[field], stdin);
			TRUNCATE(ProdFieldPtr[field]);
			break;
		case MoneyType:
			fgets(temp, NumLen, stdin);
			UnitCost = strtok(temp, "\n");
			MONEY(money, *UnitCost, UnitCost);
			*(int*)ProdFieldPtr[field] = money;
			money = 0;
			break;
		case ReorderType:
		case IntType:
			scanf("%d", (int*)ProdFieldPtr[field]);
			(void)getchar();
			break;
		}
	}

	product.prec.ProdStatus = Active;
	//store the current product id
	product.prec.pid = pid;
	product.prec.nextDelProdID = -1;
	product.prec.fistbkID = -1;
	product.prec.newbkID = -1;
	//write to the record field
	fwrite(&product, sizeof(PREC), 1, pfile);
	//set the file pointer to point to the position 0 in the file
	fseek(pfile, 0, SEEK_SET);
	//increment the product id to the next product id
	phrec.pnextid = phrec.pnextid + 1;
	//write the next product id to the file
	fwrite(&phrec, sizeof(phead), 1, pfile);
	printf("\n/*Product Added*/\n");
}
