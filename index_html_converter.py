Import("env")
import sys
import os

from subprocess import call

passwordFileName = "password.txt"

def before_build_html(source, target, env):
    print "##### before_build - Converting index.html to index_html.h #####\n"
    index_html_file = open("src/index_html.h", "w")
    call(["xxd", "-i", "web/index.html"], stdout = index_html_file)
    index_html_file.close()


def before_build_auth(source, target, env):
    if os.path.isfile(passwordFileName):

        file_conn = open('password.txt','r')
        data = file_conn.readlines()
        if (len(data) > 0):
            ciphertext = data[0]

        file_conn.close()
        fileConnection = open("src/auth.h", "w")
        fileConnection.write('const char * ciphertext = "' + ciphertext + '";\n')
        fileConnection.close()

    else:
        print "warning no auth found. try running generate_password.py"

env.AddPreAction("$BUILD_DIR/src/RobotControlServer.o", before_build_html)
#env.AddPreAction("$BUILD_DIR/src/RobotControlServer.o", before_build_auth)
