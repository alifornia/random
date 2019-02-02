#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <stack>
#include <utility>

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

    unordered_map<string , vector<string> > dir_owners; //better way to not store the whole path, maybe "relitive to paret..." using a patricia, radix tree
    unordered_map<string , vector<string> > dir_dependencies;

    unordered_set<string> required_approvals; // DONT NEED TO STORE ALL THE DIR PATH ... PREFIX ...... STRING ...
 
    void process_program_options(const int ac, const char *const av[]);

    void dir_indexing();
    void get_dir_dependencies(fs::path dir_path);
    void get_dir_owners(fs::path dir_path);
    vector<string> get_dir_owners2(fs::path dir_path);


    void find_required_approvals();

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
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files"); //change to comma seperated!!!!!1
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
}

void TwitterCodebaseApprovalSystem::dir_indexing(){
    string line;
    fs::path dir_path = ".";//repo
    vector<string> dir_direct_pwners;
    stack< pair< string, vector<string> > > dir_stack;

    //for (auto & dir_it : fs::directory_iterator("./src")){//a level
    //for ( fs::recursive_directory_iterator end, dir_it("./"); dir_it != end; ++dir_it ) {
    dir_direct_pwners = get_dir_owners2(dir_path);
    dir_stack.push({dir_path.string(), dir_direct_pwners});

    while(!dir_stack.empty()){//DFS
        dir_path = dir_stack.top().first;
        dir_direct_pwners = dir_stack.top().second;
        dir_stack.pop();

        for ( auto & dir_it : fs::recursive_directory_iterator(dir_path) ) {  //cout << dir_it.level() << endl;
            dir_direct_pwners = get_dir_owners2(dir_path);

            if (fs::is_regular_file( (dir_it.status()))){ 
                dir_path = dir_it.path();
                if(dir_it.path().filename() == OWNERS_FILE_NAME){
                    cout << "OWN: " << dir_it << endl;
                    /*dir_direct_pwners = get_dir_owners2(dir_it.path().parent_path());
                    if(!dir_direct_pwners.empty()){
                        dir_stack.push({dir_it.path().string(), dir_direct_pwners});
                        cout << dir_direct_pwners;
                    }
                    cout << endl;*/
                }
                else if (dir_path.filename() == DEPENDENCIES_FILE_NAME){
                    cout << "DEP: " << dir_it << endl;
                }
                else{
                    continue;
                }
            }
            
            /*if (fs::is_regular_file( (dir_it.status()))){ 
                dir_path = dir_it.path();
                if(dir_path.filename() == DEPENDENCIES_FILE_NAME){
                    get_dir_owners(dir_path);
                    get_dir_dependencies(dir_path);
                }
            }*/
        }
    }
    /*cout << "DEBUG BEGIN OWN" << endl;
    for(const auto& own : dir_owners){
        cout << "[" << own.first << "]={";
        for(const auto& d_o: own.second)
            cout <<  d_o << ", ";
        cout << "}\n";
    }
    cout << "DEBUG  END OWN" << endl;

    cout << "DEBUG BEGIN DEP" << endl;
    for(const auto& dep : dir_dependencies){
        cout << "[" << dep.first << "]={";
        for(const auto& d_d: dep.second)
            cout <<  d_d << ", ";
        cout << "}\n";
    }
    cout << "DEBUG  END DEP" << endl;*/
}

vector<string> TwitterCodebaseApprovalSystem::get_dir_owners2(fs::path dir_path){
        string line;
        vector<string> dir_direct_owners;
        fs::path owner_file = dir_path;
        if( fs::exists(owner_file/OWNERS_FILE_NAME) ){
            fs::ifstream file(owner_file/OWNERS_FILE_NAME);
            while(getline(file, line))
                dir_direct_owners.push_back(line);
        }
        return dir_direct_owners;
}

void TwitterCodebaseApprovalSystem::get_dir_owners(fs::path dir_path){
    if(dir_owners.find(dir_path.parent_path().string()) == dir_owners.end()){//needed for saving lots of space by not storing owners of file not required , maybe better to have find_dir_owner and call get_dir_owner if needed
        string line;
        fs::path owner_file = dir_path.parent_path();
        while( !fs::exists(owner_file/OWNERS_FILE_NAME) )
            owner_file = owner_file.parent_path();
        fs::ifstream file(owner_file/OWNERS_FILE_NAME);
        while(getline(file, line))
            dir_owners[dir_path.parent_path().string()].push_back(line);
    }
}

void TwitterCodebaseApprovalSystem::get_dir_dependencies(fs::path dir_path){
    string line;
    fs::ifstream file(dir_path);
    while(getline(file, line))
        dir_dependencies[line].push_back(dir_path.parent_path().string());
}

void TwitterCodebaseApprovalSystem::find_required_approvals(){
    for(const auto& changed_file : changed_files){
        get_dir_owners(fs::path("./"+changed_file));
        //cout << changed_file << "::OWN:: " << dir_owners["./"+fs::path(changed_file).parent_path().string()] << endl;
        //cout << changed_file << "::DEP:: " << dir_dependencies[fs::path(changed_file).parent_path().string()] << endl;

        for(const auto & dir_direct_owner : dir_owners["./"+fs::path(changed_file).parent_path().string()]){
            required_approvals.insert(dir_direct_owner);
        }
        for(const auto & dir_dep :  dir_dependencies[fs::path(changed_file).parent_path().string()]){
            //cout << "DEBUGGGGGG" << endl;
            for(const auto & dir_indirect_owner : dir_owners[dir_dep])
                required_approvals.insert( dir_indirect_owner);
        }
    }
    /*cout << "DEBUG BEGIN REQUIRED APPROVAL" << endl;
    for(const auto& ra : required_approvals)
            cout <<  ra << ", ";
    cout << "\nDEBUG  END REQUIRED APPROVAL" << endl;*/
}

bool TwitterCodebaseApprovalSystem::is_approved(){
    find_required_approvals();
    //if(required_approvals == approvers) //handle order!!!! == is fast but NO ORDER
    //    return true;
    return false;
}
int main(int argc, char** argv){

    TwitterCodebaseApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
    else cout << "Insufficient approvals" << endl;

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

