#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define ADMIN "admin"
#define PASSWORD "1234"
#define MAX_CART 100

struct Product
{
    int id;
    char name[50];
    float price;
    int stock;

    struct Product *next;
};

struct Product *head=NULL;


struct Customer
{
    int customerID;
    char customerName[50];
    char customerType[20];
    int priority;

    struct Customer *next;
};

struct Customer *front=NULL;
struct Customer *rear=NULL;
char currentCustomer[50]= "";
char currentCustomerType[20];
int currentCustomerID;


struct Cart
{
    int productID;
    char productName[50];
    float price;
    int quantity;
};

struct Cart cart[MAX_CART];

int cartSize=0;

struct Stack
{
    struct Cart item;
    struct Stack *next;
};

struct Stack *top=NULL;

void title();
void login();
void mainMenu();
void setcolor(int color);
void clearScreen();
void welcome();
void loading();

void addProduct();
void displayProducts();
void searchProduct();
void updateProduct();
void deleteProduct();


void addCustomer();
void serveCustomer();
void displayQueue();


void shoppingCart();
void viewcart();

void push(struct Cart item);
struct Cart pop();
void removeLastItem();
void undoRemove();


void generateBill();
int getCustomerName(int customerID,char customerName[]);
void saveSales(char customerName[],float total,float discount,float netAmount);
int isRegularCustomer(int customerID);
void lowStockReport();
void inventorySummary();
void saveProducts();
void loadProducts();
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen()
{
    system("cls");
}

void loading()
{
    int i;

    clearScreen();

    setColor(14);

    printf("\n\n\n");

    printf("\tSMART SUPERMARKET BILLING SYSTEM\n\n");

    printf("\tLoading... ");

    setColor(10);

    for(i=0;i<25;i++)
    {
        printf("%c",219);
        Sleep(80);
    }

    Sleep(500);
}

void welcome()
{
    clearScreen();

    setColor(11);

    printf("\n");
    printf("=====================================================\n");
    printf("      SMART SUPERMARKET BILLING SYSTEM\n");
    printf("=====================================================\n");

    setColor(10);

    printf("\nData Structure Project");

    setColor(15);

    printf("\n\nPress Any Key To Continue...");
    getch();
}

void title()
{
	setColor(11);
    printf("\n");
    printf("=====================================================\n");
    setColor(14);
    printf("      SMART SUPERMARKET BILLING SYSTEM\n");
    setColor(11);
    printf("=====================================================\n");
    time_t t;
    t=time(NULL);
    printf("Date & Time : %s",ctime(&t));
    setColor(15);
}

void login()
{
    char user[20];
    char pass[20];

    clearScreen();

    setColor(11);

    printf("\n");
    printf("============================================================\n");
    printf("                  ADMIN LOGIN PANEL\n");
    printf("============================================================\n");

    setColor(14);

    printf("\nUsername : ");
    scanf("%s", user);

    printf("Password : ");
    scanf("%s", pass);

    if(strcmp(user, ADMIN)==0 && strcmp(pass, PASSWORD)==0)
    {
        setColor(10);
        printf("\n\nLogin Successful!\n");
        Sleep(1000);
    }
    else
    {
        setColor(12);
        printf("\n\nInvalid Username or Password!\n");
        getch();
        exit(0);
    }

    setColor(15);
}

void mainMenu()
{
    int choice;

    while(1)
    {
        clearScreen();
		title();
		setColor(11);
		printf("\n=====================================================\n");
		setColor(14);
		printf("                  MAIN MENU\n");
		setColor(11);
		printf("=====================================================\n");
        
		setColor(10);
        printf("\n1. Add Product");
        printf("\n2. Display Products");
        printf("\n3. Search Product");
        printf("\n4. Update Product");
        printf("\n5. Delete Product");
        setColor(13);
        printf("\n6. Add Customer");
        printf("\n7. Serve Customer");
        printf("\n8. Display Customer Queue");
        printf("\n9. Shopping Cart");
        printf("\n10. View Shopping Cart");  
        setColor(9);
        printf("\n11. Remove Last Cart Item");        
		printf("\n12. Undo Remove");
        printf("\n13. Generate Bill");
        setColor(11);
        printf("\n14. Low Stock Report");
		printf("\n15. Inventory Summary");
		setColor(12);
        printf("\n16. Exit");
        setColor(15);
        printf("\n\nEnter Choice : ");

        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                addCustomer();
                break;

            case 7:
                serveCustomer();
                break;

            case 8:
                displayQueue();
                break;

            case 9:
                shoppingCart();
                break;
                
            case 10:
            	viewcart();
            	break;
            	
			case 11:
				removeLastItem();
				break;

			case 12:
			    undoRemove();
			    break;
			    
            case 13:
                generateBill();
                break;
			case 14:
			    lowStockReport();
			    break;
			case 15:
			    inventorySummary();
			    break;
            case 16:
				clearScreen();
    			setColor(10);
    			printf("\n\n");
    			printf("*******************************************************\n");
    			printf("*                                                     *\n");
    			printf("*          THANK YOU FOR USING OUR SYSTEM             *\n");
   	 			printf("*                                                     *\n");
    			printf("*        SMART SUPERMARKET BILLING SYSTEM             *\n");
    			printf("*                                                     *\n");
    			printf("*******************************************************\n");
    			setColor(15);
    			getch();
    			exit(0);
            default:
                printf("\nInvalid Choice");
        }

        printf("\n");
        system("pause");
        system("cls");
    }

}

void addProduct()
{
    struct Product *newNode, *temp;
    newNode = (struct Product *)malloc(sizeof(struct Product));
    if(newNode == NULL)
    {
        printf("\nMemory Allocation Failed!\n");
        return;
    }

    printf("\nEnter Product ID : ");
    scanf("%d",&newNode->id);

    printf("Enter Product Name : ");
    scanf(" %[^\n]",newNode->name);

    printf("Enter Product Price : ");
    scanf("%f",&newNode->price);

    printf("Enter Product Stock : ");
    scanf("%d",&newNode->stock);

    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
    
	setColor(10);
    printf("\nProduct Added Successfully!\n");
    setColor(15);
    saveProducts();
}

void displayProducts()
{
    struct Product *temp = head;
    if(head == NULL)
    {
        printf("\nNo Products Available.\n");
        return;
    }

    setColor(11);
	printf("\n===============================================================================\n");
	printf("| %-6s | %-25s | %-10s | %-10s |\n","ID","PRODUCT","PRICE","STOCK");
	printf("===============================================================================\n");
	setColor(15);

	while(temp!=NULL)
	{
	    printf("| %-6d | %-25s | %-10.2f | %-10d |\n",temp->id,temp->name,temp->price,temp->stock);
    	temp=temp->next;
	}

	setColor(11);
	printf("===============================================================================\n");
	setColor(15);
}

void searchProduct()
{
    int id;
    struct Product *temp = head;
    printf("\nEnter Product ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("\nProduct Found\n");

            printf("\nID : %d",temp->id);
            printf("\nName : %s",temp->name);
            printf("\nPrice : %.2f",temp->price);
            printf("\nStock : %d\n",temp->stock);

            return;
        }

        temp = temp->next;
    }
	
	setColor(12);
    printf("\nProduct Not Found.\n");
    setColor(15);
}

void updateProduct()
{
    int id;
    struct Product *temp = head;
    printf("\nEnter Product ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            int choice,stock;
            
            printf("\n1. Replace Stock");
            printf("\n2. Add new Stock");
            printf("\Enter Choice: ");
            scanf("%d",&choice);
            
            if(choice==1)
            {
            	printf("Enter New Name : ");
            	scanf(" %[^\n]",temp->name);

            	printf("Enter New Price : ");
           		scanf("%f",&temp->price);
           		
            	printf("Enter New Stock: ");
            	scanf("%d",&temp->stock);
			}
			else if(choice==2)
			{
				printf("Enter Stock To Add: ");
				scanf("%d",&stock);
				temp->stock += stock;
			}

            printf("\nProduct Updated Successfully!\n");
            saveProducts();

            return;
        }

        temp = temp->next;
    }

    printf("\nProduct Not Found.\n");
}

void deleteProduct()
{
    int id;
    struct Product *temp = head;
    struct Product *prev = NULL;
    printf("\nEnter Product ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            if(prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            printf("\nProduct Deleted Successfully!\n");
            saveProducts();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("\nProduct Not Found.\n");
}

void addCustomer()
{
    struct Customer *newNode;
    newNode = (struct Customer *)malloc(sizeof(struct Customer));

    if(newNode == NULL)
    {
        printf("\nMemory Allocation Failed!\n");
        return;
    }
    printf("\nEnter Customer ID : ");
    scanf("%d", &newNode->customerID);
    if(getCustomerName(newNode->customerID,newNode->customerName))
    {
    	printf("\nWelcome Back!\n");
    	printf("Customer Name : %s\n",newNode->customerName);
	}
	else
	{
		printf("Enter Customer Name: ");
		scanf(" %[^\n]",newNode->customerName);
	}
	
    if(isRegularCustomer(newNode->customerID))
    {
    	strcpy(newNode->customerType,"Regular");
    	newNode->priority=1;
    	printf("\nRegular Customer Detected!\n");
	}
	else
	{
		strcpy(newNode->customerType,"Normal");
		newNode->priority=2;
		printf("\nNew Customer.\n");
	}
	
    newNode->next = NULL;

    if(front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\nCustomer Added to Billing Queue Successfully!\n");
}

void serveCustomer()
{
    struct Customer *temp;

    if(front == NULL)
    {
        printf("\nNo Customers in Queue!\n");
        return;
    }
    temp = front;

    printf("\nNow Serving Customer\n");
    printf("---------------------------\n");
    printf("Customer ID   : %d\n", temp->customerID);
    printf("Customer Name : %s\n", temp->customerName);
    strcpy(currentCustomer,temp->customerName);
    currentCustomerID=temp->customerID;
    if(isRegularCustomer(currentCustomerID))
    {
    	strcpy(currentCustomerType,"Regular");
    	printf("Customer Type: Regular\n");
	}
	else
	{
		strcpy(currentCustomerType,"Normal");
		printf("Customer Type: Normal\n");
	}
	
    printf("---------------------------\n");

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }
    free(temp);
    printf("\nCustomer Removed from Queue.\n");
}

void displayQueue()
{
    struct Customer *temp = front;

    if(front == NULL)
    {
        printf("\nQueue is Empty!\n");
        return;
    }
    printf("\n=========== CUSTOMER QUEUE ===========\n");
    printf("%-10s %-25s\n", "ID", "NAME");
    printf("--------------------------------------\n");

    while(temp != NULL)
    {
        printf("%-10d %-25s\n",temp->customerID,temp->customerName);
        temp = temp->next;
    }
    printf("--------------------------------------\n");
}

void shoppingCart()
{
    int id, qty;
    struct Product *temp;

    if(cartSize >= MAX_CART)
    {
        printf("\nCart is Full!\n");
        return;
    }

    displayProducts();
    printf("\nEnter Product ID : ");
    scanf("%d",&id);

    temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Enter Quantity : ");
            scanf("%d",&qty);

            if(qty > temp->stock)
            {
                printf("\nOnly %d Items Available!\n",temp->stock);
                return;
            }

            cart[cartSize].productID = temp->id;
            strcpy(cart[cartSize].productName,temp->name);
            cart[cartSize].price = temp->price;
            cart[cartSize].quantity = qty;
            cartSize++;
            printf("\nItem Added Successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nProduct Not Found!\n");
}

void viewcart()
{
    int i;
    if(cartSize == 0)
    {
        printf("\nShopping Cart is Empty!\n");
        return;
    }
    printf("\n=============== SHOPPING CART ===============\n");
    printf("%-8s %-20s %-10s %-10s %-10s\n","ID","NAME","PRICE","QTY","TOTAL");
    
    for(i=0;i<cartSize;i++)
    {
        printf("%-8d %-20s %-10.2f %-10d %-10.2f\n",cart[i].productID,cart[i].productName,cart[i].price,cart[i].quantity,cart[i].price*cart[i].quantity);
    }
}

void generateBill()
{
    int i;
    float total = 0;
    float discount = 0;
    float netAmount;

    struct Product *temp;
    if(cartSize == 0)
    {
        printf("\nShopping Cart is Empty!\n");
        return;
    }
    
    clearScreen();
	setColor(14);
	printf("\n==============================================================\n");
	printf("               SMART SUPERMARKET BILL\n");
	printf("==============================================================\n");
	setColor(11);
	printf("\nCustomer Name : %s\n", currentCustomer);

	time_t t;
	t = time(NULL);
	printf("Date & Time   : %s", ctime(&t));
	printf("--------------------------------------------------------------\n");
	printf("%-20s %-8s %-8s %-10s\n","Product","Price","Qty","Amount");
	printf("--------------------------------------------------------------\n");
	setColor(15);

    for(i=0;i<cartSize;i++)
    {
        float amount;
        amount = cart[i].price * cart[i].quantity;
        total += amount;
        printf("%-20s %-8.2f %-8d %-10.2f\n",cart[i].productName,cart[i].price,cart[i].quantity,amount);

        temp = head;

        while(temp != NULL)
        {
            if(temp->id == cart[i].productID)
            {
                temp->stock -= cart[i].quantity;
                break;
            }

            temp = temp->next;
        }
    }

    if(total >= 1000)
        discount = total * 0.10;

    else if(total >= 500)
        discount = total * 0.05;
    if(strcmp(currentCustomerType,"Regular")==0)
    {
    	printf("\nRegular Customer Bonus Discount (5%%) Applied!\n");
    	discount +=total*0.05;
	}

    netAmount = total - discount;
	
	setColor(11);
	printf("--------------------------------------------------------------\n");
	setColor(10);
	printf("\nTotal Amount : %.2f", total);
	printf("\nDiscount     : %.2f", discount);
	printf("\nNet Amount   : %.2f", netAmount);
	setColor(14);
	
	saveSales(currentCustomer,total,discount,netAmount);
	
	printf("\n\n==============================================================\n");
	printf("           THANK YOU FOR SHOPPING WITH US\n");
	printf("==============================================================\n");
	setColor(15);
    cartSize = 0;
}

void saveProducts()
{
    FILE *fp;
    struct Product *temp = head;
    fp = fopen("products.txt","w");
    if(fp==NULL)
    {
        printf("\nCannot Open File!\n");
        return;
    }

    while(temp!=NULL)
    {
        fprintf(fp,"%d\n",temp->id);
        fprintf(fp,"%s\n",temp->name);
        fprintf(fp,"%f\n",temp->price);
        fprintf(fp,"%d\n",temp->stock);

        temp=temp->next;
    }

    fclose(fp);
    printf("\nProducts Saved Successfully.\n");
}

void loadProducts()
{
    FILE *fp;
    struct Product *newNode,*temp;
    fp=fopen("products.txt","r");
    if(fp==NULL)
    {
        printf("\nNo Saved File Found.\n");
        return;
    }
    head=NULL;
    while(1)
    {
        newNode=(struct Product*)malloc(sizeof(struct Product));
        if(fscanf(fp,"%d",&newNode->id)!=1)
        {
            free(newNode);
            break;
        }
        fgetc(fp);
        fgets(newNode->name,50,fp);
        newNode->name[strcspn(newNode->name,"\n")]=0;
        fscanf(fp,"%f",&newNode->price);
        fscanf(fp,"%d",&newNode->stock);
        newNode->next=NULL;
        if(head==NULL)
        {
            head=newNode;
        }
        else
        {
            temp=head;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=newNode;
        }
    }
    fclose(fp);
}

void saveSales(char customerName[],float total,float discount,float netAmount)
{
    FILE *fp;
    time_t t;
    t=time(NULL);
    fp=fopen("sales.txt","a");
    if(fp==NULL)
        return;

    fprintf(fp,"\n=============================\n");
    fprintf(fp,"%s",ctime(&t));
    fprintf(fp,"Customer ID : %d\n",currentCustomerID);
    fprintf(fp,"Customer Name : %s\n",customerName);
    fprintf(fp,"Total : %.2f\n",total);
    fprintf(fp,"Discount : %.2f\n",discount);
    fprintf(fp,"Net Amount : %.2f\n",netAmount);
    fprintf(fp,"=============================\n");
    fclose(fp);
}
int isRegularCustomer(int customerID)
{
	FILE *fp;
	char line[200];
	int id;
	fp=fopen("sales.txt","r");
	if(fp==NULL)
		return 0;
	while(fgets(line,sizeof(line),fp))
	{
		if(sscanf(line,"Customer ID : %d",&id)==1)
		{
			if(id==customerID)
			{
				fclose(fp);
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

void lowStockReport()
{
    struct Product *temp=head;
    printf("\nLow Stock Products\n\n");
    while(temp!=NULL)
    {
        if(temp->stock<=5)
        {
            printf("%d\t%s\t%d\n",temp->id,temp->name,temp->stock);
        }
        temp=temp->next;
    }
}

void inventorySummary()
{
    struct Product *temp=head;
    int totalProducts=0;
    float totalValue=0;
    while(temp!=NULL)
    {
        totalProducts++;
        totalValue+=temp->price*temp->stock;
        temp=temp->next;
    }
    printf("\n========== INVENTORY SUMMARY ==========\n");
    printf("\nTotal Products : %d",totalProducts);
    printf("\nInventory Value : %.2f",totalValue);
    printf("\n=======================================\n");
}

void push(struct Cart item)
{
    struct Stack *newNode;
    newNode = (struct Stack *)malloc(sizeof(struct Stack));

    if(newNode == NULL)
    {
        printf("\nStack Overflow!\n");
        return;
    }

    newNode->item = item;
    newNode->next = top;
    top = newNode;
}

struct Cart pop()
{
    struct Cart item;
    struct Stack *temp;

    if(top == NULL)
    {
        item.productID = -1;
        return item;
    }

    temp = top;
    item = temp->item;
    top = top->next;
    free(temp);
    return item;
}

void removeLastItem()
{
    if(cartSize == 0)
    {
        printf("\nShopping Cart is Empty!\n");
        return;
    }
    push(cart[cartSize - 1]);
    cartSize--;
    printf("\nLast Item Removed Successfully!\n");
}

void undoRemove()
{
    struct Cart item;
    item = pop();

    if(item.productID == -1)
    {
        printf("\nNothing to Undo!\n");
        return;
    }
    cart[cartSize] = item;
    cartSize++;
    printf("\nUndo Successful!\n");
}
int getCustomerName(int customerID, char customerName[])
{
    FILE *fp;
    char line[200];
    int id;
    char name[50];

    fp = fopen("sales.txt", "r");

    if(fp == NULL)
        return 0;

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line, "Customer ID : %d", &id) == 1)
        {
            if(fgets(line, sizeof(line), fp))
            {
                if(sscanf(line, "Customer Name : %[^\n]", name) == 1)
                {
                    if(id == customerID)
                    {
                        strcpy(customerName, name);
                        fclose(fp);
                        return 1;
                    }
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
int main()
{
	welcome();
	
	loading();
	
    title();

    login();
    
    loadProducts();
    
    mainMenu();

    return 0;
}
