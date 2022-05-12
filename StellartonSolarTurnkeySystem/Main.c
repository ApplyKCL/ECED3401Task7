#include "SSSTurnkeySys.h"
/*
Program File: Main.c
Author: Shaonan Hu & Jiaohao Chen
Last Modifed Date: Nov 19th, 2021
Functiona: 
	-The Entrance of the programand allow 
	-Prompt user to do operation
*/

int count;
int count_backorder;

//Main Entrance of the entire program
//Check the required record file is exist or not
//Prompt the user to conduct operations for read || write
int main(int argc, char* argv[]) {	
	chead chrec;
	unsigned day, month, year;
	long dateencode;
	count = 0; // terminated number of orders
	count_backorder = 0;
	/*
	-Input the data file to program
	-Convert the files to binary mode
	-Store those converted files
	*/

	initialCust(&customer);
	initialSup(&supplier);
	initialProd(&product);
	if (argc > 1)
		InputFile(argc, argv, cfile, sfile, pfile, tfile, sales);
	
	/*if (!recordcheck(&cfile, &sfile, &pfile, &sales)) {
		printf("Please Check the Record File\n");
		getchar();
		return -1;
	}
	*/
	char* file[INDEX];
	unsigned int index = 0;
	//Check if the customer file can be open
	if (!OPENFILECHECK(CUSTFILE, cfile)) {
		file[index] = CUSTFILE;
		index++;
	}
	/*Check the supplier file can be open*/
	if (!OPENFILECHECK(SUPFILE, sfile)) {
		file[index] = SUPFILE;
		index++;
	}
	/*Check the product file can be open*/
	if (!OPENFILECHECK(PRODFILE, pfile)) {
		file[index] = PRODFILE;
		index++;
	}
	//check if the sale file can be open
	if (!OPENFILECHECK(SALEFILE, sales)) {
		file[index] = SALEFILE;
		index++;
	}
	fopen_s(&payduefile, PayDueFILE, _access(PayDueFILE, 0)<0?"w+" :"r+");
	/* Display the missing file name, if file is not been opened*/
	if (index != 0) {
		printf("Missing the following Record file:\n\n");
		while (index--) {
			printf("->%s\n\n", file[index]);
		}
		return -1;
	}
	
	//Prompt the user to enter the date
	printf("Please Enter the Date Today (DD MM YY Ex: 1 1 2077): \n");
	scanf("%u %u %u", &day, &month, &year);
	(void)getchar();
	//Get the returned encode value
	dateencode = EncodeDate(day, month, year);
	//If the dateencode if invalid (The enter date is wrong)
	//Close the function
	if (dateencode < 0) {
		return-1;
	}
	printf("All of the record has loaded\n");
	/*
	-Repeat the process of making decision
	-Through the chocies to achieve add, display or makesale process
	-Until user finished all requirements, press'#' to stop
	*/

	//Record the date and orders number
	fseek(cfile, 0, SEEK_SET);
	fread(&chrec, sizeof(chead), 1, cfile);
	//First time open program, Initialize data
	if(chrec.encodedate == 0)
	{
		chrec.encodedate = dateencode;
	}
	//Open program in the same day
	else if(chrec.encodedate == dateencode)
	{
		count = chrec.ordernum; //Took record of orders number 
		count_backorder = chrec.backordernum; //Took record of backorder number
	}

	do {
		printf("You have been placed %d orders at %u,%u,%u\n", count, day, month, year);
		printf("You have been placed %d backorders\n", count_backorder);
		printf("Please read the following Instruction,\n\
--------------------------------------------\n");
/*		printf("Add New Record for Customer, please enter 1\n\
Add New Record for Supplier, please enter 2 \n\
Add New Record for Product, please enter 3 \n\
--------------------------------------------\n\
Display Record for Customer, please enter 4\n\
Display Record for Supplier, please enter 5\n\
Display Record for Product, please enter 6\n\
Display Record for Sales List,please enter 7 \n\
--------------------------------------------\n\
Make Sales, please enter 8 \n\
Stop the program please enter '#'\n\
--------------------------------------------\n");
*/
		printf("Add New Record, Please Enter 1\n\
Update Record, Please Enter 2\n\
Delete Record, Please Enter 3\n\
Read Record Please Enter 4\n\
5-Make Sale\n\
6-PayDueCheck\n\
7-Cancel\n\
8-Display PayDue\n\
9-Display Sales");
		printf("Please Enter your option: ");
		scanf("%c", &choice);
		(void)getchar();//Input the option number
		switch (choice) {
		case '1':

			//Function Call: Add Customer
			AddRecUI(cfile, sfile, pfile);
			//close customer record

			break;
		case '2':
			//Fucntion Call: Add Supplier
			UpdateRecUI(cfile, sfile, pfile, bkfile);
			//close supplier file
			break;
		case '3':
			//Function Call: Add Product
			DelRecUI(cfile, sfile, pfile);
			//close product record
			break;
		case '4':
			//Function Call: Display Customer
			ReadRecUI(cfile, sfile, pfile);
			break;
		case'5':
			MakeSales(cfile, pfile, sales, bkfile, dateencode);
			break;
		case '6':
			PayDueCheck(payduefile, sales, dateencode);
			break;
		case '7':
			CancelCustomerOrders(sales, pfile);
			break;
		case '8':
			DisplayPaydue(payduefile);
			break;
		case '9':
			DisplaySale(sales);
			break;
		case '#':
			break;
		default:
			printf("Invalid Selection\n");
			(void)getchar();
			break;
		}
		printf("\n");
		//when operationcode is # stop the loop
	} while (choice != '#');

	//Terminated how many orders was placed on today
	fseek(cfile, 0, SEEK_SET);
	fread(&chrec, sizeof(chead), 1, cfile);
	chrec.ordernum = count;
	chrec.backordernum = count_backorder;
	fseek(cfile, 0, SEEK_SET);
	fwrite(&chrec, sizeof(chead), 1, cfile);

	//Close all the open files
	fclose(cfile);
	fclose(sfile);
	fclose(pfile);
	fclose(sales);
	//Pause the system
	(void)getchar();
	//Close the system
	return;
}