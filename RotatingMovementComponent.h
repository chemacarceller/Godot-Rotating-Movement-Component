// rotating_movement.h
#ifndef ROTATING_MOVEMENT_COMPONENT_H
#define ROTATING_MOVEMENT_COMPONENT_H

// This is a custom movement component for rotating a Node3D in Godot.
// It allows you to specify a rotation vector and speed, and it will rotate the parent Node3D accordingly.
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>

// Using the godot namespace to avoid prefixing all Godot classes with 'godot::'
using namespace godot;

// The RotatingMovementComponent class inherits from Node, allowing it to be added as a child to any Node in the scene tree.
class RotatingMovementComponent : public Node {

    // Macro to register the class with Godot's type system.
    GDCLASS(RotatingMovementComponent, Node)

    private:

        // Underscored private variable for exported variables (following Godot's convention)
        // Speed in RPM (Rotations Per Minute)
        float _speed = 0.0f;
        // Rotating Vector
        Vector3 _rotatingVector = Vector3(0, 1, 0);

        // Inidcates if the component is enebled or not
        bool _isEnabled = true;
            
        // Private variables for internal use without exposing to Godot not underscored 
        Vector3 rotatingVectorNormalized = Vector3(0, 0, 0);
        float speedRad = 0.0f;

        // Store a reference to the parent actor (Node3D) to apply rotation
        Node3D* parentActor = nullptr;

    protected:

        // Method to bind properties and methods to Godot   
        static void _bind_methods();

    public:
    
        // Constructor and Destructor
        RotatingMovementComponent();
        ~RotatingMovementComponent();

        // Overridden methods from Node
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

#endif