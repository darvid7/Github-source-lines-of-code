# Python/bash script to count all sloc for a github user

## To Use

download/clone repo and extract contents

cd into folder

run using $python3 user-sloc [username]

- username is your github username

- owner specifies the script to only look at repos you own

eg: $ python3 user-sloc.py darvid7 owner

## FLags

```
192-168-1-2:github-user-all-sloc David$ python3 user-sloc.py -h
usage: user-sloc.py [-h] [-l SORT_BY_LANGUAGE] [-c COUNT_DESCENDING]
                    [-o ONLY_OWNER] [-v VERBOSITY]
                    username

Script to count all source lines of code for a Github user.

positional arguments:
  username              String, Github username

optional arguments:
  -h, --help            show this help message and exit
  -l SORT_BY_LANGUAGE, --sort_by_language SORT_BY_LANGUAGE
                        Sort results by language.
  -c COUNT_DESCENDING, --count_descending COUNT_DESCENDING
                        Sort results by SLOC count descending, if False sorts
                        in ascending order.
  -o ONLY_OWNER, --only_owner ONLY_OWNER
                        Only check repositories that the user owns.
  -v VERBOSITY, --verbosity VERBOSITY
                        Level of verbosity. 0: Only show progress bar. 1:
                        Print out repository being processed. 2: Print every
                        UPDATE and INSERT to db.
```

## Sample output

```
192-168-1-2:github-user-all-sloc David$ python3 user-sloc.py darvid7 -o=True -l=True
Password: 
  8% (4 of 45) |##########                                                                                                              | Elapsed Time: 0:00:14 ETA: 0:02:33



```


**Requires**

- Python3

- unix like environment

- cloc http://cloc.sourceforge.net/

- PyGithub https://github.com/PyGithub/PyGithub

- progressbar lib

**To do:**

- add ignore language option

- add quiet option

- add ignore file lists

- add ignore extension

- nicer formatting of results

notes:

-  git clone https://github.com/darvid7/FIT2043.git -q

- ignore node modules, virtual env, flask, framework files etc

Note: This also counts private repositories.