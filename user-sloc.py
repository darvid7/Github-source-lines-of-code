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


class GithubInstance:

    def __init__(self, username, password):
        self.instance = Github(username, password)

    def get_repositories(self):
        """Returns list of Github repositories names of form username/repository_name."""
        return [repo.full_name for repo in self.instance.get_user().get_repos()]


class DatabaseConnection:

    def __init__(self, data_path, verbosity):
        self.data_path = data_path
        self.cur, self.con = self.initialize()
        self.operation_verbosity = verbosity

    def initialize(self):
        """Initialize db to have a single table Languages with no entries."""
        con = sqlite3.connect(self.data_path + "db")
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
        self.cur.execute("SELECT language, sloc_count, no_files FROM Languages WHERE language=?", (language,))
        result = self.cur.fetchall()
        return result

    def update_db(self):
        """Read JSON shell script writes to and update db."""
        with open(self.data_path + "data.json") as json_file:
            data = json.load(json_file)
            for language in data:
                if language not in ['header','SUM']:
                    language_match = language
                    result = self.get_language_from_db(language_match)
                    if result:
                        if self.operation_verbosity == 2:
                            print("Updating  %s in db" % language)
                        sloc = result[0][1]
                        no_files = result[0][2]
                        sloc = data[language_match]["code"] + sloc
                        no_files += data[language_match]["nFiles"]
                        self.cur.execute("UPDATE Languages SET sloc_count=?, no_files=? WHERE language=?",
                                         (sloc, no_files, language_match))
                        self.con.commit()    # need this to see changeS!
                    else:
                        if self.operation_verbosity == 2:
                            print("Inserting %s into db" % language)
                        sloc = data[language_match]["code"]
                        no_files = data[language_match]["nFiles"]
                        self.cur.execute("INSERT INTO Languages Values (?,?,?)", (language_match, sloc, no_files))
                        self.con.commit()

    def get_all_languages(self):
        self.cur.execute("SELECT * FROM Languages")
        return self.cur.fetchall()


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
                                                                       "\n2: Print every UPDATE and INSERT to db.")
    args = parser.parse_args()
    password = getpass.getpass()

    try:
        g = GithubInstance(args.username, password)
        user_repositories = g.get_repositories()
        base_url = "https://github.com/"
        db = DatabaseConnection(DATAPATH, args.verbosity)
        db.initialize()
        repository_count = 0
        with progressbar.ProgressBar(max_value=len(user_repositories)) as prog_bar:
            for repository in user_repositories:
                if args.only_owner:
                    if not (args.username+"/" == repository[0:len(args.username)+1]):
                        continue  # Only process user owned repositories.
                url = base_url + repository + ".git"
                if args.verbosity == 1:
                    print("Processing repository: %s", url)
                run_cloc_script(url)  # Writes data to JSON.
                db.update_db()  # Update db from JSON file.
                repository_count += 1
                prog_bar.update(repository_count)
        print("Finished processing repositories...")
        language_tuples = db.get_all_languages()
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
    subprocess.call(['bash', SCRIPTS+'cloc-git-test.sh', repository_url])


if __name__ == "__main__":
    main()