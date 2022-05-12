#include"SSSTurnkeySys.h"

void OrdersCheck(FILE* pfile, FILE*tfile) {
	int ProdID = 0;
	int nextProdID = 0;
	if (fopen_s(&tfile, ORDERFILE, _access(ORDERFILE, 0) < 0 ? "r+" : "w+") < 0) {
		printf("Cannot Access the File-> %s\n", ORDERFILE);
		(void)getchar();
		return;
	}

	fseek(pfile, 0, SEEK_SET);
	fread(&product, sizeof(PREC), 1, pfile);
	nextProdID = product.phrec.pnextid;
	while (ProdID < nextProdID) {
		fseek(pfile, ProdID*sizeof(PREC), SEEK_SET);
		fread(&product, sizeof(PREC), 1, pfile);

		if (product.prec.stock >= product.prec.reorderlevel) {
			continue;
		}
		fprintf(tfile, "%u\n%s\n", product.prec.pid, product.prec.Productname);

		ProdID++;
	}
	fclose(tfile);
}