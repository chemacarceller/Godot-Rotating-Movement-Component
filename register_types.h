#ifndef ROTATINGMOVEMENTCOMPONENT_REGISTER_TYPES_H
#define ROTATINGMOVEMENTCOMPONENT_REGISTER_TYPES_H

// That header (class_db.hpp) is essential for registering your classes in the engine
// Needed for using namespace godot;
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

void initialize_RotatingMovementComponent(ModuleInitializationLevel p_level);
void uninitialize_RotatingMovementComponent(ModuleInitializationLevel p_level);

#endif 