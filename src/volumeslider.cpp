#include <godot_cpp/classes/h_slider.hpp>
#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;

class VolumeSlider : public HSlider {
    GDCLASS(VolumeSlider, HSlider);

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("on_value_changed", "value"), &VolumeSlider::on_value_changed);
    }

public:
    void _ready() override {
        set_min(0);
        set_max(100);
        set_value(AudioServer::get_singleton()->get_bus_volume_db(0)); // assuming bus 0 is Master
        connect("value_changed", Callable(this, "on_value_changed"));
    }

    void on_value_changed(double value) {
        float db_volume = linear_to_db(value / 100.0);
        AudioServer::get_singleton()->set_bus_volume_db(0, db_volume); // set Master volume
    }

    
private:
    float linear_to_db(float linear) {
        if (linear <= 0.00001f) {
            return -80.0f;
        }   
        return 20.0f * log10(linear);
    }   
};
