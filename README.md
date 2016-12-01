# Struck-for-VOT2015-interface
a simple struck interface  for the VOT 2015 challenge

First download the STRUCK tracker from the VOTR repository https://github.com/gnebehay/VOTR

Second, put these two files in  /VOTR-master/STRUCK/src

Third, edit 'INCLUDE_DIRECTORIES' in CMakeLists.txt in ../VOTR-master/STRUCK for opencv include directory and eigen dirctory;
change the 54th line 
string configPath = "config.txt"; // to the target where the configuration file of STRUCK located

At last,complie STRUCK. Now this can be called by the VOT2015 challenge.




