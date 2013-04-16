import os
import sys
import filecmp

root = os.environ["GELPATH"]

DLLs = ["contrib/glew-1.9.0/bin/glew32.dll",
        "contrib/freeglut-2.8.1/lib/x86/freeglut.dll",]

def __main__():

    tgtPath = sys.argv[1];
    for dll in DLLs:
        srcfile = os.path.normpath(os.path.join(root,dll));
        tgtfile = os.path.normpath(os.path.join(tgtPath,dll.rsplit("/",1)[1]));
        if not filecmp.cmp(srcfile,tgtfile):
            cmd = "copy " + os.path.normpath(os.path.join(root,dll)) + " " + tgtPath
            os.system(cmd)
        #print cmd
    
__main__()