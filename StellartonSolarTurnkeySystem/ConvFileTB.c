#include "SSSTurnkeySys.h"

void convfiletabledrivencust(FILE*cfile, FILE*infile) {
	char inrec[MAX_REC];
	char* token;
	chead chrec;
	long cid;
	int field = 0;

	fseek(cfile, 0, SEEK_SET);
	fread(&chrec, sizeof(chead), 1, cfile);

	while (fgets(inrec, MAX_REC, infile) > 0) {

		cid = chrec.cnextid;
		if (fseek(cfile, (cid - IDconstant) * sizeof(CREC), SEEK_SET) < 0) {
			printf("Invalid Cid\n");
			(void)getchar();
			return;
		}

		//strtok- Exact the string when meet the configured delimiter
		token = strtok(inrec, ",");
		//copy the string to the customer name field
		field = 0;
		while (token) {
			strcpy(CustFieldPtr[field], token, CustFieldSize[field]);
			field++;
			token = strtok(NULL, ",\t\"\r\n");
		}
		//store the current customer id to the field
		customer.crec.cid = cid;
		customer.crec.CustStatus = Active;
		customer.crec.nextDelCustID = -1;
		//write to the record field
		fwrite(&customer, sizeof(CREC), 1, cfile);
		//increment the customer id to the next id
		chrec.cnextid = chrec.cnextid + 1;

	}
	//Move the file pointer to the position 0
	fseek(cfile, 0, SEEK_SET);
	//write the data to the record
	fwrite(&chrec, sizeof(chead), 1, cfile);
	//close the file
	fclose(infile);
}

void convfieldtabledrivensup(FILE* sfile, FILE* infile) {
	char inrec[MAX_REC];
	char* token;
	shead shrec;
	long sid;
	int field = 0;
	//Move the file pointer to the position 0
	fseek(sfile, 0, SEEK_SET);
	//read the record at the position 0
	fread(&shrec, sizeof(shead), 1, sfile);

	//read the record from the input file
	while (fgets(inrec, MAX_REC, infile) > 0) {

		//store the current id to a temp variable sid
		sid = shrec.snextid;
		//move the file pointer to the next position
		//check if it is valid
		if (fseek(sfile, (sid - IDconstant) * sizeof(SREC), SEEK_SET) < 0) {
			printf("Invalid Sid\n");
			(void)getchar();
			return;
		}
		//exact the string ended by delimiter from the input record
		token = strtok(inrec, "\t");
		field = 0;
		//store the string to the field
		while (token) {
			strcpy(SupFieldPtr[field], token, SupFieldSize[field]);
			field++;
			token = strtok(NULL, "\t\"\r\n");
		}

		supplier.srec.sid = sid;
		supplier.srec.SupStatus = Active;
		supplier.srec.nextDelSupID = -1;
		fwrite(&supplier, sizeof(SREC), 1, sfile);
		//increment the current id to the next id
		shrec.snextid = shrec.snextid + 1;
	}
	
	//move the file pointer to the position 0
	fseek(sfile, 0, SEEK_SET);
	//write to the file
	fwrite(&shrec, sizeof(shead), 1, sfile);
	//close the opened file
	fclose(infile);
}

void convfieldtabledrivenprod(FILE* pfile, FILE* infile) {
	char inrec[MAX_REC];
	char* token;
	int field = 0;
	int money;
	int stock;
	int reorderlevel;
	int temp=0;
	phead phrec;
	long pid;
	//put the file pointer to the position 0
	fseek(pfile, 0, SEEK_SET);
	//read the header record 
	fread(&phrec, sizeof(phead), 1, pfile);
	//read the string from the input file
	while (fgets(inrec, MAX_REC, infile) > 0) {
		//initial money and stock
		money = 0;
		stock = 0;
		reorderlevel = 0;
		//store the current product id to a temp value pid
		pid = phrec.pnextid;
		//move the file pointer to the next record position
		//check if it is valid
		if (fseek(pfile, pid * sizeof(PREC), SEEK_SET) < 0) {
			printf("Invalid Cid\n");
			(void)getchar();
			return;
		}
		//initialize the stockstatus to high stock
		//Extact the string before the delimiter
		token = strtok(inrec, "\"\t");
		field = 0;
		while (token) {
			switch (ProdFiledType[field]) {
			case CharType:
				strcpy(ProdFieldPtr[field], token, ProdFieldSize[field]);
				break;
			case MoneyType:
				MONEY(temp, *token, token);
				*(int*)ProdFieldPtr[field] = temp;
				break;
			case ReorderType:
			case IntType:
				STOCK(temp, *token, token);
				*(int*)ProdFieldPtr[field] = temp;
				break;
			}
			temp = 0;
			field++;
			token = strtok(NULL, "\"\t\r\n");
		}
		//store the string to the field
		product.prec.pid = pid;
		product.prec.ProdStatus = Active;
		product.prec.nextDelProdID = -1;
		product.prec.fistbkID = -1;
		product.prec.newbkID = -1;
		//write the value to the record
		fwrite(&product, sizeof(PREC), 1, pfile);
		//increment the current id to next id
		phrec.pnextid = phrec.pnextid + 1;

	}
	//move the file pointer the position 0
	fseek(pfile, 0, SEEK_SET);
	//write to the record
	fwrite(&phrec, sizeof(phead), 1, pfile);
	//close the file
	fclose(infile);
}

