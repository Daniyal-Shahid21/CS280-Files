#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

enum shipType {cruise, cargo};
#include  "ship.h"
#include "cargo.h"
#include  "cruise.h"


using namespace std;

int main(int argc, char *argv [])
{

    ifstream file;
    vector< Ship * > ShipList;

    vector< Ship * >::iterator listitr;
    Cruise *boat;
    Cargo *vessel;

    string shipname;
    int type, load, year;
    shipType shType;

    if( argc >= 2 ) {

        file.open(argv[1]);
        if( !file)
        {
            /* error */
            cerr << "File cannot be opened: " << argv[1] << endl;
            exit (1);
        }

    }
    else
    {
        cerr << "No file is found." << endl;
        exit (1);
    }

    while (file >> shipname >> type >> year >> load )
    {
        //cout << type << " " << shipname << " " << load << endl;
        file.ignore();

        if(type == 1)
        {
            //Cruise
            boat = new Cruise();
            boat->setShYear(year);
            boat->setShName(shipname);
            boat->setmaxPassengers(load);
            ShipList.push_back(boat);

            boat->print();

        }
        else if(type == 2)
        {
            //Cargo
            vessel = new Cargo(shipname, year);
            vessel->setCapacity(load);
            ShipList.push_back(vessel);

            vessel->print();
        }
        else
        {

        }
    }

    cout << "List of Ships:" << endl ;

    for ( int i = 0; i < ShipList.size(); i++ )
    {
        cout<< "Ship Type: " ;
        shType = ShipList[i]->getShType();
        if(shType == cruise)
            cout<< "Cruise";
        else
            cout << "Cargo";
        cout<<endl;
        ShipList[i]->print();
    }
    file.close();
    return 0;
}