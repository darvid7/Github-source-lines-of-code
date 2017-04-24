"""Python Script to count all Source Lines of Code for a Github user."""

import subprocess
import getpass
import sqlite3
import json
import argparse
import progressbar
from github import Github
from github import BadCredentialsException

SCRIPTS = "./scripts/"
DATAPATH = "./data/"
class Repository:
    def __init__(self, github_repository):
        self.__github_repository = github_repository

    @property
    def git_url(self):
        return self.__github_repository.git_url

    @property
    def full_name(self):
        return self.__github_repository.full_name

class GithubInstance:

    def __init__(self, username, password):
        self.instance = Github(username, password)

    def get_repositories(self):
        """Returns list of Github repositories names of form username/repository_name."""
        return [Repository(repo) for repo in self.instance.get_user().get_repos()]


class LanguageReader:
    def __init__(self, data_path, operation_verbosity):
        self.__operation_verbosity = operation_verbosity
        self.__data_path = data_path
        self.__languages = dict()

    def get_language(self, filter_language):
        return self.__languages[filter_language]

    def update_languages(self):
        """Read JSON shell script writes to and update languages array."""
        with open(self.__data_path + "data.json") as json_file:
            data = json.load(json_file)
            for language in data:
                if language not in ['header', 'SUM']:
                    language_match = language
                    if language in self.__languages:
                        result = self.__languages[language]
                        if self.__operation_verbosity == 2:
                            print("Updating  %s in language collection" % language)
                        result[1] += data[language_match]["code"]
                        result[2] += data[language_match]["nFiles"]
                    else:
                        if self.__operation_verbosity == 2:
                            print("Inserting %s into language collection" % language)
                        sloc = data[language_match]["code"]
                        no_files = data[language_match]["nFiles"]
                        self.__languages[language_match] = [language, sloc, no_files]

    def get_all_languages(self):
        return list(self.__languages.values())


def main():
    parser = argparse.ArgumentParser(description="Script to count all source lines of code for a Github user.")
    # Positional arguments (required).
    parser.add_argument("username", type=str,
                        help="String, Github username")
    # Optional arguments.
    parser.add_argument("-l", "--sort_by_language", type=bool, help="Boolean, sort results by language.", default=False)
    parser.add_argument("-c", "--count_descending", type=bool,
                        help="Booleanm, sort results by SLOC count descending, if False sorts in ascending order.",
                        default=True)
    parser.add_argument("-o", "--only_owner", type=bool, help="Boolean, only check repositories that the user owns.",
                        default=False)
    parser.add_argument("-v", "--verbosity", type=int, default=0, help="Integer, level of verbosity."
                                                                       "\n0: Only show progress bar."
                                                                       "\n1: Print out repository being processed."
                                                                       "\n2: Print every UPDATE and INSERT to language collection.")
    args = parser.parse_args()
    password = getpass.getpass()

    try:
        g = GithubInstance(args.username, password)
        user_repositories = g.get_repositories()
        language_reader = LanguageReader(DATAPATH, args.verbosity)
        repository_count = 0
        with progressbar.ProgressBar(max_value=len(user_repositories)) as prog_bar:
            for repository in user_repositories:
                if args.only_owner:
                    if not (args.username+"/" == repository.full_name[0:len(args.username)+1]):
                        continue  # Only process user owned repositories.
                url = repository.git_url
                if args.verbosity == 1:
                    print("Processing repository: %s", url)
                run_cloc_script(url)  # Writes data to JSON.
                language_reader.update_languages()  # Update languages from JSON file.
                repository_count += 1
                prog_bar.update(repository_count)
        print("Finished processing repositories...")
        language_tuples = language_reader.get_all_languages()
        if args.sort_by_language:
            language_tuples.sort(key=lambda t:t[0])
        if args.count_descending:
            language_tuples.sort(key=lambda t:t[1], reverse=True)
        else:
            language_tuples.sort(key=lambda t:t[1])
        print("\nLanguage | SLOC | Num Files")
        for language_tuple in language_tuples:
            print(language_tuple)
    except BadCredentialsException:
        print("Invalid Credentials")


def run_cloc_script(repository_url):
    """Call shell script to clone repo and count Source Lines of Code."""
    # TODO: Catch error: Complex regular subexpression recursion limit (32766) exceeded at /usr/local/bin/cloc line 7272.
    try:
    	subprocess.check_output(['bash', SCRIPTS+'cloc-git-test.sh', repository_url])
    except subprocess.CalledProcessError as e:
	    print(e)

if __name__ == "__main__":
    main()
