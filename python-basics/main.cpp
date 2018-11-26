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

void process_program_options(const int ac, const char *const av[]){
    try{ //int opt;
    po::options_description desc("Usage:");
    vector<string> approvers;
    vector<string> changed_files;
    desc.add_options()
        //("help,h", "produce help message")/*("optimization", po::value<int>(&opt)->default_value(10), "optimization level")*/
        ("approvers,a", po::value(&approvers)->multitoken(), "List of approvers")
        ("changed-files,c", po::value(&changed_files)->multitoken(), "List of changed files");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);
    for(const auto & it : approvers) cout << it << endl;

    if (vm.count("help")) {cout << desc << "\n";return;}
    if (vm.count("approvers")){cout << "Approvers are: " << vm["approvers"].as< vector<string> >() << "\n";}
    if (vm.count("changed-files")){cout << "Changed files are: " << vm["changed-files"].as< vector<string> >() << "\n";}
    }catch(exception& e){cout << e.what() << endl;exit( EXIT_FAILURE );}
}
int main(int argc, char** argv){
    process_program_options(argc, argv);

    return 0;
}