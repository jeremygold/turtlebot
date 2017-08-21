Import("env")
import sys
import os

from subprocess import call

def before_build_html(source, target, env):
    print "##### before_build - Converting index.html to index_html.h #####\n"
    index_html_file = open("src/index_html.h", "w")
    call(["xxd", "-i", "web/index.html"], stdout = index_html_file)
    index_html_file.close()

env.AddPreAction("$BUILD_DIR/src/RobotControlServer.o", before_build_html)
