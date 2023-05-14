
#include "Engine/Application.h"

#include <Core/Logger.h>

extern std::unique_ptr<an::Application> an::createApplication();

int main()
{
    an::core::Logger::init();

    auto app = an::createApplication();
    app->run();
}
