/*
Author: Shaonan Hu & Jiahao Chen
Last Modified Date: Nov 19th, 2021
Function:
    -Make Sales
    -Update the Sale Record when sales are made
*/
#include "SSSTurnkeySys.h"

int count;

enum TempOrderStatus { UNFILD, FIELD };
void MakeSales(FILE* cfile, FILE* pfile, FILE* sales,FILE*bkfile, unsigned long encodedate)
{
    /*
    -Making the "makesale" file
    -Record the information included:
        -Customer name
        -Customer phone number
        -Product name
        -Manufacture code of product
        -Price of each unit
        -Total amount
        -Account balance after customer paid
        -Sale ID
    -Write into the "makesale" file
    */
    
    unsigned saleid = 0;
    long custcid = 0;
    long prodid = 0;
    int numtopurchase = 0;
    unsigned productidx = 0;
    long pnextid;
    
    int sum = 0;
    int untcost = 0;
    int idx = 0;
    char inrec[NumLen];
    char* payment;
    chead chrec;
    phead phrec;
    MSREC salelist;
    mshead mshrec;
    enum TempOrderStatus TOStatus;
    
    //Put the file pointer to the position 0
    fseek(sales, 0, SEEK_SET);
    //read the record at this file pointer
    fread(&mshrec, sizeof(mshead), 1, sales);
    printf("Next Sales ID is: %u\n", mshrec.slnextid);
    fseek(cfile, 0, SEEK_SET);
    fread(&chrec, sizeof(chead), 1, cfile);
    fseek(pfile, 0, SEEK_SET);
    fread(&phrec, sizeof(phead), 1, pfile);
    saleid = mshrec.slnextid;
    pnextid = phrec.pnextid;
    printf("Enter Customer ID: ");
    scanf("%d", &custcid);
    (void)getchar();

    if (custcid >= chrec.cnextid) {
        printf("Customer ID: %u\nDoes not Exist\n", custcid);
        return;
    }
    //Check the customer ID is exist
    //Move the file pointer to the assigned position
    fseek(cfile, (custcid - IDconstant) * sizeof(CREC), SEEK_SET);
   
    //Read the record in current position
    fread(&customer, sizeof(CREC), 1, cfile);
    //Connect the sale record with customer ID
    salelist.salerec.custid = custcid;
    salelist.salerec.saleid = saleid;
    //store the encoded date to the field
    salelist.salerec.encodedate = encodedate;
    //Copy the customer record to sale struct
    strcpy(salelist.salerec.custname, customer.crec.cname);
    strcpy(salelist.salerec.phonenumber, customer.crec.phonenum);
    
    
    salelist.salerec.totalcost = 0;
    do {
        TOStatus = FIELD;
        //Prompt User to enter the product ID
        printf("Enter the product ID: ");
        scanf("%d", &prodid);
        (void)getchar();
        fseek(pfile, 0, SEEK_SET);
        fread(&product, prodid*sizeof(phead), 1, pfile);
        
        //Check the product ID is exist
        //Move the file pointer to the assigned position
        if (prodid>=phrec.pnextid) {
            printf("Product ID Do not exist\n");
            printf("If you want to order it as a perticular product press '2' (Information of the product will be required)\n\
If you do not, and you have another product you want to purchase press '1'\n\
If you do not have any products to purchase press any other key to exist");
            scanf("%c", &choice);
            (void)getchar();
            switch (choice) {
            case'2':
                prodid = phrec.pnextid;
                AddProd(pfile);
                printf("The Product ID you provided has been reassgined to a new ID, which is %ld\n\
Please use the this new product ID if you have further request\n", prodid);
                break;
            default:
                continue;
            }
            
        }
        fseek(pfile, prodid * sizeof(PREC), SEEK_SET);
        //read the record at the assigned position
        fread(&product, sizeof(PREC), 1, pfile);
        //prompt the user to enter 
        printf("How many products you want to buy: \n");
        scanf("%d", &numtopurchase);
        (void)getchar();
        
        //Check the required number of the produt
        //Compare it with stock
        //Higher than stock, sale all of the product, update stock to 0
        //lower than stock, sale the required number, update stock
        salelist.salerec.numofpurchase[productidx] = numtopurchase;
        salelist.salerec.lacknumopurchase[productidx] = 0;
        if (numtopurchase > product.prec.stock) {
            salelist.salerec.lacknumopurchase[productidx]=numtopurchase-product.prec.stock;
            TOStatus = UNFILD;
        }
        //update the stock
        product.prec.stock = product.prec.stock - (salelist.salerec.numofpurchase[productidx]\
            - salelist.salerec.lacknumopurchase[productidx]);

        //check the stock level and update the stock status

        salelist.salerec.prodid[productidx] = prodid;
        strcpy(salelist.salerec.prodname[productidx], product.prec.Productname);
        strcpy(salelist.salerec.manucode[productidx], product.prec.ManuCode);
        salelist.salerec.unitcost[productidx] = product.prec.Unitcost;
        //Calculate the total amount and account balance
        //Store these records into the "makesale" file
        salelist.salerec.totalcost += salelist.salerec.numofpurchase[productidx] * product.prec.Unitcost * (100+COSTTAXRate)/100;
        
        //Move the file pointer to the desired position
        fseek(pfile, prodid * sizeof(PREC), SEEK_SET);
        //write to the record
        fwrite(&product, sizeof(PREC), 1, pfile);
        //increment to the next product the customer what to buy
        if (TOStatus == UNFILD)
            Createbackorder(bkfile, salelist, productidx);
        //prompt the user to choice if they still have another product they want to buy
        printf("Do you have other product want to buy? ('Yes for '1' or 'NO for any other key):\n");
        scanf("%c", &choice);
        (void)getchar();
        productidx++;
    } while (choice == '1');
    //check if there is no product is purchasd
    if (productidx == 0) {
        (void)getchar();
        return;
    }
    //unpdate the index
    salelist.salerec.index = productidx;

    //display the total cost and prompt the user to pay the bill
    printf("Total amount is: $%d.%02d\n", salelist.salerec.totalcost / 100, salelist.salerec.totalcost % 100);
    printf("Please Enter the Payment: ");
    //read the input from keyboard
    fgets(inrec, NumLen, stdin);
    payment = strtok(inrec, "\n");
    salelist.salerec.payment = 0;
    //change it to integer payment
    MONEY(salelist.salerec.payment, *payment, payment);

    //calculate the balance that own
    salelist.salerec.balance = salelist.salerec.totalcost - salelist.salerec.payment;
    if (salelist.salerec.balance == 0) {
        salelist.salerec.PAYMENTSTATUS = Paid;
    }
    else if(salelist.salerec.balance<0){
        salelist.salerec.PAYMENTSTATUS = Paid;
        printf("Over Paid, Reuturn Change:\n$%d.%02d\n", \
            abs(salelist.salerec.balance)/100, abs(salelist.salerec.balance)%100);
        salelist.salerec.balance = 0;
    }
    else {
        salelist.salerec.PAYMENTSTATUS = Unpaid;
    }
    
    //if (TOStatus == UNFIELD)
    //   Createbackorder(bkfile, pfile, salelist);
    //move the file pointer to the desired position
    fseek(sales, saleid * sizeof(MSREC), SEEK_SET);
    //write to the record
    fwrite(&salelist, sizeof(MSREC), 1, sales);
    //increment the current saleid to the next sale id
    mshrec.slnextid = saleid + 1;
    //move the file pointer to the 0 position
    fseek(sales, 0, SEEK_SET);
    //write the header to the data
    fwrite(&mshrec, sizeof(mshead), 1, sales);
    printf("\n/*The Sale has Made*/\n");
    count++; //Order been placed
}