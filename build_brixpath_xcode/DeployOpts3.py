# coding=utf-8

###### Options ######

options={}

options["<config>"]=ur'Default'
options["<os>"]=ur'playbook'
options["appdata"]=ur'/Users/codemanki/.config/marmalade/DeployTool'
options["build"]=ur'ARM GCC Release'
options["cmdline"]=['/Developer/Marmalade/6.1/s3e/makefile_builder/mkb.py', '--buildenv=xcode', '/Users/codemanki/projects/blackberry/brixpath/brixpath.mkb', '--deploy-only']
options["configlist"]=ur'Default ,'
options["device"]=ur'"{"localdir}/Deploy.py" device "{"tempdir}/DeployOpts.py" {hasmkb}'
options["dir"]=ur'/Users/codemanki/projects/blackberry/brixpath/build_brixpath_xcode'
options["folder"]=ur'"{"localdir}/Deploy.py" folder "{"tempdir}/DeployOpts.py" {hasmkb}'
options["hasmkb"]=ur'nomkb'
options["helpfile"]=ur'../docs/Deployment.chm'
options["helppage"]=ur'0'
options["lastdir"]=ur'/Users/codemanki/projects/blackberry/brixpath/build_brixpath_xcode'
options["mkb"]=ur'/Users/codemanki/projects/blackberry/brixpath/brixpath.mkb'
options["mkbdir"]=ur'/Users/codemanki/projects/blackberry/brixpath'
options["mkbfile"]=ur'brixpath.mkb'
options["outdir"]=ur'/Users/codemanki/projects/blackberry/brixpath/build_brixpath_xcode'
options["resdir"]=ur'/Developer/Marmalade/6.1/Applications/DeployTool.app/Contents/Resources/'
options["s3edir"]=ur'/Developer/Marmalade/6.1/s3e/'
options["stage"]=ur'build'
options["target"]=ur'brixpath'
options["task"]=ur'Default'
options["tasktype"]=ur'Package'

###### Tasks ######

tasks=[]

### Task Default:playbook ###

t={}
tasks.append(t)
t["tasktype"]="Package"
t["<config>"]="Default"
t["os"]="playbook"
t["endDir"]="/Users/codemanki/projects/blackberry/brixpath/build_brixpath_xcode/deployments/default/playbook/release"
t["hostname"]=["192.168.1.101"]
t["loader"]=["Default"]
t["password"]=["13560"]
