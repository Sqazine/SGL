#include <memory>
#include "system/Application.h"

#undef main
int main(int argc, char** argv)
{
	std::unique_ptr<Application> app = std::make_unique<Application>("Example",SGL::Vector2u32(800,600));
	app->Run();
	return 0;
}