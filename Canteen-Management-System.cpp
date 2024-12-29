#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <cstdio>
using namespace std;
struct canteen
{
    char dish[50];
    int key;
    float price;
} canteen;

class Canteen
{
public:
    void create();
    void query();
    void display();
    void update();
    void delet();
    void admin();
};

void Canteen::create()
{
    char a;
    int k;
    fstream obj;
top:
    do
    {
        obj.open("canteen.txt", ios::in | ios::binary);
        cout << "Enter The Dish Key : ";
        cin >> k;
        while (obj.read((char *)&canteen, sizeof(canteen)))
        {
            if (canteen.key == k)
            {
                cout << "Eey is Already Exist " << endl;
                obj.close();
                goto top;
            }
        }
        obj.close();
        obj.open("canteen.txt", ios::app | ios::binary);
        canteen.key = k;
        cin.ignore();
        cout << "Enter The Dish Name : ";
        gets(canteen.dish);
        cout << "Enter The Dish Price : ";
        cin >> canteen.price;
        obj.write((char *)&canteen, sizeof(canteen));
        cout << "Do you want to Add an Other [y/n] : ";
        cin >> a;
        obj.close();
    } while (a != 'n');
}

void Canteen::display()
{
    int c = 0;
    fstream obj;
    obj.open("canteen.txt", ios::in | ios::binary);
    cout << "\tKey\t\tDISH NAME\t\tPRICE " << endl;
    while (obj.read((char *)&canteen, sizeof(canteen)))
    {
        cout << "\t" << canteen.key << "\t\t" << canteen.dish << "\t\t\t" << canteen.price << endl;
        c++;
    }
    if (c == 0)
    {
        cout << "List is Empty " << endl;
    }
    obj.close();
}
void Canteen::query()
{
    int a, c = 0;

    fstream obj;
    obj.open("canteen.txt", ios::in);
    cout << "Enter The Dish Key : ";
    cin >> a;
    while (obj.read((char *)&canteen, sizeof(canteen)))
    {
        if (canteen.key == a)
        {
            cout << "\t" << canteen.key << "\t\t" << canteen.dish << "\t\t\t" << canteen.price << endl;
            c++;
        }
    }
    if (c == 0)
    {
        cout << "Not Found (404) " << endl;
    }
    obj.close();
}
void Canteen::update()
{
    int a, p, c = 0;
    fstream obj;
    obj.open("canteen.txt", ios::in | ios::out | ios::binary);
    cout << "Enter The Dish Key : ";
    cin >> a;
    obj.seekg(0);

    while (obj.read((char *)&canteen, sizeof(canteen)))
    {
        if (canteen.key == a)
        {
            cout << "Destination Record : " << endl;
            cout << "\t" << canteen.key << "\t\t" << canteen.dish << "\t\t\t" << canteen.price << endl;
            p = obj.tellg() - (sizeof(canteen));
            obj.seekp(p);
            cout << "Enter The Dish Key : ";
            cin >> canteen.key;
            cin.ignore();
            cout << "Enter The Dish Name : ";
            gets(canteen.dish);
            cout << "Enter The Dish Price : ";
            cin >> canteen.price;
            obj.write((char *)&canteen, sizeof(canteen));
            c++;
        }
    }
    if (c == 0) 
    {
        cout << "Not Found (404) " << endl;
    }
    obj.close();
}
void Canteen::delet()

{
    int a, c;
    fstream obj, obj1;
    obj.open("canteen.txt", ios::in | ios::binary);
    obj1.open("temp.txt", ios::app | ios::binary);
    cout << "Enter the Dish Key : ";
    cin >> a;
    while (obj.read((char *)&canteen, sizeof(canteen)))
    {
        if (canteen.key == a)
        {
            c++;
            cout << "\t" << canteen.key << "\t\t" << canteen.dish << "\t\t\t" << canteen.price << endl;
            cout << "Destination record is Deleted " << endl;
        }
        if (canteen.key != a)
        {
            obj1.write((char *)&canteen, sizeof(canteen));
        }
    }
    obj.close();
    obj1.close();
    if (c == 0)
    {
        cout << "Not Found (404) " << endl;
    }

    remove("canteen.txt");
    rename("temp.txt", "canteen.txt");
}
void Canteen::admin()
{
    char a;
    do
    {
        cout << "\n\n\t\t\t\t\t\t|||||||||||||||||||||||||" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t| 1) ADD DISH           |" << endl;
        cout << "\t\t\t\t\t\t| 2) Display            |" << endl;
        cout << "\t\t\t\t\t\t| 3) QUERY              |" << endl;
        cout << "\t\t\t\t\t\t| 4) UPDATE             |" << endl;
        cout << "\t\t\t\t\t\t| 5) DELETE             |" << endl;
        cout << "\t\t\t\t\t\t| 0) EXIT TO MAINMENU   |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|||||||||||||||||||||||||\n" << endl;
        cout << "\t\t\t\t\t\t Select the Key ";
        cin >> a;
        switch (a)
        {
        case '0':
            break;
        case '1':
            create();
            break;
        case '2':

            display();
            break;
        case '3':
            query();
            break;
        case '4':
            update();
            break;
        case '5':
            delet();
            break;
        }
    } while (a != '0');
}

struct
{
    char d[50];
    float p, amount;
    int qty;
} canteend;
class customer : public Canteen
{
public:
    void bill();
    void showbill();
    void dish_menu();
};
void customer::bill()
{
    int a, c = 0;
    char ch;
    float total = 0;
    fstream obj, obj1;
    dish_menu();
    obj1.open("bill.txt", ios::out | ios::binary);
    do
    {
        obj.open("canteen.txt", ios::in | ios::binary);
        cout << "Enter the Dish Key : ";
        cin >> a;
        while (obj.read((char *)&canteen, sizeof(canteen)))
        {
            if (canteen.key == a)
            {
                c++;
                cout << "Enter the Quantity : ";
                cin >> canteend.qty;
                canteend.amount = canteend.qty * canteen.price;
                cout << "\t" << canteen.dish << "\t\t" << canteen.price << "*" << canteend.qty << "\t\t" << canteend.amount << endl;
                strcpy(canteend.d, canteen.dish);

                canteend.p = canteen.price;
                obj1.write((char *)&canteend, sizeof(canteend));
                total = total + canteend.amount;
            }
        }
        if (c == 0)
        {
            cout << "Not Found (404) " << endl;
        }
        cout << "Do you want to Order More [y/n] ";
        cin >> ch;
        obj.close();
    } while (ch != 'n');
    obj1.close();
    cout << "\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||        ||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||  BILL  ||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||        ||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n" << endl;
    showbill();
    cout << "\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;

    cout << "|||\t\t\t\t\t\tTOTAL = " << total << "   \t\t\t\t\t\t  |||" << endl;//add <<"   "<<//
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n" << endl;
}
void customer::showbill()
{
    fstream obj;
    obj.open("bill.txt", ios::in | ios::binary);
    cout << "\tDISH NAME\t\tPRICE\t\tQTY\t\tAMOUNT " << endl;
    while (obj.read((char *)&canteend, sizeof(canteend)))
    {
        cout << "\t" << canteend.d << "\t\t\t" << canteend.p << "\t\t" << canteend.qty << "\t\t" << canteend.amount << endl;
    }
    obj.close();
}
void customer::dish_menu()
{
    fstream obj;
    obj.open("canteen.txt", ios::in | ios::binary);
    while (obj.read((char *)&canteen, sizeof(canteen)))
    {
        cout << "\t\t" << canteen.key << ") " << canteen.dish << "-------RS" << canteen.price << endl;
    }
    obj.close();
}
int main()
{
    char a;
    customer obj;
    do
    {
        cout << "\n\t\t\t\t\t\t|||||||||||||||||||||||||" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|      1)Admin          |" << endl;
        cout << "\t\t\t\t\t\t|      2)customer       |" << endl;
        cout << "\t\t\t\t\t\t|      0)Exit           |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|                       |" << endl;
        cout << "\t\t\t\t\t\t|||||||||||||||||||||||||\n" << endl;
        cout << "\t\t\t\t\t\t Select The Menu ";
        cin >> a;
        switch (a)
        {
        case '0':
            break;
        case '1':
            obj.admin();
            break;
        case '2':
            obj.bill();
            break;
        }
    } while (a != '0');
    return 0;
}
