#include<iostream>
#include<memory>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
struct vehicle_type
{
double a,b,c;  // economy car,luxury car, ev, autonomous
};
struct cable_type
{
 int current;
 double resistance;   //type a,type b,type c 
};
vehicle_type vehicle[4]={{0.3,0.45,0.25},{0.35,0.35,0.3},{0.3,0.3,0.4},{0.45,0.20,0.35}};
cable_type cabel[3]={{35,50},{40,65},{10,40}};
class ecu_communication
{
	struct communication_link
	{
		string unit1,unit2;  //units are ecu's
		double delay,link_cost;  
	};
	double a,b,c;
	vector<communication_link>link;  //edge_list
	unordered_map<string,string>parent; 
	unordered_map<string,int>rank;
	unordered_map<int,string>m={{0,"Engine Control Unit"},{1,"Brake Control Unit"},{2,"Steering Control Unit"},{3,"ADAS Processing Unit"},{4,"Battery Management System"},{5,"Infotainment Control Unit"}};
	public:
	ecu_communication()
	{
              cout<<"process started to determine minimum link cost"<<endl;
              cout<<"0)Economy vehicle 1)Luxury vehicle 2)Electronic_vehicle 3)Autonomus_vehicle"<<endl; 
             label: cout<<"select vehicle type"<<endl;
              int i;
              cin>>i;
              if(i<0||i>3)
               {  cout<<"invalid vehicle type"<<endl;
                 goto label;
               }
              a=vehicle[i].a;
              b=vehicle[i].b;
              c=vehicle[i].c;
		for(auto& [index,name]:m)   
		{
			parent[name]=name;
			rank[name]=0;
		}
	}
        ecu_communication(ecu_communication& old)  //copy constructor
        { 
         cout<<"copying communication links from model1 to model2"<<endl;
         a=old.a;
         b=old.b;
         c=old.c;
         link=old.link;
         parent=old.parent;
         rank=old.rank;
         }
	pair<double,double> cost_computation_engine()
	{       
    
		int distance=1+rand()%5;
		const double signal_speed=0.2;     //1/(2*10^8) to convert into ns //2*10^8 m/sec = 0.2 m/nsec;
		double delay=distance/signal_speed;
                 
               int cabel_type;
               cout<<"select cabel type  "<<endl<<"0)type 0"<<" "<<"1)type 1"<<" "<<"2)type 2"<<endl;
                 cin>>cabel_type;
		int current=cabel[cabel_type].current;
		double resistance=cabel[cabel_type].resistance;
		double power_loss=(current*current)*resistance;
                  
		double link_cost=a*(delay)+b*(power_loss)+c*(distance*20);  // 20 is wiring cost per unit

		return {link_cost,delay};
	}
	void hardware_modelling()
	{    
				for(auto& [index,ecu_name] :m)
					cout<<index<<" : "<<ecu_name<<endl;
		while(1)
		{
			int choice;
			cout<<"1)enter"<<" "<<"2)exit"<<endl;
			cout<<"enter your choice:";
			cin>>choice;
			if(choice==1)
		         {
				int i,j;
				cout<<"enter only two respective numbers for creating communication link:"<<endl;
				cin>>i>>j;
                if(m.find(i) == m.end() || m.find(j) == m.end())
                 {
                   cout<<"Invalid ECU index\n";
                    continue;
                 }
				auto [edge_cost,_delay]=cost_computation_engine();
				link.push_back(move(communication_link{m[i],m[j],edge_cost,_delay}));
			}
			else
				return;
		}
	}

	void optimization_engine()
	{         
	       static	double ts_cost=0,tp_delay=0;
            if(link.empty())
              {
                   cout<<"no communication links  are there in link pool to create minimum cost communication structure"<<endl;
              
              }
              else
              {
         		sort(link.begin(),link.end(),[](const communication_link& a,const communication_link& b){return a.link_cost<b.link_cost;}); 
	        
	         	int link_count=0;
	        	for(auto &it:link)
	            	{
		              	string ecu1=it.unit1;
		             	string ecu2=it.unit2;
	         		if(find_parent(ecu1)!=find_parent(ecu2))
		            	{
			            	union_set(ecu1,ecu2);
			             	cout<<ecu1<<" <-> "<<ecu2<<" of link cost "<<it.link_cost<<endl;
				            ts_cost+=it.link_cost;
			             	tp_delay+=it.delay;
			            	link_count++;
			            	if(link_count==m.size()-1)
				            	break;
		             	}
               		}
              }
		cout<<"Total system cost is: "<<ts_cost<<endl;
		cout<<"Total Propogation delay is: "<<tp_delay<<" ns" <<endl;
                cout<<"-----------------------------------------------"<<endl;
	}

	string find_parent(string ecu)
	{
		if(parent[ecu]==ecu)
			return ecu;
		return parent[ecu]=find_parent(parent[ecu]);
	}
	void union_set(string ecu1,string ecu2)
	{   string parent1=find_parent(ecu1);
            string parent2=find_parent(ecu2);
		if(rank[parent1]<rank[parent2])
		{
			parent[parent1]=parent2;
		}
		else if(rank[parent2]<rank[parent1])
		{
			parent[parent2]=parent1;
		}
		else
		{
			parent[parent2]=parent1;
			rank[parent1]++;
		}
	}
	
    ~ecu_communication()
    {
        cout<<"successfully completed determine minimum  cost communication system"<<endl;
    }
 };
int main()
{    srand(time(nullptr));
	ecu_communication ev1;
	ev1.hardware_modelling();
	ev1.optimization_engine();
        ecu_communication ev2=ev1;
        ev2.optimization_engine();
        ev1.optimization_engine();
}
