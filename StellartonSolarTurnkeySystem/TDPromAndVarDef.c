#include"SSSTurnkeySys.h"

FILE* cfile;
FILE* sfile;
FILE* pfile;
FILE* tfile;
FILE* sales;
FILE* invoice;
FILE* taxfile;
FILE* payduefile;
FILE* bkfile;
CREC customer;
SREC supplier;
PREC product;
BKREC backorder;
unsigned long filledordernum;
unsigned long filledbackordernum;
unsigned long ordernum;
char choice;

char* CustFieldPtr[MAXCUSTFIELD];
int CustFieldSize[MAXCUSTFIELD] = { NameLen, NameLen, Addrlen, NameLen, NameLen, NameLen, NumLen };
char CustFieldType[MAXCUSTFIELD] = {CharType, CharType, AddressType, AddressType, AddressType, AddressType, CharType};

char* SupFieldPtr[MAXSUPFIELD];
int SupFieldSize[MAXSUPFIELD] = { NameLen, NameLen, NameLen, Addrlen, NumLen, Addrlen };

char* ProdFieldPtr[MAXPRODFIELD];
int ProdFieldSize[MAXPRODFIELD] = {NameLen, NameLen, NameLen, intsize, NameLen, intsize, intsize };
char ProdFiledType[MAXPRODFIELD] = { CharType, CharType, CharType, MoneyType, CharType, IntType, ReorderType };

char* AddCustProm[MAXCUSTFIELD] = 
{ "Enter First and Last Name: ", \
"Enter Bussiness Name: ",\
"Enter Street Name: ",\
"Enter Town Name: ",\
"Enter Province: ",\
"Enter Postal Code: ",\
"Enter Phone Number: " };

char* AddSupProm[MAXSUPFIELD] = 
{"Enter Manufacture: ",\
"Enter Contact: ", \
"Enter Company: ", \
"Enter Address: ",\
"Enter Phone Number: ",\
"Enter Email: "};

char* AddProdProm[MAXPRODFIELD] = 
{ "Enter Product Name: ",\
"Enter Classification: ",\
"Enter Manufacture: ",\
"Enter Unit Cost: ",\
"Enter Manufacture Code: ",\
"Enter Stock: ", \
"Enter Reorder Level: " };