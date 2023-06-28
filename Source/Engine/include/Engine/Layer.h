#ifndef AN_ENGINE_LAYER
#define AN_ENGINE_LAYER

namespace an
{

class Event;

class Layer
{
    friend class LayerStack;

  public:
    virtual ~Layer() {};

    virtual void onUpdate(double deltaTime) {}
    virtual void onEvent(Event &event) {}
    virtual void onImgui() {}

  protected:
    virtual void onAttach() {}
    virtual void onDetach() {}
};

} // namespace an

#endif // AN_ENGINE_APPLICATION