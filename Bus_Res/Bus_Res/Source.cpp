#include <iostream>
#include <fstream>
#include <string>
#define size_seats 20
#define size_tickets 100
#define Size_buses 9
#define Size_Persons 50 
using namespace std;

struct Bus {
    int busNumber = 0;
    int numberOfSeats = 0;
    int avialableNoOfSeats = 0;
    float busTakeOffTime = 0;
    bool isBooked[size_seats] = { };
    string from = "-";
    string destination = "-";
    bool bus_isavialable = 0;

}Buses[Size_buses];

struct Person {
    string name = "-";
    string password = "-";
    bool isAdmin = false;
    int noOfBussesBooked = 0;
    int noOfSeatsBooked = 0;

}Persons[Size_Persons];

struct Ticket {
    int tickets_reserved = 0;
    int ID = 0;
    int seat_number = 0;
    float TakeOffTIme = 0;
    int busNumber = 0;
    string from = "-";
    string destination = "-";
    string user = "-";


}tickets[size_tickets];

bool sign_in();//zahran
void datasetup();//zahran
void savebusdata();//zahran
void ticketsetup();//zahran
void saveticketdata();//zahran
void personsetup();//zahran
void personsave();//zahran



void sign_up();//Ali
int get_ticket_number();//Ali

void insert_bus();//mostafa
void delete_bus();//mostafa
bool check_bus_num(int&);//mostafa


void available_buses();//nasser
void view_alltickets();//naser


void display_seats_status_and_num(int&);//wagih
int get_bus_number();//wagih
void bus_schedule(int&);//wagih




int get_bus_idx(int&);//yehia
void bus_status();//yehia


void welcome_message();//all
char get_input();//all
void Menu();//all
void book_tickets();//all
void cancel_res();//all
void opening();//all

bool isAdmin = false;
int user_idx;

int main()
{
    personsetup();
    ticketsetup();
    datasetup();
first:
    opening();


    if (sign_in()) {


        welcome_message();

        char ch;
        do
        {

            Menu();
            bus_status();
            ch = get_input();
            system("cls");

            if (ch == 'D' || ch == 'd') {
                available_buses();
            }
            else if (ch == 's' || ch == 'S') {
                cout << "Enter bus number to find" << endl;
                int num = get_bus_number();

                bus_schedule(num);
            }
            else if (ch == 'B' || ch == 'b') {
                book_tickets();
            }
            else if (ch == 'C' || ch == 'c') {
                cancel_res();
            }
            else if (ch == 'Q' || ch == 'q')
                cout << "\t\t\n\nThank you for working with us\n";
            else if ((ch == 'A' || ch == 'a') && isAdmin)
                insert_bus();
            else if (ch == 'L' || ch == 'l') {
                cout << "\n\n";
                goto first;
            }
            else if (ch == 'v' || ch == 'V')
                view_alltickets();
            else if ((ch == 'R' || ch == 'r') && isAdmin)
            {
                delete_bus();
            }
            else
                cout << "Invalid input - Please enter a valid character\n";



        } while (ch != 'q' && ch != 'Q');
    }

    savebusdata();
    saveticketdata();
    personsave();

    cout << endl;
    return 0;
}

void opening()
{

    char d;
    do {
        cout << "G  -  if you already have an account " << endl;
        cout << "S  -  To sign up " << endl;
        d = get_input();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
            cout << "Invalid input , try one more time: ";
            
        }
        else if (d == 'S' || d == 's') {
            sign_up();
            cout << "\n\n";

        }
        else if (d == 'g' || d == 'G')
            break;
        else
        {
            cout << "\nplease Enter a valid character\n\n\a";
            
        }


    } while (true);
    system("cls");
}

bool sign_in() {
    string user, password;

    bool userFound = true, passCorrect = false;
    cout << "\t\tSign in page\n\n";
    do
    {
        cout << "Enter your username: ";
        cin >> user;
        for (int i = 0; i < Size_Persons; i++)
        {
            if (user == Persons[i].name) {
                user_idx = i;
                userFound = true;
                break;
            }
            else {
                userFound = false;
            }
        }
        if (!userFound) {
            cout << "\nUsername not found. Please enter a valid username\n";
        }
    } while (!userFound);
    do
    {
        cout << "Enter Password: ";
        cin >> password;
        if (password == Persons[user_idx].password) {
            passCorrect = true;
            if (Persons[user_idx].isAdmin) {
                isAdmin = true;
            }
            else {
                isAdmin = false;
            }
            return 1;
        }
        else {
            passCorrect = false;
            cout << "Incorrect password. Please enter the correct password to proceed\n";
        }

    } while (!passCorrect);


}
void sign_up()
{
    string user, pass, pass2;
    int user_indx;

    cout << "\t\tSignup page\n" << endl;
    while (true)
    {
        bool available = true;
        cout << "\nEnter the user name : ";
        cin >> user;
        for (int i = 0; i < Size_Persons; i++)
        {
            if (user == Persons[i].name)
            {
                available = false;
                break;
            }
        }
        if (available)
        {
            for (int i = 0; i < Size_Persons; i++)
            {
                if (Persons[i].name == "-")
                {
                    Persons[i].name = user;
                    user_indx = i;
                    break;
                }
            }
            break;
        }
        else if (!available)
        {
            cout << "Username is used   -  try another " << endl;
            continue;
        }
    }
    cout << "Enter new password : ";
    cin >> pass;
    cout << "Confirm new password : ";
    while (true)
    {
        cin >> pass2;
        if (pass == pass2)
        {
            Persons[user_indx].password = pass;
            break;
        }
        else
        {
            cout << "\tthe password is incorrect" << endl;
            cout << "reconfirm your password : ";
        }
            continue;
    }

}

void welcome_message() {
    cout << "\t\t   ______________________________________\n";
    cout << "\t\t  /___                 _____ _____       |\n";
    cout << "\t\t /    |      ___      |     |     |      |\n";
    cout << "\t\t|_____|     | | |     |_____|_____|      |\n";
    cout << "\t\t|           | | |                        |\n";
    cout << "\t\t|    ___    | | |                 ___    |\n";
    cout << "\t\t|___/ . \\___|_|_|________________/ . \\___|\n";
    cout << "\t\t    \\_'_/                        \\_'_/\n";

    cout << "\n\t\t   Welcome to bus reservation program" << endl;


}

void Menu() {
    if (isAdmin)
    {
        cout << "\nA - Add bus" << endl;
        cout << "\nR - Remove a bus" << endl;
    }
    cout << "\nD - Display all available buses" << endl;
    cout << "\nS - Display specific bus schedule" << endl;
    cout << "\nB - Book ticket" << endl;
    cout << "\nV - view all tickets" << endl;
    cout << "\nC - Cancel booking" << endl;
    cout << "\nQ - Exit program" << endl;
    cout << "\nL - Log out" << endl;
}

char get_input() {
    char ch[100];
    cout << "\nEnter your choice: ";
    ch[2] = '*';
    cin >> ch;
    if (ch[2] != '*')
        return 'm';
    else
        return ch[0];
}

void available_buses() {
    for (int i = 0; i < Size_buses; i++)
    {
        if (Buses[i].busNumber > 0) {
            cout << "\tBus number: " << 00 << Buses[i].busNumber << endl;
            cout << "\tBus takes off at: " << Buses[i].busTakeOffTime << endl;
            cout << "from: " << Buses[i].from << "\t\t";
            cout << "to: " << Buses[i].destination << endl;
            cout << "\tAvaialble seats: " << Buses[i].avialableNoOfSeats << endl;
            cout << "\n--------------------------------------\n";
        }
    }
}

int get_bus_number() {
    int num, i;
    cin >> num;
    
    if (num >= 1 && num <= Size_buses)
    {
        for (i = 0; i < Size_buses; i++)
        {
            if (Buses[i].busNumber == num)
            {
                break;
            }

        }
        return i;
    }

    else if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        cout << "Input is not number , try one more time: ";
        cout << "\nEnter bus number again: ";
        get_bus_number();
    }

    else  {
        cout << "Not a valid bus number\n";
        char ch;
        do
        {
            cout << "Do you want to book again ? (Y/N): ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                book_tickets();
            else if (ch != 'N' && ch != 'n')
                cout << "please enter only y or Y or n or N\n";
            

        } while (ch != 'n' && ch != 'N');

        return -720;

       
    }
    
}

void bus_schedule(int& i) {
    cout << "\n--------------------------------------\n";
    cout << "Bus number: " << Buses[i].busNumber << endl;
    cout << "Bus takes off at: " << Buses[i].busTakeOffTime << endl;
    cout << "From: " << Buses[i].from << endl;
    cout << "To: " << Buses[i].destination << endl;
    cout << "Avaialble seats: " << Buses[i].avialableNoOfSeats << endl;
    display_seats_status_and_num(i);
    cout << "\n--------------------------------------\n";
}


void datasetup() {
    int BN, S, avs;
    string D, F;
    string conv;
    float time;
    fstream myfile;
    myfile.open("busdata.txt");
    if (myfile.is_open()) {
        int i = 0;
        while (myfile >> BN >> S >> F >> D >> time >> avs >> conv) {
            Buses[i].busNumber = BN;
            Buses[i].numberOfSeats = S;
            Buses[i].from = F;
            Buses[i].destination = D;
            Buses[i].busTakeOffTime = time;
            Buses[i].avialableNoOfSeats = avs;
            for (int j = 0; j < conv.size(); j++)
            {
                if (conv[j] == '1') {
                    Buses[i].isBooked[j] = true;
                }
                else {
                    Buses[i].isBooked[j] = false;
                }
            }
            i++;
        }
    }
    else {
        cout << "error";
    }
    myfile.close();
}

void book_tickets() {
    book_tickets:
    int  bus_idx, seat_num, seat_idx;
    char ch;
    cout << "Enter bus number: ";
    bus_idx = get_bus_number();
    if (bus_idx != -720)
    {
        display_seats_status_and_num(bus_idx);
        cout << "\nEnter seat num: ";
        cin >> seat_num;
        seat_idx = seat_num - 1;

       
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "Input is not number , try one more time \n";
            book_tickets();
        }
    
    else if (!Buses[bus_idx].isBooked[seat_idx] && seat_idx >= 0 && seat_idx <= 19) {
            Buses[bus_idx].isBooked[seat_idx] = 1;
            int ticket_idx = 0;
            for (int i = 0; i <= size_tickets; i++)
            {
                if (tickets[i].busNumber == 0) {
                    ticket_idx = i;
                    break;
                }
            }


            Buses[bus_idx].avialableNoOfSeats -= 1;
            tickets[ticket_idx].busNumber = Buses[bus_idx].busNumber;
            tickets[ticket_idx].TakeOffTIme = Buses[bus_idx].busTakeOffTime;
            tickets[ticket_idx].from = Buses[bus_idx].from;
            tickets[ticket_idx].destination = Buses[bus_idx].destination;
            tickets[ticket_idx].seat_number = seat_num;
            tickets[ticket_idx].ID = Buses[bus_idx].busNumber * 10000 + 2022 + seat_num;
            tickets[ticket_idx].user = Persons[user_idx].name;
            Persons[user_idx].noOfBussesBooked++;
            Persons[user_idx].noOfSeatsBooked++;
            cout << "Reservation has been made :)\n" << endl;
            cout << "Your ticket ID is: " << tickets[ticket_idx].ID << "\n" << endl;
            cout << "Have a nice trip\n\n";

        }
        else if (Buses[bus_idx].isBooked[seat_idx] && seat_idx >= 0 && seat_idx <= 19)
        {
            char ch;
            cout << "Sorry - Seat alreday booked\n";
            do
            {
                cout << "Do you want to book again ? (Y/N): ";
                cin >> ch;
                if (ch == 'y' || ch == 'Y')
                    goto book_tickets;
                else
                    cout << "please enter only y or Y or n or N\n";

            } while (ch != 'n' && ch != 'N');
        }
        else {
            char ch;
            cout << "Not a valid seat number - please enter numbers from the seat list\n";
            book_tickets();
        }
    }
}



int get_ticket_number() {
    int num, i;
    char ch;
    bool isFound = false;
    cin >> num;
    if (num <= 0) {
        cout << "ERROR - Please enter positive numbers\n" << endl;
        do
        {
            cout << "Do you want to continue canceling ? (Y/N): ";
            cin >> ch;

            if (ch == 'Y' || ch == 'y')
                cancel_res();

            else if (ch == 'N' || ch == 'n')
                break;
            else
                cout << "Please enter (y/Y) or (n/N) only\n" << endl;
        } while (ch != 'y' && ch != 'Y' && ch != 'N' && ch != 'n');
    }
    for (i = 0; i < Size_buses; i++)
    {
        if (tickets[i].ID == num)
        {
            isFound = true;
            break;
        }
    }
    if (isFound)
        return i;
    else
        return -1;
}

void cancel_res() {
    int num_tickets, ticket_idx;
    char ch;
    cout << "Enter ticket ID: ";
    ticket_idx = get_ticket_number();
    if (ticket_idx == -1) {

        cout << "Sorry invalid ID\n";
        do
        {
            cout << "Do you want to continue canceling ? (Y/N): ";
            ch = get_input();

            if (ch == 'Y' || ch == 'y')
                cancel_res();

            else if (ch == 'N' || ch == 'n')
                break;
            else if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<int>::max(), '\n');
                cout << "Please enter (y/Y) or (n/N) only\n" << endl;

            }
                
        } while (ch != 'y' && ch != 'Y' && ch != 'N' && ch != 'n');
    }
    else {
        int seat_idx = tickets[ticket_idx].seat_number - 1;
        int bus_idx = get_bus_idx(seat_idx);
        if (bus_idx != -1) {
            Buses[bus_idx].isBooked[seat_idx] = 0;
            tickets[ticket_idx].busNumber = 0;
            tickets[ticket_idx].TakeOffTIme = 0;
            tickets[ticket_idx].from = "-";
            tickets[ticket_idx].destination = "-";
            tickets[ticket_idx].ID = 0;
            tickets[ticket_idx].user = "-";
            cout << "Canceled successfully\n\n";
        }
        else {
            cout << "ERROR in cancel\n";
        }
    }

}


void savebusdata() {
    fstream busfile("busdata.txt");
    for (int i = 0; i < Size_buses; i++)
    {
        busfile << Buses[i].busNumber << "\t";
        busfile << Buses[i].numberOfSeats << "\t";
        if (Buses[i].from == "-")
        {
            busfile << "-\t";
        }
        else {
            busfile << Buses[i].from << "\t";
        }
        if (Buses[i].destination == "-")
        {
            busfile << "-\t";
        }
        else {
            busfile << Buses[i].destination << "\t";
        }
        busfile << Buses[i].busTakeOffTime << "\t";
        busfile << Buses[i].avialableNoOfSeats << "\t";

        for (int j = 0; j < size_seats; j++)
        {
            busfile << Buses[i].isBooked[j];
        }
        busfile << endl;
    }

    busfile.close();
}

void ticketsetup() {
    fstream ticketsfile("tickets.txt");
    int ID, BN, TR;
    string D, F, U;
    float TOT;
    if (ticketsfile.is_open())
    {
        //cout << " ticketsfile opened successfuly\n";
        int i = 0;
        while (ticketsfile >> ID >> BN >> F >> D >> TOT >> U) {
            tickets[i].ID = ID;
            tickets[i].busNumber = BN;
            tickets[i].from = F;
            tickets[i].destination = D;
            tickets[i].TakeOffTIme = TOT;
            tickets[i].user = U;
            i++;
        }
    }
    else {
        cout << "error occured";
    }
    ticketsfile.close();
}

void saveticketdata() {
    fstream ticketsfile("tickets.txt");
    for (int i = 0; i < size_tickets; i++)
    {
        ticketsfile << tickets[i].ID << "\t";
        ticketsfile << tickets[i].busNumber << "\t";
        if (tickets[i].from == "-")
        {
            ticketsfile << "-\t";
        }
        else {
            ticketsfile << tickets[i].from << "\t";
        }
        if (tickets[i].destination == "-")
        {
            ticketsfile << "-\t";
        }
        else {
            ticketsfile << tickets[i].destination << "\t";
        }
        ticketsfile << tickets[i].TakeOffTIme << "\t";
        ticketsfile << tickets[i].user << "\n";
    }
    ticketsfile.close();
}

bool check_bus_num(int& bus_num) {
    bool Same = false;
    for (int i = 0; i < Size_buses; i++)
    {
        if (bus_num == Buses[i].busNumber)
        {
            cout << "Bus number already exists - please enter another number\n";
            Same = true;
            break;
        }
    }

    return Same;
}

void insert_bus() {
    int bus_idx, bus_num;
    bool isFound = false;

    for (int i = 0; i < Size_buses; i++)
    {
        if (Buses[i].busNumber == 0)
        {
            bus_idx = i;
            isFound = true;
            break;
        }
    }
    if (isFound) {
       
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        
        cout << "Enter bus number: ";
        cin >> bus_num;
        insert_bus:
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "Invalid input - please enter numbers only\n";
            goto insert_bus;
        }

        bool same = check_bus_num(bus_num);
        while (same)
        {
            cout << "Enter bus number: ";
            cin >> bus_num;
            same = check_bus_num(bus_num);
        }
        Buses[bus_idx].busNumber = bus_num;
        cout << "From: ";
        cin >> Buses[bus_idx].from;
        cout << "To: ";
        cin >> Buses[bus_idx].destination;
        cout << "Bus take off : ";
        cin >> Buses[bus_idx].busTakeOffTime;
        cout << "\n\n\tAdded sucsesfully\n\n";
        Buses[bus_idx].avialableNoOfSeats = size_seats;
    }

    else {
        cout << "Error - Buses are complete \n";
    }

}


void personsetup() {
    fstream person;
    person.open("persondata.txt");
    string N, P;
    bool iA;
    if (person.is_open()) {
        //cout << "persondata opened succesfully\t";
        int i = 0;
        while (person >> N >> P >> iA) {
            Persons[i].name = N;
            Persons[i].password = P;
            Persons[i].isAdmin = iA;
            i++;
        }
    }
    else {
        cout << "error persondata\t";
    }
}

void display_seats_status_and_num(int& i) {
    for (int j = 1; j <= size_seats; j++)
    {
        if (Buses[i].isBooked[j - 1] == 0)
            cout << "Seat No: " << j << " -> Empty" << "\t";
        else
            cout << "Seat No: " << j << " -> Booked" << "\t";

        if (j % 4 == 0)
            cout << endl;
    }
}

int get_bus_idx(int& seat_idx) {
    bool isFound = false;
    int bus_idx;
    for (int i = 0; i < Size_buses; i++)
    {
        if (Buses[i].isBooked[seat_idx]) {
            isFound = true;
            bus_idx = i;
            break;
        }
        else
            isFound = false;
    }
    if (isFound)
        return bus_idx;
    else
        return -1;
}

void personsave() {
    fstream person("persondata.txt");
    for (int i = 0; i < Size_Persons; i++)
    {
        person << Persons[i].name << "\t";
        person << Persons[i].password << "\t";
        person << Persons[i].isAdmin << "\n";
    }
    person.close();
}
void view_alltickets() {
    cout << "\n number of buses you booked: " << Persons[user_idx].noOfBussesBooked << "\t Number of seats you booked: " << Persons[user_idx].noOfSeatsBooked << endl;
    for (int i = 0; i < size_tickets; i++)
    {
        if (tickets[i].user == Persons[user_idx].name)
        {
            cout << "-----------------------------------\n";
            cout << " id : " << tickets[i].ID << "\t\t";
            cout << "bus number  :  " << tickets[i].busNumber << endl;
            cout << "From : " << tickets[i].from << "\t\t";
            cout << "To : " << tickets[i].destination << endl;
            cout << "take off : " << tickets[i].TakeOffTIme << endl;
            cout << "seat number : " << tickets[i].seat_number << endl;

        }
    }
}

void bus_status()
{
    for (int i = 0; i < Size_buses; i++)
    {
        if (Buses[i].avialableNoOfSeats == 0)

            Buses[i].bus_isavialable = false;

        else
            Buses[i].bus_isavialable = true;
    }
}
void delete_bus() {
    char choice;
    int num, bus_idx;
    bool check = false;
    cout << "Enter the number of bus you want to delete :";
    cin >> num;
    for (size_t i = 0; i < Size_buses; i++)
    {
        if (num == Buses[i].busNumber)
        {
            bus_idx = i;
            Buses[bus_idx].busNumber = 0;
            Buses[bus_idx].numberOfSeats = 0;
            Buses[bus_idx].avialableNoOfSeats = 0;
            Buses[bus_idx].busTakeOffTime = 0;
            for (size_t j = 0; j < size_seats; j++)
            {
                Buses[bus_idx].isBooked[j] = 0;
            }
            Buses[bus_idx].from = "-";
            Buses[bus_idx].destination = "-";
            cout << "Delete has been made \n";
            check = true;
            break;
        }
    }
    if (check == false) {
        cout << "invalid number - do you want to try again (y/n) \n";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
            delete_bus();
    }

}

// 1- Allow new user to reigster an account in the sign in page (independant function)
// 2- Allow admin to cancel a specific bus (independant function)
// 3- Allow user to view all tickets 
// 4- Fix person and ticket files (modify progress)
// 5- Add to and from destination and date data 
// 6- Redesign UI
// 7- Add bus status (filled or available)