#include <iostream>
using namespace std;

class LibraryItem {
protected:
    int id;
    string title;
    string author;
    bool available;

public:
    LibraryItem(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        available = true;
    }

    virtual void displayDetails() = 0;
    virtual string getType() = 0;

    int getId() {
        return id;
    }

    bool isAvailable() {
        return available;
    }

    void checkOut() {
        if (!available)
            throw "Item already checked out!";
        available = false;
    }

    void returnItem() {
        available = true;
    }

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem {
    int pages;

public:
    Book(int i, string t, string a, int p)
        : LibraryItem(i, t, a) {
        pages = p;
    }

    void displayDetails() {
        cout << "\n[Book]";
        cout << "\nID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPages: " << pages;
        cout << "\nStatus: " << (available ? "Available" : "Issued") << endl;
    }

    string getType() {
        return "Book";
    }
};

class DVD : public LibraryItem {
    int duration;

public:
    DVD(int i, string t, string a, int d)
        : LibraryItem(i, t, a) {
        duration = d;
    }

    void displayDetails() {
        cout << "\n[DVD]";
        cout << "\nID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nDuration: " << duration << " mins";
        cout << "\nStatus: " << (available ? "Available" : "Issued") << endl;
    }

    string getType() {
        return "DVD";
    }
};

int main() {

    LibraryItem* items[20];
    int count = 0;
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Add DVD";
        cout << "\n3. Display All Items";
        cout << "\n4. Checkout Item";
        cout << "\n5. Return Item";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                int id, pages;
                string title, author;

                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin >> title;
                cout << "Enter Author: ";
                cin >> author;
                cout << "Enter Pages: ";
                cin >> pages;

                if (pages <= 0)
                    throw "Invalid number of pages!";

                items[count++] = new Book(id, title, author, pages);
                cout << "Book added successfully.\n";
            }

            else if (choice == 2) {
                int id, duration;
                string title, author;

                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin >> title;
                cout << "Enter Author: ";
                cin >> author;
                cout << "Enter Duration (mins): ";
                cin >> duration;

                if (duration <= 0)
                    throw "Invalid duration!";

                items[count++] = new DVD(id, title, author, duration);
                cout << "DVD added successfully.\n";
            }

            else if (choice == 3) {
                for (int i = 0; i < count; i++)
                    items[i]->displayDetails();
            }

            else if (choice == 4) {
                int id;
                cout << "Enter ID to checkout: ";
                cin >> id;

                for (int i = 0; i < count; i++) {
                    if (items[i]->getId() == id) {
                        items[i]->checkOut();
                        cout << "Item checked out successfully.\n";
                    }
                }
            }

            else if (choice == 5) {
                int id;
                cout << "Enter ID to return: ";
                cin >> id;

                for (int i = 0; i < count; i++) {
                    if (items[i]->getId() == id) {
                        items[i]->returnItem();
                        cout << "Item returned successfully.\n";
                    }
                }
            }
        }
        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }

    } while (choice != 0);


    for (int i = 0; i < count; i++)
        delete items[i];

    return 0;
}