#include <StreamingMarketData.h>
#include <xll/xll.h>

using namespace xll;

//int break_me = []() { return _crtBreakAlloc = 1178; }();

AddIn xai_tick(
	Function(XLL_DOUBLE, "xll_tick", "TICK")
	.Arguments({
		// Arg(XLL_CSTRING, "seccode", "the security code for which you want to get tick data.", "10*rand()")
	})
	.FunctionHelp("Return the tick value.")
	.Category("CRYPTO-MARKET")
	.HelpTopic("")
);
double WINAPI xll_tick()
{
#pragma XLLEXPORT
	using namespace std::chrono_literals;
	StreamingMarketData stream;
	stream.SecID("BTC/USD");
	stream.start();
	std::this_thread::sleep_for(1s);
	Tick t = stream.getTick("BTC/USD");
	return t.last;
}
