# Python/bash script to count all sloc for a github user

## Usage

download/clone repo and extract contents

cd into folder

run using $python3 user-sloc [username]

- username is your github username

- owner specifies the script to only look at repos you own

eg: $ python3 user-sloc.py darvid7 owner

## FLags

```
192-168-1-2:github-user-all-sloc David$ python3 user-sloc.py darvid7 -h
usage: user-sloc.py [-h] [-l SORT_BY_LANGUAGE] [-c COUNT_DESCENDING]
                    [-o ONLY_OWNER] [-v VERBOSITY]
                    username

Script to count all source lines of code for a Github user.

positional arguments:
  username              String, Github username

optional arguments:
  -h, --help            show this help message and exit
  -l SORT_BY_LANGUAGE, --sort_by_language SORT_BY_LANGUAGE
                        Boolean, sort results by language.
  -c COUNT_DESCENDING, --count_descending COUNT_DESCENDING
                        Booleanm, sort results by SLOC count descending, if
                        False sorts in ascending order.
  -o ONLY_OWNER, --only_owner ONLY_OWNER
                        Boolean, only check repositories that the user owns.
  -v VERBOSITY, --verbosity VERBOSITY
                        Integer, level of verbosity. 0: Only show progress
                        bar. 1: Print out repository being processed. 2: Print
                        every UPDATE and INSERT to db.

```

## Sample output

```
192-168-1-2:github-user-all-sloc David$ python3 user-sloc.py darvid7 -o=True -l=True
Password: 
 64% (29 of 45) |############################################################################                                           | Elapsed Time: 0:20:31 ETA: 0:22:42
Finished processing repositories...

Language | SLOC | Num Files
('JavaScript', 743657, 6415)
('Markdown', 142645, 1244)
('Python', 139684, 960)
('JSON', 132866, 1291)
('XML', 84705, 254)
('CSS', 39598, 134)
('HTML', 31157, 264)
('PHP', 11044, 162)
('Java', 10349, 233)
('LESS', 7272, 87)
('XSLT', 4238, 29)
('CoffeeScript', 2588, 16)
('C', 2452, 53)
('YAML', 2444, 210)
('XSD', 2208, 6)
('SASS', 1787, 17)
('Assembly', 1371, 17)
('Swift', 962, 37)
('make', 848, 72)
('Bourne Again Shell', 365, 3)
('Groovy', 335, 18)
('INI', 308, 10)
('Bourne Shell', 300, 28)
('DOS Batch', 192, 3)
('C/C++ Header', 123, 31)
('ERB', 112, 2)
('TypeScript', 104, 2)
('Prolog', 83, 5)
('C++', 77, 2)
('Handlebars', 67, 4)
('Arduino Sketch', 65, 2)
('Go', 52, 4)
('C Shell', 17, 1)
('Ruby', 16, 2)
('Lisp', 12, 2)
('PowerShell', 4, 1)
```


**Requires**

- Python3

- unix like environment

- cloc http://cloc.sourceforge.net/

- PyGithub https://github.com/PyGithub/PyGithub

```
$ pip install PyGithub
```

- progressbar lib 

```
$ pip install progressbar2
```

**To do:**

- add ignore language option

- add quiet option

- add ignore file lists

- add ignore extension

- nicer formatting of results

- ignore frameworks

notes:

-  git clone https://github.com/darvid7/FIT2043.git -q

- ignore node modules, virtual env, flask, framework files etc

Note: This also counts private repositories.
