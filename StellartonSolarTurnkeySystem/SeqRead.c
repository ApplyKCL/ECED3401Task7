/*
Author: Shaonan Hu & Jiahao Chen
Last Modified Date: Nov 13rd 2021
Function:
	-Display the exist record sequencially
*/
#include "SSSTurnkeySys.h"

//Display the Customer in the Order of the Customer ID increases
//untill reach to the last Customer ID
void DisplayCust(FILE*ofile) {
	
	chead hrec;
	//The customer ID is start from 1000
	long cid=1000;

	//Move the file pointer to the 0 position
	fseek(ofile, 0, SEEK_SET);
	//Read the rec in the position that pointed by the file pointer
	fread(&hrec, sizeof(chead), 1,  ofile);
	//check if the next customer ID is 1000 (Start Customer ID)
	if (hrec.cnextid == 1000) {
		printf("No Records in Customer file");
		return;
	}

	//While Loop break when the current Customer ID less than the next customer ID
	while (cid < hrec.cnextid) {
		//Check if the current custome ID is valid at the position that pointed by file pointer
		if (fseek(ofile, (cid-999)* sizeof(CREC), SEEK_SET) < 0) {
			printf("Invalid Cid\n");
			(void)getchar();
			return;
		}
		//Read the customer ID at he current position
		fread(&customer, sizeof(CREC), 1, ofile);
		//Display the record at the current customer ID
		printf("<%d>\n<%s> <%s>\n<%s> <%s> <%s> <%s> <%s>\n",
			customer.crec.cid,
			customer.crec.cname,
			customer.crec.bname,
			customer.crec.strname,
			customer.crec.town,
			customer.crec.province,
			customer.crec.ptcode,
			customer.crec.phonenum);
		if (customer.crec.CustStatus == Deleted) {
			printf("--Deleted--\n");
		}
		else if(customer.crec.CustStatus==Active){
			printf("--Active--\n");
		}
		//Increase the Current Customer ID to the next Customer ID
		cid++;
	}
	printf("\n/*The Customer List has displayed*/\n");
	return;
}


//Display the Supplier in the Order of the Supplier ID increases
//untill reach to the last Supplier ID
void DisplaySup(FILE* ofile) {
	shead hrec;
	//The supplier ID is start from 1000
	long sid = 1000;

	//Move the file pointer to the 0 pointer
	fseek(ofile, 0, SEEK_SET);
	//Read the rec in the position that pointed by the file pointer
	fread(&hrec, sizeof(shead), 1, ofile);

	//check if the next supliier ID is 1000 (Start Supplier ID)
	if (hrec.snextid == 1000) {
		printf("No Records in Supplier file");
		return;
	}
	//While Loop break when the current Suplier ID less than the next Suplier ID
	while (sid < hrec.snextid) {
		//Check if the current supplier ID is valid at the position that pointed by file pointer
		if (fseek(ofile, (sid - 999) * sizeof(SREC), SEEK_SET) < 0) {
			printf("Invalid Supplier Id\n");
			(void)getchar();
			return;
		}
		//Read the customer ID at he current position
		fread(&supplier, sizeof(SREC), 1, ofile);
		//Display the record at the current supplier ID
		printf("<%u>\n<%s> <%s> <%s> <%s>\n<%s> <%s>\n",
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
		else if (supplier.srec.SupStatus == Active) {
			printf("--Active--\n");
		}
		//Increase the Current Suplier ID to the next Supplier ID
		sid++;
	}

	printf("\n/*The Supplier List has displayed*/\n");
	return;
}

//Display the Supplier in the Order of the Supplier ID increases
//untill reach to the last Supplier ID
void DisplayProd(FILE* ofile) {

	phead hrec;
	//The product ID is start from 1
	long pid = 1;
	//Move the file pointer to the 0 pointer
	fseek(ofile, 0, SEEK_SET);
	//Read the rec in the position that pointed by the file pointer
	fread(&hrec, sizeof(phead), 1, ofile);

	//check if the next Product ID is 1 (Start Product ID)
	if (hrec.pnextid == 1) {
		printf("No Records in Product file\n");
		return;
	}
	//While Loop break until Product ID
	while (pid < hrec.pnextid) {
		//Check if the current product ID is valid at the position that pointed by file pointer
		if (fseek(ofile, pid* sizeof(PREC), SEEK_SET) < 0) {
			printf("Invalid Product Id\n");
			(void)getchar();
			return;
		}
		//Move the file pointer to the 0 pointer
		fread(&product, sizeof(PREC), 1, ofile);
		//Read the rec in the position that pointed by the file pointer
		printf("<%u>\n<%s %s %s> <$%d.%02d> <%s> <%d> <%d>\n",
			product.prec.pid,
			product.prec.Productname,
			product.prec.Classification,
			product.prec.Manufacturer,
			product.prec.Unitcost / 100,
			product.prec.Unitcost % 100,
			product.prec.ManuCode,
			product.prec.stock,
			product.prec.reorderlevel);
		if (product.prec.ProdStatus == Deleted) {
			printf("--Deleted--\n");
		}
		else if (product.prec.ProdStatus == Active) {
			printf("-Active-\n");

		}
		//Check the Stock Status, and display the
		//Stock Status
	
		//Increase product ID to the next Product ID
		pid++;
	}
	printf("\n/*The Product List has displayed*/\n");
	return;
}

//Display the Product in the Order of the Product ID increases
//untill reach to the last Product ID
void DisplaySale(FILE*ofile) {
	
	MSREC salelist;
	mshead mshrec;
	
	//The Sales ID is start from 1
	long saleid = 1;
	unsigned day, month, year;

	//Move the file pointer to the 0 pointer
	fseek(ofile, 0, SEEK_SET);

	//Read the rec in the position that pointed by the file pointer
	fread(&mshrec, sizeof(mshead), 1, ofile);
	//While Loop break until Sales ID
	if (mshrec.slnextid == 1) {
		printf("No Record in Sales File\n");
		(void)getchar();
		return;
	}
	//Display the prompt
	printf("Date >Sale ID<\n >Customer Name< >Customer ID< >Phonenumber<\n >Product ID< >Product Name< >Manufacture Code<\
	>Unit Cost< >Amount<\n >Total Cost< >Customer Paid< >Account Balance<\n >Payment State<\n");
	//While loop break untile the next ID of Sales is reached
	while (saleid < mshrec.slnextid) {
		int index = 0;
		//Check if the current Sales ID is valid at the position that pointed by file pointer
		if (fseek(ofile, saleid * sizeof(MSREC), SEEK_SET) < 0) {
			printf("Invalid Sale ID\n");
			(void)getchar();
			return;
		}
		//Read the Record at the position that pointed by the file pointer
		fread(&salelist, sizeof(MSREC), 1, ofile);
		//Decode the encoded data
		DecodeDate(salelist.salerec.encodedate, &day, &month, &year);
		//display the record
		printf("\n>%u/%u/%u< >%u<\n>%s< >%u< >%s<\n",
			day,month,year,
			salelist.salerec.saleid,
			salelist.salerec.custname,
			salelist.salerec.custid,
			salelist.salerec.phonenumber
			);
		//While loop break until reach to the last sales index of product
		while(index<salelist.salerec.index){
			//display each of the products that the customer purchase
			printf("\n>%u< >%s< >%s< >$%d.%02d< >%d<\n",
				salelist.salerec.prodid[index],
				salelist.salerec.prodname[index],
				salelist.salerec.manucode[index],
				salelist.salerec.unitcost[index]/100,
				salelist.salerec.unitcost[index]%100,
				salelist.salerec.numofpurchase[index]);
			index++;
		}
		//display the money details in the record
		printf("\n>$%d.%02d<  >$%d.%02d<  >$%d.%02d<\n",
			salelist.salerec.totalcost/100,
			salelist.salerec.totalcost%100,
			salelist.salerec.payment/100,
			salelist.salerec.payment%100,
			salelist.salerec.balance/100,
			salelist.salerec.balance%100);
		
		//check the payments status
		switch (salelist.salerec.PAYMENTSTATUS) {
		case Unpaid:
			printf("Unpaided Bill\n");
			break;
		case Paid:
			printf("Balanced Own\n");
			break;
		
		}
		//increas the Sales ID to the next Sales
		saleid++;
	}
	printf("\n/*The Sales List has displayed*/\n");
	return;
}

void DisplayPaydue(FILE* paydue) {

	PDREC payduerec;
	pdhead pdhrec;
	//The product ID is start from 1
	long pid = 1;
	unsigned day, month, year;
	//Move the file pointer to the 0 pointer
	fseek(paydue, 0, SEEK_SET);
	//Read the rec in the position that pointed by the file pointer
	fread(&pdhrec, sizeof(phead), 1, paydue);

	//check if the next Product ID is 1 (Start Product ID)
	if (pdhrec.payduenextid == 0) {
		printf("No Records in Product file\n");
		return;
	}

	//While Loop break until Product ID
	while (pid <= pdhrec.payduenextid) {
		//Check if the current product ID is valid at the position that pointed by file pointer
		if (fseek(paydue, pid * sizeof(PDREC), SEEK_SET) < 0) {
			printf("Invalid Product Id\n");
			(void)getchar();
			return;
		}
		//Move the file pointer to the 0 pointer
		fread(&payduerec, sizeof(PDREC), 1, paydue);
		DecodeDate(payduerec.paydue.encodedate, &day, &month, &year);
		//Read the rec in the position that pointed by the file pointer
		printf("<%u/%u/%u>\n<%u %s %s> <$%d.%02d>\n",
			day,month,year,
			payduerec.paydue.cusid,
			payduerec.paydue.cusname,
			payduerec.paydue.phonenum,
			payduerec.paydue.balance / 100,
			payduerec.paydue.balance % 100);

		pid++;
	}
	printf("\n/*The Product List has displayed*/\n");
	return;
}