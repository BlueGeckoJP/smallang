cmake_minimum_required(VERSION 3.10.0)
project(smallang VERSION 0.1.0 LANGUAGES C CXX)

add_executable(smallang
    main.cpp
    lexer.cpp
    parser.cpp
)

