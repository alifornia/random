#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
//#include <experimental/filesystem>
//#include <filesystem>
#include <unistd.h>


#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <exception>
#include <unordered_set>
#include <unordered_map>


using namespace std;
namespace po = boost::program_options; //using namespace boost;
namespace fs = boost::filesystem;


template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

//g++ -std=c++17  TwitterCodebaseApprovalSystem.cpp -I ~/Downloads/boost_1_68_0/Program/include/boost-1_68/ -L ~/Downloads/boost_1_68_0/Program/lib/ -lboost_program_options-mgw81-mt-d-x32-1_68
//g++ -std=c++17  TwitterCodebaseApprovalSystem.cpp -I C\:/Program\ Files/boost/include/boost-1_68  -L C\:/Program\ Files/boost/lib -lboost_program_options-mgw81-mt-d-x32-1_68 -lboost_filesystem-mgw81-mt-d-x32-1_68 -lboost_system-mgw81-mt-d-x32-1_68

class TwitterCodebaseApprovalSystem{
private:
    string repo_path;
    vector<string> approvers;
    vector<string> changed_files;
    vector<string> required_approvals;
    vector<string> dependencies;

    void process_program_options(const int ac, const char *const av[]);
    string get_parent_dir(string dir_path); //use boost util

    vector<string> get_dependecies(string dir_path); //??????????????? others deps or its deps?
    vector<string> get_owners(string dir_path);
    unordered_map<string, vector<string>> get_required_approvals();
    unordered_map<string, vector<string> , vector<string> > index_dirs(); //owners maybe make a classss?~!?!!
public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
        //check if files are valid
        repo_path=(fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
        cout << repo_path << endl;
        // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
    }
    bool is_approved();
};

void TwitterCodebaseApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    desc.add_options()
        ("help,h", "produce help message")
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files"); 
        /////////////// changed it as it says on the question
        ///////Both flags arguments are comma separated.
        ///////////////////////////////////////////////
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
        exit( EXIT_FAILURE );
    }
    cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; 
    //FASTERRRR??? IDK cout << vm["changed-files"].as< vector<string> >();

}

string TwitterCodebaseApprovalSystem::get_parent_dir(string dir_path){
    string parent_dir_path =((fs::path(dir_path)).parent_path()).string();
    cout << parent_dir_path << endl;
    //use boost util to get parent path or just truncate
    return parent_dir_path;
}
vector<string> TwitterCodebaseApprovalSystem::get_dependecies(string dir_path){
    vector<string> dependencies;
    if ( fs::is_regular_file(fs::status(dir_path+"/DEPENDENCIES")) ) //windowsssss
        cout << "yes" << endl;

    //read DEPS file if exist add to dependencies
    return dependencies;
}

vector<string> TwitterCodebaseApprovalSystem::get_owners(string dir_path){
    vector<string> owners;
    //while( if no OWNERS exist in dir_path) goto parent
    //read OWNERS file 
    return owners;
}

unordered_map<string, vector<string>> TwitterCodebaseApprovalSystem::get_required_approvals(){
    unordered_set<string> visited_path; //make sure set is faster than map
    string current_path, parent_path; 
    vector<string> owners;
    vector<string> dependencies;

    unordered_map<string, vector<string>> required_approvals;

    while(!changed_files.empty()) ///!!!! use  stack to do one operatn?!! vetcor has better performace tho!!!!
    { 
        current_path = changed_files.front();
        changed_files.pop_back(); 
        //if not visited 
        visited_path.insert(current_path); //parent or current checkkkkk
        owners = get_owners(current_path);
        
        //Hashmapp? STL unorder_map is fast

        dependencies = get_dependecies(current_path);
        
        //get DEPENDECIES ??????? of this dir ot everything deps on this CHECK WITH TWITTER
        //add to stack

        cout << "DEBUD: not empty" << endl;
    }
    return required_approvals;
}

bool TwitterCodebaseApprovalSystem::is_approved(){
    if(required_approvals == approvers) //handle order!!!! == is fast but NO ORDER
        return true;
    return false;
}
int main(int argc, char** argv){
    //string pp1 = (std::experimental::filesystem::current_path()).sring()+"asdasd";

    string pp1 = (fs::current_path()).string()+"/OWNERS";

    //string pp2 = (fs::current_path()).string()+"asdasd";
    cout << pp1 << endl;

    //if ( std::filesystem::exists(std::filesystem::status(pp)) && !std::filesystem::is_directory(std::filesystem::status(pp)) ); //windowsssss
    //if ( std::experimental::filesystem::exists(std::experimental::filesystem::status(pp)) && !std::experimental::filesystem::is_directory(std::experimental::filesystem::status(pp)) ); //windowsssss
    
    if (fs::exists(fs::status(pp1)) && !fs::is_directory(fs::status(pp1)) )
        cout << "yes" << endl;

    TwitterCodebaseApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
    else cout << "Insufficient approvals" << endl;
    return 0;
}


//I would use data storage/DB to index only once a directory and apply changes by indexing
//however here itis only a CMD I cannpt do this so go through files everytime of the run of the program


// I also skip storing all the dependecies and store only by as I go (instead of all dependecies)
//however since I don't know what will happen as I go, I may add see some dependciens that I have passed bu they just found
//may be there is a weired strcuture like this:

/repo
    /etc
        OWNERS={d}
        DEP={src/com}
    /lib
        OWNER={b}
        DEP={src/com}
    /src
        /com
            OWNERS={b, c}
            DEP={test/com}    
    /test
        /com
            OWNERS={a, b}
            FILE

1)  if I change FILE
    OWNER_HASH
         test/com   ---->   {a, b}
    done with initial add

2)  now parse all dirs and find dependecies on intial OWNER HASH 
    I find "src/com" depens on "test/com"
    add to hash
    OWNER_HASH
         test/com   ---->   {a, b}
         src/com    ---->   {b, c}

BUG: also "etc" and "lib" depends on "src/com" and must be added but we parser may have passed them already (indexing direction does not help).
so I have to store all the dependecies which is not space-ideal.

1)  parse all dirs and find all dependecies
    DEP_HASH
        src/com     ---->   {etc, lib, }  
        test/com    ---->   {src/com, }
2)  now if make owners
    OWNER_HASH
         test/com   ---->   {a, b}
    done with initial add
    add DEP_HASH[test/com]
    OWNER_HASH
        test/com   ---->   {a, b}
        src/com    ---->   {b, c}
    add DEP_HASH[src/com]
        etc        ---->   {d}
        lib        ---->   {b}



