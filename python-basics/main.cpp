#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <exception>
#include <unordered_set>
#include <unordered_map>

using namespace std;
namespace po = boost::program_options; //using namespace boost;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); return os;}


class TwitterApprovalSystem{
private:
    string repo_path;
    vector<string> approvers, changed_files, required_approvers, dependencies;
    void process_program_options(const int ac, const char *const av[]);
    void get_dependecies(string path);
    void get_owners(string path);
    unordered_map<string, vector<string>> get_approvers();
public:
    TwitterApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
    }
    bool is_approved();
};

void TwitterApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    desc.add_options()
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers") //("help,h", "produce help message")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files");
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
    }
    catch(exception& e){cout << e.what() << endl;exit( EXIT_FAILURE );}
    cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; //cout << vm["changed-files"].as< vector<string> >();

}

unordered_map<string, vector<string>> TwitterApprovalSystem::get_approvers(){
    unordered_set<string> visited_path; //make sure set is faster than map
    string current_path, parent_path;
    unordered_map<string, vector<string>> required_approvers;

    while(!changed_files.empty()){ ///!!!! use  stack to do one operatn?!! vetcor has better performace tho!!!!
        current_path = changed_files.front;
        changed_files.pop_back(); 
        //if not visited 
        visited_path.insert(current_path);
        //get OWNERS
        
        //Hashmapp? STL unorder_map is fast


        //get DEPENDECIES ??????? of this dir ot everything deps on this CHECK WITH TWITTER
        //add to stack

        cout << "DEBUD: not empty" << endl;
        return required_approvers;
    }
}

bool TwitterApprovalSystem::is_approved(){
    if(required_approvers == approvers) //handle order!!!! == is fast but NO ORDER
        return true;
    return false;
}
int main(int argc, char** argv){
    TwitterApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
    else cout << "Insufficient approvals" << endl;
    return 0;
}

function(){
    
    /dir1
        OWN={root,usr}
    /dir2
        DEP={dir1}
        OWN={usr}

    unordered_map<string, vector<string>> dir_owners;
    // /dir1 --> [root, usr]
    // /dir2 --> [usr]
    unordered_map<string, vector<string>> dir_dependencies;
    // /dir1 --> [dir2]
    
    unordered_map<string, vector<vector<string>>> dir_owners_and_dependencies;
    // /dir1 --> [ [/dir1, root, usr] [/dir2, usr] ]
    // /dir2 --> [ [/dir2, usr] ]

    // I one-time walk through all direcories from "./" 
    // where each directory has owner and may has dependency files 
    // and read their content and build hash table(s)
    

    // Later in this program, I will do some look-up or find() operation to check ownership and dependencies.

}