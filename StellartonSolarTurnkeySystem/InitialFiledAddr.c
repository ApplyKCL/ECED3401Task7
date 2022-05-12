#include"SSSTurnkeySys.h"

void initialCust(CREC* Customer) {
	CustFieldPtr[0] = (char*)&Customer->crec.cname;
	CustFieldPtr[1] = (char*)&Customer->crec.bname;
	CustFieldPtr[2] = (char*)&Customer->crec.strname;
	CustFieldPtr[3] = (char*)&Customer->crec.town;
	CustFieldPtr[4] = (char*)&Customer->crec.province;
	CustFieldPtr[5] = (char*)&Customer->crec.ptcode;
	CustFieldPtr[6] = (char*)&Customer->crec.phonenum;

}

void initialSup(SREC* Supplier) {
	SupFieldPtr[0] = (char*)&Supplier->srec.Manufacturer;
	SupFieldPtr[1] = (char*)&Supplier->srec.Contact;
	SupFieldPtr[2] = (char*)&Supplier->srec.Company;
	SupFieldPtr[3] = (char*)&Supplier->srec.Addr;
	SupFieldPtr[4] = (char*)&Supplier->srec.phonenum;
	SupFieldPtr[5] = (char*)&Supplier->srec.email;
}

void initialProd(PREC* Product) {
	ProdFieldPtr[0] = (char*)&Product->prec.Productname;
	ProdFieldPtr[1] = (char*)&Product->prec.Classification;
	ProdFieldPtr[2] = (char*)&Product->prec.Manufacturer;
	ProdFieldPtr[3] = (char*)&Product->prec.Unitcost;
	ProdFieldPtr[4] = (char*)&Product->prec.ManuCode;
	ProdFieldPtr[5] = (char*)&Product->prec.stock;
	ProdFieldPtr[6] = (char*)&Product->prec.reorderlevel;
}