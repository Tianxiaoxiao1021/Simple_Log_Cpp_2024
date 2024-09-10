#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <chrono>
#include <fstream>
#include <iostream>
#include <functional>

std::string formatTime(const std::chrono::system_clock::time_point& timePoint) {
    auto timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm localTime;
#if defined(_WIN32)
    localtime_s(&localTime, &timeT);
#else
    std::localtime_r(&timeT, &localTime);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const std::tm& tm) {
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    os << oss.str();
    return os;
}

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Log {
private:
    std::fstream log;
    std::function<void(const std::string&)> ERRORCallback;
    std::function<void(const std::string&)> WARNINGCallback;
    std::function<void(const std::string&)> INFOCallback;
    std::string Read_line(int line) {
        if (!log.is_open()) throw std::runtime_error("Log file is closed");
        std::streampos originalPos = log.tellg();
        log.clear();
        log.seekg(0, std::ios::beg);
        std::string result;
        std::string tempLine;
        int currentLine = 0;
        while (std::getline(log, tempLine)) {
            if (++currentLine >= line) {
                result = tempLine;
                break;
            }
        }
        log.clear();
        log.seekg(originalPos);
        return result;
    }

    std::tm parseTimeFromString(const std::string& timeStr) {
        std::tm tm = {};
        std::istringstream iss(timeStr);
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (iss.fail()) throw std::runtime_error("Failed to parse time");
        return tm;
    }
public:
    Log(const std::string& name, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::trunc) {
        log.open(name, mode);
    }
    void set_ERROR_Callback(std::function<void(const std::string&)> callback) {
        ERRORCallback = callback;
    }
    void set_WARNING_Callback(std::function<void(const std::string&)> callback) {
        WARNINGCallback = callback;
    }
    void set_INFO_Callback(std::function<void(const std::string&)> callback) {
        INFOCallback = callback;
    }
    void Close() { if (log.is_open())log.close(); }
    void Write(const LogLevel l, const std::string& msg) {
        if (log.is_open()) {
            auto now = std::chrono::system_clock::now();
            log << "<" << formatTime(now) << ">";
            std::string logMsg;
            if (l == LogLevel::INFO) {
                logMsg = "[INFO]: " + msg;
                log << logMsg;
                if (!INFOCallback)return;
                INFOCallback(msg);
            }
            else if (l == LogLevel::WARNING) {
                logMsg = "[WARNING]: " + msg;
                log << logMsg;
                if (!WARNINGCallback)return;
                WARNINGCallback(msg);
            }
            else if (l == LogLevel::ERROR) {
                logMsg = "[ERROR]: " + msg;
                log << logMsg;
                if (!ERRORCallback)return;
                ERRORCallback(msg);
            }
        }
        else {
            throw std::runtime_error("Log file is closed");
        }
    }

    std::string operator[](int line) { return Read_line(line + 1); }

    std::tm get_time(int line) {
        std::string lineContent = Read_line(line + 1);
        size_t startPos = lineContent.find('<');
        size_t endPos = lineContent.find('>', startPos);
        if (startPos == std::string::npos || endPos == std::string::npos) {
            std::time_t t = std::time(nullptr);
            std::tm localTime;
#if defined(_WIN32)
            localtime_s(&localTime, &t);
#else
            std::localtime_r(&t, &localTime);
#endif
            return localTime;
        }
        std::string timeStr = lineContent.substr(startPos + 1, endPos - startPos - 1);
        return parseTimeFromString(timeStr);
    }

    ~Log() {
        if (log.is_open()) log.close();
    }
};