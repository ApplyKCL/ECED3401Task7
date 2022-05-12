/*
Author: Shaonan Hu & Jiahao Chen
Last Modified Date: Nov 17th 2021
Function:
	-Initialize files using in the program
	-Set the id number for every kinds of files
*/
#include "SSSTurnkeySys.h"

void InitCust(FILE*cfile) {
	/*
	-Make the header to customer file
	-Set the first customer id is 1000
	-Move the file pointer to the assigned position
	-Writen down the first whole Customer record into binary file
	*/
	CREC cheader;
	//Set the next id as 1000 since the customer start id is 1000
	cheader.chrec.cnextid = 1000;
	cheader.chrec.DelCustList = -1;
	cheader.chrec.encodedate = 0;
	//move the file pointer to the position 0
	fseek(cfile, 0, SEEK_SET);
	//write to the rec
	fwrite(&cheader, sizeof(CREC), 1, cfile);
}
//Samiler to Customer initial fuction
void InitSup(FILE*sfile) {
	
	//This is for supplier
	SREC sheader;
	//Set the next id as 1000 since the Supplier start id is 1000
	sheader.shrec.snextid = 1000;
	sheader.shrec.DelSupList = -1;
	//move the file pointer to the position 0
	fseek(sfile, 0, SEEK_SET);
	//write to the rec
	fwrite(&sheader, sizeof(SREC), 1, sfile);
}
void InitProd(FILE*pfile) {
	//This is for product
	PREC pheader;
	//First product id is 1
	pheader.phrec.pnextid = 1;
	pheader.phrec.DelProdList = -1;
	//move the file pointer to the position 0
	fseek(pfile, 0, SEEK_SET);
	//write to the rec
	fwrite(&pheader, sizeof(PREC), 1, pfile);
}

void InitSale(FILE* sales) {
	//This is for make sale
	MSREC msheader;
	//initial the next id as 1 since the sales start form id 1
	msheader.mshrec.slnextid = 1;
	//move the file pointer to the position 0 at the file
	fseek(sales, 0, SEEK_SET);
	//write to the file
	fwrite(&msheader, sizeof(MSREC), 1, sales);
}

void InitPaydue(FILE* paydue){
	PDREC pdhearder;
	pdhearder.pdhrec.payduenextid = 1;
	fseek(paydue, 0, SEEK_SET);
	fwrite(&pdhearder,sizeof(PDREC), 1, paydue);
}

void InitBackorder(FILE* backorder) {
	BKREC backorderrec;
	backorderrec.bkheader.backorder_nextid = 1;
	//backorderrec.bkordhrec.backorder_subid = 1;
	fseek(backorder, 0, SEEK_SET);
	fwrite(&backorderrec, sizeof(PDREC), 1, backorder);
}