//requirement: c++ 1z on mac or c++11x on linux, g++, boost (check versions later)
//build
//g++ -std=c++1z twest.cpp -l boost_program_options -l boost_system -l boost_filesystem

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <exception>
#include <unordered_set>
#include <unordered_map>

#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/path.hpp"
#include <boost/tokenizer.hpp>



#define DEPENDENCIES_FILE_NAME    "DEPENDENCIES"
#define OWNERS_FILE_NAME          "OWNERS"

using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
typedef unordered_map<string, vector< string > > hashmap_v;
typedef unordered_map<string, set <string> >     hashmap_s;    


template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}


class DirDependenciesOwners{ // maybe for larger OO design but not needed for this quesion
public:
    vector<string> dependencies;
    vector<string> owners; 
};

class TwitterCodebaseApprovalSystem{
private:
    string repo_path;
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

public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
        repo_path=(fs::current_path()).string(); // shoudl be this (because one may run the command in a different directory): repo_path=(changed_files[0] - fs::current_path()).string();    //cout << fs::system_complete(argv[0]) << endl;
        dir_indexing();
    }
    bool is_approved();
};

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

void TwitterCodebaseApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    desc.add_options()
        ("help,h", "produce help message")
        //tried to change it to comma seperated, but getting headache!!!!! It's not standard and it takes time to handle it with tokenizer and a namespace
        //("bapprovers,b", po::value<mylist_option>()->multitoken(), "List of approvers")
        //("mattr", po::value<lli::CommaSeparatedVector>(&MAttrs), "Target specific attributes (-mattr=help for details)");
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files"); 
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
    //cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; 
}

void TwitterCodebaseApprovalSystem::dir_indexing(){
    string line;
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

int main(int argc, char** argv){

    TwitterCodebaseApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
    else
        cout << "Insufficient approvals" << endl;

    return 0;
}

