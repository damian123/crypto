#include <streaming/StreamingMarketData.h>
#include <xll/xll.h>

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
	StreamingMarketData::getInstance().SecID("BTC/USD");
	StreamingMarketData::getInstance().start();
	return TRUE;
});

Auto<Close> xai_close([]() {
	StreamingMarketData::getInstance().stop();  // shutdown the market data stream.
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
