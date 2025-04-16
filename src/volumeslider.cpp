#include "volumeslider.h"

#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <cmath>

using namespace godot;

void VolumeSlider::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_value_changed", "value"), &VolumeSlider::on_value_changed);
    ClassDB::bind_method(D_METHOD("toggle_mute"), &VolumeSlider::toggle_mute);
    ClassDB::bind_method(D_METHOD("is_muted"), &VolumeSlider::is_muted);
}

VolumeSlider::VolumeSlider() = default;
VolumeSlider::~VolumeSlider() = default;

void VolumeSlider::_ready() {
    set_min(0);
    set_max(100);

    float db = AudioServer::get_singleton()->get_bus_volume_db(0);
    float linear = db_to_linear(db);
    float initial_volume = linear * 100.0f;

    last_volume = initial_volume > 0 ? initial_volume : 100.0f;
    set_value(initial_volume);

    connect("value_changed", Callable(this, "on_value_changed"));
}

void VolumeSlider::on_value_changed(double value) {
    float linear = static_cast<float>(value) / 100.0f;
    float db_volume = linear_to_db(linear);
    AudioServer::get_singleton()->set_bus_volume_db(0, db_volume);
}

void VolumeSlider::toggle_mute() {
    if (get_value() > 0.01f) {
        last_volume = get_value();
        set_value(0);
        on_value_changed(0);
    } else {
        set_value(last_volume);
        on_value_changed(last_volume);
    }
}

bool VolumeSlider::is_muted() const {
    return get_value() <= 0.01f;
}

float VolumeSlider::linear_to_db(float linear) {
    if (linear <= 0.00001f) {
        return -80.0f;
    }
    return 20.0f * std::log10(linear);
}

float VolumeSlider::db_to_linear(float db) {
    return std::pow(10.0f, db / 20.0f);
}
