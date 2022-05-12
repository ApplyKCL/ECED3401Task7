#pragma once
/*Program File: task6.h
* Author: Shaonan Hu & Jiaohao Chen
* Last Modified Date: Nov 19th, 2021
* Function: 
*	Header file that defines
*	The variable, struct, Macro,
*	libary... used in the program
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<io.h>


#define True 1
#define False 0
#define NUL '\0'
#define INDEX 8
#define NumLen 16
#define NameLen 32
#define Addrlen 64
#define MAX_REC 256
#define COSTTAXRate 15
#define INTERESTRATE 1.5
#define RevenueTaxRate 15
#define GainTaxRate 20
#define STARTYR 1990 //base on the provided file
#define MAXDAYYR 366
#define LOWSTOCK 5
#define IDconstant 999
#define StartCSID 1000
#define MAXCUSTFIELD 7
#define MAXSUPFIELD 6
#define MAXPRODFIELD 7
#define MAXITEM 16
#define CharType 'C'
#define AddressType 'A'
#define MoneyType 'M'
#define IntType 'I'
#define ReorderType 'R'
#define CustPhnumField 4
#define CustAddrFiled 2
#define intsize sizeof(int)



//Define the file name
#define CUSTFILE "Customer.dat"
#define SUPFILE "Supplier.dat"
#define PRODFILE "Product.dat"
#define SALEFILE "Sales.dat"
#define ORDERFILE "ORDERS.dat"
#define PayDueFILE "PAY-DUE.dat"
//#define INVOICEFILE "Invoice.dat"
//#define TAXFILE "Tax.dat"

#define LEAPYEAR(year) ((year)%400==0)||((year)%100!=0&&(year)%4==0)
//Macro Defination for remove the Line Feed
#define TRUNCATE(name) name[strlen(name)-1]='\0'
//Macro Defination for determine the file can be open or not return 1 or 0 
#define OPENFILECHECK(filename, filepointer) fopen_s(&filepointer, filename, "r+")==0
//Macro Defination for open the file
#define WRITEFILE(filename, filepointer) fopen_s(&filepointer, filename, "w+")
//Repeat using getchar, pre-process it
//Repeet using close file function

#define ALPHACHECK(str) (str >= 'A' && str <= 'Z') || (str >= 'a' && str <= 'z')
//Macro Function Defination, for convert the string money to integer money
//return the value of money in integer for 100 times higher
#define MONEY(money, str, position) while (str) {\
if (ALPHACHECK(str)) break;\
if ((str == '$') || (str == '.')||(str==',')) { position++;}\
money = (money * 10 )+ (str - '0');\
position++;}

//Macro Function Defination, for convert the string stock amount to integer
#define STOCK(stock, str, position) while (str){\
if (ALPHACHECK(str)) break;\
stock = (stock * 10) + (str - '0');\
position++;}

//State defination for the Curremt Payment Status.
enum paymentstatus { Unpaid, Paid };
enum RecStatus{Active, Deleted};
enum paymentduestatus { Overdue, Not_Overdue };
enum OrderStatus{Canceled, Not_Canceled};
enum BackOrderStatus { Unfilled, Filled };

//Struct Defination
//Customer Struct
struct CUSTOMER {
	long cid;
	char cname[NameLen];
	char bname[NameLen];
	char strname[Addrlen];
	char town[NameLen];
	char province[NameLen];
	char ptcode[NameLen];
	char phonenum[NumLen];
	enum RecStatus CustStatus;
	long nextDelCustID;
	
};
typedef struct CUSTOMER cust;


//Supplier Struct
struct SUPPLIER {
	long sid;
	char Manufacturer[NameLen];
	char Contact[NameLen];
	char Company[NameLen];
	char Addr[Addrlen];
	char phonenum[NumLen];
	char email[Addrlen];
	enum RecStatus SupStatus;
	long nextDelSupID;
};
typedef struct SUPPLIER sup;


//Product Struct
struct PRODUCT {
	long pid;
	char Productname[NameLen];
	char Classification[NameLen];
	char Manufacturer[NameLen];
	int Unitcost;
	char ManuCode[NameLen];
	int stock;
	int reorderlevel;
	long fistbkID;
	long newbkID;
	enum RecStatus ProdStatus;
	long nextDelProdID;
	//long lackingamount;
};
typedef struct PRODUCT prod;



//Sale Struct
struct SALEINFO {
	
	char custname[NameLen];
	char phonenumber[NameLen];
	char prodname[MAXITEM][NameLen];
	char manucode[MAXITEM][NameLen];
	int unitcost[MAXITEM];
	int numofpurchase[MAXITEM];
	int lacknumopurchase[MAXITEM];
	int totalcost;
	int payment;
	int balance;
	long saleid;
	long custid;
	long prodid[NameLen];
	int index;
	unsigned long encodedate;
	enum paymentstatus PAYMENTSTATUS;
	enum OrderStatus ORDERSTATUS;
};
typedef struct SALEINFO sale;

//Sales Header Struct
struct MSHEADER {
	long slnextid;
	
};
typedef struct MSHEADER mshead;

//Union the Sales Header struct and Sale Struct
union MAKESALE {
	sale salerec;
	mshead mshrec;
};
typedef union MAKESALE MSREC;

//Customer Header Struct
struct CHEADER {
	long cnextid;
	long DelCustList;
	long encodedate;
	int ordernum;
	int backordernum;
};
typedef struct CHEADER chead;

//Supplier Header Struct
struct SHEADER {
	long snextid;
	long DelSupList;
};
typedef struct SHEADER shead;


//Product Header Struct
struct PHEADER {
	long pnextid;
	long DelProdList;
};
typedef struct PHEADER phead;

//Union the Customer Header Struct and Customer Struct
union CRECFILE{
	cust crec;
	chead chrec;
};
typedef union CRECFILE CREC;

//Union Supplier Header Struct and Supplier Header
union SRECFILE {
	sup srec;
	shead shrec;
};
typedef union SRECFILE SREC;

//Union Product Header Struct and Product Struct
union PRECFILE {
	prod prec;
	phead phrec;
};
typedef union PRECFILE PREC;

struct PAYMENTDUE {
	unsigned long encodedate;
	char cusname[NameLen];
	long cusid;
	char phonenum[NameLen];
	int balance;
	enum paymentstatus PAYMENTSTATUS;
};
typedef struct PAYMENTDUE PD;

struct PDHEADER {
	long payduenextid;
};
typedef struct PDHEADER pdhead;

union PAYMENTDUEREC {
	PD paydue;
	pdhead pdhrec;
};
typedef union PAYMENTDUEREC PDREC;

//BackOrder Structures
struct BACKORDER {
	long backorderid;
	long custid;
	char cust[NameLen];
	char productname[NameLen];
	long prodid;
	long nextbkID;
	int requierdquality;
	//unsigned int item;
	unsigned long encodedate;
	enum BackOrderStatus BkStatus;
};
typedef struct BACKORDER bo;

struct BACKORDERHEADER {
	long backorder_nextid;
};
typedef struct BACKORDERHEADER bkhead;

union BACKORDERREC {
	bo bkrec;
	bkhead bkheader;
};
typedef union BACKORDERREC BKREC;

//Eable the Other file to access the file opinter & Functions
extern FILE* cfile;
extern FILE* sfile;
extern FILE* pfile;
extern FILE* tfile;
extern FILE* sales;
extern FILE* invoice;
extern FILE* taxfile;
extern FILE* Paydue;
extern FILE* bkfile;
extern FILE* payduefile;
extern CREC customer;
extern SREC supplier;
extern PREC product;
extern BKREC backorder;
extern int count;  // Count how many orders been placed
extern int count_backorder; // Count how many backorders been placed
extern char choice;
extern unsigned long filledordernum;
extern unsigned long filledbackordernum;
extern unsigned long ordernum;
extern char* CustFieldPtr[MAXCUSTFIELD];
extern int CustFieldSize[MAXCUSTFIELD];
extern char CustFieldType[MAXCUSTFIELD];
extern char* SupFieldPtr[MAXSUPFIELD];
extern int SupFieldSize[MAXSUPFIELD];
extern char* ProdFieldPtr[MAXPRODFIELD];
extern int ProdFieldSize[MAXPRODFIELD];
extern char ProdFiledType[MAXPRODFIELD];
extern char* AddCustProm[MAXCUSTFIELD];
extern char* AddSupProm[MAXSUPFIELD];
extern char* AddProdProm[MAXPRODFIELD];
//Enable to access Initialization Function
extern void InitCust(FILE*);
extern void InitSup(FILE*);
extern void InitProd(FILE*);
extern void InitSale(FILE*);


//Eanbale to access Input file function
extern void InputFile(int, char*argv[], FILE*, FILE*, FILE*, FILE*, FILE*);
//extern int recordcheck(FILE*, FILE*, FILE*, FILE*);

//Eanble to access TEXT FILE Conversion Function
extern void CovCustFile(FILE*, FILE*);
extern void CovSupFile(FILE*, FILE*);
extern void CovProdFile(FILE*, FILE*);

//Enable to access add new record Function
extern void AddCust(FILE*);
extern void AddSup(FILE*);
extern void AddProd(FILE*);

//Eable to Update Record
extern void UpdateCust(FILE*);
extern void UpdateSup(FILE*);
extern void UpdateProd(FILE*, FILE*);

//Enable to delete record
extern void DelCust(FILE*);
extern void DelSup(FILE*);
extern void DelProd(FILE*);

//Enable to access file reading Function
extern void DisplayCust(FILE*);
extern void DisplaySup(FILE*);
extern void DisplayProd(FILE*);
extern void DisplaySale(FILE*);
extern void DisplayPaydue(FILE*);
//Eable to access the record by enter the ID
extern void IdAccessCust(FILE*);
extern void IdAccessSup(FILE*);
extern void IdAccessProd(FILE*);

//Enable to access the makesale function
extern void MakeSales(FILE*, FILE*, FILE*,FILE*, unsigned long);

//Enable to access the encodedata and decodedata function
extern long EncodeDate(unsigned, unsigned, unsigned);
extern void DecodeDate(unsigned long, unsigned*, unsigned*, unsigned*);

//User Interface
extern void AddRecUI(FILE*, FILE*, FILE*);
extern void UpdateRecUI(FILE*, FILE*, FILE*);
extern void DelRecUI(FILE*, FILE*, FILE*);
extern void ReadRecUI(FILE*, FILE*, FILE*);

//For PayDue Function
extern void InitPaydue(FILE*);
extern void PayDueCheck(FILE*, FILE*, unsigned long);
extern void CancelCustomerOrders(FILE*, FILE*);
extern void DisplayPaydue(FILE*);

//Back Order Function
extern void Createbackorder(FILE*, MSREC, int);
extern void InitBackorder(FILE*);
extern void FillBackUpOrder(PREC, FILE*);

//Table Driven
extern void initialCust(CREC*);
extern void initialSup(SREC*);
extern void initialProd(PREC*);

extern void convfiletabledrivencust(FILE*, FILE*);
extern void convfieldtabledrivensup(FILE*, FILE*);
extern void convfieldtabledrivenprod(FILE*, FILE*);