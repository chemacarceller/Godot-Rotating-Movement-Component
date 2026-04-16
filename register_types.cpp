#include "register_types.h"
#include "RotatingMovementComponent.h"

using namespace godot;

void initialize_RotatingMovementComponent(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // We registered our personalized class
    ClassDB::register_class<RotatingMovementComponent>();
}

void uninitialize_RotatingMovementComponent(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT
    RotatingMovementComponent_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization*r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address,p_library, r_initialization);
        init_obj.register_initializer(initialize_RotatingMovementComponent);
        init_obj.register_terminator(uninitialize_RotatingMovementComponent);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}