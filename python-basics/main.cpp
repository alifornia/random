#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <exception>

using namespace std;
namespace po = boost::program_options; //using namespace boost;

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){copy(v.begin(), v.end(), ostream_iterator<T>(cout, " ")); return os;}


class TwitterApprovalSystem{
private:
    void process_program_options(const int ac, const char *const av[]);
public:
    TwitterApprovalSystem(int argc, char** argv){
        process_program_options(argc, argv);
    }
};

void TwitterApprovalSystem::process_program_options(const int ac, const char *const av[]){
    po::options_description desc("Usage:");
    vector<string> approvers, changed_files;
    desc.add_options()
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers") //("help,h", "produce help message")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files");
    try{po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
    }catch(exception& e){cout << e.what() << endl;exit( EXIT_FAILURE );}
    cout << "Approveres: " << approvers << " | Changed files: " << changed_files << endl; //cout << vm["changed-files"].as< vector<string> >();

}

int main(int argc, char** argv){
    TwitterApprovalSystem app(argc, argv);

    return 0;
}