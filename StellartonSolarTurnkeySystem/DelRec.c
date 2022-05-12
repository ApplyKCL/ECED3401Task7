#include "SSSTurnkeySys.h"

void DelCust (FILE*cfile){
	long custID = 0;
	long nextCustID = 0;
	CREC customer;
	chead cheader;

	fseek(cfile, 0, SEEK_SET);

	fread(&cheader, sizeof(chead), 1, cfile);
	nextCustID = cheader.cnextid;
	if (nextCustID == StartCSID) {
		printf("No Record Exist\n");
		return;
	}

	printf("Please Enter the Customer ID that you want to delete\n");
	scanf("%d", &custID);
	(void)getchar();

	if ((custID >= nextCustID)||\
		(fseek(cfile, (custID - IDconstant) * sizeof(CREC), SEEK_SET) < 0)) {
		printf("Invalid Customer ID: %u\n", custID);
		return;
	}
	
	fread(&customer, sizeof(CREC), 1,cfile);
	if (customer.crec.CustStatus==Deleted)
	{
		printf("The Record Has deleted\n");
		return;
	}
	customer.crec.CustStatus = Deleted;
	customer.crec.nextDelCustID = cheader.DelCustList;
	cheader.DelCustList = custID;
	fseek(cfile, (custID - IDconstant) * sizeof(CREC), SEEK_SET);
	fwrite(&customer, sizeof(CREC), 1, cfile);
	fseek(cfile, 0, SEEK_SET);
	fwrite(&cheader, sizeof(chead), 1, cfile);
}
void DelSup(FILE* sfile) {
	long supID = 0;
	long nextSupID = 0;
	SREC supplier;
	shead sheader;

	fseek(sfile, 0, SEEK_SET);

	fread(&sheader, sizeof(shead), 1, sfile);
	nextSupID = sheader.snextid;
	if (nextSupID == StartCSID) {
		printf("No Record Exist\n");
		return;
	}

	printf("Please Enter the Supplier ID that your want to Delete: \n");
	scanf("%d", &supID);
	(void)getchar();
	if ((supID >= nextSupID)||\
		(fseek(sfile, (supID - IDconstant) * sizeof(SREC), SEEK_SET) < 0)) {
		printf("Invalid Supplier ID: %u\n", supID);
		return;
	}
	
	fread(&supplier, sizeof(SREC), 1, sfile);
	if (supplier.srec.SupStatus == Deleted)
	{
		printf("The Record Has deleted\n");
		return;
	}
	supplier.srec.SupStatus= Deleted;
	supplier.srec.nextDelSupID = sheader.DelSupList;
	sheader.DelSupList = supID;
	fseek(sfile, (supID - IDconstant) * sizeof(SREC), SEEK_SET);
	fwrite(&supplier, sizeof(SREC), 1, sfile);
	fseek(sfile, 0, SEEK_SET);
	fwrite(&sheader, sizeof(shead), 1, sfile);
}
void DelProd(FILE* pfile) {
	long prodID = 0;
	long nextProdID = 0;
	PREC product;
	phead pheader;

	fseek(pfile, 0, SEEK_SET);

	fread(&pheader, sizeof(phead), 1, pfile);
	nextProdID = pheader.pnextid;
	if (nextProdID == 1) {
		printf("No Record Exist\n");
		return;
	}

	printf("Please Enter the Product ID that your want to Delete: \n");
	scanf("%d", &prodID);
	(void)getchar();
	if ((prodID >= nextProdID)||\
		(fseek(pfile, prodID * sizeof(PREC), SEEK_SET) < 0)) {
		printf("Invalid Product ID: %u\n", prodID);
		return;
	}
	
	fread(&product, sizeof(PREC), 1, pfile);
	if (product.prec.ProdStatus == Deleted)
	{
		printf("The Record Has deleted\n");
		return;
	}
	fseek(pfile, prodID * sizeof(PREC), SEEK_SET);
	fread(&product, sizeof(PREC), 1, pfile);
	if (product.prec.stock != 0) {
		printf("Still has remaining stock which should not be deleted reight now\n");
		return;
	}
	product.prec.ProdStatus = Deleted;
	product.prec.nextDelProdID = pheader.DelProdList;
	pheader.DelProdList = prodID;
	fseek(pfile, prodID * sizeof(PREC), SEEK_SET);
	fwrite(&product, sizeof(PREC), 1, pfile);
	fseek(sfile, 0, SEEK_SET);
	fwrite(&pheader, sizeof(phead), 1, pfile);
}