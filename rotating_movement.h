#ifndef ROTATING_MOVEMENT_COMPONENT_H
#define ROTATING_MOVEMENT_COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

    class RotatingMovementComponent : public Node {
        GDCLASS(RotatingMovementComponent, Node)

        private:
            bool _isEnabled = true;
            Vector3 rotatingVector = Vector3(0, 0, 0);
            Vector3 _rotatingVectorNormalized = Vector3(0, 0, 0);
            float speed = 0.0f;
            float _speedRad = 0.0f;
            Node3D* _parentActor = nullptr;

        protected:
            static void _bind_methods();

        public:
            RotatingMovementComponent();
            ~RotatingMovementComponent();

            void _ready() override;
            void _physics_process(double delta) override;
            void _notification(int p_what);

            // Getters and Setters
            void set_enabled(bool p_enabled);
            bool is_enabled() const;

            void set_rotating_vector(Vector3 p_vector);
            Vector3 get_rotating_vector() const;

            void set_speed(float p_speed);
            float get_speed() const;
    };

}

#endif