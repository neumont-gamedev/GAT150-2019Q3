#pragma once

#include "timer.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

enum class eLogPriority
{
	PRIORITY_VERBOSE = 1,
	PRIORITY_DEBUG_1,
	PRIORITY_DEBUG_2,
	PRIORITY_DEBUG_3,
	PRIORITY_WARNING_1,
	PRIORITY_WARNING_2,
	PRIORITY_ERROR
};

class LogOutput
{
public:
	virtual ~LogOutput() {}
	virtual void OpenStream(const std::string& name) = 0;
	virtual void CloseStream() = 0;
	virtual void Write(const std::string& message) = 0;
};

class FileLogOutput : public LogOutput
{
public:
	~FileLogOutput() {}
	void OpenStream(const std::string& name);
	void CloseStream();
	void Write(const std::string& message);

private:
	std::ofstream m_stream;
};

template< typename TOutput >
class Logger
{
public:
	Logger(const std::string& name, eLogPriority priority);
	~Logger();

	void SetSevertity(eLogPriority priority);

	template<eLogPriority priority, typename...Args>
	void Print(Args&& ...args);

private:
	void PrintImplementation(std::stringstream& stream);

	template<typename First, typename...Rest>
	void PrintImplementation(std::stringstream& stream, First& parm1, Rest& ...parm);

private:
	eLogPriority m_priority;
	TOutput m_output;
};


template<typename TOutput>
inline Logger<TOutput>::Logger(const std::string& name, eLogPriority priority) : m_priority(priority)
{
	m_output.OpenStream(name);
}

template<typename TOutput>
inline Logger<TOutput>::~Logger()
{
	m_output.Write("<Logger End>");
	m_output.CloseStream();
}

template<typename TOutput>
inline void Logger<TOutput>::SetSevertity(eLogPriority priority)
{
	m_priority = (priority > eLogPriority::PRIORITY_ERROR) ? eLogPriority::PRIORITY_ERROR : priority;
}

template<typename TOutput>
inline void Logger<TOutput>::PrintImplementation(std::stringstream& stream)
{
	m_output.Write(stream.str());
}

template<typename TOutput>
template<typename First, typename ...Rest>
inline void Logger<TOutput>::PrintImplementation(std::stringstream& stream, First& parm1, Rest& ...parm)
{
	stream << parm1;
	PrintImplementation(stream, parm...);
}

template<typename TOutput>
template<eLogPriority priority, typename ...Args>
inline void Logger<TOutput>::Print(Args&& ...args)
{
	if (priority < m_priority) return;

	std::stringstream log_stream;

	switch (m_priority)
	{
	case eLogPriority::PRIORITY_VERBOSE:
		log_stream << "LOG: ";
		break;
	case eLogPriority::PRIORITY_DEBUG_1:
	case eLogPriority::PRIORITY_DEBUG_2:
	case eLogPriority::PRIORITY_DEBUG_3:
		log_stream << "DEBUG: ";
		break;
	case eLogPriority::PRIORITY_WARNING_1:
	case eLogPriority::PRIORITY_WARNING_2:
		log_stream << "WARNING: ";
		break;
	case eLogPriority::PRIORITY_ERROR:
		log_stream << "ERROR: ";
		break;
	}

	PrintImplementation(log_stream, args...);
}


