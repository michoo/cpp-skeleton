#CPP-SKELETON

This project is for helping me in building a new cpp app

So in this skeleton you'll find default settings and some default code for 
- managing properties in files with key/value
- managing log easily
- managing postgres database
- managing opencv 
- managing gtest
- managing doxygen (still have bugs)

in cmake mode 

It's not perfect, still need to improve that but I'll be happy if you can add new ideas (rest, user management, data validation...)

M42

##prerequesites

```
libboost-all-dev
doxygen
libpqxx-4.0
libpqxx-dev
postgresql-server-dev-9.4
```

##About properties sources

example of properties integration
http://www.paulsenzee.com/2008/02/java-style-properties-files-in-c.html


##About google test
https://crascit.com/2015/07/25/cmake-gtest/
https://github.com/Crascit/DownloadProject
https://github.com/Crascit/DownloadProject

###PS:becareful when you move files inside your ide
https://github.com/Crascit/DownloadProject/blob/master/DownloadProject.cmake
