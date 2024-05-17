#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


struct Clock
{

    int b_hour;
    int s_hour;
    int b_min;
    int s_min;

    // uint8_t b_hour;
    // uint8_t s_hour;
    // uint8_t b_min;
    // uint8_t s_min;

    int summ_minut = b_hour*600+s_hour*60+b_min*10+s_min;
};

struct Gamers_club
{
    int tables;
    Clock start_working;
    Clock finish_working;
    int price;
};

struct Event
{
    Clock clock;
    int ID;
    char username[20];
    int table = 0;

};

struct Table
{
    char username[20];
};


// время переводить в минуты или секунды и вычитать из большего меньшее
void read_file(string filename,vector<Event>& event_from_file,Gamers_club& init_club);
void print_time(Clock time);

int main(int argc, char* argv[])
{
    Gamers_club new_club;
    vector<Event> events;
    read_file(argv[1],events,new_club);

    // cout<<"tables:"<<new_club.tables<<endl;
    // print_time(new_club.start_working);
    // print_time(new_club.finish_working);
    


}


void read_file(string filename,vector<Event>& event_from_file,Gamers_club& init_club)
{
    std::ifstream indate;
    indate.open(filename,ios::in);

    int table;
    char working_hours[11];
    if(indate.is_open())
    {
        indate >> init_club.tables;
        
        indate.seekg(3,ios::beg);
        indate.read(working_hours,11);

        indate >> init_club.price;
        //cout<<"price: "<<init_club.price<<"   ";

        init_club.start_working.b_hour = working_hours[0]-48;
        init_club.start_working.s_hour = working_hours[1]-48;
        init_club.start_working.b_min = working_hours[3]-48;
        init_club.start_working.s_min = working_hours[4]-48;

        init_club.finish_working.b_hour = working_hours[6]-48;
        init_club.finish_working.s_hour = working_hours[7]-48;
        init_club.finish_working.b_min = working_hours[9]-48;
        init_club.finish_working.s_min = working_hours[10]-48;

        //cout<<init_club.start_working.b_hour<<init_club.start_working.s_hour<<":"<<init_club.start_working.b_min<<" "<<init_club.start_working.s_min<<endl;
        //cout<<(int)working_hours[0]<<" "<<(int)working_hours[1]<<":"<<(int)working_hours[3]<<" "<<(int)working_hours[4]<<endl;


        // char time[4];
        // event_from_file.resize(1);
        // indate.seekg(20,ios::beg);
        
        // indate.read(time,5);
        // event_from_file[0].clock.b_hour = time[0]-48;
        // event_from_file[0].clock.s_hour = time[1]-48;
        // event_from_file[0].clock.b_min = time[3]-48;
        // event_from_file[0].clock.s_min = time[4]-48;
        
        // print_time(event_from_file[0].clock);

        // indate >> event_from_file[0].ID;
        // cout <<"ID: "<< event_from_file[0].ID<<endl;
        // indate >> event_from_file[0].username;
        // cout <<"username: "<< event_from_file[0].username<<endl;

        // if(event_from_file[0].ID == 2)
        //     indate >> event_from_file[0].table;
        // cout<< event_from_file[0].table;

        indate.seekg(20,ios::beg);
        event_from_file.resize(100);
        int iter = 0;
        while (iter <= 20)
        {
            
            char time[4];
            
            
        
            indate.read(time,5);
            event_from_file[iter].clock.b_hour = time[0]-48;
            event_from_file[iter].clock.s_hour = time[1]-48;
            event_from_file[iter].clock.b_min = time[3]-48;
            event_from_file[iter].clock.s_min = time[4]-48;
        
            print_time(event_from_file[iter].clock);

            indate >> event_from_file[iter].ID;
            cout <<"ID: "<< event_from_file[iter].ID<<endl;
            indate >> event_from_file[iter].username;
            cout <<"username: "<< event_from_file[iter].username<<endl;

            if(event_from_file[iter].ID == 2)
            {
                indate >> event_from_file[iter].table;
                cout<<"table: "<< event_from_file[iter].table<<endl;
            }
            else
            {
                cout<<"";
            }

            iter++;
            indate.seekg(2,ios::cur);
        }
        








    }
    else
    {
        cout<<"file not open"<<endl;
    }
    
    indate.close();
}

void print_time(Clock time)
{
    cout<<time.b_hour<<time.s_hour<<":"<<time.b_min<<time.s_min<<endl;
}

