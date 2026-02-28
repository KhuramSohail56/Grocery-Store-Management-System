#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 int const MAX_ITEMS = 100;
string itemNames[MAX_ITEMS];
float itemPrices[MAX_ITEMS];
int itemQuantities[MAX_ITEMS];
int itemCount = 0;
void loadInventory() {
    ifstream File("inventory.txt");
    if (File.is_open()) {
        File >> itemCount;
        for (int i = 0; i < itemCount; i++)
{
            File >> itemNames[i] >> itemPrices[i] >> itemQuantities[i];
}
        File.close();
    } else {
        cout << "No previous inventory data found." << endl;
    }
}
void saveInventory() {
    ofstream File("inventory.txt");

    if (File.is_open()) {
        File << itemCount << endl;
        for (int i = 0; i < itemCount; i++) {
            File << itemNames[i] << " " << itemPrices[i] << " " << itemQuantities[i] << endl;
        }
        File.close();
    } else {
        cout << "Unable to save inventory data." << endl;
    }
}
void addItem() {
    if (itemCount < MAX_ITEMS) {
        cout << "Enter item name: ";
        cin >> itemNames[itemCount];
        cout << "Enter item price: ";
        cin >> itemPrices[itemCount];
        cout << "Enter item quantity: ";
        cin >> itemQuantities[itemCount];
        itemCount++;
    } else {
        cout << "Inventory is full!" << endl;
    }
}
void displayInventory() {
    cout << "Inventory:" << endl;
    cout << "-----------------------------" << endl;
    cout << "Name\tPrice\tQuantity" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << itemNames[i] << "\t" << itemPrices[i] << "\t" << itemQuantities[i] << endl<<endl;
    }
}
void updateItem() {
    displayInventory();
    string itemName;
    int newQuantity;
    float newPrice;
    cout << "Enter item name to update: ";
    cin >> itemName;
    for (int i = 0; i < itemCount; i++) {
        if (itemNames[i] == itemName) {
            cout << "Enter new quantity for " << itemName << ": ";
            cin >> newQuantity;
            itemQuantities[i] = newQuantity;
            cout << "Enter new price for " << itemName << ": ";
            cin >> newPrice;
            itemPrices[i] = newPrice;

            cout << "Item updated!" << endl;
            return;
        }
    }
    cout << "Item not found!" << endl;
}
void deleteItem() {
    displayInventory();
    string itemName;
    cout << "Enter item name to delete: ";
    cin >> itemName;

    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (itemNames[i] == itemName) {
            found = true;
            for (int j = i; j < itemCount -1; j++) {
                itemNames[j] = itemNames[j + 1];
                itemPrices[j] = itemPrices[j + 1];
                itemQuantities[j] = itemQuantities[j + 1];
            }
            itemCount--;
            cout << "Item deleted!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Item not found!" << endl;
    }
}
void calculateTotalCost() {
    string itemName;
    int quantity;
    float totalCost = 0.0;
    cout << "Enter item name and quantity to purchase (type 'done' to finish):" << endl;
    while (true) {
        cout << "Item name: ";
        cin >> itemName;
        if (itemName == "done") {
            break;
        }
        cout << "Quantity: ";
        cin >> quantity;

        bool itemFound = false;
        for (int i = 0; i < itemCount; i++) {
            if (itemNames[i] == itemName) {
                itemFound = true;
                if (itemQuantities[i] >= quantity) {
                    totalCost += itemPrices[i] * quantity;
                    itemQuantities[i] -= quantity;
                } else {
                    cout << "Not enough stock for " << itemName << endl;
                }
                break;
            }
        }
        if (!itemFound) {
            cout << "Item not found!" << endl;
            return;
        }
    }

    cout << "Total cost: " << totalCost << endl;
}
int main() {
    int choice;
    loadInventory();

    while (true) {
        cout << "\nGrocery Store Management System" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Display Inventory" << endl;
        cout << "3. Update Item" << endl;
        cout << "4. Calculate Total Cost" << endl;
        cout << "5. Delete Item" << endl; // New option
        cout << "6. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                calculateTotalCost();
                break;
            case 5:
                deleteItem();
                break;
            case 6:

                saveInventory();
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

