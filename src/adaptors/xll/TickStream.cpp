#include <streaming/StreamingMarketData.h>
#include <xll/xll.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <codecvt>

using namespace xll;

using xcstr = traits<XLOPERX>::xcstr;

std::wstring s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

int XLL_ERROR(const char* s, bool b)
{
	return 0;
}

int XLL_INFO(const char* s, bool b)
{
	return 0;
}

Auto<Open> xai_open([]() {
	spdlog::init_thread_pool(8192, 2);
	{
		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
		std::vector<spdlog::sink_ptr> sinks{ stdout_sink };
		auto logger = std::make_shared<spdlog::async_logger>("CryptoData", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		logger->flush_on(spdlog::level::err);   // trigger flush whenever errors or more severe messages are logged
		logger->set_level(spdlog::level::debug);
		spdlog::register_logger(logger);
	}

	{
		auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("ftx_log.txt", 1024 * 1024 * 10, 3);
		std::vector<spdlog::sink_ptr> sinks{ rotating_sink };
		auto logger = std::make_shared<spdlog::async_logger>("ftx", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		logger->flush_on(spdlog::level::err);   // trigger flush whenever errors or more severe messages are logged
		logger->set_level(spdlog::level::debug);
		spdlog::register_logger(logger);
	}

	return TRUE;
});

Auto<Close> xai_close([]() {
	//StreamingMarketData::getInstance().stop();  // shutdown the market data stream.
	//spdlog::drop_all();
	return TRUE;
});

AddIn xai_subscribe(
	Function(XLL_LPOPER, "xll_subscribe", "SUBSCRIBE")
	.Arguments({
		Arg(XLL_CSTRING, "SecCode", "The security code", "")
		})
	.FunctionHelp("Subscribe to tick data.")
	.Category("CRYPTO-MARKET")
	.HelpTopic("")
);
LPOPER WINAPI xll_subscribe(xcstr seccode)
{
#pragma XLLEXPORT
	static OPER result;
	static auto firstCall = true;

	try {
		std::string sc = ws2s(seccode);
		if (firstCall)
		{
			StreamingMarketData::getInstance().SecID(sc);
			StreamingMarketData::getInstance().start();
			firstCall = false;
		}
		else
		{		
			StreamingMarketData::getInstance().Subscribe(sc);
		}
		result = "OK";	// We will receive an async message with the result of the message send to the exchange server. 
						// Maybe have a future wait for the message to arrive with the result of this request.
						// At the moment it will be send to the log
	}
	catch (std::exception ex) {
		result = ex.what();
	}

	return &result;
}

AddIn xai_tick(
	Function(XLL_LPOPER, "xll_tick", "TICK")
	.Arguments({
		Arg(XLL_CSTRING, "SecCode", "The security code", "")
	})
	.FunctionHelp("Return the tick value.")
	.Category("CRYPTO-MARKET")
	.HelpTopic("")
);
LPOPER WINAPI xll_tick(xcstr seccode)
{	
#pragma XLLEXPORT
	static OPER result;

	try {		
		std::string sc = ws2s(seccode);
		Tick t = StreamingMarketData::getInstance().getTick(sc);
		result = (t.bid+t.ask)/2.0;		
	}
	catch (std::exception ex) {
		result = ex.what();
	}

	return &result;
}
