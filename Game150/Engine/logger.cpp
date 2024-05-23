/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Huiuk Jang
Created:    March 8, 2023
Updated:    TODAY¡¯S DATE
*/

#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start) : min_level(severity), out_stream("Trace.log"), start_time(start) {
    SetTraceLogLevel(LOG_NONE);
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf());
        start_time = std::chrono::system_clock::now();
    }
}

CS230::Logger::~Logger() {
    out_stream.flush();
    out_stream.close();
}

double CS230::Logger::seconds_since_start()
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration<double>(now- start_time.time_since_epoch()).count();
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {
    //TODO: Write this function
    int num = static_cast<int>(severity);
    int min_num = static_cast<int>(min_level);
    std::string name[4] = { "Verbose",
            "Debug",
            "Event",
            "Error" };
    //char i = static_cast<char>(severity);
    //std: name= severity;
    if (min_num-num<1)
    {
        out_stream.precision(4);
        out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
        out_stream << name[num] <<"\t" << message << std::endl;
    }        
    
    return;
}
