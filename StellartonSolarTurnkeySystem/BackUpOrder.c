#include"SSSTurnkeySys.h"

int count_backorder;

void Createbackorder(FILE* bkfile, MSREC salelist, int idx) {
	BKREC backorder;
	bkhead bkheader;
	long tempbkID;
	
	fseek(bkfile, 0, SEEK_SET);
	fread(&bkheader, sizeof(bkhead), 1, bkfile);

	if (fseek(bkfile, bkheader.backorder_nextid * sizeof(BKREC), SEEK_SET) < 0) {
		printf("Invalid BackOrder ID: %u\n",\
			bkheader.backorder_nextid);
		return;
	}

	fread(&backorder, sizeof(BKREC), 1, bkfile);
	backorder.bkrec.backorderid = bkheader.backorder_nextid;
	backorder.bkrec.custid = salelist.salerec.custid;
	strcpy(backorder.bkrec.cust, salelist.salerec.custname);
	strcpy(backorder.bkrec.productname, product.prec.Productname);
	backorder.bkrec.prodid = product.prec.pid;
	if (product.prec.fistbkID == -1)
		product.prec.fistbkID = backorder.bkrec.backorderid;
	tempbkID = product.prec.newbkID;
	product.prec.newbkID = backorder.bkrec.backorderid;
	backorder.bkrec.requierdquality = salelist.salerec.lacknumopurchase[idx];
	backorder.bkrec.nextbkID = -1;
	fseek(bkfile, backorder.bkrec.backorderid * sizeof(BKREC), SEEK_SET);
	fwrite(&backorder, sizeof(BKREC), 1, bkfile);
	if (tempbkID != -1) {
		fseek(bkfile, tempbkID * sizeof(BKREC), SEEK_SET);
		fread(&backorder, sizeof(BKREC), 1, bkfile);
		backorder.bkrec.nextbkID = tempbkID;
		fseek(bkfile, tempbkID * sizeof(BKREC), SEEK_SET);
		fwrite(&backorder, sizeof(BKREC), 1, bkfile);
	}
	count_backorder++;
}
//If the orders has already writed, fill the order
//IF the reorder level Unchange
//Stock Level
//What ever the reorder level is changed or not, the only thing that determine the backorder
//is the Stock Has stock, we have to like modify
//we check the stock level at the end of the fill back up order function at the end
//If still remain low
//do we care?/?
//No, we only check the order once in the entire program 
//well since, the only change of the product record will influnce the overall function is just stock
//Also, indicate when both reorder level and stock reach to 0;
//Prec??
//Back up Order may need to be written in the function
//maybe instead transfer we have to make sure the current stock reach to reorderlevel
//what we read form keyboard, is how much we added to the stock
//it never to be 0;
//what we pass ?
//*(int*)stock+=input amount
//Pass the entire rec
//we get *(int*)
//We may can
//entire rec
//return stock current
//int
//re link
//we must PREC and BKFILE POINTER
//why we care
//no
//
void FillBackUpOrder(PREC product, FILE*bkfile) {
	BKREC backorder;
	bkhead bkheader;

	fseek(bkfile, 0, SEEK_SET);
	fread(&bkheader, sizeof(bkhead), 1, bkfile);
	while (product.prec.newbkID!=-1) {
		
		fseek(bkfile, product.prec.fistbkID * sizeof(BKREC), SEEK_SET);
		fread(&backorder, sizeof(BKREC), 1, bkfile);
		switch (product.prec.stock > backorder.bkrec.requierdquality) {
		case True:
			product.prec.stock -= backorder.bkrec.requierdquality;
			backorder.bkrec.requierdquality = 0;
			backorder.bkrec.BkStatus = Filled;
			product.prec.fistbkID = backorder.bkrec.nextbkID;
			break;
		case False:
			backorder.bkrec.requierdquality -= product.prec.stock;
			product.prec.stock = 0;
			break;
		}
		fseek(bkfile, backorder.bkrec.backorderid * sizeof(BKREC), SEEK_SET);
		fwrite(&bkheader, sizeof(BKREC), 1, bkfile);
		if (product.prec.fistbkID == -1) {
			product.prec.newbkID = -1;
			printf("All of the BackOrder assigned to this product has filled\n");
			(void)getchar;
		}
	}
}
/*void Createbackorder(FILE* bkfile, FILE* pfile, MSREC salelist) {
	BKREC backorder;
	bkhead bkheader;
	unsigned int index = 0;
	long currentbkorderID = 0;

	fseek(bkfile, 0, SEEK_SET);
	fread(&bkheader, sizeof(bkhead), 1, SEEK_SET);

	if (fseek(bkfile, bkheader.backorder_nextid * sizeof(BKREC), SEEK_SET) < 0) {
		printf("Invalid BackOrder ID\n");
		return;
	}
	currentbkorderID = bkheader.backorder_nextid;
	backorder.bkrec.backorderid = currentbkorderID;
	backorder.bkrec.custid = salelist.salerec.custid;
	strcpy(backorder.bkrec.cust, salelist.salerec.custname);
	backorder.bkrec.item = salelist.salerec.index;
	backorder.bkrec.encodedate = salelist.salerec.encodedate;
	while (index<= backorder.bkrec.item)
	{
		strcpy(backorder.bkrec.productname[index], salelist.salerec.prodname[index]);
		backorder.bkrec.prodid[index] = salelist.salerec.prodid[index];
		backorder.bkrec.requierdquality[index] = salelist.salerec.lacknumopurchase[index];
		backorder.bkrec.nextbkID[index] = -1;
		fseek(pfile, salelist.salerec.prodid[index] * sizeof(PREC), SEEK_SET);
		fread(&product, sizeof(PREC), 1, pfile);
		if (product.prec.fistbkID == -1)
			product.prec.fistbkID = currentbkorderID;
		if (product.prec.newbkID == -1) {
			product.prec.newbkID = backorder.bkrec.backorderid;
		}
		fseek(pfile, salelist.salerec.prodid[index] * sizeof(PREC), SEEK_SET);
		fwrite(&product, sizeof(PREC), 1, pfile);
	}
	return;
}
*/