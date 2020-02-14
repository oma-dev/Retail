#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>



using namespace std;


struct prod {  //structure to hold our products' data. all of them are strings except quantity, in order to be able to increase the quantity.
        string InvoiceNo;
        string StockCode;
        string Description;
        int Quantity;
        string InvoiceDate;
        string UnitPrice;
        string CustomerID;
        string Country;
    };


class Node  {  //standard node implementation, with holding product (structure) data

public:

    Node* next;
    struct prod data;
    };

class LinkedList {

public:
    int length;
    Node* head;

    LinkedList();

    void add(struct prod data);


}    ;


LinkedList::LinkedList() {
    this->length = 0;
    this->head = NULL;


}


void LinkedList::add(struct prod data){
    Node* node = new Node();
    node->data = data;
    node->next = this->head;
    this->head = node;
    this->length++;
}




class Hash
{
    int BUCKET;
    LinkedList *table;

public:
    Hash(int b);  // Constructor

    struct prod filler;

    void sortAndPrint(int hm);

    struct prod* findItem(const char*key);


    void insertItem(const char * key, struct prod urun);




    void deleteItem(const char * key);


    int hashFunction(const char * key) {  //similar logic to hashing algorithms used in password hashing, except it's a two sided function
        int genPrime = 401;
        int a;

        while(*key != '\0') {
            genPrime = ((genPrime << 4) + (int)(*key)) % BUCKET;
            key++;
        }


        return genPrime;
    }


};

Hash::Hash(int b)
{
    this->BUCKET = b;
    this->filler.Country = "Banana Republic";
    this->filler.Quantity = 0;




    table = new LinkedList[BUCKET];

}

void Hash::insertItem(const char * key, struct prod urun)
{
    int index = hashFunction(key);
    table[index].add(urun);
}

void Hash::sortAndPrint(int hm) {

     cout << left << setw(40) << setfill(' ') << "Product (StockCode)" << left << setw(40) << setfill(' ') << "Description" << left << setw(40) << setfill(' ') << "#TotalQuantity" << endl;

    struct prod *max = &(this->filler);
    for(int syc = 0; syc < hm; syc++) {

        for(int xyc = 0; xyc < this->BUCKET; xyc++) {

            Node* current = table[xyc].head;
        struct prod* pointer;

        while (current != NULL)
        {
            if (current->data.Quantity > (*(max)).Quantity) {
                max = &(current->data);

            }
            current = current->next;
        }


        }

        cout   << left << setw(2) << syc + 1 << "-  " << left << setw(30) << setfill(' ') << (*(max)).StockCode << left << setw(50) << setfill(' ') << (*(max)).Description << left << setw(40) << setfill(' ') << (*(max)).Quantity << endl;
        (*(max)).Quantity = 0;

    }

}



struct prod* Hash::findItem(const char*key) {

        int i = hashFunction(key);

        Node* current = table[i].head;
        struct prod* pointer;

        while (current != NULL)
        {
            if (current->data.StockCode == key) {
                pointer = &(current->data);
                return pointer;
            }
            current = current->next;
        }


        pointer = &(this->filler);
        return pointer;


    }


int main()
{

   ifstream ip("OnlineRetail.csv");




    const int SIZE = 600000;
    static struct prod myArr[SIZE];

    string tc1, tc2, tc3, tc4, tc5, tc6, tc7, tc8;

    ip.ignore(256, '\n'); //ignores the first line

    clock_t begin = clock();

    for(int s = 0; ip.good(); s++) {

        struct prod temp;

        getline(ip, tc1, ';');
        getline(ip, tc2, ';');
        getline(ip, tc3, ';');
        getline(ip, tc4, ';'); //q
        getline(ip, tc5, ';');
        getline(ip, tc6, ';');
        getline(ip, tc7, ';');
        getline(ip, tc8, '\n');


        stringstream g3(tc4); //typecasting from string to int


        temp.InvoiceNo = tc1;
        temp.StockCode = tc2;
        temp.Description = tc3;
        g3 >> temp.Quantity  ;
        temp.InvoiceDate = tc5;
        temp.UnitPrice = tc6;
        temp.CustomerID = tc7;
        temp.Country = tc8;

        myArr[s] = temp;


     }

     int nsize = sizeof(myArr)/sizeof(myArr[0]);

     Hash h(50000);

     for (int x = 0; x < nsize; x++) {



        struct prod *tempo = h.findItem((myArr[x].StockCode).c_str());

         if((*tempo).Country == "Banana Republic") {
                h.insertItem((myArr[x].StockCode).c_str(), myArr[x]);
        } else {
            (*tempo).Quantity+= myArr[x].Quantity;
       }



     }

     h.sortAndPrint(10);





    clock_t end = clock();
    double elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
    cout << "\nTotal Elapsed Time: " << elapsed_time << " seconds";




    return 0;
}

























