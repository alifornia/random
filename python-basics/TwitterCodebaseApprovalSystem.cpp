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
ostream& operator<<(ostream& os, const vector<T>& v){ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); 
    return os;
}


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

public:
    TwitterCodebaseApprovalSystem(int argc, char** argv){
        //repo_path===CWD root repo 
        process_program_options(argc, argv);
    }
    bool is_approved();
};

void TwitterCodebaseApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    desc.add_options()
        ("help,h", "produce help message")
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
    cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; 
    //FASTERRRR??? IDK cout << vm["changed-files"].as< vector<string> >();

}

string TwitterCodebaseApprovalSystem::get_parent_dir(string dir_path){
    string parent_dir_path;
    //use boost util to get parent path or just truncate
    return parent_dir_path;
}
vector<string> TwitterCodebaseApprovalSystem::get_dependecies(string dir_path){
    vector<string> dependencies;
    //read DEPS file if exist add to dependencies
    return dependencies;
}

vector<string> TwitterCodebaseApprovalSystem::get_owners(string dir_path){
    vector<string> owners;
    //while( if no OWNERS exist in dir_path) goto parent
    //read OWNERS file 
    return dependencies;
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
    TwitterCodebaseApprovalSystem app(argc, argv);
    if(app.is_approved())
        cout << "Approved" << endl;
    else cout << "Insufficient approvals" << endl;
    return 0;
}
