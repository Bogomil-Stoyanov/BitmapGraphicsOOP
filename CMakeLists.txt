cmake_minimum_required(VERSION 3.25)
project(BitmapGraphics)

set(CMAKE_CXX_STANDARD 17)

add_executable(BitmapGraphics main.cpp BitmapImageApp/BitmapImageApp.cpp BitmapImageApp/BitmapImageApp.h Commands/CommandDispatcher.cpp Commands/CommandDispatcher.h SessionManager/SessionManager.cpp SessionManager/SessionManager.h Commands/CommandTypes/Command.cpp Commands/CommandTypes/Command.h Commands/CommandTypes/ExitCommand.cpp Commands/CommandTypes/ExitCommand.h Commands/CommandTypes/ErrorCommand.cpp Commands/CommandTypes/ErrorCommand.h SessionManager/Session/Session.cpp SessionManager/Session/Session.h)
