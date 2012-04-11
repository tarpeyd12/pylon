./pylon -debug -bench --forcesingle -numsim 1
rm *.txt && gprof -p pylon gmon.out > flatprofile.txt && gprof -q pylon gmon.out > callgraphprofile.txt && gedit *.txt
