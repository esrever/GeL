import os
import sys
import filecmp
import os.path

root = os.environ["GELPATH"]

DLLs = ["contrib/glew-1.9.0/bin/glew32.dll",
        "contrib/freeglut-2.8.1/lib/x86/freeglut.dll",
        "contrib/anttweakbar/lib/anttweakbar.dll",
        "contrib/FreeImage/Dist/FreeImage.dll"]

def __main__():

    tgtPath = sys.argv[1];
    for dll in DLLs:
        srcfile = os.path.normpath(os.path.join(root,dll));
        tgtfile = os.path.normpath(os.path.join(tgtPath,dll.rsplit("/",1)[1]));
        if (not os.path.isfile(tgtfile)) or (not filecmp.cmp(srcfile,tgtfile)):
            cmd = "copy " + os.path.normpath(os.path.join(root,dll)) + " " + tgtPath
            os.system(cmd)
        #print cmd
    
__main__()