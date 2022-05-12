#include "SSSTurnkeySys.h"


void AddRecUI(FILE*cfile, FILE*sfile, FILE*pfile) {
	
	
	do
	{
		printf("Please Enter which Record you want to add\n");
		printf("Press 1 to Add New Customer\n");
		printf("Press 2 to Add New Supplier\n");
		printf("Press 3 to Add New Product\n");
		printf("Press # to exist\n");
		scanf("%c", &choice);
		(void)getchar();
		switch (choice) {
		case '1':
			AddCust(cfile);
			break;
		case '2':
			AddSup(sfile);
			break;
		case '3':
			AddProd(pfile);
			break;
		}
	} while (choice!='#');
	
}

void UpdateRecUI(FILE* cfile, FILE* sfile, FILE* pfile, FILE*bkfile) {
	

	do
	{
		printf("Please Enter which Record you want to update\n");
		printf("Press 1 to Update Customer Rec\n");
		printf("Press 2 to Update Supplier Rec\n");
		printf("Press 3 to Update Product Rec\n");
		printf("Press # to exist\n");
		scanf("%c", &choice);
		(void)getchar();
		switch (choice) {
		case '1':
			UpdateCust(cfile);
			break;
		case '2':
			UpdateSup(sfile);
			break;
		case '3':
			UpdateProd(pfile, bkfile);
			break;
		}
	} while (choice != '#');

}
void DelRecUI(FILE* cfile, FILE* sfile, FILE* pfile) {
	
	do
	{
		printf("Please Enter which Record you want to delete\n");
		printf("Press 1 to Delete Customer Rec\n");
		printf("Press 2 to Delete Supplier Rec\n");
		printf("Press 3 to Delete Product Rec\n");
		printf("Press # to exist\n");

		scanf("%c", &choice);
		(void)getchar();
		switch (choice) {
		case '1':
			DelCust(cfile);
			break;
		case '2':
			DelSup(sfile);
			break;
		case '3':
			DelProd(pfile);
			break;
		}
	} while (choice != '#');

}
void ReadRecUI(FILE* cfile, FILE* sfile, FILE* pfile) {


	do
	{
		printf("Enter Key to Display Record\n");
		printf("Press 1 to Display the All Customer Rec\n");
		printf("Press 2 to Display the All Supplier Rec\n");
		printf("Press 3 to Display the All Product Rec\n");
		printf("Press 4 to Display the Specific Customer Rec\n");
		printf("Press 5 to Display the Specific Supplier Rec\n");
		printf("Press 6 to Display the Specific Product Rec\n");
		printf("Press # to exist\n");
		scanf("%c", &choice);
		(void)getchar();
		switch (choice) {
		case '1':
			DisplayCust(cfile);
			break;
		case '2':
			DisplaySup(sfile);
			break;
		case '3':
			DisplayProd(pfile);
			break;
		case '4':
			IdAccessCust(cfile);
			break;
		case '5':
			IdAccessSup(sfile);
			break;
		case '6':
			IdAccessProd(pfile);
			break;
		}
	} while (choice != '#');

}