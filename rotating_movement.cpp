#include "rotating_movement.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void RotatingMovementComponent::_bind_methods() {

    // Record of methods for Godot to see.
    ClassDB::bind_method(D_METHOD("is_enabled"), &RotatingMovementComponent::is_enabled);
    ClassDB::bind_method(D_METHOD("set_enabled", "p_enabled"), &RotatingMovementComponent::set_enabled);
    
    ClassDB::bind_method(D_METHOD("get_rotating_vector"), &RotatingMovementComponent::get_rotating_vector);
    ClassDB::bind_method(D_METHOD("set_rotating_vector", "p_vector"), &RotatingMovementComponent::set_rotating_vector);
    
    ClassDB::bind_method(D_METHOD("get_speed"), &RotatingMovementComponent::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &RotatingMovementComponent::set_speed);

    // Exporting properties (equivalent to @export)
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_isEnabled"), "set_enabled", "is_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "rotatingVector"), "set_rotating_vector", "get_rotating_vector");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

RotatingMovementComponent::RotatingMovementComponent() {}
RotatingMovementComponent::~RotatingMovementComponent() {}

void RotatingMovementComponent::_ready() {
    // Equivalent to @onready var _parentActor = get_parent()
    _parentActor = Object::cast_to<Node3D>(get_parent());
}

void RotatingMovementComponent::set_enabled(bool p_enabled) {
    _isEnabled = p_enabled;
}

bool RotatingMovementComponent::is_enabled() const {
    return _isEnabled;
}

void RotatingMovementComponent::set_rotating_vector(Vector3 p_vector) {
    rotatingVector = p_vector;
    if (rotatingVector != Vector3(0, 0, 0)) {
        _rotatingVectorNormalized = rotatingVector.normalized();
    }
}

Vector3 RotatingMovementComponent::get_rotating_vector() const {
    return rotatingVector;
}

void RotatingMovementComponent::set_speed(float p_speed) {
    speed = p_speed;
    // RPM to Radians/second conversion: (RPM * 2 * PI) / 60
    _speedRad = p_speed * Math_PI / 30.0f;
}

float RotatingMovementComponent::get_speed() const {
    return speed;
}

void RotatingMovementComponent::_notification(int p_what) {
    if (p_what == NOTIFICATION_WM_CLOSE_REQUEST) {
        queue_free();
    }
}

void RotatingMovementComponent::_physics_process(double delta) {
    if (_isEnabled && _parentActor != nullptr) {
        // In C++ we use _speedRad to avoid recalculating the constant in each frame
        _parentActor->rotate(_rotatingVectorNormalized, _speedRad * (float)delta);
    }
}