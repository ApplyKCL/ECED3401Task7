#include "SSSTurnkeySys.h"

void UpdateCust(FILE* cfile) {
	long custID = 0;
	int field;
	chead cheader;
	printf("Enter the Customer ID that you want to update?\n");
	scanf("%d", &custID);
	(void)getchar();

	fseek(cfile, 0, SEEK_SET);
	fread(&cheader, sizeof(chead), 1, cfile);
	if (custID >= cheader.cnextid) {
		printf("Customer ID: %d\n Do not exist\n", custID);
		return;
	}

	fseek(cfile, (custID - IDconstant) * sizeof(CREC), SEEK_SET);
	fread(&customer, sizeof(CREC), 1, cfile);
	if (customer.crec.CustStatus == Deleted) {
		printf("This Customer has been deleted\n");
		return;
	}
	do {
		printf("Which Types of Customer information you want to update ?\n");
		printf("Press 1 to update customer name\n");
		printf("Press 2 to update customer busniess name\n");
		printf("Press 3 to update Customer address\n");
		printf("Press 4 to update customer phone number\n");
		printf("Press 0 to Exist\n");
		scanf("%d", &field);
		(void)getchar();
		if (field == CustPhnumField) {
			field = MAXCUSTFIELD;
		}
		field -= 1;
		switch (field) {
		case -1:
			break;
		case 2:
			while (field < MAXCUSTFIELD - 1) {
				printf("%s\n", AddCustProm[field]);
				fgets(CustFieldPtr[field], CustFieldSize[field], stdin);
				TRUNCATE(CustFieldPtr[field]);
				field++;
			}
			break;
		default:
			printf("%s\n", AddCustProm[field]);
			fgets(CustFieldPtr[field], CustFieldSize[field], stdin);
			TRUNCATE(CustFieldPtr[field]);
			break;
		}
	} while (field != -1);
	fseek(cfile, (custID - IDconstant) * sizeof(CREC), SEEK_SET);
	fwrite(&customer, sizeof(CREC), 1, cfile);
}

void UpdateSup(FILE * sfile) {
		long supID = 0;
		int field;
		shead sheader;
		printf("Enter the Supplier ID you want to update: \n");
		scanf("%d", &supID);
		(void)getchar();
		fseek(sfile, 0, SEEK_SET);
		fread(&sheader, sizeof(shead), 1, sfile);
		if (supID > sheader.snextid) {
			printf("Supplier ID: %d\n Does not exist\n", supID);
			return;
		}
		fseek(cfile, (supID - IDconstant) * sizeof(SREC), SEEK_SET);
		fread(&supplier, sizeof(SREC), 1, sfile);
		if (supplier.srec.SupStatus == Deleted) {
			printf("This Supplier has Already Deleted\n");
			return;
		}
		do {
			printf("Which Types of the Supplier Information You Want to Update? \n\
Press 1 for Update Maufacture\n\
Press 2 for Update Contact\n\
Press 3 for Update Company\n\
Press 4 for Update Address\n\
Press 5 for Update phone Number\n\
Press 6 for Update Email\n\
Press 0 for Exist\n");
			scanf("%d", &field);
			(void)getchar();
			field -= 1;
			printf("%s\n", AddSupProm[field]);
			fgets(SupFieldPtr[field], SupFieldSize[field], stdin);
			TRUNCATE(SupFieldPtr[field]);
		} while (field != -1);
		fseek(cfile, (supID - IDconstant) * sizeof(SREC), SEEK_SET);
		fwrite(&supplier, sizeof(SREC), 1, sfile);
	}

void UpdateProd(FILE* pfile, FILE*bkfile) {
	long proID=0;
	char* UnitCost;
	char temp[NumLen];
	int money = 0;
	int field = 0;
	int inputstock = 0;
	phead pheader;
	printf("Enter the Product ID you want to update: \n");
	scanf("%d", &proID);
	(void)getchar();
	fseek(pfile, 0, SEEK_SET);
	fread(&pheader, sizeof(phead), 1, pfile);
	if (proID > pheader.pnextid) {
		printf("Product ID: %u\n Does not exist\n", proID);
		return;
	}
	fseek(pfile, (proID - IDconstant) * sizeof(PREC), SEEK_SET);
	fread(&product, sizeof(PREC), 1, pfile);
	if (product.prec.ProdStatus == Deleted) {
		printf("Product Has Already Deleted\n");
		(void)getchar();
		return;
	}
	do {
		printf("Which Types of the Product Information You Want to Update? \n\
Press 1 for Update Product Name\n\
Press 2 for Update Classification\n\
Press 3 for Update Manufacture\n\
Press 4 for Update Unit Cost\n\
Press 5 for Update Manufacture Code\n\
Press 6 for Update Stock\n\
Press 7 for Update Reorder Level\n\
Press 0 for Exist\n");
		scanf("%d", &field);
		(void)getchar();
		field -= 1;
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
			//
		case ReorderType:
			scanf("%d", (int*)ProdFieldPtr[field]);
			(void)getchar();
			break;
			//Since the stock is unkown, update the stock level could be add on the new stock
			//Base on this stock=orginal stock+added stock
			//No Company want to loose stock
		case IntType:
			printf("The Current Stock remain is %d\n\
Please Enter the number of Stock you want to added\n", product.prec.stock);
			scanf("%d", &inputstock);
			(void)getchar();
			*(int*)ProdFieldPtr[field]+=inputstock;
			//-1 indicate that there is no back up order linked
			//Else, we have backorder linked
			if (product.prec.newbkID != -1) {
				FillBackUpOrder(product, bkfile);
			}
			break;
		}

	} while (field != -1);
	fseek(pfile, (proID - IDconstant) * sizeof(PREC), SEEK_SET);
	fwrite(&product, sizeof(PREC), 1, pfile);
	return;
}