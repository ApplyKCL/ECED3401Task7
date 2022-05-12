#include"SSSTurnkeySys.h"

void CancelCustomerOrders(FILE* sales, FILE* pfile) {
	MSREC SalesRec;
	mshead msheader;

	long SalesID = 0;
	long nextSalesID = 0;
	int index = 0;
	fseek(sales, 0, SEEK_SET);
	fread(&msheader, sizeof(mshead), 1, sales);
	nextSalesID = msheader.slnextid;
	printf("Which Order you want to cancel?\n");
	scanf("%d", &SalesID);

	if (SalesID >= nextSalesID) {
		printf("Invalid Sales ID: %d\n", SalesID);
		(void)getchar();
		return;
	}
	fseek(sales, SalesID * sizeof(MSREC), SEEK_SET);
	fread(&SalesRec, sizeof(MSREC), 1, sales);

	if (SalesRec.salerec.ORDERSTATUS == Canceled) {
		printf("Order ID: %d\nOrder Has Canceled\n", SalesID);
		return;
	}
	SalesRec.salerec.ORDERSTATUS = Canceled;
	
	while (index > SalesRec.salerec.index) {
		fseek(pfile, SalesRec.salerec.prodid[index]*sizeof(PREC), SEEK_SET);
		fread(&product, sizeof(PREC), 1, pfile);
		product.prec.stock += SalesRec.salerec.numofpurchase[index];
		SalesRec.salerec.numofpurchase[index] = 0;
		fseek(pfile, SalesRec.salerec.prodid[index] * sizeof(PREC), SEEK_SET);
		fwrite(&product, sizeof(PREC), 1, pfile);
		index++;
	}
	fseek(sales, SalesID * sizeof(MSREC), SEEK_SET);
	fwrite(&SalesRec, sizeof(MSREC), 1, sales);
}