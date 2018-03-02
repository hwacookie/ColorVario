#include "dlog.h"
#include "VarioController.h"
#include <dali/dali.h>
#include <exception>

int main(int argc, char *argv[])
{
	Kystsoft::dlog::setLogTag("ColorVario");
	Kystsoft::dlog(DLOG_DEBUG) << "Hello!";
	try
	{
		Dali::Application application = Dali::Application::New(&argc, &argv);
		Kystsoft::VarioController controller(application);
		application.MainLoop();
	}
	catch (std::exception& e)
	{
		Kystsoft::dlog(DLOG_FATAL) << e.what();
		return 1;
	}
	catch (...)
	{
		Kystsoft::dlog(DLOG_FATAL) << "Unknown error";
		return 2;
	}
	Kystsoft::dlog(DLOG_DEBUG) << "Goodbye!";
	return 0;
}
