#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mainMenu();
void addProduct();
void viewProducts();
void saveProducts();
void loadProducts();
void updateProducts();
void searchProducts();
void deleteProducts();
void sellProducts();
void stockManagement();
void salesReport();

/* Product Structure */
struct product
{
    int id;
    char category[30];
    char size[20];
    float price;
    int quantity;
};

struct product products[100];
int totalProducts = 0;

int main()
{
    loadProducts();
    mainMenu();
    return 0;
}

void mainMenu()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("\n");
        printf("==============================================\n");
        printf("           FASHION SHOP MANAGEMENT\n");
        printf("==============================================\n");

        printf("1. Add Product\n");
        printf("2. View Total Item\n");
        printf("3. Update Product\n");
        printf("4. Search Item\n");
        printf("5. Delete Item\n");
        printf("6. Sell Product\n");
        printf("7. Stock Management\n");
        printf("8. Sales Report\n");
        printf("0. Exit\n");

        printf("\n----------------------------------------------\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
        case 1:
            addProduct();
            break;

        case 2:
            viewProducts();
            break;

        case 3:
            updateProducts();
            break;

        case 4:
            searchProducts();
            break;

        case 5:
            deleteProducts();
            break;


        case 6:
           sellProducts();
            break;

        case 7:
        stockManagement();
        break;

        case 8:
        salesReport();
        break;

        case 0:
        printf("\nThank You For Using Our Software!\n");
        exit(0);

        default:
            printf("\nInvalid Choice! Please Try Again.\n");
        }

        printf("\nPress Enter to Continue...");
        getchar();
        getchar();
    }
}

/* Add Product */
void addProduct()
{
    if(totalProducts >= 100)
    {
    printf("\nProduct Storage Full!\n");
    return;
    }
    int choice;

    system("cls");

    printf("==========================================\n");
    printf("            ADD PRODUCT\n");
    printf("==========================================\n");

    printf("1. T-Shirt\n");
    printf("2. Pants\n");
    printf("3. Shirt\n");
    printf("4. Jacket\n");
    printf("0. Back to Main Menu\n");

    printf("\nEnter Choice        : ");
    scanf("%d", &choice);

    if(choice == 0){
        return;
    }

    switch(choice)
    {
    case 1:
        strcpy(products[totalProducts].category, "T-Shirt");
        break;

    case 2:
        strcpy(products[totalProducts].category, "Pants");
        break;

    case 3:
        strcpy(products[totalProducts].category, "Shirt");
        break;

    case 4:
        strcpy(products[totalProducts].category, "Jacket");
        break;

    default:
        printf("\nInvalid Choice!\n");
        return;
    }

    products[totalProducts].id = totalProducts +1;
    printf("Product ID          : %d", products[totalProducts].id);


    printf("\nSize (S/M/L/XL/XXL) : ");
    scanf("%s", products[totalProducts].size);

    printf("Unit Price          : ");
    scanf("%f", &products[totalProducts].price);

    printf("Product Quantity    : ");
    scanf("%d", &products[totalProducts].quantity);

    totalProducts++;

    saveProducts();

    printf("\nProduct Added Successfully!\n");
}


/*save product start*/
void saveProducts()
{
    FILE *fp = fopen("products.txt", "w");

    if(fp == NULL)
    {
        printf("\nFile Opening Error!\n");
        return;
    }

    for(int i = 0; i < totalProducts; i++)
    {
        fprintf(fp, "%d %s %s %.2f %d\n",
                products[i].id,
                products[i].category,
                products[i].size,
                products[i].price,
                products[i].quantity);
    }

    fclose(fp);

    printf("\nProduct Data Saved Successfully!\n");
}
/* lode product*/
void loadProducts()
{
    FILE *fp = fopen("products.txt", "r");

    if(fp == NULL)
    {
        totalProducts = 0;
        return;
    }

    totalProducts = 0;

    while(totalProducts < 100 &&
          fscanf(fp, "%d %29s %19s %f %d",
                 &products[totalProducts].id,
                 products[totalProducts].category,
                 products[totalProducts].size,
                 &products[totalProducts].price,
                 &products[totalProducts].quantity) == 5)
    {
        totalProducts++;
    }

    fclose(fp);
}

/* View Products */
void viewProducts()
{
    int i;

    system("cls");

    if(totalProducts == 0)
    {
        printf("\n==========================================\n");
        printf("      No Product Available!\n");
        printf("==========================================\n");
        return;
    }

    printf("\n=============== PRODUCT LIST ===============\n");
    printf("--------------------------------------------\n");
    printf("ID\tCategory\tSize\tPrice\tQuantity\n");
    printf("--------------------------------------------\n");

    for(i = 0; i < totalProducts; i++)
    {
       printf("%d\t%-10s\t%-5s\t%.2f\t%d\n",
       products[i].id,
       products[i].category,
       products[i].size,
       products[i].price,
       products[i].quantity);
    }

    printf("--------------------------------------------\n");
    printf("Total Products : %d\n", totalProducts);
    printf("--------------------------------------------\n");
}
//view products end

//Update products start
void updateProducts()
{
    int id, choice;
    int found = 0;

    system("cls");

    printf("\n========== UPDATE PRODUCT ==========\n");
    printf("Press 0 Back to the Main Menu \n");
    printf("Enter Product ID: ");
    scanf("%d", &id);

    if(id == 0){
        return;
    }

    for(int i = 0; i < totalProducts; i++)
    {
        if(products[i].id == id)
        {
            found = 1;

            printf("\nProduct Found!\n");
            printf("------------------------------------\n");
            printf("Product ID : %d\n", products[i].id);
            printf("Category   : %s\n", products[i].category);
            printf("Size       : %s\n", products[i].size);
            printf("Price      : %.2f\n", products[i].price);
            printf("Quantity   : %d\n", products[i].quantity);

            printf("\nWhat do you want to update?\n");
            printf("1. Category\n");
            printf("2. Size\n");
            printf("3. Price\n");
            printf("4. Quantity\n");
            printf("5. Update All\n");
            printf("Enter Choice: ");
            scanf("%d", &choice);
            switch(choice)
            {
                case 1:
                    printf("Enter New Category (T-Shirt/Pants/Shirt/Jacket): ");
                    scanf("%29s", products[i].category);
                    break;

                case 2:
                    printf("Enter New Size: ");
                    scanf("%19s", products[i].size);
                    break;

                case 3:
                    printf("Enter New Price: ");
                    scanf("%f", &products[i].price);
                    break;

                case 4:
                    printf("Enter New Quantity: ");
                    scanf("%d", &products[i].quantity);
                    break;

                case 5:
                    printf("Enter New Category: ");
                    scanf("%29s", products[i].category);

                    printf("Enter New Size: ");
                    scanf("%19s", products[i].size);

                    printf("Enter New Price: ");
                    scanf("%f", &products[i].price);

                    printf("Enter New Quantity: ");
                    scanf("%d", &products[i].quantity);
                    break;

                default:
                    printf("\nInvalid Choice!\n");
                    return;
            }

            saveProducts();

            printf("\nProduct Updated Successfully!\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct Not Found!\n");
    }

    printf("\nPress Enter to Continue...");
    getchar();
}
/*Update section end*/
/*Search section start*/
void searchProducts(){
    char idInput[20];
    char category[30];
    int id, i, found = 0;
    system("cls");

    printf("==============================================\n");
    printf("                SEARCH PRODUCT\n");
    printf("==============================================\n");

    printf("\nEnter ID or Category or Both.");

    printf("\nEnter product ID:");

    fgets(idInput, sizeof(idInput), stdin);
    idInput[strcspn(idInput, "\n")] = '\0';

    printf("\nEnter Category:");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0';

    if(strlen(idInput)== 0 && strlen(category)==0){
        printf("\nPlease enter ID or Category!");
        return;
    }

    if(strlen(idInput) > 0){
        id = atoi(idInput);
    }

    for(i = 0; i < totalProducts; i++){
        int idMatch = 1;
        int categoryMatch = 1;


        if(strlen(idInput) > 0){
            if(products[i].id != id){

            idMatch = 0;
        }
    }

    if(strlen(category) > 0){
        if(strcmp(products[i].category, category) != 0){
            categoryMatch = 0;
        }
    }

    if(idMatch && categoryMatch){
        found = 1;

        printf("==============================================\n");
        printf("                 PRODUCT FOUND\n");
        printf("==============================================\n");

        printf("ID       : %d\n", products[i].id);
        printf("Category : %s\n", products[i].category);
        printf("Size     : %s\n", products[i].size);
        printf("Price    : %2.f\n", products[i].price);

        printf("==============================================\n");
    }
}

if(!found){

    printf("\nProduct not found\n");
}
    printf("\nPress Enter to continue....");
    getchar();
}
/* Product search end */
/* Product delete start */

void deleteProducts(){
    int id, i, found =0;
    char confirm;

    system("cls");

    printf("==============================================\n");
    printf("                DELETE PRODUCT\n");
    printf("==============================================\n");

    printf("Press 0 Back to the Main Menu \n");
    printf("Enter Product ID:");
    scanf("%d", &id);

    if( id == 0){
        return;
    }

    for(i = 0; i < totalProducts; i++){
        if(products[i].id == id){
            found = 1;

            printf("\nProduct Found\n");
            printf("ID         :%d\n", products[i].id);
            printf("Category   :%s\n", products[i].category);
            printf("Size       :%s\n", products[i].size);
            printf("Price      :%.2f\n", products[i].price);

            printf("\nAre you suer you want to delete this product?(Y/N):");
            scanf(" %c", &confirm);

            if(confirm == 'Y' || confirm == 'y'){

            for(int j = i; j < totalProducts - 1; j++){

                products[j] = products[j + 1];

            }

            totalProducts--;
            saveProducts();

            printf("\nProduct deleted successfully!\n");


        }else{
            printf("\nDelete cancelld!\n");
        }
        break;
        }
    }
    if(!found){
        printf("\nProduct not found!\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
/*Sell product start*/
    void sellProducts() {
    int searchId, sellQty;
    int found = 0;
    float total;

    printf("==============================================\n");
    printf("                SELL PRODUCT\n");
    printf("==============================================\n");

    printf("Press 0 Back to the Main Menu \n");
    printf("Enter Product ID: ");
    scanf("%d", &searchId);
    if( searchId == 0){
        return;
    }

   for (int i = 0; i < totalProducts; i++) {

        if (products[i].id == searchId) {

            found = 1;

            printf("\nProduct Found!\n");
            printf("----------------------------\n");

            printf("Product ID : %d\n", products[i].id);
            printf("Category   : %s\n", products[i].category);
            printf("Size       : %s\n", products[i].size);
            printf("Price      : %.2f\n", products[i].price);
            printf("Stock      : %d\n", products[i].quantity);

            printf("Press 0 Back to the Main Manu \n");
            printf("\nEnter Selling Quantity: ");
            scanf("%d", &sellQty);

            if (sellQty <= 0) {
                printf("\nInvalid Quantity!\n");
            }
            else if (sellQty > products[i].quantity) {
                printf("\nSorry! Insufficient Stock.\n");
            }
            else {

                total = products[i].price * sellQty;

                // Get current date
            time_t now = time(NULL);
            struct tm *t = localtime(&now);

            char date[11];

            strftime(date, sizeof(date), "%Y-%m-%d", t);

            // Calculate total sale
            float total = sellQty * products[i].price;

            // Save sales record
            FILE *fp = fopen("sales.txt", "a");

            if(fp != NULL)
            {
                fprintf(fp, "%s %d %d %.2f\n",
                        date,
                        products[i].id,
                        sellQty,
                        total);

                fclose(fp);
            }
            else
            {
                printf("\nSales Data Saving Failed!\n");
            }

// Save updated stock
saveProducts();

                products[i].quantity -= sellQty;
                saveProducts();

                printf("\n========== SALES INVOICE ==========\n");

                printf("Product ID : %d\n", products[i].id);
                printf("Category   : %s\n", products[i].category);
                printf("Size       : %s\n", products[i].size);
                printf("Price      : %.2f Tk\n", products[i].price);
                printf("Quantity   : %d\n", sellQty);

                printf("-----------------------------------\n");
                printf("Total Bill : %.2f Tk\n", total);

                printf("-----------------------------------\n");
                printf("Product Sold Successfully!\n");
                printf("Remaining Stock: %d\n",
                       products[i].quantity);
            }

            break;
        }
    }

    if (found == 0) {
        printf("\nProduct Not Found!\n");
    }
}
/* Stock Management */

void stockManagement()
{
    int i;
    int totalStock = 0;
    int lowStock = 0;
    int outOfStock = 0;

    system("cls");

    printf("\n");
    printf("============================================================\n");
    printf("                    STOCK MANAGEMENT\n");
    printf("============================================================\n");

    if(totalProducts == 0)
    {
        printf("\nNo Product Available!\n");
        return;
    }

    printf("\n");
    printf("%-8s %-15s %-8s %-12s %-12s\n",
           "ID", "Category", "Size", "Price", "Quantity");

    printf("------------------------------------------------------------\n");

    for(i = 0; i < totalProducts; i++)
    {
        printf("%-8d %-15s %-8s %-12.2f %-12d",
               products[i].id,
               products[i].category,
               products[i].size,
               products[i].price,
               products[i].quantity);

        if(products[i].quantity == 0)
        {
            printf(" OUT OF STOCK");
            outOfStock++;
        }
        else if(products[i].quantity <= 5)
        {
            printf(" LOW STOCK ALERT!");
            lowStock++;
        }

        printf("\n");

        totalStock += products[i].quantity;
    }

    printf("------------------------------------------------------------\n");

    printf("\n              STOCK SUMMARY\n");
    printf("============================================================\n");

    printf("Total Product Items : %d\n", totalProducts);
    printf("Total Stock Quantity: %d\n", totalStock);
    printf("Low Stock Products : %d\n", lowStock);
    printf("Out of Stock Items : %d\n", outOfStock);

    printf("============================================================\n");

    if(lowStock > 0 || outOfStock > 0)
    {
        printf("\nWARNING! Some Products Need Restocking.\n");
    }
    else
    {
        printf("\nAll Products Have Sufficient Stock.\n");
    }
}

void salesReport()
{
    FILE *fp;
    char date[11], today[11];
    int id, quantity;
    float amount;

    int totalQuantity = 0;
    float totalAmount = 0;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(today, sizeof(today), "%Y-%m-%d", t);

    fp = fopen("sales.txt", "r");

    system("cls");

    printf("\n========== DAILY SALES REPORT ==========\n");
    printf("Date: %s\n", today);
    printf("----------------------------------------\n");

    if(fp == NULL)
    {
        printf("\nNo Sales Record Found!\n");
    }
    else
    {
        printf("\n%-10s %-10s %-10s %-12s\n",
               "Date", "Product ID", "Quantity", "Amount");

        printf("----------------------------------------\n");

        while(fscanf(fp, "%10s %d %d %f",
                     date, &id, &quantity, &amount) == 4)
        {
            if(strcmp(date, today) == 0)
            {
                printf("%-10s %-10d %-10d %-12.2f\n",
                       date, id, quantity, amount);

                totalQuantity += quantity;
                totalAmount += amount;
            }
        }

        fclose(fp);
    }

    printf("----------------------------------------\n");
    printf("Total Products Sold : %d\n", totalQuantity);
    printf("Total Sales Amount  : %.2f Taka\n", totalAmount);

    printf("\nPress Enter to Continue...");
    getchar();
}
