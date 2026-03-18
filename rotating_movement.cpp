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
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "_rotatingVector"), "set_rotating_vector", "get_rotating_vector");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_speed"), "set_speed", "get_speed");
}

// Constructor and Destructor
RotatingMovementComponent::RotatingMovementComponent() {
    speedRad = _speed * Math_PI / 30.0f;
    rotatingVectorNormalized = _rotatingVector.normalized();
}

RotatingMovementComponent::~RotatingMovementComponent() {}

// Called when the node enters the scene tree for the first time.
void RotatingMovementComponent::_ready() {
    // Equivalent to @onready var _parentActor = get_parent()
    parentActor = Object::cast_to<Node3D>(get_parent());
}

// Getters and Setters
void RotatingMovementComponent::set_enabled(bool p_enabled) {
    _isEnabled = p_enabled;
}

bool RotatingMovementComponent::is_enabled() const {
    return _isEnabled;
}

void RotatingMovementComponent::set_rotating_vector(Vector3 p_vector) {
    _rotatingVector = p_vector;
    if (_rotatingVector != Vector3(0, 0, 0)) {
        rotatingVectorNormalized = _rotatingVector.normalized();
    }
}

Vector3 RotatingMovementComponent::get_rotating_vector() const {
    return _rotatingVector;
}

void RotatingMovementComponent::set_speed(float p_speed) {
    _speed = p_speed;

    // RPM to Radians/second conversion: (RPM * 2 * PI) / 60
    speedRad = p_speed * Math_PI / 30.0f;
}

float RotatingMovementComponent::get_speed() const {
    return _speed;
}

// Called every physics frame. 'delta' is the elapsed time since the previous frame.
void RotatingMovementComponent::_notification(int p_what) {
    if (p_what == NOTIFICATION_WM_CLOSE_REQUEST) {
        queue_free();
    }
}

// Called every physics frame. 'delta' is the elapsed time since the previous frame.
void RotatingMovementComponent::_physics_process(double delta) {
    if (_isEnabled && parentActor != nullptr) {
        // In C++ we use _speedRad to avoid recalculating the constant in each frame
        parentActor->rotate(rotatingVectorNormalized, speedRad * (float)delta);
    }
}