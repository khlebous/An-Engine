#ifndef AN_ENGINE_EDITOR_EDITOR_APPLICATION
#define AN_ENGINE_EDITOR_EDITOR_APPLICATION

#include <Engine/Application.h>

class EditorApplication : public an::Application
{
  public:
    EditorApplication() : Application() {}
};

std::unique_ptr<an::Application> an::createApplication() {
    return std::make_unique<EditorApplication>();
}


#endif // AN_ENGINE_EDITOR_EDITOR_APPLICATION