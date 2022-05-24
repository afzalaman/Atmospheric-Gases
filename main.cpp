//Title:         Simulation of gases under series of Atmospheric Conditions

#include <iostream>
#include <exception>
#include <fstream>
#include <string.h>
#include <vector>
#include "Gases.hpp"
#include "Conditions.hpp"


using namespace std;

//Task:          Filling the vector of gases and the variables from a file of a given name
//Input:         string str	- name of the text file
//Output:        vector<Gases*> &gases  - vector of pointers of the gases
//               vector<Conditions*> &agent - vector of the Variables
//Activity:      creating the gases and their pointers
//               filling the vector of gases
//               filling the vector of the Variables
void create(const string &str, vector<Gases*> &gases, vector<Conditions*> &agent)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    int n; 
    f >> n;
    cout<<"The content of file :"<<endl;
    cout<<n<<endl;
    gases.resize(n);
    for( int i=0; i<n; ++i )
    {
        char ch;  double p;
        f >> ch >> p;
        cout<<ch<<" "<<p<<endl;
        switch(ch){
            case 'Z' : gases[i] = new Ozone("Ozone        ",p); break;
            case 'X' : gases[i] = new Oxygen("Oxygen       ",p); break;
            case 'C' : gases[i] = new CarbonDioxide("Carbondioxide",p);   break;
        }
    }

    string m;
    f >> m;
    cout<<m<<"\n"<<endl;
    agent.resize(m.length());
    for( int j=0; j<m.length(); ++j ) 
    {
        char k; 
        k = m[j];
        switch(k)
        {
            case 'T' : agent[j] = Thunderstorm::instance();  break;
            case 'S' : agent[j] = Sunshine::instance(); break;
            case 'O' : agent[j] = Other::instance(); break;
        }
    }
}

//Task:       The Cleanup
//Input:      vector<Gases*> &gases  - vector of pointers of the gases
//Output:     vector<Gases*> &gases  - vector of pointers of the gases after cleanup
//Activity:   To cleanup the gases if their thickness is less than 0.5km
void cleanup(vector<Gases*> &gases)
{
    for(unsigned int i=0; i < gases.size(); ++i )
    {
        if (!(gases[i]->exist()))
        {
            bool l = false;
            for (unsigned int k = i+1;!l && k<gases.size();k++)
            {
                if (gases[k]->name() == gases[i]->name())
                {
                    l = true;
                    gases[k]->addThickness(gases[i]->getThickess());
                }
            }
            gases.erase(gases.begin()+i);
        }
    }
}

/*void simulate(vector<Gases*> &gases, vector<Conditions*> &agent, vector< vector <Gases*> > &answer)
{
    try{
        answer.clear();
        int initial=gases.size();
        while(gases.size() >=3 && gases.size() < (3*initial) && agent.size() > 0 )
        {
        for( unsigned int i=0; i < agent.size(); i++ )
        {
            for( unsigned int j=0; j < gases.size(); j++ )
            {
                Gases* temp = agent[i]->transform(gases[j]);
                if (temp->name() == gases[j]->name())
                {
                    continue;
                }
                bool l = false;
                for (unsigned int k = j+1;!l && k<gases.size();k++)
                {
                    if((gases[k]->name() == temp->name()))
                    {
                        l = true;
                        gases[k]->addThickness(temp->getThickess());
                    }
                }
                if (!l)
                {
                    gases.push_back(temp);
                }
                cleanup(gases);  
            }
        }
        answer.push_back(gases);
    }
    catch(exception e)
    {
        cout << e.what() << endl;
    }
    // return answer;
}*/

//Task:       The Simulation
//Input:      vector<Gases*> &gases  - vector of pointers of the gases
//            vector<Conditions*> &agent - vector of the Atmospheric Variables(Conditions)
//Output:     vector< vector <pair <string,double> > > &answer  - Two dimensional vector of pairs of the gas name and its thickness
//Activity:   every Gases gets affected by the atmospheric variables one after the other (meanwhile the layers of gases may change),
//            as long as the gases layer is greater than equal to 3 or its not the triple of the initial number.
void simulate(vector<Gases*> &gases, vector<Conditions*> &agent, vector< vector <pair <string,double> > > &answer)
{
    try
    {
        answer.clear();
        int initial=gases.size();
        int counter = 0;
        while(gases.size() >=3 && gases.size() != (3*initial) && agent.size() > 0 )
        {
        for( unsigned int i=0; i < agent.size(); i++ )
        {
            for( unsigned int j=0; j < gases.size(); j++ )
            {
                Gases* temp = agent[i]->transform(gases[j]);
                if (temp->name() == gases[j]->name())
                {
                    continue;
                }
                bool l = false;
                for (unsigned int k = j+1;!l && k<gases.size();k++)
                {
                    if((gases[k]->name() == temp->name()))
                    {
                        l = true;
                        gases[k]->addThickness(temp->getThickess());
                    }
                }
                if (!l)
                {
                    gases.push_back(temp);
                }
                cleanup(gases);  
            }

//For printing each layer after the effect of each Variables (Not a series of Variables like a simulation)
                    // for( unsigned int z=0; z < gases.size(); z++ )
                    // {
                    //         cout << gases[z]->name() << "       " << gases[z]->getThickess() << "km" << endl;
                    // }  
                    // cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";  

        }
        answer.resize(counter+1);

                 for( unsigned int z=0; z < gases.size(); z++ )
                    {
                            answer[counter].push_back(make_pair(gases[z]->name(),gases[z]->getThickess()));
                    }  
                    ++counter; 
        }
    }
    catch(exception e)
    {
        cout << e.what() << endl;
    }
}


//Task:       Destruction of the gases
//Input:      vector<Gases*> &gases  - vector of pointers of the gases
//Activity:   destroys every dinamically allocated Gases
void destroy(vector<Gases*> &gases)
{
    for(int i=0; i<gases.size(); ++i) delete gases[i];
}

//Task:       Destruction of the Variables
//Activity:   destroys every dinamically allocated Conditions
void destroyConditions()
{
    Thunderstorm::destroy();
    Sunshine::destroy();
    Other::destroy();
}

// To change between the manual and the unit test mode
#define NORMAL_MODE
#ifdef NORMAL_MODE



int main()
{
    vector<Gases*> gases;
    vector<Conditions*> agent;
    create("inp.txt", gases, agent);
    cout<<"\n#######################################\n\n";
    cout << "Initailly The layers of Gases are" << endl;
    
    for(unsigned int i=0; i<gases.size(); ++i)
    { 
        cout << gases[i]->name() << "       " << gases[i]->getThickess() << "km" << endl;
    }

    cout<<"\n#######################################\n\n\n";

    //vector< vector<Gases*> >ans;
    vector< vector <pair <string,double> > > ans;

    simulate(gases,agent,ans);

    for (int z=0;z<ans.size(); z++)
    {
         cout << "After " << z+1 << " Simulation, The layers are" << endl;
        for(int y=0;y<ans[z].size();y++)
        {
            cout << ans[z][y].first << "       " << ans[z][y].second << "km" << endl;
        }
        cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";  
    }


    // Destruction of the objects
    destroy(gases);
    destroyConditions();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "inp1*.txt")
{
    vector<Gases*> gases;
    vector<Conditions*> agent;
    vector< vector <pair <string,double> > > ans;

    create("inp1a.txt", gases, agent);
    simulate(gases, agent, ans);
    CHECK(ans.size() == 0);
    destroy(gases);
    destroyConditions();

    create("inp1b.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans.size() == 29);
    destroy(gases);
    destroyConditions();

    create("inp1cde.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans.size() == 6);
    destroy(gases);

    create("inp1cde.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans[0][0].first == "Carbondioxide");
    CHECK(to_string(ans[0][0].second) == "2.205276");
    CHECK(ans[0][1].first == "Ozone        ");
    CHECK(to_string(ans[0][1].second) == "3.107601");
    CHECK(ans[0][2].first == "Ozone        ");
    CHECK(to_string(ans[0][2].second) == "7.747942");
    destroy(gases);

    create("inp1cde.txt", gases, agent);
    simulate(gases, agent, ans);
    CHECK(ans[5][0].first == "Ozone        ");
    CHECK(to_string(ans[5][0].second) == "0.516121");
    CHECK(ans[5][1].first == "Ozone        ");
    CHECK(to_string(ans[5][1].second) == "1.286804");

    destroy(gases);
    destroyConditions();
}

TEST_CASE("2", "inp2*.txt")
{
    vector<Gases*> gases;
    vector<Conditions*> agent;
    vector< vector <pair <string,double> > > ans;

    gases.clear();
    agent.clear();
    create("inp2a.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans.size() == 0);
    destroy(gases);
    destroyConditions();

    create("inp2b.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans.size() == 0);
    destroy(gases);
    destroyConditions();

    create("inp2cde.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans.size() == 7);
    destroy(gases);

    create("inp2cde.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans[0][0].first == "Carbondioxide");
    CHECK(to_string(ans[0][0].second) == "2.205276");
    CHECK(ans[6][0].first == "Ozone        ");
    CHECK(to_string(ans[6][0].second) == "1.306346");
    destroy(gases);

    create("inp2cde.txt", gases, agent );
    simulate(gases, agent, ans);
    CHECK(ans[0][3].first == "Carbondioxide");
    CHECK(to_string(ans[0][3].second) == "3.781723");
    CHECK(ans[6][1].first == "Carbondioxide");
    CHECK(to_string(ans[6][1].second) == "0.927227");

    destroy(gases);
    destroyConditions();
}

TEST_CASE("3", "") {

    vector<Gases*> gases;
    vector<Conditions*> agent;
    vector< vector <pair <string,double> > > ans;

    gases.clear();
    agent.clear();
    create("inp3a.txt", gases, agent );
    simulate(gases, agent, ans);

    CHECK(gases[0]->exist() == true);
    CHECK(agent[0] == Other::instance());
    CHECK(agent[6] == Thunderstorm::instance());
    CHECK(agent[14] == Sunshine::instance());

    CHECK(ans.size() == 6);
    CHECK(ans[0][0].first == "Ozone        ");
    CHECK(to_string(ans[0][0].second) == "2.205276");
    CHECK(ans[0][3].first == "Carbondioxide");
    CHECK(to_string(ans[0][3].second) == "1.608128");

    CHECK(ans[2][0].first == "Ozone        ");
    CHECK(to_string(ans[2][0].second) == "1.191643");
    CHECK(ans[2][3].first == "Carbondioxide");
    CHECK(to_string(ans[2][3].second) == "0.868968");

    CHECK(ans[5][0].first == "Ozone        ");
    CHECK(to_string(ans[5][0].second) == "1.971453");

    gases.clear();
    agent.clear();
    ans.clear();

    create("inp3b.txt", gases, agent );
    simulate(gases, agent, ans);

    CHECK(gases[0]->exist() == true);
    CHECK(agent[0] == Sunshine::instance());
    CHECK(agent[6] == Sunshine::instance());;
    CHECK(agent[11] == Thunderstorm::instance());

    CHECK(ans.size() == 14);
    CHECK(ans[0][0].first == "Ozone        ");
    CHECK(to_string(ans[0][0].second) == "9.444446");
    CHECK(ans[0][4].first == "Carbondioxide");
    CHECK(to_string(ans[0][4].second) == "2.199167");

    CHECK(ans[6][0].first == "Ozone        ");
    CHECK(to_string(ans[6][0].second) == "2.757675");
    CHECK(ans[6][3].first == "Carbondioxide");
    CHECK(to_string(ans[6][3].second) == "0.642133");

    CHECK(ans[13][0].first == "Ozone        ");
    CHECK(to_string(ans[13][0].second) == "0.655849");
    CHECK(ans[13][1].first == "Ozone        ");
    CHECK(to_string(ans[13][1].second) == "0.727361");

    gases.clear();
    agent.clear();

    gases.push_back(new Ozone("Ozone        ", 5.7));
    gases.push_back(new Oxygen("Oxygen       ", 2.4));
    gases.push_back(new CarbonDioxide("Carbondioxide", 3.3));
    gases.push_back(new Ozone("Ozone        ", 1.7));

    agent.push_back(Thunderstorm::instance()); agent.push_back(Sunshine::instance()); agent.push_back(Other::instance());
    simulate(gases, agent, ans);

    CHECK(gases.size() == 2);
    CHECK(agent[0] == Thunderstorm::instance());
    CHECK(agent[1] == Sunshine::instance());
    CHECK(agent[2] == Other::instance());

    destroy(gases);
    destroyConditions();
}


#endif // NORMAL_MODE