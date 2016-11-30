"""
Python Script to count all sloc for a github user

need cloc-git.sh in the same folder and cloc (count lines of code)
see http://stackoverflow.com/questions/26881441/can-you-get-the-number-of-lines-of-code-from-a-github-repository

requires:
- PyGithub library https://github.com/PyGithub/PyGithub

"""
import sys
import subprocess
import getpass                                                  # read pw without echo
from github import Github
from github import BadCredentialsException

languages = ["Python", "Java"]

def get_repos(username, password):
    github_object = Github(username, password)
    return [repo.full_name for repo in github_object.get_user().get_repos()]

def run_cloc_script(url):
    # subprocess.call(['cloc-git.sh', url])
    exec('ls')

def count_user_sloc(username, password):
    user_repos = get_repos(username, password)                  # all repos the user owns/contributed to
    base_url = "https://github.com/"
    for repo_name in user_repos:
        url = base_url + repo_name + ".git"
        run_cloc_script(url)


if __name__ == "__main__":
    username = sys.argv[1]
    password = getpass.getpass()
    try:
        count_user_sloc(username, password)
    except BadCredentialsException:
        print("Invalid Credentials")
        sys.exit(0)
