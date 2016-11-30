import os
# exec('ls')
import subprocess
# subprocess.call(['bash', 'cloc-git-test.sh', 'https://github.com/darvid7/Life-of-Pi.git'])

import json

# 1 read json data
# 2 update sql lite db
#

import sqlite3

def update_db():
    con = sqlite3.connect('db')
    cur = con.cursor()
    cur.execute("DROP TABLE IF EXISTS LANGUAGES")
    cur.executescript("""
                        CREATE TABLE LANGUAGES
                            (language TEXT,
                            sloc_count INTEGER,
                            no_files INTEGER,
                            PRIMARY KEY(language))
                    """)    # can be done with cur.execute without formatting and string contact, but this looks nicer
    cur.execute("INSERT INTO LANGUAGES VALUES ('Python', 69, 1)")
    con.commit()    # need this to commit insert
    with open('data.json') as json_data:
        data = json.load(json_data)
        for language in data:
            if language not in ['header','SUM']:
                language_match = "Python"
                cur.execute('SELECT language, sloc_count, no_files FROM Languages WHERE language=?', (language_match,))    # , means there are other things after this entry
                result = cur.fetchall()
                # gives back a row's data if something, else empty array
                print(result)
                if result: # row in table, just updated
                    sloc = result[0][1]
                    no_files = result[0][2]
                else:   # insert
                # if in sql table, just update
                    cur.execute('INSERT INTO Language Values (?,?,?)', (1,2,3))
                # else if not in sql table, create row

        print(data)
        print(data["Python"])
        for thing in data:
            print(thing)
update_db()


# In computer science and technology, a database cursor is a control structure that enables traversal over the records in a database.