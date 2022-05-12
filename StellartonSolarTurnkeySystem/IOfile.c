#include "SSSTurnkeySys.h"
/*
Author: Shaonan Hu & Jiahao Chen
Last Modified Date: Nov 16th 2021
Function:
	-Check does input file exist
	-Exist: Ask for covert file
	-Not Exist: Return to Main
*/

void InputFile(int argc, char* argv[], FILE*cfile, FILE*sfile, FILE*pfile, FILE*tfile, FILE*sales) {
	int idx = 1;
	int choice;
	//Check user already input data files
	//Go through every input files
	if (!OPENFILECHECK(SALEFILE, sales)) {
		WRITEFILE(SALEFILE, sales);
		//Function call for initial record
		InitSale(sales);
	}
	fclose(sales);
	while (idx<argc) {
		fopen_s(&tfile, argv[idx], "r");
		//Display the file address to tell user, which file was been handled
		printf("Input Identified->%s<-\n", argv[idx]);
		printf("Enter the file type for write\n(1. Customer, 2. Supplier, 3. Product, anyother key to exist) :\n");
		scanf("%d", &choice);
		(void)getchar();
		switch (choice){
		case 1:
			//Check the binary file is exist or not
			//If yes, return to while check next file
			//If not, create the output file as Customer.txt
			//Initilize the file and finish the convertion
			if (!OPENFILECHECK(CUSTFILE, cfile)) {
				//creat the record file for read an write
				WRITEFILE(CUSTFILE, cfile);
				//initial the record
				InitCust(cfile);
				//covert the TEXT Data to BINARY Data
				//CovCustFile(cfile, tfile);
				convfiletabledrivencust(cfile, tfile);
				fclose(cfile);
				break;
			}
			printf("Do not Overwrite the data file->%s<-Please select other data for coverting\n", CUSTFILE);
			fclose(cfile);
			continue;
		case 2:
			//Same process as case 1
			//The case 2 is for supplier file
			if (!OPENFILECHECK(SUPFILE, sfile)) {
				//creat the record file for read an write
				WRITEFILE(SUPFILE, sfile);
				//initial the record
				InitSup(sfile);
				//covert the TEXT Data to BINARY Data
				//CovSupFile(sfile, tfile);
				convfieldtabledrivensup(sfile, tfile);
				fclose(sfile);
				break;
			}
			printf("Do not Overwrite the data file->%s<-Please select other data for coverting\n", SUPFILE);
			fclose(sfile);
			continue;
		case 3:
			//Same process as case 1
			//The case 3 is for product file
			if (!OPENFILECHECK(PRODFILE, pfile)) {
				//creat the record file for read an write
				WRITEFILE(PRODFILE, pfile);
				//initial the record
				InitProd(pfile);
				//covert the TEXT Data to BINARY Data
				//CovProdFile(pfile, tfile);
				convfieldtabledrivenprod(pfile, tfile);
				fclose(pfile);
				break;
			}
			printf("Do not Overwrite the data file->%s<-Please select other data for coverting\n", PRODFILE);
			fclose(pfile);
			continue;
		default:
			(void)getchar();
			return;
		}

		idx++;
	}
	return;
}

/*int recordcheck(FILE* cfile, FILE* sfile, FILE* pfile, FILE* sales) {
	
	//close all of the record
	return True;
}
*/