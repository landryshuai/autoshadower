PROJECT(main)


SET(SRC_LIST ../src/main.cpp
             ../src/lib/helper/Misc.cpp
             ../src/lib/helper/Time.cpp
             ../src/lib/helper/CmdlineOption.cpp
             ../src/lib/helper/Webpage.cpp
             ../src/lib/self/Boafanx.cpp
             ../src/lib/self/Itplayer.cpp
             ../src/lib/self/Efmoe.cpp
             #../src/lib/self/Jslink.cpp
             #../src/lib/self/Dbops.cpp
             ../src/lib/self/Certificate.cpp)
SET(CMAKE_EXE_LINKER_FLAGS "-lcurl -lpthread -liconv")

# linux
#>>>>>>>>>>>>>>>>>>>>>>

## debug
#SET(CMAKE_CXX_COMPILER "clang++")
#SET(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Weverything -Wno-documentation -Wno-disabled-macro-expansion -Wno-float-equal -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-missing-prototypes -Wno-padded -Wno-old-style-cast")
#SET(CMAKE_BUILD_TYPE debug)
#ADD_EXECUTABLE(main ${SRC_LIST})
#TARGET_LINK_LIBRARIES(main curl)

# release
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
SET(CMAKE_BUILD_TYPE release)
ADD_EXECUTABLE(autoshadower ${SRC_LIST})
TARGET_LINK_LIBRARIES(autoshadower curl)
INSTALL(PROGRAMS autoshadower DESTINATION /usr/bin/)

#<<<<<<<<<<<<<<<<<<<<<<


## cygwin
##>>>>>>>>>>>>>>>>>>>>>>

#SET(CMAKE_CXX_COMPILER "g++")
#SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -s -DCYGWIN")
#SET(CMAKE_BUILD_TYPE release)
#ADD_EXECUTABLE(autoshadower ${SRC_LIST})
#target_link_libraries(autoshadower /bin/cygcurl-4.dll)
#target_link_libraries(autoshadower /lib/libiconv.a)

##<<<<<<<<<<<<<<<<<<<<<<
