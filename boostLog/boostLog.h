#pragma once

#include <string>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/trivial.hpp>

class Log {
public:
	Log(const std::string &sLogFilePfx = "Log", const unsigned int nRotSize = 5 * 1024 * 1024);
	~Log();

	void fatalLog(const std::wstring &wsTxt);
	void errorLog(const std::wstring &wsTxt);
	void warningLog(const std::wstring &wsTxt);
	void infoLog(const std::wstring &wsTxt);
	void debugLog(const std::wstring &wsTxt);
	void traceLog(const std::wstring &wsTxt);

#define M_LOG_USE_TIME_LINE BOOST_LOG_SCOPED_THREAD_ATTR("Timeline", boost::log::attributes::timer());
#define M_LOG_USE_NAMED_SCOPE(named_scope) BOOST_LOG_NAMED_SCOPE(named_scope);

private:
	void internLog(const std::wstring &wsTxt, const boost::log::trivial::severity_level eSevLev);
	boost::log::sources::wseverity_logger_mt<boost::log::trivial::severity_level> m_oWsLogger;
};
