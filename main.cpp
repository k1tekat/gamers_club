#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

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
    string username;
    int table = 0;

};

struct Table
{
    char username[20];
    int revenue;
    Clock busy_time;
};

void read_file(string filename,vector<Event>& event_from_file,Gamers_club& init_club);
void print_time(Clock time);

int main(int argc, char* argv[])
{
    Gamers_club new_club;
    vector<Event> events;
    read_file(argv[1],events,new_club);

    cout<<"start working: ";
    print_time(new_club.start_working);

    cout<<endl;

    for(int i = 0; i < events.size(); i++)
    {

        print_time(events[i].clock);
        cout<<events[i].username<<endl;
        cout<<"ID:"<<events[i].ID<<endl;

        if(events[i].ID == 1)
        {
            if(events[i].clock.summ_minut<new_club.start_working.summ_minut)
            {
                cout<<"NotOpenYet"<<endl;
            }


            for(int j = i - 1; j>=0; j--)
            {
                if ((events[j].username == events[i].username) && (events[j].ID == 1)) 
                {
                    cout<<"YouShallNotPass"<<endl;
                    j=0;
                } 
            }
        }
        cout<<endl;
    }
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

        indate.seekg(20,ios::beg);
        event_from_file.resize(14); //ДОБАВИТЬ ИТЕРАТОР ДЛЯ ДИНАМИКИ
        int iter = 0;
        while (iter < 14) //ДОБАВИТЬ УСЛОВИЕ 
        {   
            char time[5];

            indate.read(time,6);
            event_from_file[iter].clock.b_hour = time[0]-48;
            event_from_file[iter].clock.s_hour = time[1]-48;
            event_from_file[iter].clock.b_min = time[3]-48;
            event_from_file[iter].clock.s_min = time[4]-48;
        
            //print_time(event_from_file[iter].clock);

            // cout<<endl;
            // for (int i = 0; i <=5; i++)
            // {
            //     cout<<" "<<time[i]<<" ";
            // }
            // cout<<endl;

            indate >> event_from_file[iter].ID;
            //cout <<"ID: "<< event_from_file[iter].ID<<endl;
            indate >> event_from_file[iter].username;
            //cout <<"username: "<< event_from_file[iter].username<<endl;



            if(event_from_file[iter].ID == 2)
            {
                indate >> event_from_file[iter].table;
                //cout<<"table: "<< event_from_file[iter].table<<endl;
            }
            else
            {
                //cout<<"";
            }

            iter++;
            indate.seekg(2,ios::cur);
            //cout<<endl;
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