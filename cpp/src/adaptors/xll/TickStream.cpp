#include <streaming/StreamingMarketData.h>
#include <xll/xll.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace xll;

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

	StreamingMarketData::getInstance().SecID("BTC/USD");
	StreamingMarketData::getInstance().start();
	return TRUE;
});

Auto<Close> xai_close([]() {
	StreamingMarketData::getInstance().stop();  // shutdown the market data stream.
	spdlog::drop_all();
	return TRUE;
});

AddIn xai_tick(
	Function(XLL_DOUBLE, "xll_tick", "TICK")
	.Arguments({
		Arg(XLL_CSTRING, "SecCode", "The security code", "")
	})
	.FunctionHelp("Return the tick value.")
	.Category("CRYPTO-MARKET")
	.HelpTopic("")
);
double WINAPI xll_tick()
{	
#pragma XLLEXPORT	

	Tick t = StreamingMarketData::getInstance().getTick("BTC/USD");
	return t.last;
	// return 5.0;
}
