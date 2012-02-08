REM del ../bin/UnitaryRelease/rc.pylon
cd ../archiveCode
"C:\Program Files\CodeBlocks\MinGW\bin\zip.exe" -FS -9 -r ../bin/UnitaryRelease/rc.pylon . -x \*.svn/*
