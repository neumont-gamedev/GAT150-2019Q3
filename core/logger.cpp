#include "logger.h"
#include "assert.h"

void FileLogOutput::OpenStream(const std::string& name)
{
	m_stream.open(name.c_str(), std::ios_base::binary | std::ios_base::out);
	ASSERT(m_stream.is_open());
	m_stream.precision(20);
}

void FileLogOutput::CloseStream()
{
	if (m_stream.is_open())
	{
		m_stream.close();
	}
}

void FileLogOutput::Write(const std::string& message)
{
	m_stream << message << std::endl << std::flush;
}
