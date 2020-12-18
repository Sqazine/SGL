#include <memory>
#include "Application.h"

#undef main
int main(int argc, char** argv)
{
	std::unique_ptr<Application> app = std::make_unique<Application>("Example",800, 600);
	app->Run();
	return 0;
}