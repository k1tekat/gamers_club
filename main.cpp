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
    bool reserv = false;
    string username;
    int revenue; //выручка
    Clock busy_time;
    Clock revenue_time;
};

void read_file(string filename,vector<Event>& event_from_file,Gamers_club& init_club);
void print_time(Clock time);
bool find_user(string username, queue<string> user_queue);





int main(int argc, char* argv[])
{
    Gamers_club new_club;
    vector<Event> events;
    vector<Table> tables;

    read_file(argv[1],events,new_club);

    tables.resize(new_club.tables);

    queue<string> user_queue; 

    print_time(new_club.start_working);
    cout<<endl;

    for(int i = 0; i < events.size(); i++)
    {

        print_time(events[i].clock);
        cout<<""<<events[i].ID<<" ";
        cout<<events[i].username<<" ";
      

        if(events[i].ID == 1)
        {
            if(events[i].clock.summ_minut<new_club.start_working.summ_minut)
            {
                cout<<endl;
                print_time(events[i].clock);
                cout<<"13 NotOpenYet"<<" ";
            }
            else
            {
                for(int j = i - 1; j>=0; j--)
                {
                    if ((events[j].username == events[i].username) && (events[j].ID == 1) && (events[j].clock.summ_minut>new_club.start_working.summ_minut)) 
                    {
                        cout<<endl;
                        print_time(events[i].clock);
                        cout<<"13 YouShallNotPass"<<" ";
                        j=0;
                    } 
                }
            }
            cout<<endl;
        }

        if(events[i].ID == 2)
        {
            cout<<events[i].table;
            if(tables[events[i].table-1].reserv == 0)
            {
                tables[events[i].table-1].reserv = true;
                tables[events[i].table-1].username = events[i].username;
                tables[events[i].table-1].busy_time.summ_minut = events[i].clock.summ_minut;  

            }
            else
            {
                cout<<endl;
                print_time(events[i].clock);
                cout<<"13 PlacesBusy"<<" ";

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
                    cout<<"13 ICanWaitNoLonger!"<<" ";
                    break;
                }
                else
                {
                    if(user_queue.size()!=  tables.size())
                    {
                        user_queue.push(events[i].username);
                    }
                    else
                    {
                    cout<<endl;
                    print_time(events[i].clock);
                    cout<<"11"<<" ";
                    cout<<events[i].username<<" ";
                    }
                    break;
                }
            }
            cout<<endl;
        }

        if(events[i].ID == 4)
        {
            for(int j = 0; j < tables.size(); j++)
            {
                if ((events[i].username == tables[j].username) || (find_user(events[i].username,user_queue)))
                {
                    if(events[i].username == tables[j].username)
                    {

                        if(user_queue.size() == 0)
                        {
                            tables[j].revenue_time.summ_minut = tables[j].revenue_time.summ_minut + (events[i].clock.summ_minut - tables[j].busy_time.summ_minut);
                            tables[j].revenue = tables[j].revenue + (int((events[i].clock.summ_minut - tables[j].busy_time.summ_minut)/60)*new_club.price);
                            (events[i].clock.summ_minut - tables[j].busy_time.summ_minut)%60 >0? tables[j].revenue+=10:false;
                            tables[j].reserv=false;
                            tables[j].username = "";
                        }
                        else
                        {
                            tables[j].revenue_time.summ_minut = tables[j].revenue_time.summ_minut + (events[i].clock.summ_minut - tables[j].busy_time.summ_minut);
                            tables[j].revenue = tables[j].revenue + (int((events[i].clock.summ_minut - tables[j].busy_time.summ_minut)/60)*new_club.price);
                            (events[i].clock.summ_minut - tables[j].busy_time.summ_minut)%60 >0? tables[j].revenue+=10:false;
                            tables[j].busy_time.summ_minut = events[i].clock.summ_minut; 
                            tables[j].username = user_queue.front();
                            user_queue.pop();

                            cout<<endl;
                            print_time(events[i].clock);
                            cout<<"12"<<" ";
                            cout<<events[i].username<<" "<<j+1;

                        }
                    }
                    break;
                }
                else
                {
                    if(j == tables.size()-1)
                    {
                        cout<<endl;
                        print_time(events[i].clock);
                        cout<<"13 ClientUnknow"<<" ";
                        break;
                    }

                }
            }
            cout<<endl;
        }

        if (i == events.size()-1)
        {
            vector<string> last_users;
            last_users.resize(new_club.tables);

            for(int j = 0; j< tables.size();j++)
            {
                last_users[j] = tables[j].username;
            }

            while (!user_queue.empty())
            {
                last_users.push_back(user_queue.front());
                user_queue.pop();
            }

            sort(last_users.begin(),last_users.end());
            

            for(string j : last_users)
            {
                if(j != "")
                {
                print_time(new_club.finish_working);
                cout<<"11 ";
                cout<<j<<endl;
                }

            }
            print_time(new_club.finish_working);
            cout<<endl;



            for (int j = 0; j < tables.size(); j++)
            {
                if(tables[j].reserv != 0)
                {
                    
                    tables[j].revenue_time.summ_minut = new_club.finish_working.summ_minut - tables[j].busy_time.summ_minut;
                    tables[j].revenue = tables[j].revenue + (int((new_club.finish_working.summ_minut - tables[j].busy_time.summ_minut)/60)*new_club.price);
                    (new_club.finish_working.summ_minut - tables[j].busy_time.summ_minut)%60 >0? tables[j].revenue+=10:false;
                    tables[j].reserv=false;
                    tables[j].username = "";
                }
                
            }

            for(int j = 0; j< tables.size();j++)
            {
                Clock last_time;
                last_time.b_hour = (tables[j].revenue_time.summ_minut/60)/10;
                last_time.s_hour = (tables[j].revenue_time.summ_minut/60)%10;
                last_time.b_min = (tables[j].revenue_time.summ_minut%60)/10;
                last_time.s_min = (tables[j].revenue_time.summ_minut%60)%10;
                cout<<j+1<<" "<< tables[j].revenue<<" "<<last_time.b_hour<<last_time.s_hour<<":"<<last_time.b_min<<last_time.s_min<<endl;
            }

        }
        
    
    }
}

bool find_user(string username, queue<string> user_queue)
{
    bool buf;
    username == user_queue.front() ? buf = true:buf = false;
    return buf;
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
        ; //ДОБАВИТЬ ИТЕРАТОР ДЛЯ ДИНАМИКИ
        int iter = 0;
        while (!indate.eof()) //ДОБАВИТЬ УСЛОВИЕ 
        {
            string str;
            getline(indate,str);
            //cout<<str<<endl;
            event_from_file.resize(iter+1);
            
            char time[5];

            //indate.read(time,6);
            for(int j = 0; j<sizeof(time);j++)
                time[j] = str[j];
            
            event_from_file[iter].clock.b_hour = time[0]-48;
            event_from_file[iter].clock.s_hour = time[1]-48;
            event_from_file[iter].clock.b_min = time[3]-48;
            event_from_file[iter].clock.s_min = time[4]-48;

            if ((event_from_file[iter].clock.b_hour == 0)||
            (event_from_file[iter].clock.b_hour == 1)||
            (event_from_file[iter].clock.b_hour == 2))
            {
                if((event_from_file[iter].clock.s_hour == 0)||
                (event_from_file[iter].clock.s_hour == 1)||
                (event_from_file[iter].clock.s_hour == 2)||
                (event_from_file[iter].clock.s_hour == 3)||
                (event_from_file[iter].clock.s_hour == 4)||
                (event_from_file[iter].clock.s_hour == 5)||
                (event_from_file[iter].clock.s_hour == 6)||
                (event_from_file[iter].clock.s_hour == 7)||
                (event_from_file[iter].clock.s_hour == 8)||
                (event_from_file[iter].clock.s_hour == 9))
                {
                    if((event_from_file[iter].clock.b_min == 0)||
                    (event_from_file[iter].clock.b_min == 1)||
                    (event_from_file[iter].clock.b_min == 2)||
                    (event_from_file[iter].clock.b_min == 3)||
                    (event_from_file[iter].clock.b_min == 4)||
                    (event_from_file[iter].clock.b_min == 5)||
                    (event_from_file[iter].clock.b_min == 6))
                    {
                        if((event_from_file[iter].clock.s_hour == 0)||
                        (event_from_file[iter].clock.s_hour == 1)||
                        (event_from_file[iter].clock.s_hour == 2)||
                        (event_from_file[iter].clock.s_hour == 3)||
                        (event_from_file[iter].clock.s_hour == 4)||
                        (event_from_file[iter].clock.s_hour == 5)||
                        (event_from_file[iter].clock.s_hour == 6)||
                        (event_from_file[iter].clock.s_hour == 7)||
                        (event_from_file[iter].clock.s_hour == 8)||
                        (event_from_file[iter].clock.s_hour == 9))
                        {
                            
                        }
                        else
                        {
                            cout<<"Warning, bad format in: "<<iter+4<<","<<4<<endl;
                            break;
                        }
                        
                    }
                    else
                    {
                        cout<<"Warning, bad format in: "<<iter+4<<","<<3<<endl;
                        break;
                    }
                }
                else
                {
                    cout<<"Warning, bad format in: "<<iter+4<<","<<1<<endl;
                break;
                }

            }
            else
            {
                cout<<"Warning, bad format in: "<<iter+4<<","<<0<<endl;
                break;
            }
            

            event_from_file[iter].clock.summ_minut = 
            (event_from_file[iter].clock.b_hour*600)+
            (event_from_file[iter].clock.s_hour*60)+
            (event_from_file[iter].clock.b_min*10)+
            event_from_file[iter].clock.s_min;
        
            //indate >> event_from_file[iter].ID;
            event_from_file[iter].ID =str[6]-48;
            //cout <<"ID: "<< event_from_file[iter].ID<<endl;
            //indate >> event_from_file[iter].username;            
            
            //event_from_file[iter].username = buf;
            //cout <<"username: "<< event_from_file[iter].username<<endl;
            //print_time(event_from_file[iter].clock);
            //cout<<endl;

            // if(str[str.size()] == "\n")// ДОПИСАТЬ ОБРАБОТКУ ПОСЛЕДНЕЙ СТРОКИ
            // {
                
            // }

            if(event_from_file[iter].ID == 2)
            {
                event_from_file[iter].username.append(str,8,str.size()-11);
                //cout <<"username: "<< event_from_file[iter].username<<endl;
                event_from_file[iter].table = str[str.size()-2]-48;
                //cout<<"\n"<<str[str.size()-2]<<" "<<str.size()<<endl;
                //indate >> event_from_file[iter].table;
                //cout<<"table: "<< event_from_file[iter].table<<endl;
            }
            else
            {
                
                event_from_file[iter].username.append(str,8,str.size()-9);
                //cout <<"username: "<< event_from_file[iter].username<<endl;
                //cout<<"";
            }
            //cout<<endl;

            iter++;
            //indate.seekg(2,ios::cur);
           
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