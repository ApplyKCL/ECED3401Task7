#include "SSSTurnkeySys.h"
/*
* Author: Shaonan Hu & Jiahao Chen
* Date Nov 30th 2021
* Fuction:
*	-Enable the user to check the record by input ID
*/

void IdAccessCust(FILE* cfile) {
	long custID=0;
	long nextCustID = 0;
	chead cheader;

	//move file pointer to the start of the file
	fseek(cfile, 0, SEEK_SET);
	//read the header record
	fread(&cheader, sizeof(chead), 1, cfile);
	nextCustID = cheader.cnextid;

	do {
		printf("Please Enter the Customer You want to Check?\n");
		scanf("%u", &custID);
		(void)getchar();
		if (custID >= nextCustID) {
			printf("Wrong Input ID: %u \n\
Do you have other Customer ID to Check ?\n\
Enter 1 if you still have another customer to check\n\
Enter 0 if you do not have any other custmoer to check\n", custID);
			scanf("%c", &choice);
			(void)getchar();;
			continue;
		}
		fseek(cfile, (custID - IDconstant) * sizeof(CREC), SEEK_SET);
		fread(&customer, sizeof(CREC), 1, cfile);
		printf("<%u>\n<%s> <%s>\n<%s> <%s> <%s> <%s> <%s>\n",
			customer.crec.cid,
			customer.crec.cname,
			customer.crec.bname,
			customer.crec.strname,
			customer.crec.town,
			customer.crec.province,
			customer.crec.ptcode,
			customer.crec.phonenum);
		if (customer.crec.CustStatus == Deleted) {
			printf("Customer Has Deleted\n");
		}
		else if(customer.crec.CustStatus==Active){
			printf("Customer is Active\n");
		}
		printf("Do you have any other Custmoer ID to Check ?\n\
Enter 1 if you still have another customer to check\n\
Enter 0 if you do not have any other custmoer to check\n");
		scanf("%c", &choice);
		(void)getchar();

	} while (choice != '0');
	

}

void IdAccessSup(FILE* sfile) {
	int supID = 0;
	int nextSupID = 0;
	shead sheader;
	//move file pointer to the start of the file
	fseek(sfile, 0, SEEK_SET);
	//read the header record at the start of the file
	fread(&sheader, sizeof(shead), 1, sfile);
	//assign the next record ID stored at the filed to variable nextSupID
	nextSupID = sheader.snextid;

	do {
		printf("Please Enter the Supplier ID You want to Check?\n");
		scanf("%d", &supID);
		(void)getchar();
		if (supID >= nextSupID) {
			printf("Wrong Input ID, do you have other Supplier ID to Check ?\n\n\
Enter 1 if you still have another supplioer to check\n\
Enter 0 if you do not have any other supplier to check\n");
			scanf("%c", &choice);
			(void)getchar();
			continue;
		}
		fseek(sfile, (supID - IDconstant) * sizeof(SREC), SEEK_SET);
		fread(&supplier, sizeof(SREC), 1, sfile);
		printf("<%d>\n<%s> <%s> <%s> <%s>\n<%s> <%s>\n",
			supplier.srec.sid,
			supplier.srec.Manufacturer,
			supplier.srec.Contact,
			supplier.srec.Company,
			supplier.srec.Addr,
			supplier.srec.phonenum,
			supplier.srec.email);
		if (supplier.srec.SupStatus == Deleted) {
			printf("--Deleted--\n");
		}
		else if (supplier.srec.SupStatus==Active) {
			printf("--Active--\n");
		}
		printf("Do you have any other Supplier ID to Check ?\n\n\
Enter 1 if you still have another supplier to check\n\
Enter 0 if you do not have any other supplier to check\n");
		scanf("%c", &choice);
		(void)getchar();

	} while (choice!='0');
}

void IdAccessProd(FILE* pfile) {
	int prodID = 0;
	int nextProdID = 0;
	phead pheader;

	fseek(pfile, 0, SEEK_SET);

	fread(&pheader, sizeof(shead), 1, pfile);

	nextProdID = pheader.pnextid;

	do {
		printf("Please Enter the Product ID You want to Check?\n");
		scanf("%d", &prodID);
		(void)getchar();
		if (prodID >= nextProdID) {
			printf("Wrong Input ID, do you have other Product ID to Check ?\n\n\
Enter 1 if you still have another product to check\n\
Enter 0 if you do not have any other product to check\n");
			scanf("%c", &choice);
			(void)getchar();
			continue;
		}
		fseek(pfile, prodID* sizeof(PREC), SEEK_SET);
		fread(&product, sizeof(PREC), 1, pfile);
		printf("<%d>\n<%s %s %s> <$%d.%02d> <%s> <%d> <%d>\n",
			product.prec.pid,
			product.prec.Productname,
			product.prec.Classification,
			product.prec.Manufacturer,
			product.prec.Unitcost / 100,
			product.prec.Unitcost % 100,
			product.prec.ManuCode,
			product.prec.stock,
			product.prec.reorderlevel);
		//Check the Stock Status, and display the
		//Stock Status
		if (product.prec.ProdStatus==Deleted) {
			printf("--Deleted--\n");
		}
		else if (product.prec.ProdStatus==Active) {
			printf("-Active-\n");

		}
		printf("Do you have any other Product ID to Check ?\n\n\
Enter 1 if you still have another product to check\n\
Enter 0 if you do not have any other product to check\n");
		scanf("%c", &choice);
		(void)getchar();

	} while (choice != '0');

}