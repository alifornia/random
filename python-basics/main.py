'''
The Challenge
At Twitter, all changes to source code are required to be approved by other engineers responsible for the source files that are affected by the changes. As a simplified model, assume each directory may optionally contain two special files that contain information used to identify who must approve a change:
DEPENDENCIES files list the paths to other directories that its containing directory depends upon. Paths must be relative to the root directory of the source code repository. A directory is considered to be affected by a change if a file or directory in that directory or in one of its transitive dependencies is modified (including creation and deletion).
OWNERS files list the login names of all of the engineers who are able to approve changes affecting a directory. If there is no one listed in the OWNERS file or it does not exist then the parent directories OWNERS file should be applied.
For example, consider the following directory tree:
 x/
   DEPENDENCIES = "y\n"
   OWNERS = "A\nB\n"
 y/
   OWNERS = "B\nC\n"
   file
If a change modifies y/file, it affects both directories y (contains file) and x (depends on y). This change must at a minimum be approved by either B alone (owner of x and y) or both A (owner of x) and C (owner of y).
Build a command line tool that validates the correct people have approved the changes made to a set of files.
As an example, the following is expected to work on the example directory structure we have provided to you.
$ validate_approvals --approvers alovelace ghopper --changed-files src/com/twitter/follow/Follow.java src/com/twitter/user/User.java
Approved
$ validate_approvals --approvers alovelace --changed-files src/com/twitter/user/User.java
Insufficient approvals
Expectations
The challenge should take about three hours to complete.
Choice of programming language is entirely up to you.
Documentation
README with instructions on how to build and run your program.
Code is tested

How do i know what is the root directory? is the cmd line tool run from inside the dir?

python3 main.py -v alovelace -cf src/com/twitter/follow/Follow.java
'''

#!/usr/bin/python3


import sys
import argparse
from pathlib import Path
from collections import deque, defaultdict


class Approvals_Validator:
    def __init__(self):
        parser = argparse.ArgumentParser(description='Validate approvals')
        parser.add_argument('-v', '--validators', nargs='+',
                            help='validators for files')
        parser.add_argument('-cf', '--changed-files', nargs='+',
                            help='changeddd files')
        args = parser.parse_args()
        self.validators = args.validators
        self.changed_files = args.changed_files
        self.project_root_dir = self.__get_project_root__()

    def __get_project_root__(self):
        '''
        returns the path of the repository
        '''
        return Path().cwd()

    def __get_enclosing_directory__(self, path):
        '''
        returns the parent directory of a file or dir
        given the path
        '''
        return str(Path(path).parent)

    def __read_file_contents__(self, file_path):
        contents = []
        with open(file_path, 'r') as ip_file:
            for line in ip_file:
                contents.append(line.strip())
        return contents

    def __get_owners__(self, dir_name):
        owners = []
        curr_dir = dir_name
        owners_file = '/OWNERS'
        while(not self.__file_exists__(curr_dir, owners_file)):
            curr_dir = self.__get_enclosing_directory__(curr_dir)
        owners = self.__read_file_contents__(str(curr_dir)+owners_file)
        return owners

    def __file_exists__(self, parent_dir, file_name):
        has_dep = False
        if Path(parent_dir+file_name).is_file():
            has_dep = True
        return has_dep

    def __get_dependencies__(self, parent_dir, dependencies_file):
        dependencies = []
        if self.__file_exists__(parent_dir, dependencies_file):
            dependencies = self.__read_file_contents__(
                                parent_dir+dependencies_file)
        return dependencies

    def get_required_approvers(self):
        #print("DEBUG: ", self.validators)
        #print("DEBUG: ", self.changed_files)
        
        def update_result(dictionary, keys, value):
            for key in keys:
                dictionary[key].append(value)
            #print("DEBUG: ", dictionary)
        
        stack_files = deque()
        required_approvers = defaultdict(list)
        # initial set of files to be reviewed
        stack_files.extend(self.changed_files)
        print("DEBUG: ", stack_files)

        visited = set()

        while stack_files:
            # print("stack:", stack_files)
            curr_listing = stack_files.popleft()
            print("curr_listing:", curr_listing)
            parent_dir = self.__get_enclosing_directory__(curr_listing)
            print("parent:", parent_dir)
            # use visited to keep track of visited directories
            if parent_dir not in visited:
                visited.add(parent_dir)
                print(stack_files, visited)
                # find owners for each file
                # and add to required approvers
                owners = self.__get_owners__(parent_dir)
                # print("owners:", owners)
                update_result(required_approvers, owners, parent_dir)

                # if there are dependencies, add to stack
                dependencies_file = '/DEPENDENCIES'
                dependent_files = self.__get_dependencies__(parent_dir, dependencies_file)
                if dependent_files:
                    stack_files.extend(dependent_files)
            print("\n")
        return required_approvers

    def has_sufficient_approvers(self, required_approvers):
        # TO DO
        pass

    def validate_approvals(self):
        required_approvers = self.get_required_approvers()
        print("required:", required_approvers)
        # self.has_sufficient_approvers(required_approvers)

def main():
    validator = Approvals_Validator()
    sufficient = validator.validate_approvals()
    if sufficient:
        print("Approved")
    else:
        print("Insufficient approvals")

if __name__ == '__main__':
    main()

