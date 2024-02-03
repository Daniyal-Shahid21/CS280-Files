cmake_minimum_required(VERSION 3.26)
project(CS280_Test_Learner)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS280_Test_Learner RA1_s_shahid.cpp
        RA2_s_shahid.cpp
        RA3_s_shahid.cpp
        RA4_s_shahid.cpp
        RA5_s_shahid.cpp
        lex.h
        tokensListing.cpp
        TESTER.cpp
        PA1_s_shahid.cpp
        lex.cpp
        RA6_s_shahid.cpp
        RA8_s_shahid.cpp
        ship.h
        cruise.h
        cargo.h
        RA9Prog.cpp
)
