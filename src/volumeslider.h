#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <godot_cpp/classes/h_slider.hpp>
#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
namespace godot {
    class VolumeSlider : public HSlider {
        GDCLASS(VolumeSlider, HSlider);

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("on_value_changed", "value"), &VolumeSlider::on_value_changed);
    }   
public:;
    void on_value_changed (double value);

private:
    float linear_to_db (float linear);
};
#endif // VOLUMESLIDER_H
}