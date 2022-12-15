#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

/* Hi I'm Maria Kailahti and this is my hotel room project.
I've asked my tutors and friends for assistance and inspiration and gotten inspiration them (special shoutout to my amazing tutors)
I've also watched a lot of youtube videos how to use vectors and cin.(smthg) functions cause i've been told to use them.
This has been a fun project to do since it was challenging to learn a lot of new information and combining with the information i've already learned.
*/

struct Client
{
    string name;
    int bookingnumb;
    int nightiez;
    int roomnumb;
};

vector<Client> client(4);
// vectors are basically arrays that can change their size => in this program im able to store clients' bookings
// the amount of variables must be inside the brackets.

struct Room
{
    int number;
    int type;
    float price;
    bool free;
    string Pokemon;
    Client client;
};

// Functions for the program to make it easier to understand what's going on

void program(vector<Room>&, vector<Client>&);                          // The program starts with a loop, which the client can exit when entering 0 or all rooms are full.
int IchooseYouPikachu();                                               // This asks the user what they would like to do in the very beginning of the program.
int checkAvailability(vector<Room>);                                   // Checks if any rooms are available at the beginning of the program.
void whatwillPikachudo(vector<Room>&, vector<Client>&, int, int);      // This will return the amount of free rooms. and if the hotel is booked it then returns to the function where u can choose options.
void bookings(vector<Room>&, vector<Client>&, int);                    // Main function for reserving rooms.
bool available(vector<Room>, int);                                     // Returns true if the room is free.
bool typeAvailability(vector<Room>, int);                              // Returns true if there's min. 1 free room of the chosen room type.
bool booked(vector<Room>);                                             // Returns true if all the rooms are free
int choosetype(vector<Room>);                                          // Returns the room type aka single (1) or double (2).
int roomselection();                                                   // Asks the user if they wanna decide on the room number themselves or not.
int randomsandomroomiewoomie(vector<Room>&, int);                      // If the computer decides the users room, it returns a random integer depending on the room type
int clientchoosestomanuallyselecttheroom(vector<Room>&, int);          // Returns a room number that the user chose.
string whatPokemon();                                                  // Client chooses a Pokemon theme for their room.
void istheroomfreeornauwr(vector<Room>);                               // Returns true if  the room is free or not.
float discountchecker(Room, Client);                                   // Returns a discount depending on the situation.
float calculatetheprice(float, int, float);                            // Returns the price.
void checkout(vector<Room>&, vector<Client>&);                         // Check out for the client and prints invoice and sets the room available for other clients.
void Invoice(vector<Room>, vector<Client>, int);                       // Prints an invoice to the user with their information of the reservation.

vector<Room> hotel(6);
// there needs to be 6 inside the vector thingie cuz it works that way and otherwise it doesn't work idk
void Invoice(vector<Room> hotel, vector<Client> client, int room);

void errorMessage()
{
    cout << "Error! input.exe not found. \nPlease, try to do that properly" << endl;
    cin.clear();
    cin.ignore(256, '\n');
}
// I had the error message multiple times written in this program. This is a simpler way to put it without the code repeating the same thing too often.
/*
 * The error message comes in handy when the user adds non numbers or weird combinations of things.
 * The error message tells the user that their input was not understood  therefore, the users gotta try again
 * this error message doesn't work with number combos tho :C
 * however with number combos that are not apart of the program; the program will continue by repeating the same function when asking for a number for x reason
 */

bool booked(vector<Room> hotel)
{
    int istheroomtaken = 0;
    // is hotel booked or not
    for (int i = 0; i < hotel.size(); i++)
    {
        // loop, checking every room if its booked
        if (hotel[i].free == false)
        {
            istheroomtaken++;
        }
    }
    if (istheroomtaken == 0)
        return true;
    // if the result is 0 = hotel's not booked
    return false;
}

bool available(vector<Room> hotel, int roomnumero)
{ // returns true or false if the room is available
    if (hotel[roomnumero - 1].free)
        return true;
    return false;
}

int checkAvailability(vector<Room> hotel)
{
    // returns the number of rooms available and if 0, then the hotel is booked uwu
    int availability = 0;
    for (int i = 0; i < hotel.size(); i++)
    {
        if (hotel[i].free == true)
        {
            availability++;
        }
    }
    return availability;
}

float discountchecker(Room room, Client client)
{
    /* Discounts: from 0 to 4 nights it's 0%
    from 5 to 9 nighs it's 5%
    and over 10 nights it's 10%
    Discount is doubled if it's a double room
    returns the discount as either 0 or 0.1 or 0.2
    */
    float discount;

    if (client.nightiez >= 10)
    {
        discount = 0.1;
    }
    else if (client.nightiez >= 5)
    {
        discount = 0.05;
    }
    else if (client.nightiez < 5)
    {
        return 0;
    }

    if (room.type == 2)
    {
        return (discount * 2);
    }

    return discount;
}

float calculatetheprice(float price, float discount, int nights)
{
    float discountedPrice;

    discountedPrice = price * (static_cast<float>(nights)) * (1.0 - discount);
    // it calculates the price
    return discountedPrice;
    // static_cast returns a value of type. it forces one data type to be converted into another data type
    // yes i googled that because i didnt know how to explain it myslf in my own words yolo
}

bool typeAvailability(vector<Room> hotel, int input)
{
    // checks if any room type is available *gasp*
    int checkRoomAvailability = 0;

    if (input == 1)
    {
        for (int x = 0; x < hotel.size(); x += 2)
        {
            if (hotel[x].free)
            {
                checkRoomAvailability++;
            }
        }
    }

    if (input == 2)
    {
        for (int x = 1; x < hotel.size(); x += 2)
        {
            if (hotel[x].free)
            {
                checkRoomAvailability++;
            }
        }
    }
    // u know.. yea it does two things thing
    if (checkRoomAvailability == 0)
    {
        return false;
    }

    return true;
}

int choosetype(vector<Room> hotel)
{ // basically returns the room you've chosen aka double or single uwu
    int input;
    int yezornauwr;
    // yezornauwr sounds stupid but it just means yes or no.
    // basically its the variable that asks the user if they wanna continue the program or not
    do
    {
        cout << "What room would you like to have: a single room or a double room?" << endl // asks the user what room they wanna have
            << "Choose 1 for single room \nChoose 2 for double room." << endl
            << "Choose 0 to DEGUGHI (EXIT)." << endl;
        // I wanted to include Japanese in the program since the hotel is located in Tokyo.
        // I did add translation to deguchi (exit) so it would be less confusing to the user.
        cin >> input;
        while (cin.fail())
        {
            // cin.fail is there to check if its an integer or not, if not user will get this response:
            errorMessage();
            cin >> input;
        }

        if (input == 0)
        {
            return 0;
        }

    } while (input != 1 && input != 2);
    // gonna check that the input would be correct

    // if (input == 1)
    // {
    //     // if no single rooms are available the program will ask the client if they want to select another room perhaps??
    //     do
    //     {

    //         cout << "Unfortunately single rooms aren't available at the moment." << endl
    //              << "Would you like to book a double room instead or not make a reservation at all?" << endl
    //              << "Choose 1 to continue, and choose 0 to stop making reservations." << endl;
    //         cin >> yezornauwr;
    //         while (cin.fail())
    //         {
    //             errorMessage();
    //             cin >> yezornauwr;
    //         }
    //     } while (yezornauwr != 0 && yezornauwr != 1);
    //     if (yezornauwr == 0)
    //     {
    //         return 0;
    //     }
    //     input = 2;
    // }
    // /*
    //  * Evaluates the condition aka in the upper one its single rooms, if not available it asks the user if they wanna book another room instead
    //  * The error message comes in handy when the user adds non numbers or weird combinations of things.
    //  * The error message tells the user that their input was not understood  therefore, the users gotta try again
    //  * Same goes for the code below but for double rooms. uwu
    //  */
    // else if (input == 2)
    // {
    //     do
    //     {
    //         cout << "Unfortunately double rooms aren't available at the moment." << endl
    //              << "Would you like to book a single room instead or not make a reservation at all?" << endl
    //              << "Choose 1 to continue, and choose 0 to stop making reservations." << endl;
    //         cin >> yezornauwr;
    //         while (cin.fail())
    //         {
    //             errorMessage();
    //             cin >> yezornauwr;
    //         }
    //     } while (yezornauwr != 0 && yezornauwr != 1);
    //     if (yezornauwr == 0)
    //     {
    //         return 0;
    //     }
    //     input = 1;
    // }
    // has an issue didnt have time to figure out how to fix it

    return input;
}

int roomselection()
{
    int input;
    do
    {
        cout << "Would you like to your room to be selected by the program or would you like to choose it yourself? \n Press 1 if you would like to decide yourself, \n Press 2  for automatic selection " << endl;
        cin >> input;
        while (cin.fail())
        {
            errorMessage();
            cin >> input;
        }
    } while (input != 1 && input != 2);

    return input;
}
// Quite self explanatory. program asks if the user wants the program to decide on their room or do they wanna do it themselves.

int randomsandomroomiewoomie(vector<Room>& hotel, int type)
{ // the random room selection thingie if u want the program to decide it uwu
    int roomnbr;
    if (type == 1)
    {
        do
        {
            roomnbr = 2 * (rand() % hotel.size() / 2) + 1;
        } while (!(available(hotel, roomnbr)));
    }
    else if (type == 2)
    {
        do
        {
            roomnbr = 2 * (rand() % hotel.size() / 2 + 1);
        } while (!(available(hotel, roomnbr)));
    }

    cout << "Your room number is: " << roomnbr << endl;
    return roomnbr;
}

int clientchoosestomanuallyselecttheroom(vector<Room>& hotel, int type)
{
    int roomnumb;
    // asking for the room number what they chose and it checks if its an integer or not
    do
    {
        if (type == 1)
        {
            do
            {
                cout << "Single rooms are odd numbered" << endl
                    << "Which will you book?" << endl;
                cin >> roomnumb;
                while (cin.fail())
                { // cin.fail works the same way as in before
                    errorMessage();
                    cin >> roomnumb;
                }
            } while (roomnumb <= 0 && printf("Error! wrong number, please choose again.\n") || roomnumb % 2 == 0 && printf("Error! wrong number, please choose again.\n") || roomnumb > (hotel.size() + 1) && printf("Error! wrong number, please choose again.\n"));
            // I use printf cause its inside the while statement. i tried to use cout but it didnt work uwu plus it checks if the room is odd numbered
        }
        else if (type == 2)
        {
            do
            {
                cout << "Double rooms are even numbered" << endl
                    << "Which room will you book?" << endl;
                cin >> roomnumb;
                while (cin.fail())
                {
                    errorMessage();
                    cin >> roomnumb;
                }
            } while (roomnumb <= 0 && printf("Error! wrong number, please choose again.\n") || roomnumb % 2 != 0 && printf("Error! wrong number, please choose again.\n") || roomnumb > (hotel.size() + 1) && printf("Error! wrong number, please choose again.\n"));
            // checks if the room is even numbered
        }
    } while (!(available(hotel, roomnumb)) && printf("Unfortunately this room is not available, please choose another room.\n"));

    return roomnumb;
}

string whatPokemon()
{
    int selectedPokemon;
    string selectedPokemonString;
    do
    {
        cout << "What Pokemon theme would you like to choose for your room? (Enter the number)" << endl
            << "1. Pikachu." << endl
            << "2. Snorlax." << endl
            << "3. Eevee." << endl
            << "4. Clefairy." << endl;
        cin >> selectedPokemon;
        while (cin.fail())
        {
            errorMessage();
            cin >> selectedPokemon;
        }
    } while (selectedPokemon < 0 || selectedPokemon > 4);
    if (selectedPokemon == 1)
    {
        selectedPokemonString = "Pikachu";
    }
    else if (selectedPokemon == 2)
    {
        selectedPokemonString = "Snorlax";
    }
    else if (selectedPokemon == 3)
    {
        selectedPokemonString = "Eevee";
    }
    else
    {
        selectedPokemonString = "Clefairy";
    }
    return selectedPokemonString;
    // asks what pokemon themed hotel room the client wants to stay in uwu
}

void bookings(vector<Room>& hotel, vector<Client>& client, int clientnumb)
{

    string name;
    int nights;
    int type;
    int roomnumb;
    int yezornnauwr;
    int available = 0;
    string selectedPokemon;
    // asks the user if its a single room or not.
    type = choosetype(hotel);

    if (type == 0)
    { // if the user doesn't want to proceed with the booking
        return;
    }

    int roomselectionz = roomselection();

    switch (roomselectionz)
    {
    case 1:
        roomnumb = clientchoosestomanuallyselecttheroom(hotel, type);
        break;
    case 2:
        roomnumb = randomsandomroomiewoomie(hotel, type);
        break;
    }
    selectedPokemon = whatPokemon();
    // asks how many nights staying
    do
    {
        cout << "How long will you be staying in our hotel?" << endl;
        cin >> nights;
        while (cin.fail())
        {
            errorMessage();
            cin >> nights;
        }
    } while (nights < 1 && printf("Unfortunately it is not possible to stay less than 1 night, please try again, thank you.\n") || nights > 300 && printf("Too many nights lool, just buy a house instead :)\n"));

    // for the bookings we need the clients name obviously so here we gon ask.
    cout << "Write your full name, please." << endl;
    cin.ignore();
    getline(cin, name);
    // to store all the info cuz we popularrrr

    srand((unsigned int)time(NULL)); // database basically
    client[clientnumb].bookingnumb = rand() % 89999 + 10000;
    client[clientnumb].name = name;
    client[clientnumb].roomnumb = roomnumb;
    client[clientnumb].nightiez = nights;

    hotel[roomnumb - 1].client = client[clientnumb];
    hotel[roomnumb - 1].free = false;
    hotel[roomnumb - 1].Pokemon = selectedPokemon;

    cout << endl
        << "Thank you, " << hotel[roomnumb - 1].client.name << ", Your room number is " << roomnumb << "\nYour booking number is " << hotel[roomnumb - 1].client.bookingnumb << ". You'll need to remember this for checkout!" << endl
        << endl;
}

void istheroomfreeornauwr(vector<Room> hotel)
{ // prints if the room is free or nauwwrrr
    int numberfortheroom;

    do
    {
        cout << "Please enter the number of the room: (Enter 0 to exit)" << endl;
        cin >> numberfortheroom;
        while (cin.fail())
        {
            cout << "Error! input.exe not found. \nPlease, choose a number from 1 to " << hotel.size() << ": ";
            // not using the error message here cause i wanted to add the amount of rooms the hotel has owo
            cin.clear();
            cin.ignore(256, '\n');
            cin >> numberfortheroom;
        }

        if (numberfortheroom == 0)
            return;

    } while (numberfortheroom < 1 || numberfortheroom > hotel.size());

    if (available(hotel, numberfortheroom))
        cout << endl
        << "Room number " << numberfortheroom << " is available." << endl
        << endl;
    else if (!available(hotel, numberfortheroom))
        cout << endl
        << "Unfortunately room number " << numberfortheroom << " is not available." << endl
        << endl;
}

void checkout(vector<Room>& hotel, vector<Client>& client)
/*
 * The vector here stores clients' data so the system knows if the rooms are booked or not and
 * if they wanna proceed to checkout which this thing's about, obviously, the program will ask the user for their info
 * so in the future another client is able to book the same room. (after its checked out ofc)
 */
{
    int roomnumb;
    int bookingnumb;

    cout << "To be able to continue your check out, please enter your booking number and room number. (0 to go back)" << endl;
    do
    {
        cout << "Enter your booking number:" << endl;
        cin >> bookingnumb;
        while (cin.fail())
        {
            errorMessage();
            cin >> bookingnumb;
        }

        if (bookingnumb == 0)
            return;

    } while (bookingnumb < 1);

    do
    {
        cout << "Enter your room number:" << endl;
        cin >> roomnumb;
        while (cin.fail())
        {
            cout << "Error! input.exe not found. \nPlease, choose a number from 1 to " << hotel.size() << ": ";
            // again not using the errormessage command cause i wanted to have the amount of rooms to the thingie
            cin.clear();
            cin.ignore(256, '\n');
            cin >> roomnumb;
        }

        if (roomnumb == 0)
            return;

    } while (roomnumb < 1 || roomnumb > hotel.size());

    // checking that the chosen room is actually taken owo.
    if (hotel[roomnumb - 1].free)
    {
        cout << endl
            << "This room is available" << endl
            << endl;
    }
    else if (hotel[roomnumb - 1].client.bookingnumb == bookingnumb)
        // checks that the booking number of the room number entered matches with the booking number entered.
    {

        Invoice(hotel, client, roomnumb);

        client.erase( // deleting the client from the vector
            remove_if(client.begin(), client.end(), [&](Client const& x)
                { return x.roomnumb == roomnumb; }),
            client.end());
        client.push_back(Client()); // adding an empty customer to have still the same amount of possible customers as rooms.
        hotel[roomnumb - 1].free = true;

        cout << endl
            << "Thank you for choosing MIMARU Tokyo, hope you enjoyed the stay.\n"
            << endl;
    }
    else
    {
        cout << endl
            << "ERROR: the booking number you entered for the room doesn't match with system.\n"
            << "~ Returns ~." << endl
            << endl;
    }
}

void Invoice(vector<Room> hotel, vector<Client> client, int room)
{
    // Calculatezz discount price as well as gross price first for it to be easier uwu
    float discount = discountchecker(hotel[room - 1], hotel[room - 1].client);
    float tehprice = hotel[room - 1].price * (static_cast<float>(hotel[room - 1].client.nightiez));

    if (hotel[room - 1].free)
    {
        cout << endl
            << "No one is staying in that room." << endl;
        // before proceeding with the check out u gotta know if the room is free or nott duh
        return;
    }
    // if it is taken, I proceed to print the invoice for the person staying there.
    cout << "\n--------------------------------------------------" << endl
        << "INVOICE \nMIMARU Tokyo Shinjuku West\n3-chome-3-11 Nishishinjuku City \nTokyo 160-0023, Japan" << endl
        << "\nPayer's name: " << hotel[room - 1].client.name << "     Booking number: " << hotel[room - 1].client.bookingnumb << endl
        << "Room: " << room << "\nRoom type: " << hotel[room - 1].type << "\nNights: " << hotel[room - 1].client.nightiez << "\nPokemon theme: " << hotel[room - 1].Pokemon
        << endl
        << endl
        << "PRICE BEFORE DISCOUNT: $" << tehprice
        << endl
        << "DISCOUNT: " << discount * 100 << "%"
        << endl
        << "TOTAL: $" << tehprice - (discount * tehprice)
        << endl
        << "------------------------------------------------------" << endl;
}

int IchooseYouPikachu()
{
    // This asks the user/client what they would like to do in the very beginning of the program
    // You have 4 choices and the exit function
    // after the user/client has chosen what to do the program will continue with the selected choice and continue from there
    int choice;
    do
    {
        cout << "What would you like to do? (Enter the number)" << endl
            << "1. Book a room." << endl
            << "2. Find a room." << endl
            << "3. Checkout." << endl
            << "4. Invoice." << endl
            << "0. Deguchi (EXIT)." << endl;
        cin >> choice;
        while (cin.fail())
        {
            errorMessage();
            IchooseYouPikachu();
        }
    } while (choice < 0 || choice > 4);
    // If the user tries to choose anything above 4 or below 0 or letters, the program will show an error message which is written in other functions
    return choice;
}

void whatwillPikachudo(vector<Room>& hotel, vector<Client>& client, int thechosenone, int clientnumb)
{
    int roomnumb;
    // the program  will return the amount of free rooms if the hotel is booked and then returns to the function where u can choose options (ichooseupikachu).
    switch (thechosenone)
    {
    case 1:
        if (checkAvailability(hotel) == 0)
        {
            cout << "Unfortunately the hotel is fully booked at the moment, we hope to see you again." << endl
                << endl;
            break;
        }
        else
        {
            bookings(hotel, client, clientnumb);
            break;
        }
    case 2:
        istheroomfreeornauwr(hotel);
        break;
    case 3:
        checkout(hotel, client);
        break;
    case 4:
        if (booked(hotel))
        {
            cout << "No one is staying in the hotel at the moment so, unfortunately invoices can't be printed.\n";
            break;
        }

        do
        {
            cout << "Enter the room number, please: (Press 0 to go back)\n";
            cin >> roomnumb;
            while (cin.fail())
            {
                errorMessage();
                cin >> roomnumb;
            }
        } while (roomnumb < 0 || roomnumb > hotel.size());

        if (roomnumb == 0)
        {
            break;
        }

        Invoice(hotel, client, roomnumb);
        break;
    }
}

void program(vector<Room>& hotel, vector<Client>& client)
{
    // Starts the program and handles all the function callings.
    int IchooseYou;
    int clientnumb = 0;

    cout << endl
        << "Welcome to the MIMARU Tokyo Pokemon Hotel Service where you can stay in a room with Pokemon!" << endl
        << "Our hotel has " << hotel.size() << " Pokemon themed rooms and our hotel offers single and double rooms." << endl
        << "Our prices are: \n$100 for a single room per night and \n150$ for a double room per night." << endl
        << endl;

    // this loops goes on until the user presses 0 which is the exit function
    while (true)
    {
        if (checkAvailability(hotel) != 0)
            IchooseYou = IchooseYouPikachu();

        // if hotel is full, the program will end.
        if (checkAvailability(hotel) == 0)
        {
            cout << "Unfortunately the hotel is fully booked at the moment, we hope to see you again." << endl;
            break;
        }
        if (IchooseYou == 0)
            break;

        whatwillPikachudo(hotel, client, IchooseYou, clientnumb);

        // this will handle the users every time the loop goes through
        clientnumb++;
    }
}

int main()
{
    // Odd numbers for single room and even numbers for double rooms cause idk makes sense.

    srand((unsigned int)time(NULL));
    // srand for random number generator thingie and here were giving a seed aka starting point to it
    int randomroomcalc = 2 * (rand() % 20 + 20);
    // calculates the rooms and its randomized

    for (int i = 0; i < randomroomcalc; i++)
    {
        // Random number is the vectors max limit
        hotel.push_back(Room());
        // Push back works so the user can add a room
        client.push_back(Client());
        // Here the fuction so u can have as many clients as there are rooms cause sometimes hotels can be fully booked so it makes sense

        hotel[i].number = i + 1;
        if (hotel[i].number % 2 == 0)
        {
            // Even number = Double room = price is 150 dollars
            hotel[i].type = 2;
            hotel[i].price = 150;
            hotel[i].free = true;
        }
        else
        {
            // Odd number = Single room = price is 100 dollars
            hotel[i].type = 1;
            hotel[i].price = 100;
            hotel[i].free = true;
        }
    }

    program(hotel, client);
    // starts the user interface

    cout << "Thank you for visiting! We hope to see you again." << endl;
    return 0;
}