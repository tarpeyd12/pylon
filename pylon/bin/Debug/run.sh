cd ..
sh ../createDebugArchive.sh
cd Debug
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./:/usr/lib:/usr/lib/python2.7 ./pylon -debug -bench
