# Python script to count all sloc for a github user

download/clone repo and extract contents

cd into folder

run using $python3 user-sloc [username] [optional: owner]

- username is your github username

- owner specifies the script to only look at repos you own

eg: $ python3 user-sloc.py darvid7 owner


**Requires**

- Python3

- unix like environment

- cloc http://cloc.sourceforge.net/

- PyGithub https://github.com/PyGithub/PyGithub

**To do:**

- add ignore language option

- add quiet option

- add ignore file lists

- add ignore extension

- nicer formatting of results

notes:

-  git clone https://github.com/darvid7/FIT2043.git -q

- ignore node modules, virtual env, flask, framework files etc