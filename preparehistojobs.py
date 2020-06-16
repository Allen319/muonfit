#!/usr/bin/env python
import sys
import re
import os
import yaml
import shutil

def prepare_job_script():
    global outputDirectory  
#if os.path.exists(jobsDirectory+'/'+'mkhis_'+fileName+'.sh'):
#       os.remove(jobsDirectory+'/'+'mkhis_'+fileName+'.sh') 
#    os.mknod(jobsDirectory+'/'+'mkhis_'+fileName+'.sh')
    os.system("cp makehistos "+jobsDirectory)
    os.system("cp fitMuons.C "+ jobsDirectory)
    for fileName in samples:
        scriptFile = open(jobsDirectory+'/'+'mkhis_'+fileName+'.sh','w')
        scriptLines = ''
  #  scriptLines += 'source $VO_CMS_SW_DIR/cmsset_default.sh\n'
        scriptLines += 'export VO_CMS_SW_DIR=/nfs/soft/cms\n'
        scriptLines += 'export SCRAM_ARCH=slc6_amd64_gcc530\n'
        scriptLines += 'export BUILD_ARCH=slc6_amd64_gcc530\n'
        scriptLines += ('export INITDIR='+jobsDirectory+'\n')
        scriptLines += ('cd $INITDIR\n')
        scriptLines += 'eval `scramv1 runtime -sh`\n'
#    scriptLines += 'ulimit -c 0;\n'
    #scriptLines += 'cp '+os.getcwd()+'/makehistos .;\n'
        scriptLines += 'hostname ;\n'
        scriptLines += ("date;\n")
#        scriptLines += ("dccp "+aFile+" inputFile_"+str(jobID)+"_"+str(iteFileInJob)+".root;\n")
		    #scriptLines += ("./makehistos fileName="+fileName+";\n")
        scriptLines += ("./makehistos fileName="+fileName+" ref=Mu17;\n")
        scriptFile.write(scriptLines)
        scriptFile.close()
	
        jobsFiles = open(jobsDirectory+"/sendJobs.cmd","a")
        jobsFiles.write("qsub  "+jobsDirectory+'/'+'mkhis_'+fileName+'.sh\n')
        jobsFiles.close()

def main():

    global jobsDirectory
    global outputDirectory
    global mergedDirectory
    outputDirectory = os.getcwd()
    jobsDirectory = outputDirectory+"/outputs_tightNoOnePairCut"
    mergedDirectory= outputDirectory+"/outputs"
    plotsDirectory = outputDirectory+"/outputs"
    if not os.path.exists(outputDirectory):
        os.makedirs(outputDirectory) 
    if not os.path.exists(jobsDirectory):
        os.makedirs(jobsDirectory)
    else:
        action = raw_input("\033[1;31m ATTENTION: perform this analysis will delete all former OUTPUTS ! Continue? \033[0;m y/n ")
        if action == 'Y' or action == 'y' or action == 'yes':
            print("Ok, I will do it ")
            shutil.rmtree(jobsDirectory)
            os.makedirs(jobsDirectory)
    prepare_job_script()
	

if __name__ == '__main__':
    f = open(r'config.yaml')
    config = yaml.load(f)#Loader=yaml.FullLoader)
    samples = config['sample']
    #refs = config['ref']
    main()


