

#include <string>
#include <iostream>

#ifdef __MINGW32__
#define CLEAR "\x1b[0;0m"
#define GREEN "\x1b[0;32m"
#define BLUE "\x1b[0;34m"
#define RED "\x1B[0;31m"
#define MAGENTA "\e[0;35m"

#define CLEAR_BOLD "\x1b[1;0m"
#define GREEN_BOLD "\x1b[1;32m"
#define BLUE_BOLD "\x1b[1;34m"
#define RED_BOLD "\x1B[1;31m"
#define MAGENTA_BOLD "\e[1;35m"
#endif

namespace lamp
{
    enum LOGGING_SEVERITY
    {
        ERROR = 0,
        WARNING,
        TRACE,
        INFO
    };

    class Logging
    {
    private:
        const std::string m_logging_severity_map[4] = {"ERROR", "WARNING", "TRACE", "INFO"};
        const std::string m_logging_severity_colors[4] = {RED, MAGENTA, GREEN, BLUE};

    public:
        void
        Log(std::string mess, int level, int line = -1, std::string time = "", std::string file = "")
        {
            std::cout << m_logging_severity_colors[level];
            std::cout << file << ":" << line << "  ";
            std::cout << m_logging_severity_map[level] << "  ";
            std::cout << mess << "  ";
            std::cout << CLEAR;
            std::cout << "\n";
        }
    };

    static Logging s_lamp_log;

} // namespace lamp

#define LOG(LEVEL, MESSAGE) lamp::s_lamp_log.Log(MESSAGE, (int)LEVEL, __LINE__, __TIME__, __FILE__)

// #define LOG(LEVEL, MESSAGE)
