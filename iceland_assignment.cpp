/*
	ICELAND : Stationery Store Management System
	
	Member 1 :	Chan Lin Chee				1191202546
	Member 2 :	Irdina Binti Ahmad Hilmi	1191200368
	Member 3 :	Nur Irdina Binti Hassan		1191202351
	Member 4 :	Yong Jing Ping				1191202279
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Product {
	string pID, productName, category, brand;
	float price;
	int stockNum;
	Product *next;
};

void menu();
string byCategory();
Product* initProduct(string buff);
Product* readData(Product *head);
void printProductList(Product *curr, string cat);
Product* addProduct(Product *curr);
Product* sortProduct(Product *head);
Product* searchProduct(Product *head, string pid);
Product* editProduct(Product *head);
Product* deleteProduct(Product *head);
void saveData(Product *head);

/* Chan Lin Chee */
int main()
{
	int option;
	string category;

	// built set
	Product *head = initProduct("|");
	Product *tail = initProduct("|");
	head->next = tail;
	head = readData(head);		// get data from text file
	head = sortProduct(head);	// sort the product to prevent if the data in text file is not in order
	
	do {
		menu();
		cin>>option;
		while(cin.fail() || option<0 || option>5) {	
			cout<<"Invalid option! Please re-enter : ";
			cin.clear();
			cin.ignore(256,'\n');
			cin>>option;
		}
		system("cls");
		cin.ignore();
		
		switch(option) {
			case 1 :	cout<<"\n :: Add New Product ::\n\n";
						head = addProduct(head);
						head = sortProduct(head);
						cout<<" ::[ Newest Product List ]::\n\n";
						printProductList(head->next, "");	cout<<endl;
						break;

			case 2 :	head = editProduct(head);
						break;

			case 3 :	head = deleteProduct(head);
						break;
						
			case 4 :	cout<<"\n :: View Product List ::\n\n";
						if(head->next->pID != "") 	// check if the list is empty
						{
							category = byCategory();
							system("cls");
							printProductList(head->next, category);
						} 
						else
							cout<<" There is no product in the list.\n\n\n";
						break;

			case 5 :	if(head->next->pID != "") 	// check if the list is empty
						{
							string pid;
							cout<<"\n -[ Search by Product ID ]- "
								<<"\n Please enter a product ID :  ";
							cin>>pid;
							pid.resize(5,' ');
							transform(pid.begin(), pid.end(), pid.begin(), ::toupper);
							Product* result = searchProduct(head, pid);
							if(result != NULL) {
								cout<<"\n >> ID : \t"<<result->pID<<endl
									<<"    Product : \t"<<result->productName<<endl
									<<"    Category :  "<<result->category<<endl
									<<"    Brand : \t"<<result->brand<<endl
									<<"    Price : \tRM "<<setprecision(2)<<result->price<<endl
									<<"    Stock : \t"<<result->stockNum<<endl<<endl<<endl;
							} else {
								cout<<"\n :: There is no product with this product ID :: \n\n";
							}
						}
						else
							cout<<"\n :: There is no product in the list :: \n\n";
						break;
		}
	} while(option != 0);
	saveData(head);
	cout<<"\n        HAVE A NICE DAY ! :D\n";
	return 0;
}

void menu()
{
	cout<<"-----------------------------------------------------------------\n"
		<<"-\t\tICELAND STATIONERY MANAGEMENT SYSTEM\t\t-\n"
		<<"-----------------------------------------------------------------\n"
		<<" [1] Add New Product\n"
		<<" [2] Edit Product Details\n"
		<<" [3] Delete Product\n"
		<<" [4] View Product List\n"
		<<" [5] Search by Product ID\n"
		<<" [0] Save Data & Quit\n"
		<<" Please enter your choice >> ";
}

string byCategory()
{
	int cat;
	string catName;
	cout<<" [1] ALL Categories\n"
		<<" [2] Calculator\n"
		<<" [3] Eraser/Ruler/Corrector\n"
		<<" [4] File\n"
		<<" [5] Paper/Book\n"
		<<" [6] Writing Instrument\n"
		<<" [0] Others\n"
		<<" Select Category >> ";
	cin>>cat;
	while(cin.fail() || cat<0 || cat>6) {	
		cout<<"Invalid option! Please re-enter : ";
		cin.clear();
		cin.ignore(256,'\n');
		cin>>cat;
	}
	switch(cat) {
		case 1 :	catName = "All";	break;
		case 2 :	catName = "Calculator";	break;
		case 3 :	catName = "Eraser/Ruler/Corrector";	break;
		case 4 :	catName = "File";	break;
		case 5 :	catName = "Paper/Book";	break;
		case 6 :	catName = "WritingInstrument";	break;
		case 0 :	catName = "Others";	break;
	}
	return catName;
}

/* Chan Lin Chee */
Product* initProduct(string buff)
{
	Product *temp = new Product;	
	stringstream ss(buff);
	string pNum, sNum;
	getline(ss, temp->pID, '|');
	getline(ss, temp->productName, '|');
	getline(ss, temp->category, '|');
	getline(ss, temp->brand, '|');
	
	getline(ss, pNum, '|');
	stringstream converted_P(pNum);
	converted_P >> temp->price;
	
	getline(ss, sNum, '|');
	stringstream converted_S(sNum);
	converted_S >> temp->stockNum;
	
	temp->next = NULL;
	return temp;
}

/*Irdina binti Ahmad Hilmi*/
Product* readData(Product *node)
{
	string temp;
	Product *head = node;
	Product *current;
	
	ifstream readfile("productList.txt");
	if(readfile.is_open()) {
		while(getline(readfile, temp)) {
			current = initProduct(temp);
			current->next = node->next;
			node->next = current;
			node = current;
		}
	}
	// If the file is not found, the program will automatically create it when the admin saves the data
	readfile.close();	
	return head;
}

/*Irdina binti Ahmad Hilmi*/
void saveData(Product *head) 
{
	Product *temp = head->next;		// first node is head
	ofstream saveData;
	saveData.open("productList.txt");
	while( (temp != NULL) && (temp->pID != "") ) {
		stringstream ss1, ss2;
		string price, stock;
		ss1<<fixed<<setprecision(2)<<temp->price;		
		ss1>>price;		
		price.resize(10,' ');
		
		ss2<<temp->stockNum;
		ss2>>stock;
		
		saveData << temp->pID << "|" << temp->productName << "|" << temp->category << "|" << temp->brand << "|" 
				 << price << "|" << stock << endl;
		temp = temp->next;
	}
	saveData.close();
	cout<<"\n [Data is saved in 'productList.txt']";
}

/* Nur Irdina Binti Hassan */
void printProductList(Product *curr, string cat)
{
	int count = 0;
	if(cat == "All") {
		cout<<"\n ::[ Full Product List ]::\n\n"
		<<" | \t\t Product Name\t\t\t      | Product ID | \t       Category \t     |             Brand              | Price (RM) |  Stock \n"
		<<"--------------------------------------------------------------------------------"
		<<"-----------------------------------------------------------------------------\n";
	} else if(cat != ""){
		cout<<"\n ::[ "<<cat<<" ]::\n\n"
		<<" | \t\t Product Name\t\t\t      | Product ID |             Brand              | Price (RM) |  Stock \n"
		<<"--------------------------------------------------------------------------------------------------------------------------\n";
	}
	while(curr && (curr->pID != "") ) {
		string str = curr->category;
		str.erase(remove(str.begin(),str.end(),' '),str.end());
		
		if(cat == "") {
			cout<<" "<<curr->pID<<"  "<<curr->productName<<endl;
			count++;
		}
		else {
			if(cat == "All") { 
				cout<<" | "<<curr->productName<<" |   "<<curr->pID<<"    |  "<<curr->category<<" | "<<curr->brand
					<<" | "<<setw(10)<<left<<fixed<<setprecision(2)<<curr->price<<" | "<<curr->stockNum<<endl;
				count++;
			}
			if(str == cat) {
				cout<<" | "<<curr->productName<<" |   "<<curr->pID<<"    | "<<curr->brand
					<<" | "<<setw(10)<<left<<fixed<<setprecision(2)<<curr->price<<" | "<<curr->stockNum<<endl;
				count++;
			}
		}
		curr = curr->next;
	}
	if(count == 0) {
		cout<<" There is no product in the list.\n\n\n";
	} else {
		cout<<"\n [ Total : "<<count<<" product(s). ]\n\n\n";
	}
}

/* Chan Lin Chee */
Product* addProduct(Product *curr)
{
	Product *newPro;
	Product *head = curr;
	int catOpt, s, number;
	float p;
	string pid, name, category, brand, price, stock, message;
	
	cout<<" How many products you want to add? >> ";
	cin>>number;
	
	if(cin.fail() || number<=0) {
		system("cls");	
		return head;
	}
	
	for(int i=1; i<=number; i++) {
		stringstream ss1, ss2;
		cin.ignore();
		cout<<"\n Product Name >> ";			getline(cin, name);					name.resize(50,' ');
		cout<<" Product ID >> ";				cin>>pid;							pid.resize(5,' ');
		cout<<"  [1] Calculator\n"<<"  [2] Eraser/Ruler/Corrector\n"<<"  [3] File\n"
			<<"  [4] Paper/Book\n"<<"  [5] Writing Instrument\n"<<"  [6] Others\n"
			<<" Product Category >> ";			cin>>catOpt;						cin.ignore();
		cout<<" Product Brand >> ";				getline(cin, brand);				brand.resize(30,' ');
		cout<<" Product Price >> RM ";			cin>>p;		ss1<<fixed<<setprecision(2)<<p;		ss1>>price;		price.resize(10,' ');
		cout<<" Stock Availability >> ";		cin>>s;		ss2<<s;	ss2>>stock;
		
		switch(catOpt) {
			case 1 :	category = "Calculator";	break;
			case 2 :	category = "Eraser/Ruler/Corrector";	break;
			case 3 :	category = "File";	break;
			case 4 :	category = "Paper/Book";	break;
			case 5 :	category = "Writing Instrument";	break;
			case 6 :	category = "Others";	break;
			default :	category = "Others";	break;
		}
		category.resize(30,' ');
		transform(pid.begin(), pid.end(), pid.begin(), ::toupper);
		string buff = pid + "|" + name + "|" + category + "|" + brand + "|" + price + "|" + stock;
		newPro = initProduct(buff);
		
		// insert new product if its pID does not exist
		while( (curr->next->pID != newPro->pID) && (curr->next->pID != "") ) {
			curr = curr->next;
		}
		if(curr->next->pID != newPro->pID) {
			newPro->next = curr->next;
			curr->next = newPro;
		} 
		else if(curr->next->pID == newPro->pID) {
			message += "\n ! Product ID : " + newPro->pID + "\n   Old Product : " + curr->next->productName + "\n   Replaced with : " + newPro->productName + "\n";
			newPro->next = curr->next->next;
			curr->next->next = NULL;
			curr->next = newPro;
		}
		curr = head;
	}
	system("cls");
	cout<<message<<endl;
	return head;
}

/* Chan Lin Chee */
Product* sortProduct(Product *head) 
{
	// sort product list by product name (case sensitive) , not product ID
	Product *sorted = initProduct("|");
	Product *tail = initProduct("|");
	sorted->next = tail;
	Product *curr = head->next;		// first node is head
	head->next = NULL;
	Product *currNext;
	while(curr->pID != "") {		// check node is not a tail
		currNext = curr->next;
		if( (sorted->next->pID == "") || (sorted->next->productName >= curr->productName) ) {
			curr->next = sorted->next;
			sorted->next = curr;
		} 
		else {
			Product *temp = sorted;
			while( (temp->next->pID != "") && (temp->next->productName) < curr->productName) {
				temp = temp->next;
			}
			curr->next = temp->next;
			temp->next = curr;
		}
		curr = currNext;
	}
	return sorted;
}

// YONG JING PING
Product *searchProduct(Product *head, string pid)
{
	// sequential search
	Product *curr = head->next;		// first node is head
	while(curr && (curr->pID != "")) {
		if(curr->pID == pid) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

// YONG JING PING
Product* editProduct(Product *head)
{
	Product *curr;
	string pid, name, category, brand;
	char cont;
	int catOpt, stock;
	float price;
	
	do {
		curr = head->next;
		cout<<"\n :: Edit Product Details ::\n\n";
		printProductList(head->next, "");
		
		if(head->next->pID != "") 		// check if the list is empty
		{
			cout<<" Please enter the product ID to edit its details >> ";
			cin>>pid;
			cin.ignore();
			pid.resize(5, ' ');
			transform(pid.begin(), pid.end(), pid.begin(), ::toupper);
			
			while(curr && (curr->pID != "")) {
				if(curr->pID == pid) {
					break;
				}
				curr = curr->next;
			}
			
			if( (curr->pID == "") || !curr ) {
				cout<<" !! No matching data found. !! \n";
			} else {
				cout<<"\n * Product ID >> "<<curr->pID;
				cout<<"\n   Product Name >> ";				getline(cin, name);					name.resize(50,' ');
				cout<<"    [1] Calculator\n"<<"    [2] Eraser/Ruler/Corrector\n"<<"    [3] File\n"
					<<"    [4] Paper/Book\n"<<"    [5] Writing Instrument\n"<<"    [6] Others\n"
					<<"   Product Category >> ";			cin>>catOpt;						cin.ignore();
				cout<<"   Product Brand >> ";				getline(cin, brand);				brand.resize(30,' ');
				cout<<"   Product Price >> RM ";			cin>>price;
				cout<<"   Stock Availability >> ";			cin>>stock;
				
				switch(catOpt) {
					case 1 :	category = "Calculator";	break;
					case 2 :	category = "Eraser/Ruler/Corrector";	break;
					case 3 :	category = "File";	break;
					case 4 :	category = "Paper/Book";	break;
					case 5 :	category = "Writing Instrument";	break;
					case 6 :	category = "Others";	break;
					default :	category = "Others";	break;
				}
				category.resize(30,' ');
				transform(pid.begin(), pid.end(), pid.begin(), ::toupper);
				curr->productName = name;
				curr->category = category;
				curr->brand = brand;
				curr->price = price;
				curr->stockNum = stock;
			}
			cout<<"\n Do you wish to edit another product ? [Y-yes] >> ";
			cin>>cont;
			cout<<endl;
			head = sortProduct(head);
			system("cls");
		} else {
			return head;
		}	
	} while( cont == 'Y' || cont == 'y' );
	return head;
}

/* Nur Irdina Binti Hassan */
Product* deleteProduct(Product *curr)
{
	Product* head = curr;
	string pid;
	char cont, confirm;
	int found = 0;
	
	do {
		cout<<"\n :: Delete Product ::\n\n";
		printProductList(head->next, "");
		
		if(head->next->pID != "") 		// check if the list is empty
		{
			cout<<" Please enter the product ID >> ";
			cin>>pid;
			pid.resize(5, ' ');
			transform(pid.begin(), pid.end(), pid.begin(), ::toupper);
			
			while( (curr->next != NULL) && (curr->next->pID != "")) {
				if(curr->next->pID == pid) {
					cin.ignore();
					cout<<"\n Product ID : "<<curr->next->pID
						<<"\n Product Name : "<<curr->next->productName
						<<"\n **Confirm to delete ? [Y-yes] >> ";
					cin>>confirm;
					if( confirm == 'Y' || confirm == 'y' ) {
						Product *temp = curr->next;
						curr->next = temp->next;
						temp->next = NULL;
						delete temp;	// free memory
					}
					found++;
					break;
				}
				curr = curr->next;
			}
			
			if(found==0) {		// when product not found
				cout<<" !! No matching data found. !! \n";
			}
			cout<<"\n Do you wish to delete another product ? [Y-yes] >> ";
			cin>>cont;
			curr = head;
			system("cls");
		} else {
			return head;
		}
	} while( cont == 'Y' || cont == 'y' );
	return head;
}
