"""
Python Script to count all Source Lines of Code for a Github user.

need cloc-git.sh in the same folder and cloc (count lines of code)
see http://stackoverflow.com/questions/26881441/can-you-get-the-number-of-lines-of-code-from-a-github-repository

requires:
- PyGithub library https://github.com/PyGithub/PyGithub

"""
import sys
import subprocess
import getpass
import sqlite3
import json
import argparse
from github import Github
from github import BadCredentialsException

SCRIPTS = "./scripts/"
DATA = "./data/"

def main():
    parser = argparse.ArgumentParser(description="")
    # Positional arguments (required).
    parser.add_argument("user_name", type=str,
                        help="String, Github username")
    # Optional arguments.
    parser.add_argument("--sort_by_language", type=bool, help="Sort results by language", default=False)
    parser.add_argument("--sort_by_count_accending", type=bool, help="Sort results by SLOC count accenndung", default=False)

    args = parser.parse_args()
    print(args.user_name)


class GithubInstance:

    def __init__(self, username, password):
        self.instance = Github(username, password)

    def get_repositories(self):
        """Returns list of Github repositories names of form username/repository_name."""
        return [repo.full_name for repo in self.instance.get_user().get_repos()]


class DatabaseConnection:

    def __init__(self, database_path):
        self.cur, self.con = self.initialize(database_path)

    def initialize(self, database_path):
        """Initialize db to have a single table Languages with no entries."""
        con = sqlite3.connect(database_path + "db")
        cur = con.cursor()
        cur.execute("DROP TABLE IF EXISTS LANGUAGES")
        # Can be done with cur.execute without formatting and string contact, but this looks nicer.
        cur.executescript(
            """
            CREATE TABLE LANGUAGES
            (language TEXT,
            sloc_count INTEGER,
            no_files INTEGER,
            PRIMARY KEY(language))
            """
        )
        return cur, con

    def get_language_from_db(self, language):
        self.cur.execute("SELECT language, sloc_count, no_files FROM Languages WHERE language=?", language)
        result = self.cur.fetchall()
        return result

    def update_db(self):
        """Read JSON shell script writes to and update db."""
        with open(DATA + "data.json") as json_file:
            data = json.load(json_file)
            for language in data:
                if language not in ['header','SUM']:
                    language_match = language
                    result = self.get_language_from_db(language_match)
                    if result:
                        print("Updating  %s in db" % language)
                        sloc = result[0][1]
                        no_files = result[0][2]
                        sloc = data[language_match]["code"] + sloc
                        no_files += data[language_match]["nFiles"]
                        self.cur.execute("UPDATE Languages SET sloc_count=?, no_files=? WHERE language=?",
                                         (sloc, no_files, language_match))
                        self.con.commit()    # need this to see changeS!
                    else:
                        print("Inserting %s into db" % language)
                        sloc = data[language_match]["code"]
                        no_files = data[language_match]["nFiles"]
                        self.cur.execute("INSERT INTO Languages Values (?,?,?)", (language_match, sloc, no_files))
                        self.con.commit()


def count_user_sloc(username, password, check_owner = False):
    user_repos = get_repos(username, password)                  # all repos the user owns/contributed to
    # user_repos = ["darvid7/life-of-pi"]
    base_url = "https://github.com/"
    cur, con = initalize_db()
    for repo_name in user_repos:
        check_this = True
        if check_owner:
            if not (username+"/" == repo_name[0:len(username)+1]):          # only process repos that the user owns
                check_this = False
        if check_this:
            url = base_url + repo_name + ".git"
            run_cloc_script(url)
            update_db(cur, con)
    print("Finished processing repos...")
    print("Final SLOC Count")
    cur.execute("SELECT * FROM Languages")
    print(cur.fetchall())




def run_cloc_script(repo_url):
    """Call shell script to clone repo and count Source Lines of Code."""
    subprocess.call(['bash', SCRIPTS+'cloc-git-test.sh', repo_url])


if __name__ == "__main__":
    """
    username = sys.argv[1]
    password = getpass.getpass()
    # print("sys.argv: " + str(sys.argv))
    check_owner = False
    if "owner" in sys.argv:
        check_owner = True
    try:
        # count_user_sloc(username, password, check_owner)
    except BadCredentialsException:
        print("Invalid Credentials")
        sys.exit(0)
    """
    main()