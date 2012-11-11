import os
import sys

root = os.environ["GELPATH"]

DLLs = ["contrib/glew-1.9.0/bin/glew32.dll",
        "contrib/freeglut/bin/freeglut.dll",]

def __main__():

    tgtPath = sys.argv[1];
    for dll in DLLs:
        cmd = "copy " + os.path.normpath(os.path.join(root,dll)) + " " + tgtPath
        os.system(cmd)
        #print cmd
    
__main__()