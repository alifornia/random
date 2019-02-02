<<<<<<< HEAD
#include <iostream>
=======
//author: Ali Abbasinasab

//requirement: c++ 1z on mac or c++11x on linux, g++, boost (check versions later)
//build
//g++ -std=c++1z twest.cpp -l boost_program_options -l boost_system -l boost_filesystem

#include <iostream>
#include <fstream>
>>>>>>> refs/remotes/origin/master
#include <iterator>
#include <string>
#include <vector>
#include <stack>
#include <utility>
<<<<<<< HEAD

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

=======
#include <exception>
#include <unordered_set>
#include <unordered_map>
>>>>>>> refs/remotes/origin/master

#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/path.hpp"
<<<<<<< HEAD
#include <exception>
#include <unordered_set>
#include <unordered_map>
=======
#include <boost/tokenizer.hpp>


>>>>>>> refs/remotes/origin/master

#define DEPENDENCIES_FILE_NAME    "DEPENDENCIES"
#define OWNERS_FILE_NAME          "OWNERS"

<<<<<<< HEAD

using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
=======
using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
typedef unordered_map<string, vector< string > > hashmap_v;
typedef unordered_map<string, set <string> >     hashmap_s;    
>>>>>>> refs/remotes/origin/master


template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}

<<<<<<< HEAD
//g++ -std=c++1z tweet.cpp -l boost_program_options -l boost_system -l boost_filesystem

=======

class DirDependenciesOwners{ // maybe for larger OO design but not needed for this quesion
public:
    vector<string> dependencies;
    vector<string> owners; 
};
>>>>>>> refs/remotes/origin/master

class TwitterCodebaseApprovalSystem{
private:
    string repo_path;
<<<<<<< HEAD
    
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
=======
    vector<string> approvers;
    vector<string> changed_files;
    hashmap_v dir_dependencies;// DONT NEED TO BE IN THE OBJECT
    hashmap_s required_approvals;


    void process_program_options(const int ac, const char *const av[]);

    void dir_indexing();//index dir: dep and owners

    void get_dir_dependencies(fs::path &dir_path); //gets deps

    void get_required_approvals(); // get all required approvals
    bool check_dir_has_approval(string changed_file); //check if a dir has appprovals

    void get_dir_owners(string changed_file, hashmap_v & dir_direct_owners); // gets all required ownerships
    vector<string> get_dir_direct_owners(string dir_path_str, hashmap_v & dir_direct_owners); //get immidiate owners
>>>>>>> refs/remotes/origin/master

public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
<<<<<<< HEAD
        repo_path=(fs::current_path()).string();
        cout << repo_path << endl;
        // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
=======
        repo_path=(fs::current_path()).string(); // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
>>>>>>> refs/remotes/origin/master
        dir_indexing();
    }
    bool is_approved();
};

<<<<<<< HEAD
=======
/*struct mylist_option 
{
    vector<std::string> values;

    static void
    validate(boost::any &v, std::vector<std::string> const &tokens)
    {
        if (v.empty())
            v = boost::any(mylist_option());

        mylist_option *p = boost::any_cast<mylist_option>(&v);
        BOOST_ASSERT(p);

        boost::char_separator<char> sep(",");
        BOOST_FOREACH(std::string const& t, tokens)
        {
            if (t.find(",")) {
                boost::tokenizer<boost::char_separator<char> > tok(t, sep);
                std::copy(tok.begin(), tok.end(), 
                    std::back_inserter(p->values));
            }
            else {
                p->values.push_back(t);
            }
        }
    }
};*/

/* 
//second effort on changing default program option to comma sepretaed, it seems not doable 
namespace lli {
  class CommaSeparatedVector 
  {
      public:
        // comma separated values list
        std::vector<std::string> values;
  };
}

void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = ",")
{
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos) {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}

// mapper for "lli::CommaSeparatedVector"
std::istream& operator>>(std::istream& in, lli::CommaSeparatedVector &value)
{
    std::string token;
    in >> token;
    tokenize(token, value.values);
    return in;
}*/

>>>>>>> refs/remotes/origin/master
void TwitterCodebaseApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    desc.add_options()
        ("help,h", "produce help message")
<<<<<<< HEAD
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files"); //change to comma seperated!!!!!1
=======
        //tried to change it to comma seperated, but getting headache!!!!! It's not standard and it takes time to handle it with tokenizer and a namespace
        //("bapprovers,b", po::value<mylist_option>()->multitoken(), "List of approvers")
        //("mattr", po::value<lli::CommaSeparatedVector>(&MAttrs), "Target specific attributes (-mattr=help for details)");
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files"); 
>>>>>>> refs/remotes/origin/master
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
<<<<<<< HEAD
    cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; 
=======
    //cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; 
>>>>>>> refs/remotes/origin/master
}

void TwitterCodebaseApprovalSystem::dir_indexing(){
    string line;
<<<<<<< HEAD
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
=======
    fs::path dir_path = ".";//or repo (shorter path)

    for ( fs::recursive_directory_iterator end, dir_it("."); dir_it != end; ++dir_it ) {//
        if (fs::is_regular_file( (dir_it.status()))){ 
            dir_path = dir_it->path();
            if (dir_path.filename() == DEPENDENCIES_FILE_NAME)
                get_dir_dependencies(dir_path);
        }
    }
    /*
        cout << "DEBUG" << endl;
        for(const auto & dd: dir_dependencies){
        cout << "[" << dd.first << "]={";
        for(const auto& ddd: dd.second)
            cout <<  ddd << ", ";
        cout << "}\n";    
    }*/

    get_required_approvals();

    /*
    cout << "DEBUG" << endl;
    for(const auto & cf: required_approvals){
        cout << "[" << cf.first << "]={";
        for(const auto& cfo: cf.second)
            cout <<  cfo << ", ";
        cout << "}\n";    
    }
    */

}

void TwitterCodebaseApprovalSystem::get_dir_dependencies(fs::path &dir_path){
    string line;
    fs::ifstream file(dir_path);
    while(getline(file, line)){
        dir_dependencies["./"+line].push_back(dir_path.parent_path().string());
    }
}
vector<string> TwitterCodebaseApprovalSystem::get_dir_direct_owners(string dir_path_str, hashmap_v & dir_direct_owners){
    string line;
    fs::path dir_path(dir_path_str);
    while(fs::exists(dir_path)){
        if( fs::exists(dir_path/OWNERS_FILE_NAME) ){
            fs::ifstream file(dir_path/OWNERS_FILE_NAME);
            while(getline(file, line))
                dir_direct_owners[dir_path_str].push_back(line);
        }
        dir_path = dir_path.parent_path();//goes all the way to the top
    }
    return dir_direct_owners[dir_path_str];
}


void TwitterCodebaseApprovalSystem::get_dir_owners(string changed_file, hashmap_v & dir_direct_owners){
    unordered_map<string, bool> visited_dir;

    fs::path changed_file_path("./"+changed_file);
    string dir_path_str = changed_file_path.parent_path().string();

    stack<string> stack;
    stack.push(dir_path_str);
    while(!stack.empty()){//DFS to get all owners: direct or through dependencies
        dir_path_str = stack.top();
        stack.pop();

        if(visited_dir.find(dir_path_str) == visited_dir.end()){// prevent circular dependency
            visited_dir[dir_path_str]=true; 
            if(dir_direct_owners.find(dir_path_str) == dir_direct_owners.end()) //improve performance for large FS if obtained owner before via other changed file or other routes   
                get_dir_direct_owners(dir_path_str, dir_direct_owners);
            for(const auto & owners : dir_direct_owners[dir_path_str])
                required_approvals[dir_path_str].insert(owners);
        }
        //cout << "DEBUG: " << dir_path_str << endl;
        for(const auto & dep_dir_path_str : dir_dependencies[dir_path_str])      //cout << "DEBUG 2: " << dep_dir_path_str << endl;
            if(visited_dir.find(dep_dir_path_str) == visited_dir.end()) //not seen before
                stack.push(dep_dir_path_str);
    }
}

void TwitterCodebaseApprovalSystem::get_required_approvals(){
    for(const auto & changed_file : changed_files){
        hashmap_v dir_direct_owners;//storing dir owners to avoid redundant owner finding (if foudn from differnt route)
        get_dir_owners(changed_file, dir_direct_owners);
    }
}

bool TwitterCodebaseApprovalSystem::check_dir_has_approval(string dir_to_check){
        for(const auto & app: approvers)
            if(required_approvals[dir_to_check].find(app) != required_approvals[dir_to_check].end())
                return true;
    return false;
}

bool TwitterCodebaseApprovalSystem::is_approved(){
    for(const auto & dir_to_check : required_approvals)
        if(!check_dir_has_approval(dir_to_check.first))
            return false;
    return true;
}

>>>>>>> refs/remotes/origin/master
int main(int argc, char** argv){

    TwitterCodebaseApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
<<<<<<< HEAD
    else cout << "Insufficient approvals" << endl;
=======
    else
        cout << "Insufficient approvals" << endl;
>>>>>>> refs/remotes/origin/master

    return 0;
}

<<<<<<< HEAD

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

=======
>>>>>>> refs/remotes/origin/master
