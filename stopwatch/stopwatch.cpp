
#include "stopwatch.h"

#include <sstream>
#include <iomanip>

using namespace sw;
using namespace std::chrono;

void stopwatch::start()
{
	start_time = steady_clock::now();
}

void stopwatch::lap()
{
	laps++;
}

void stopwatch::stop()
{
	end_time = steady_clock::now();
}

duration<double> stopwatch::get_total_time() const
{
	return end_time - start_time;
}

duration<double> stopwatch::get_mean_time() const
{
	return get_total_time() / laps;
}

std::string stopwatch::get_total_str() const
{
	return format_time(get_total_time());
}

std::string stopwatch::get_mean_str() const
{
	return format_time(get_mean_time());
}

std::string stopwatch::format_time(const duration<double>& time)
{
	std::stringstream ss;

	unsigned int mil_sec = duration_cast<milliseconds>(time).count() % 1000;
	unsigned int sec = duration_cast<seconds>(time).count() % 60;
	unsigned int min = duration_cast<minutes>(time).count() % 60;
	unsigned int hour = duration_cast<hours>(time).count();

	if(hour > 0)
		ss << std::setfill('0') << std::setw(2) << hour << ":";
	ss << std::setfill('0') << std::setw(2) << min << ":";
	ss << std::setfill('0') << std::setw(2) << sec << ":";
	ss << std::setfill('0') << std::setw(3) << mil_sec;

	return ss.str();
}

std::ostream& sw::operator<<(std::ostream& out, const stopwatch& sw)
{
	out << sw.get_total_str();
	return out;
}
