#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>


#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/path.hpp"
#include <exception>
#include <unordered_set>
#include <unordered_map>

#define DEPENDENCIES    "DEPENDENCIES"
#define OWNERS          "OWNERS"


using namespace std;
namespace po = boost::program_options;
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
    unordered_map<string , vector<string> > dir_owners;
    unordered_map<string , vector<string> > dir_dependencies;

 
    void process_program_options(const int ac, const char *const av[]);
    void get_dependecies();
    void get_owners();

    void dir_indexing(fs::path dir_path);
public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
        repo_path=(fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
        cout << repo_path << endl;
        // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
        get_dependecies();
        for(const auto& dep : dependencies){
            cout << dep.first << " APPEARED IN: " << endl;
            for(const auto& d_a_o: dep.second)
                cout <<  d_a_o << endl;
        }
        cout << "GET DPS" << endl;
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

void TwitterCodebaseApprovalSystem::get_dependecies(){
    string dir_path;
    string line;
    vector<string> dirs_and_owners;
    for ( fs::recursive_directory_iterator end, dir("./"); dir != end; ++dir ) {
        if( fs::is_regular_file( (dir.status())) ){ // dir=/etc/DEP 
            if( dir->path().filename() == "DEPENDENCIES"){//cout << dir->path().filename() << endl; //std::cout << *dir << "\n";  // full path
                fs::ifstream file(dir->path()); // DEP contians /src
                cout << *dir << "\n";
                //dirs_and_owners =  {dir->path().parent_path().string() , get_owners(dir->path())} ; // / {etc, [d] }
                dirs_and_owners = get_dirs_and_owners(dir->path().parent_path());
                //cout << dirs_and_owners << endl;
                
                /************************111111*********************
                 dependencies.insert( {dir->path , get_dirs_and_owners(dir->path().parent_path())} );
                *********************************************/
                

                while(getline(file, line)){
                    unordered_map<string, vector<vector<string> >>::const_iterator got = dependencies.find (line);

                    if(got != dependencies.end()){
                        dependencies[line].push_back(dirs_and_owners);
                    }
                    else{
                        //cout << "NOT EXIST" << endl;
                        vector<vector<string> > new_dirs_and_owners={dirs_and_owners};
                        dependencies.insert( {line , new_dirs_and_owners} ); // { /src --> {etc, [d] } }
                        //dependencies.first = line;
                        //dependencies.second.push_back(dirs_and_owners);
                    }//fisr chech exist or not exist order performace???
                }
            }
        }
        //std::cout << dir->path().filename() << "\n"; // just last bit
    }

    if ( fs::is_regular_file(fs::status(dir_path+"/DEPENDENCIES")) ) //windowsssss
        cout << "yes" << endl;

    //read DEPS file if exist add to dependencies
}

vector<string> TwitterCodebaseApprovalSystem::get_dirs_and_owners(fs::path dir_path){
    vector<string> dirs_and_owners;
    dirs_and_owners.push_back(dir_path.string()); // add the dir to the first elemt and then owner to avoid using pair BETTER PERFOMACE
    string line;
    fs::path owner_file = dir_path;
    owner_file /="OWNERS";
    while(!fs::exists(owner_file)){//maybe bottom up is a bit better so that I can find all the owner all the way to parent but for sisters dirs I have to go back again.
    //it is the matter of if exists is fast or checking the exitence in hash
        dir_path = dir_path.parent_path();
        owner_file = dir_path;
        owner_file /="OWNERS";
    }
    fs::ifstream file(owner_file); // DEP contians /src       
    while(getline(file, line)){
        dirs_and_owners.push_back(line);
    }
    return dirs_and_owners;
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


    unordered_map<string, vector<string>> dir_ownerss;
    // /dir1 --> [root, usr]
    // /dir2 --> [usr]
    unordered_map<string, vector<string>> dir_dependenciess;
    // /dir1 --> [dir2]
    
    unordered_map<string, vector<vector<string>>> dir_owners_and_dependenciess;
    // /dir1 --> [ [/dir1, root, usr] [/dir2, usr] ]
    // /dir2 --> [ [/dir2, usr] ]

    return 0;
}


/*
I would use data storage/DB to index only once a directory and apply changes by indexing 
however here itis only a CMD I cannpt do this so go through files everytime of the run of the program


I also skip storing all the dependecies and store only by as I go (instead of all dependecies)
however since I do not know what will happen as I go, I may add see some dependciens that I have passed bu they just found
may be there is a weired strcuture like this:

/repo
ONWE={e}
    /usr
        /root
            DEP={usr/ali} 
        /ali
            OWNER={f}
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
            FILE2
        /bin
            FILE1


1'')  parse all dirs and find all dependecies
    DEP_HASH
        src/com    ---->   ( [src/com, [b,c]], [etc,[d]] , [lib,[b]] , )  
        test/com   ---->   ( [test/com, [a,b]], [src/com,[b,c]] , )
        usr/ali    ---->   ( [usr/ali ,[f]] , [usr/root, [e]], [test/com, [a,b]]) //will not be used SEE improvement below??

        test/bin   ---->   ( [test/bin, [e]]) //no body dep but in changed files

2'')  now if make owners (set is enough)
    add FILE1 test/bin owners easy => [e]  
    OWNER_SET
        [e]
    add FILE2 test/com owners easy => [a,b]
    OWNER_SET
        [e]
        [a, b]
    DONE

    see if DEP_HASH[test/com] exist => yes => add deps [src/com,[b,c]]
    OWNER_SET
        [a, b]
        [b, c]
    find 
    see if DEP_HASH[src/com] exist => yes add deps [etc,[d]] , [lib,[b]]
    OWNER_SET
        [a, b]
        [b, c]
        [d]
        [b]
    see if DEPS[etc] exists => no
    see of DEPS[lob] exist => no
    finsihed done!
*/

// IMPROVEMENT: THERE ARE SOME UNNECESARY THING IN DEPS but I cannot remove them initially before I don't know if there is a deps would happen
//but I can prune them when I'm done with exploring all deps (by chekcing )

