#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
    pid_ = pid;
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    string line;
    vector <string> values = {};
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kStatFilename );
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        for (int i=0; i<22; i++) {
            linestream >> values[i];
        }
    }

    float utime = stof( values[13] ) / sysconf(_SC_CLK_TCK);
    float stime = stof( values[14] ) / sysconf(_SC_CLK_TCK);
    float cutime = stof( values[15] ) / sysconf(_SC_CLK_TCK);
    float cstime = stof( values[16] ) / sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;

    return total_time / LinuxParser::UpTime(pid_);
    }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return true; }
//bool Process::operator<(Process const& a) const { return stol(Ram()) < stol(a.Ram()); }