
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <string>
#include <iostream>
#include <chrono>

namespace sw
{
	struct stopwatch
	{
	private:
		std::chrono::steady_clock::time_point start_time;
		std::chrono::steady_clock::time_point end_time;
		int laps = 1;

	public:
		void start();
		void lap();
		void stop();

		std::chrono::duration<double> get_total_time() const;
		std::chrono::duration<double> get_mean_time() const;

		std::string get_total_str() const;
		std::string get_mean_str() const;

		static std::string format_time(const std::chrono::duration<double>& time);

		friend std::ostream& operator<<(std::ostream& out, const stopwatch& sw);
	};
};

#endif /* STOPWATCH_H */
