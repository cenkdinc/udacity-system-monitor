#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    vector <string> cpu_data = LinuxParser::CpuUtilization(); 

    float user = stof( cpu_data[1] );
    float nice = stof( cpu_data[2] );
    float system = stof( cpu_data[3] );
    float idle = stof( cpu_data[4] );
    float iowait = stof( cpu_data[5] );
    float irq = stof( cpu_data[6] );
    float softirq = stof( cpu_data[7] );
    float steal = stof( cpu_data[8] );

    float Idle = idle + iowait;
    float NonIdle = user + nice + system + irq + softirq + steal;
    float Total = Idle + NonIdle;

    //float prevIdle = 0;
    //float prevNonIdle = 0;
    //float prevTotal = 0;

    //float Idle_dt = Idle - prevIdle;
    //float NonIdle_dt = NonIdle - prevNonIdle;
    //float Total_dt = Total - prevTotal;

    float cpu_usage = (Total-Idle) / Total;

    return cpu_usage;
    }