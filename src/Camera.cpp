#include <Camera.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), Up(0, 1, 0),
    MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    rotateNumber = 0;
    distanceToCenter = glm::distance(Position, glm::vec3(0, 0, 0));

    Position.x = distanceToCenter * glm::cos(glm::radians(rotateNumber));
    Position.z = distanceToCenter * glm::sin(glm::radians(rotateNumber));

    updateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
    float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::LookAtGameObject(glm::vec3 position) {
    return glm::lookAt(Position, position, Up);
}

// Processes input received from any keyboard-like input system. Accepts input
// parameter in the form of camera defined ENUM (to abstract it from windowing
// systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;

    updateCameraVectors();
}

// Processes input received from a mouse input system. Expects the offset
// value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset,
    GLboolean constrainPitch) {

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    rotateNumber += xoffset;
    //Position += Right * xoffset;

    Position.x = distanceToCenter * glm::cos(glm::radians(rotateNumber));
    Position.z = distanceToCenter * glm::sin(glm::radians(rotateNumber));


    // Update Front, Right and Up Vectors using the updated Euler angles
    // 
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires
// input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    const glm::mat4 inverted = glm::inverse(LookAtGameObject(glm::vec3(0, 0, 0)));

    glm::vec3 position = glm::vec3(inverted[3]);
    glm::vec3 direction = -glm::vec3(inverted[2]);
    float yaw = glm::degrees(glm::atan(direction.z, direction.x));
    float pitch = glm::degrees(glm::asin(direction.y));

    if (!isnan(yaw) && !isnan(pitch)) {
        Yaw = yaw;
        Pitch = pitch;
    }




    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(static_cast<double>(Yaw))) *
        cos(glm::radians(static_cast<double>(Pitch))));

    front.y = static_cast<float>(sin(glm::radians(static_cast<double>(Pitch))));

    front.z = static_cast<float>(sin(glm::radians(static_cast<double>(Yaw))) *
        cos(glm::radians(static_cast<double>(Pitch))));


    Front = glm::normalize(direction);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(
        Front, WorldUp)); // Normalize the vectors, because their length gets
                          // closer to 0 the more you look up or down which
                          // results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
