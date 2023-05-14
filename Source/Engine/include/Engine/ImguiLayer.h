#ifndef AN_ENGINE_IMGUI_LAYER
#define AN_ENGINE_IMGUI_LAYER

#include "Engine/Layer.h"

namespace an
{

class ImguiLayer final : public Layer
{
  public:
    void onAttach() final;
    void onDetach() final;
    void onUpdate() final;

    void onEvent(Event &event) final;

  private:
    float time = 0.0f;
};

} // namespace an

#endif // AN_ENGINE_IMGUI_LAYER