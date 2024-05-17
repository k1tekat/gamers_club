#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Event
{
    int hours;
    int minutes;
};


// время переводить в минуты или секунды и вычитать из большего меньшее
void read_file(string filename);

int main(int argc, char* argv[])
{
    std::cout << argv[1] << std::endl;
    read_file(argv[1]);

}


void read_file(string filename)
{
    std::ifstream indate;
    indate.open(filename,ios::in);

    int table;
    int working_hours_start;
    int working_hours_finish;
    if(indate.is_open())
    {
        indate >> table >>working_hours_start>>working_hours_finish;

    }
    else
    {
        cout<<"file not open"<<endl;
    }
    
    indate.close();
    cout<<table<<endl;
    cout<<working_hours_start<<endl;
    cout<<working_hours_finish;
}