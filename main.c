#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PRODUCTS 100
#define LOW_STOCK_LIMIT 5

void mainMenu(void);
void addProduct(void);
void viewProducts(void);
void saveProducts(void);
void loadProducts(void);
void updateProducts(void);
void searchProducts(void);
void deleteProducts(void);
void sellProducts(void);
void stockManagement(void);
void salesReport(void);

/* Product Structure */
struct product
{
    int id;
    char category[30];
    char size[20];
    float price;
    int quantity;
};

struct product products[MAX_PRODUCTS];
int totalProducts = 0;

/* ================= Helper Functions ================= */

/* Clear the console on both Windows and Linux/macOS */
void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Read one full line safely; extra characters are discarded */
void readLine(char *buf, size_t size)
{
    if(fgets(buf, (int)size, stdin) == NULL)
    {
        /* Input closed (Ctrl+Z / Ctrl+D): exit cleanly instead of looping */
        printf("\n");
        exit(0);
    }

    size_t len = strcspn(buf, "\n");

    if(buf[len] == '\n')
    {
        buf[len] = '\0';
    }
    else
    {
        int c;
        while((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
}

/* Keep asking until a whole number >= min is entered */
int readInt(const char *prompt, int min)
{
    char buf[64];
    char *end;
    long value;

    while(1)
    {
        printf("%s", prompt);
        readLine(buf, sizeof(buf));

        value = strtol(buf, &end, 10);

        while(isspace((unsigned char)*end))
        {
            end++;
        }

        if(end != buf && *end == '\0' && value >= min && value <= 1000000000L)
        {
            return (int)value;
        }

        if(min == 0)
            printf("Invalid input! Please enter a number (0 or more).\n");
        else
            printf("Invalid input! Please enter a number (%d or more).\n", min);
    }
}

/* Keep asking until a positive price is entered */
float readPrice(const char *prompt)
{
    char buf[64];
    char *end;
    double value;

    while(1)
    {
        printf("%s", prompt);
        readLine(buf, sizeof(buf));

        value = strtod(buf, &end);

        while(isspace((unsigned char)*end))
        {
            end++;
        }

        if(end != buf && *end == '\0' && value > 0 && value <= 10000000)
        {
            return (float)value;
        }

        printf("Invalid price! Please enter a positive amount.\n");
    }
}

/* Case-insensitive string compare (works on every compiler) */
int equalsIgnoreCase(const char *a, const char *b)
{
    while(*a && *b)
    {
        if(tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

/* Show category menu; returns 1 if a category was chosen, 0 to go back */
int chooseCategory(char *dest)
{
    const char *categories[] = {"T-Shirt", "Pants", "Shirt", "Jacket"};
    int choice;

    printf("1. T-Shirt\n");
    printf("2. Pants\n");
    printf("3. Shirt\n");
    printf("4. Jacket\n");
    printf("0. Back\n");

    while(1)
    {
        choice = readInt("\nEnter Choice        : ", 0);

        if(choice == 0)
            return 0;

        if(choice >= 1 && choice <= 4)
        {
            strcpy(dest, categories[choice - 1]);
            return 1;
        }

        printf("Invalid Choice! Please select 1-4.\n");
    }
}

/* Keep asking until a valid size (S/M/L/XL/XXL) is entered */
void readSize(const char *prompt, char *dest)
{
    const char *sizes[] = {"S", "M", "L", "XL", "XXL"};
    char buf[20];

    while(1)
    {
        printf("%s", prompt);
        readLine(buf, sizeof(buf));

        for(int i = 0; i < 5; i++)
        {
            if(equalsIgnoreCase(buf, sizes[i]))
            {
                strcpy(dest, sizes[i]);
                return;
            }
        }

        printf("Invalid size! Please enter S, M, L, XL or XXL.\n");
    }
}

/* Next unique product ID = highest existing ID + 1 */
int nextProductId(void)
{
    int maxId = 0;

    for(int i = 0; i < totalProducts; i++)
    {
        if(products[i].id > maxId)
            maxId = products[i].id;
    }

    return maxId + 1;
}

/* Returns array index of product with given ID, or -1 */
int findProductIndex(int id)
{
    for(int i = 0; i < totalProducts; i++)
    {
        if(products[i].id == id)
            return i;
    }
    return -1;
}

void printProductDetails(int i)
{
    printf("------------------------------------\n");
    printf("Product ID : %d\n", products[i].id);
    printf("Category   : %s\n", products[i].category);
    printf("Size       : %s\n", products[i].size);
    printf("Price      : %.2f Tk\n", products[i].price);
    printf("Quantity   : %d\n", products[i].quantity);
    printf("------------------------------------\n");
}

/* ================= Main Program ================= */

int main(void)
{
    loadProducts();
    mainMenu();
    return 0;
}

void mainMenu(void)
{
    int choice;
    char dummy[8];

    while(1)
    {
        clearScreen();

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
        choice = readInt("Enter your choice : ", 0);

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

        /* Single pause point for every menu option */
        printf("\nPress Enter to Continue...");
        readLine(dummy, sizeof(dummy));
    }
}

/* Add Product */
void addProduct(void)
{
    struct product p;

    clearScreen();

    printf("==========================================\n");
    printf("            ADD PRODUCT\n");
    printf("==========================================\n");

    if(totalProducts >= MAX_PRODUCTS)
    {
        printf("\nProduct Storage Full!\n");
        return;
    }

    if(!chooseCategory(p.category))
    {
        printf("\nBack to Main Menu.\n");
        return;
    }

    p.id = nextProductId();
    printf("Product ID          : %d\n", p.id);

    readSize("Size (S/M/L/XL/XXL) : ", p.size);
    p.price = readPrice("Unit Price          : ");
    p.quantity = readInt("Product Quantity    : ", 0);

    products[totalProducts] = p;
    totalProducts++;

    saveProducts();

    printf("\nProduct Added Successfully!\n");
}

/* Save products to file */
void saveProducts(void)
{
    FILE *fp = fopen("products.txt", "w");

    if(fp == NULL)
    {
        printf("\nFile Opening Error! Data not saved.\n");
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
}

/* Load products from file */
void loadProducts(void)
{
    FILE *fp = fopen("products.txt", "r");

    totalProducts = 0;

    if(fp == NULL)
    {
        return;
    }

    while(totalProducts < MAX_PRODUCTS &&
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
void viewProducts(void)
{
    clearScreen();

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

    for(int i = 0; i < totalProducts; i++)
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

/* Update Product */
void updateProducts(void)
{
    int id, i, choice;

    clearScreen();

    printf("\n========== UPDATE PRODUCT ==========\n");
    printf("Press 0 Back to the Main Menu \n");
    id = readInt("Enter Product ID: ", 0);

    if(id == 0)
    {
        return;
    }

    i = findProductIndex(id);

    if(i == -1)
    {
        printf("\nProduct Not Found!\n");
        return;
    }

    printf("\nProduct Found!\n");
    printProductDetails(i);

    printf("\nWhat do you want to update?\n");
    printf("1. Category\n");
    printf("2. Size\n");
    printf("3. Price\n");
    printf("4. Quantity\n");
    printf("5. Update All\n");
    printf("0. Cancel\n");
    choice = readInt("Enter Choice: ", 0);

    switch(choice)
    {
    case 0:
        printf("\nUpdate Cancelled!\n");
        return;

    case 1:
        printf("\nSelect New Category:\n");
        if(!chooseCategory(products[i].category))
        {
            printf("\nUpdate Cancelled!\n");
            return;
        }
        break;

    case 2:
        readSize("Enter New Size (S/M/L/XL/XXL): ", products[i].size);
        break;

    case 3:
        products[i].price = readPrice("Enter New Price: ");
        break;

    case 4:
        products[i].quantity = readInt("Enter New Quantity: ", 0);
        break;

    case 5:
        printf("\nSelect New Category:\n");
        if(!chooseCategory(products[i].category))
        {
            printf("\nUpdate Cancelled!\n");
            return;
        }
        readSize("Enter New Size (S/M/L/XL/XXL): ", products[i].size);
        products[i].price = readPrice("Enter New Price: ");
        products[i].quantity = readInt("Enter New Quantity: ", 0);
        break;

    default:
        printf("\nInvalid Choice!\n");
        return;
    }

    saveProducts();

    printf("\nProduct Updated Successfully!\n");
}

/* Search Product */
void searchProducts(void)
{
    char idInput[20];
    char category[30];
    char *end;
    long id = 0;
    int found = 0;

    clearScreen();

    printf("==============================================\n");
    printf("                SEARCH PRODUCT\n");
    printf("==============================================\n");

    printf("\nEnter ID or Category or Both (leave blank to skip).");

    printf("\nEnter Product ID : ");
    readLine(idInput, sizeof(idInput));

    printf("Enter Category   : ");
    readLine(category, sizeof(category));

    if(strlen(idInput) == 0 && strlen(category) == 0)
    {
        printf("\nPlease enter ID or Category!\n");
        return;
    }

    if(strlen(idInput) > 0)
    {
        id = strtol(idInput, &end, 10);

        if(end == idInput || *end != '\0')
        {
            printf("\nInvalid Product ID!\n");
            return;
        }
    }

    for(int i = 0; i < totalProducts; i++)
    {
        int idMatch = 1;
        int categoryMatch = 1;

        if(strlen(idInput) > 0 && products[i].id != id)
        {
            idMatch = 0;
        }

        if(strlen(category) > 0 && !equalsIgnoreCase(products[i].category, category))
        {
            categoryMatch = 0;
        }

        if(idMatch && categoryMatch)
        {
            found = 1;

            printf("\n==============================================\n");
            printf("                 PRODUCT FOUND\n");
            printf("==============================================\n");

            printf("ID       : %d\n", products[i].id);
            printf("Category : %s\n", products[i].category);
            printf("Size     : %s\n", products[i].size);
            printf("Price    : %.2f Tk\n", products[i].price);
            printf("Quantity : %d\n", products[i].quantity);
        }
    }

    if(!found)
    {
        printf("\nProduct not found!\n");
    }
}

/* Delete Product */
void deleteProducts(void)
{
    int id, i;
    char confirm[8];

    clearScreen();

    printf("==============================================\n");
    printf("                DELETE PRODUCT\n");
    printf("==============================================\n");

    printf("Press 0 Back to the Main Menu \n");
    id = readInt("Enter Product ID: ", 0);

    if(id == 0)
    {
        return;
    }

    i = findProductIndex(id);

    if(i == -1)
    {
        printf("\nProduct not found!\n");
        return;
    }

    printf("\nProduct Found\n");
    printProductDetails(i);

    printf("\nAre you sure you want to delete this product? (Y/N): ");
    readLine(confirm, sizeof(confirm));

    if(confirm[0] == 'Y' || confirm[0] == 'y')
    {
        for(int j = i; j < totalProducts - 1; j++)
        {
            products[j] = products[j + 1];
        }

        totalProducts--;
        saveProducts();

        printf("\nProduct deleted successfully!\n");
    }
    else
    {
        printf("\nDelete cancelled!\n");
    }
}

/* Sell Product */
void sellProducts(void)
{
    int searchId, sellQty, i;
    float total;

    clearScreen();

    printf("==============================================\n");
    printf("                SELL PRODUCT\n");
    printf("==============================================\n");

    printf("Press 0 Back to the Main Menu \n");
    searchId = readInt("Enter Product ID: ", 0);

    if(searchId == 0)
    {
        return;
    }

    i = findProductIndex(searchId);

    if(i == -1)
    {
        printf("\nProduct Not Found!\n");
        return;
    }

    printf("\nProduct Found!\n");
    printProductDetails(i);

    if(products[i].quantity == 0)
    {
        printf("\nSorry! This product is out of stock.\n");
        return;
    }

    printf("Press 0 Back to the Main Menu \n");
    sellQty = readInt("Enter Selling Quantity: ", 0);

    if(sellQty == 0)
    {
        printf("\nSale Cancelled!\n");
        return;
    }

    if(sellQty > products[i].quantity)
    {
        printf("\nSorry! Insufficient Stock.\n");
        return;
    }

    total = sellQty * products[i].price;

    /* Get current date */
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[11];

    strftime(date, sizeof(date), "%Y-%m-%d", t);

    /* Save sales record */
    FILE *fp = fopen("sales.txt", "a");

    if(fp == NULL)
    {
        printf("\nSales Data Saving Failed! Sale not completed.\n");
        return;
    }

    fprintf(fp, "%s %d %d %.2f\n",
            date,
            products[i].id,
            sellQty,
            total);

    fclose(fp);

    /* Update and save stock */
    products[i].quantity -= sellQty;
    saveProducts();

    printf("\n========== SALES INVOICE ==========\n");

    printf("Date       : %s\n", date);
    printf("Product ID : %d\n", products[i].id);
    printf("Category   : %s\n", products[i].category);
    printf("Size       : %s\n", products[i].size);
    printf("Price      : %.2f Tk\n", products[i].price);
    printf("Quantity   : %d\n", sellQty);

    printf("-----------------------------------\n");
    printf("Total Bill : %.2f Tk\n", total);

    printf("-----------------------------------\n");
    printf("Product Sold Successfully!\n");
    printf("Remaining Stock: %d\n", products[i].quantity);
}

/* Stock Management */
void stockManagement(void)
{
    int totalStock = 0;
    int lowStock = 0;
    int outOfStock = 0;

    clearScreen();

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

    for(int i = 0; i < totalProducts; i++)
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
        else if(products[i].quantity <= LOW_STOCK_LIMIT)
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
    printf("Low Stock Products  : %d\n", lowStock);
    printf("Out of Stock Items  : %d\n", outOfStock);

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

/* Daily Sales Report */
void salesReport(void)
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

    clearScreen();

    printf("\n========== DAILY SALES REPORT ==========\n");
    printf("Date: %s\n", today);
    printf("----------------------------------------\n");

    fp = fopen("sales.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Sales Record Found!\n");
    }
    else
    {
        printf("\n%-12s %-12s %-10s %-12s\n",
               "Date", "Product ID", "Quantity", "Amount");

        printf("----------------------------------------\n");

        while(fscanf(fp, "%10s %d %d %f",
                     date, &id, &quantity, &amount) == 4)
        {
            if(strcmp(date, today) == 0)
            {
                printf("%-12s %-12d %-10d %-12.2f\n",
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
}
