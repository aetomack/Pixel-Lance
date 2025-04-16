#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <godot_cpp/classes/h_slider.hpp>

namespace godot {

class VolumeSlider : public HSlider {
    GDCLASS(VolumeSlider, HSlider);

protected:
    static void _bind_methods();

public:
    VolumeSlider();
    ~VolumeSlider();

    void _ready() override;
    void on_value_changed(double value);

    void toggle_mute();
    bool is_muted() const;

private:
    float linear_to_db(float linear);
    float db_to_linear(float db);

    float last_volume = 100.0f; // default to full volume
};

} // namespace godot

#endif // VOLUME_SLIDER_H
