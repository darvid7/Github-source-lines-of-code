""" Tests for counting source line of code in a repository. """
import unittest
import subprocess
import os

SCRIPTS = "../scripts/"
OUTPUT_JSON = "../data/data.json"

class TestCountSlocInARepository(unittest.TestCase):

    def setUp(self):
        self.expected = (
            "\n"
            "github.com/AlDanial/cloc v 1.68  T=0.18 s (149.0 files/s, 5435.6 lines/s)\n"
            "-------------------------------------------------------------------------------\n"
            "Language                     files          blank        comment           code\n"
            "-------------------------------------------------------------------------------\n"
            "C                               14             91            170            540\n"
            "C/C++ Header                    12             36             84             48\n"
            "Markdown                         1              7              0              9\n"
            "-------------------------------------------------------------------------------\n"
            "SUM:                            27            134            254            597\n"
            "-------------------------------------------------------------------------------\n"
        )

        mock_repo_path = os.path.join(os.getcwd(), "..", "mock_repos", "temp-sloc-repo")
        p = subprocess.Popen(["cloc", "--quiet", mock_repo_path], stdout=subprocess.PIPE)
        self.output, self.error = p.communicate()
        self.assertEqual(self.error, None)
        self.output = self.output.decode("utf-8")

    def test_count_sloc_in_a_repoository(self):
        self.maxDiff = None
        # Remove first two elements as first one is just whitespace, second is relative to run time of script.
        output_split = self.output.split("\n")[2:]
        expected_split = self.expected.split("\n")[2:]
        self.assertEqual(output_split, expected_split)

if __name__ == "main":
    unittest.main()



