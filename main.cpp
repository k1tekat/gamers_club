#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>

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

    int summ_minut = 0;
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
    bool reserv = 0;
    string username;
    int revenue; //выручка
    Clock busy_time;
};

void read_file(string filename,vector<Event>& event_from_file,Gamers_club& init_club);
void print_time(Clock time);



int main(int argc, char* argv[])
{
    Gamers_club new_club;
    vector<Event> events;
    vector<Table> tables;

    read_file(argv[1],events,new_club);

    tables.resize(new_club.tables);

    queue<string> user_queue;

    cout<<"start working: ";
    print_time(new_club.start_working);
    cout<<endl;


    for(int i = 0; i < events.size(); i++)
    {

        print_time(events[i].clock);
        cout<<"ID:"<<events[i].ID<<" ";
        cout<<events[i].username<<" ";
      

        if(events[i].ID == 1)
        {
            if(events[i].clock.summ_minut<new_club.start_working.summ_minut)
            {
                cout<<endl;
                print_time(events[i].clock);
                cout<<"NotOpenYet"<<" ";
            }
            else
            {
                for(int j = i - 1; j>=0; j--)
                {
                    if ((events[j].username == events[i].username) && (events[j].ID == 1) && (events[j].clock.summ_minut>new_club.start_working.summ_minut)) 
                    {
                        cout<<endl;
                        print_time(events[i].clock);
                        cout<<"YouShallNotPass"<<" ";
                        j=0;
                    } 
                }
            }
            cout<<endl;
        }

        if(events[i].ID == 2)
        {

            if(tables[events[i].table].reserv == 0)
            {
                tables[events[i].table].reserv = true;
                tables[events[i].table].username = events[i].username;
                tables[events[i].table].busy_time = events[i].clock;
            }
            else
            {
                cout<<endl;
                print_time(events[i].clock);
                cout<<"PlacesBusy"<<" ";
            }
            cout<<endl;
        }



        if(events[i].ID == 3)
        {
            for(int j = 0; j< tables.size();j++)
            {
                if(tables[j].reserv == 0)
                {
                    cout<<endl;
                    print_time(events[i].clock);
                    cout<<"ICanWaitNoLonger!"<<" ";
                    break;
                }
                else
                {
                    if(user_queue.size()!=  tables.size())
                    {
                        cout<<"      "<<user_queue.size()<<"  ";
                        user_queue.push(events[i].username);
                    }
                    else
                    {
                    cout<<endl;
                    print_time(events[i].clock);
                    cout<<"ID:11"<<" ";
                    cout<<events[i].username<<" ";
                    }
                    break;
                }
            }
            cout<<endl;
        }

        if(events[i].ID == 4)
        {
            cout<<endl;
        }
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

        init_club.start_working.b_hour = working_hours[0]-48;
        init_club.start_working.s_hour = working_hours[1]-48;
        init_club.start_working.b_min = working_hours[3]-48;
        init_club.start_working.s_min = working_hours[4]-48;

        init_club.finish_working.b_hour = working_hours[6]-48;
        init_club.finish_working.s_hour = working_hours[7]-48;
        init_club.finish_working.b_min = working_hours[9]-48;
        init_club.finish_working.s_min = working_hours[10]-48;

        init_club.start_working.summ_minut = 
        (init_club.start_working.b_hour*600)+
        (init_club.start_working.s_hour*60)+
        (init_club.start_working.b_min*10)+
        init_club.start_working.s_min;


        init_club.finish_working.summ_minut = 
        (init_club.finish_working.b_hour*600)+
        (init_club.finish_working.s_hour*60)+
        (init_club.finish_working.b_min*10)+
        init_club.finish_working.s_min;

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

            event_from_file[iter].clock.summ_minut = 
            (event_from_file[iter].clock.b_hour*600)+
            (event_from_file[iter].clock.s_hour*60)+
            (event_from_file[iter].clock.b_min*10)+
            event_from_file[iter].clock.s_min;
        
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
    cout<<time.b_hour<<time.s_hour<<":"<<time.b_min<<time.s_min<<" ";
}