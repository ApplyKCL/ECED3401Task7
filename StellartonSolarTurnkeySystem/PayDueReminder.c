/*
-Check the make sale file to find unpaid sale order
-Check the date of sale order stay on unpaid for more than 30days
-Record inforamtion of sale order to PayDue File
*/
#include"SSSTurnkeySys.h"

void PayDueCheck(FILE*paydue, FILE*sales, unsigned long encodedate)
{
	/*
	-Read the record in makesale file
	-Search the record is passed 30 days from the date when they been made
	-Copy the information to paydue filefopen_s(&filepointer, filename, "r+")
	*/
	MSREC makesalerec;
	mshead mshrec;
	PDREC pdrec;
	pdhead pdhrec;
	//Initialize the id value
	long makesaleid = 1;
	long paydueid = 1;
   
	//Move the file pointer to original position
	fseek(sales, 0, SEEK_SET);
	fread(&mshrec,sizeof(mshead),1,sales);
	fseek(paydue, 0, SEEK_SET);
	fread(&pdhrec,sizeof(pdhead),1,paydue);
	paydueid = pdhrec.payduenextid; //

	fseek(sales, makesaleid*sizeof(MSREC), SEEK_SET);
	fread(&makesalerec, sizeof(MSREC), 1, sales);

	while ((encodedate-30) > makesalerec.salerec.encodedate)
	{
		fseek(sales, makesaleid * sizeof(MSREC), SEEK_SET);
		fread(&makesalerec, sizeof(MSREC), 1, sales);

		if (makesalerec.salerec.PAYMENTSTATUS == Unpaid)
		{
			strcpy(pdrec.paydue.cusname, makesalerec.salerec.custname);
			
			strcpy(pdrec.paydue.phonenum, makesalerec.salerec.phonenumber);
			pdrec.paydue.cusid = makesalerec.salerec.custid;
			pdrec.paydue.balance = makesalerec.salerec.balance;
			pdrec.paydue.encodedate = makesalerec.salerec.encodedate + 30;

			fseek(paydue, paydueid * sizeof(PDREC), SEEK_SET);
			fwrite(&pdrec, sizeof(PDREC), 1,paydue);
			paydueid++;
			pdhrec.payduenextid = paydueid;
			fseek(paydue, 0, SEEK_SET);
			fwrite(&pdhrec, sizeof(pdhead), 1, paydue);
		}
		makesaleid++;
		if (makesaleid >= mshrec.slnextid)
		{
			break;
		}
	}

	return;
}
