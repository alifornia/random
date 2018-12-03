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

#define DEPENDENCIES_FILE_NAME    "DEPENDENCIES"
#define OWNERS_FILE_NAME          "OWNERS"


using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;


template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

//g++ -std=c++1z tweet.cpp -l boost_program_options -l boost_system -l boost_filesystem


class TwitterCodebaseApprovalSystem{
private:
    string repo_path;
    
    vector<string> approvers;
    vector<string> changed_files;

    vector<string> required_approvals;
    unordered_map<string , vector<string> > dir_owners;
    unordered_map<string , vector<string> > dir_dependencies;
 
    void process_program_options(const int ac, const char *const av[]);
    void get_dir_dependencies(fs::path dir_path);
    void get_dir_owners(fs::path dir_path);

    void dir_indexing();

public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
        repo_path=(fs::current_path()).string();
        cout << repo_path << endl;
        // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
        dir_indexing();
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

void TwitterCodebaseApprovalSystem::dir_indexing(){
    string line;
    for ( fs::recursive_directory_iterator end, dir_path("./"); dir_path != end; ++dir_path ) {
        //cout << *dir_path << endl;
        if (fs::is_regular_file( (dir_path.status()))){ 
            if(dir_path->path().filename() == DEPENDENCIES_FILE_NAME){
                get_dir_owners(dir_path->path().parent_path());
                //get_dir_dependencies(dir_path->path().parent_path());
            }
        }
    }
    cout << "BEGIN" << endl;
    for(const auto& dep : dir_dependencies){
        cout << dep.first << " APPEARED IN: " << endl;
        for(const auto& d_a_o: dep.second)
            cout <<  d_a_o << endl;
    }
    cout << "END" << endl;
}
void TwitterCodebaseApprovalSystem::get_dir_dependencies(fs::path dir_path){
    string line;
    string dir_path_string = dir_path.string();
    fs::ifstream file(dir_path);
    //cout << dir_path.string() << endl;
    while(getline(file, line)){
        unordered_map<string, vector<string> >::const_iterator got = dir_dependencies.find(line);
        if(got != dir_dependencies.end()){
            dir_dependencies[line].push_back(dir_path_string);
        }
        else{
            dir_dependencies[line].push_back(dir_path_string);
            //dir_dependencies[line] = dir_path_string;
            //dir_dependencies.insert({line, dir_path_string}); // { /src --> {etc, [d] } }
        }
    }
}

void TwitterCodebaseApprovalSystem::get_dir_owners(fs::path dir_path){
    string line;
    fs::path owner_file = dir_path;
    string dir_path_string = dir_path.string();
    fs::path debug_dir_path = dir_path;
    //cout << dir_path.string() << endl;
    owner_file /= OWNERS_FILE_NAME;
    while( !fs::exists(owner_file) ){
        dir_path = dir_path.parent_path();
        owner_file = dir_path;
        owner_file /= OWNERS_FILE_NAME;
    }
    cout << "DEBUG" << endl;
    cout << owner_file << " of " << debug_dir_path << endl;
    fs::ifstream file(owner_file);
    while(getline(file, line)){
        unordered_map<string, vector<string> >::const_iterator got = dir_owners.find(line);
        if(got != dir_owners.end()){
            dir_owners[dir_path_string].push_back(line);
        }
        else{
            //vector<string> new_dirs_and_owners={dirs_and_owners};
            dir_owners[dir_path_string].push_back(line);
            //dir_owners[dir_path_string] = line;
            //dir_owners.insert({dir_path_string , line});
        }  
    }
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

