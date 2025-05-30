/*

 _____                         ______                 ___   ____ 
|  __ \                        |  _  \               /   | / ___|
| |  \/  __ _  _ __ ___    ___ | | | |  ___ __   __ / /| |/ /___ 
| | __  / _` || '_ ` _ \  / _ \| | | | / _ \\ \ / // /_| || ___ \
| |_\ \| (_| || | | | | ||  __/| |/ / |  __/ \ V / \___  || \_/ |
 \____/ \__,_||_| |_| |_| \___||___/   \___|  \_/      |_/\_____/


*/

/* 
	AUTHOR: GameDev46

	Youtube: https://www.youtube.com/@gamedev46
	Github: https://github.com/GameDev46
*/

// Include the raylib library
#include "include/raylib.h"

#include <iostream>
#include <string>
#include <cmath>
#include <time.h>

// Switch to the standard namespace
using namespace std;

/* ---------------------- */
/* MATHEMATICAL FUNCTIONS */
/* ---------------------- */

float distanceBetweenPoints(Vector2 point1, Vector2 point2) {
    // Calculate squared distance between points
    float gdistance = ( (point2.x - point1.x) * (point2.x - point1.x) ) + ( (point2.y - point1.y) * (point2.y - point1.y) );  
    return sqrt(gdistance);
}

float distanceBetweenPointsSqrd(Vector2 point1, Vector2 point2) {
    // Calculate squared distance between points
    float gdistance = ( (point2.x - point1.x) * (point2.x - point1.x) ) + ( (point2.y - point1.y) * (point2.y - point1.y) );  
    return gdistance;
}

float lengthOfVector(Vector2 length) {
    // Calculate squared distance between points
    float gdistance = ( length.x * length.x ) + ( length.y * length.y );
    return sqrt(gdistance);
}

float clamp(float d, float min, float max) {
  const float t = d < min ? min : d;
  return t > max ? max : t;
}

float minNum(float num1, float num2) {
    if (num1 < num2) return num1;
    return num2;
}

int generateRandomNumber(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

float lerp(float a, float b, float f) {
    return a * (1.0 - f) + (b * f);
}

/* ---------------------- */
/* CLASSES */
/* ---------------------- */

// UI Textbox
class numberInput {
    public:
        Vector2 size = Vector2({20.0f, 20.0f});
        Vector2 position = Vector2({0.0f, 0.0f});

        char value[8];
        char defaultValue[8];

        bool checkForInput(Vector2 mousePosition, bool isMouseDown) {

           numberInputRectangle = { position.x, position.y, size.x, size.y };

           if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) SetMouseCursor(2);

            if (isMouseDown) {
                if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) {
                    isSelected = true;

                    for (int i = 0; i < 8; i++) {
                        textInput[i] = ' ';
                    }

                    arrayIndex = 0;

                } else {
                    isSelected = false;

                    for (int i = 0; i < 8; i++) {
                        value[i] = textInput[i];
                    }

                    return true;
                }
            }
            
            if (isSelected) {

                if (IsKeyPressed(KEY_ONE)) textInput[arrayIndex++] = '1';
                if (IsKeyPressed(KEY_TWO)) textInput[arrayIndex++] = '2';
                if (IsKeyPressed(KEY_THREE)) textInput[arrayIndex++] = '3';
                if (IsKeyPressed(KEY_FOUR)) textInput[arrayIndex++] = '4';
                if (IsKeyPressed(KEY_FIVE)) textInput[arrayIndex++] = '5';
                if (IsKeyPressed(KEY_SIX)) textInput[arrayIndex++] = '6';
                if (IsKeyPressed(KEY_SEVEN)) textInput[arrayIndex++] = '7';
                if (IsKeyPressed(KEY_EIGHT)) textInput[arrayIndex++] = '8';
                if (IsKeyPressed(KEY_NINE)) textInput[arrayIndex++] = '9';
                if (IsKeyPressed(KEY_ZERO)) textInput[arrayIndex++] = '0';

                if (arrayIndex >= 7 || IsKeyPressed(KEY_ENTER)) {
                    isSelected = false;

                    for (int i = 0; i < 8; i++) {
                        value[i] = textInput[i];
                    }

                    arrayIndex = 0;

                    return true;
                }

            }

            return false;
        }

        void draw() {

            DrawRectangle(position.x, position.y + size.y - 5.0f, size.x, 3.0f, GetColor(0xffffffff) );

            if (isSelected) {
                DrawText(textInput, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            } else {
                DrawText(defaultValue, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            }

            return;
        }

    private:
        int arrayIndex = 0;
        char textInput[8];

        bool isSelected = false;

        Rectangle numberInputRectangle;
};

// Create the circleCollider class
class circleCollider {
    public:
        Vector2 position = Vector2({ 0.0f, 0.0f });
        Vector2 oldPosition = Vector2({ 0.0f, 0.0f });
        Vector2 velocity = Vector2({ 0.0f, 0.0f });
        Vector2 acceleration = Vector2({ 0.0f, 0.0f });

        double lastImpactSoundTime = 0.0f;
        double lastImpactSoundTimeForBorder = 0.0f;

        float radius = 1.0f;

        bool isKinematic = true;
        bool isActive = false;

        int connectedSpringIndex = -1;

        int id = -1;

        float systemEnergy = 0.0f;

        void setMass(float newMass) {
            mass = newMass;
            return;
        }

        float getMass() {
            return mass;
        }

        void setGravity(float newGravity) {
            gravity = newGravity;
            return;
        }

        void setPosition(float xPos, float yPos) {
            position.x = xPos;
            position.y = yPos;

            oldPosition.x = position.x;
            oldPosition.y = position.y;
            return;
        }

        void changePosition(float deltaXPos, float deltaYPos) {
            position.x += deltaXPos;
            position.y += deltaYPos;
            return;
        }

        void setVelocity(float xVel, float yVel) {
            velocity.x = xVel;
            velocity.y = yVel;
            return;
        }

        void changeVelocity(float accelX, float accelY) {
            acceleration.x += accelX;
            acceleration.y += accelY;
            return;
        }

        void setAcceleration(float xAccel, float yAccel) {
            acceleration.x += xAccel;
            acceleration.y += yAccel;
            return;
        }

        bool resolveCollision(circleCollider *otherObj) {

            float dist = distanceBetweenPoints(position, otherObj->position);

            float minDist = radius + otherObj->radius;

            if (dist - minDist < 0.0f) {

                // Move circles apart
                float collisionAxisDirection = atan2(position.y - otherObj->position.y, position.x - otherObj->position.x);

                float overlap = dist - minDist;

                position.x += cos(collisionAxisDirection) * -overlap * 0.5f;
                position.y += sin(collisionAxisDirection) * -overlap * 0.5f;

                otherObj->position.x += cos(collisionAxisDirection) * overlap * 0.5f;
                otherObj->position.y += sin(collisionAxisDirection) * overlap * 0.5f;

                return true;

            }

            return false;
        }

        void updateBody(float delta) {
            
            if (isKinematic && delta > 0.0f) {
                acceleration.y += gravity * 100.0f;

                // EULER Method
                /*velocity.y += gravity * delta;
                position.y += velocity.y * delta;

                position.x += velocity.x * delta;*/

                // Verlet Integration

                velocity.x = (position.x - oldPosition.x) / delta;
                velocity.y = (position.y - oldPosition.y) / delta;

                oldPosition.x = position.x;
                oldPosition.y = position.y;

                float xNew = position.x + (velocity.x * delta) + (0.5f * acceleration.x * delta * delta);
                float yNew = position.y + (velocity.y * delta) + (0.5f * acceleration.y * delta * delta);

                //velocity.x = (xNew - position.x) / delta;
                //velocity.y = (yNew - position.y) / delta;

                position.x = xNew;
                position.y = yNew;

            } else {
                
                velocity.x = 0.0f;
                velocity.y = 0.0f;

            }

            // Update total energy
            systemEnergy = 0.5f * mass * lengthOfVector(velocity) * lengthOfVector(velocity);
            systemEnergy += mass * gravity * (GetScreenHeight() - position.y);

            // Reset acceleration for next iteration
            acceleration.x = 0.0f;
            acceleration.y = 0.0f;

            return;
        }

        void drawInformation() {

            char idText[256];
            snprintf(idText, sizeof(idText), "ID: %d", id);
            DrawText(idText, position.x + 25.0f, position.y - 40.0f, 12, GetColor(0xffffffff) );

            char connectedSpringText[256];
            snprintf(connectedSpringText, sizeof(connectedSpringText), "Connected Spring: %d", connectedSpringIndex);
            DrawText(connectedSpringText, position.x + 25.0f, position.y - 60.0f, 12, GetColor(0xffffffff) );

            char massText[256];
            snprintf(massText, sizeof(massText), "Mass: %d g", int(round(mass)));
            DrawText(massText, position.x + 25.0f, position.y - 80.0f, 12, GetColor(0xffffffff) );

            char positionText[256];
            snprintf(positionText, sizeof(positionText), "Position: %d %d", int(round(position.x)), int(round(position.y)));
            DrawText(positionText, position.x + 25.0f, position.y - 100.0f, 12, GetColor(0xffffffff) );

            char velocityText[256];
            snprintf(velocityText, sizeof(velocityText), "Velocity: %d %d", int(round(velocity.x)), int(round(velocity.y)));
            DrawText(velocityText, position.x + 25.0f, position.y - 120.0f, 12, GetColor(0xffffffff) );

            return;
        }

    private:
        float mass = 1.0f;
        float gravity = 9.81f;

};

// Spring join class
class SpringJoint {
    public:
        float systemEnergy = 0.0f;
        bool isActive = false;

        int id = -1;

        void setSpringConstant(float newSpringConstant) {
            springConstant = newSpringConstant;
            return;
        }

        void setUnstretchedLength(float newUnstretchedLength) {
            unstretchedLength = newUnstretchedLength;
            return;
        }

        void setConnectedCircles(circleCollider *obj1, circleCollider *obj2) {
            object1 = obj1;
            object2 = obj2;
            return;
        }

        bool isConnectedTo(circleCollider *obj) {
            if (obj == object1 || obj == object2) return true;
            return false;
        }

        void updateJoint(float delta) {       
            distBetweenObj = distanceBetweenPoints(object1->position, object2->position);

            extension = distBetweenObj - unstretchedLength;
            force = springConstant * extension;

            direction = atan2(object1->position.y - object2->position.y, object1->position.x - object2->position.x);

            sinDirection = sin(direction);
            cosDirection = cos(direction);

            sinDirectionNegative = sin(-direction);
            cosDirectionNegative = cos(-direction);

            // For Object 1
            float acceleration = force / object1->getMass();
            object1->changeVelocity( cos(direction) * -acceleration, sin(direction) * -acceleration);

            // For Object 2
            acceleration = force / object2->getMass();
            object2->changeVelocity( cos(direction) * acceleration, sin(direction) * acceleration);

            // Update system energy
            systemEnergy = 0.5f * springConstant * extension * extension;

            return;
        }

        void draw() {

            if (distBetweenObj < 40.0f && distBetweenObj > -40.0f) distBetweenObj = 40.0f;

            float inverseDistance = (1 / distBetweenObj);

            float offsetX = sinDirection * inverseDistance * 600.0f;
            float offsetY = cosDirection * inverseDistance * 600.0f;

            int steps = 30;

            Vector2 startPoint = Vector2({ object1->position.x, object1->position.y });
            Vector2 endPoint = Vector2({ object1->position.x, object1->position.y });

            for (int i = 0; i < steps; i++) {
                
                endPoint = Vector2({ lerp(object1->position.x, object2->position.x, float(i) / float(steps) ) + (((i % 3) - 1) * offsetX), lerp(object1->position.y, object2->position.y, float(i) / float(steps) ) + (((i % 3) - 1) * offsetY) });
                
                // Shadow + white
                DrawLineBezier(startPoint, endPoint, 8.0f, GetColor(0x131313ff) );
                DrawLineBezier(startPoint, endPoint, 4.0f, GetColor(0xffffffff) );

                startPoint = endPoint;
            }

            return;
        }

        void drawInformation(Vector2 mousePosition, bool isMouseDown) {

            float offsetX = (cosDirection * -unstretchedLength) + (sinDirectionNegative * 25.0f);
            float offsetY = (sinDirection * -unstretchedLength) + (cosDirectionNegative * 25.0f);

            Vector2 startPoint = Vector2({ object1->position.x + (sinDirectionNegative * 25.0f), object1->position.y + (cosDirectionNegative * 25.0f) });
            Vector2 endPoint = Vector2({ object1->position.x + offsetX, object1->position.y + offsetY });

            DrawLineEx( startPoint, endPoint, 3.0f, GetColor(0xffffffff) );

            // Arrowheads
            DrawCircle( startPoint.x, startPoint.y, 5.0f, RAYWHITE);
            DrawCircle( endPoint.x, endPoint.y, 5.0f, RAYWHITE);

            char forceText[256];
            snprintf(forceText, sizeof(forceText), "Force: %.d N", int(round(force)));
            DrawText(forceText, object1->position.x + 45.0f, object1->position.y, 12, GetColor(0xffffffff) );

            char extensionText[256];
            snprintf(extensionText, sizeof(extensionText), "Extension: %d m", int(round(extension)));
            DrawText(extensionText, object1->position.x + 45.0f, object1->position.y + 20.0f, 12, GetColor(0xffffffff) );

            /*char springConstantText[256];
            snprintf(springConstantText, sizeof(springConstantText), "Spring Const: %d N/m", int(round(springConstant)));
            DrawText(springConstantText, object1->position.x + 45.0f, object1->position.y + 40.0f, 12, GetColor(0xffffffff) );*/
            DrawText("Spring Const: ", object1->position.x + 45.0f, object1->position.y + 40.0f, 12, GetColor(0xffffffff) );

            // Allow user to edit spring constant
            springConstantInput.position = Vector2( { object1->position.x + 130.0f, object1->position.y + 35.0f } );
            springConstantInput.size = Vector2( { 60.0f, 25.0f } );

            char defaultValText[8];
            snprintf(defaultValText, sizeof(defaultValText), "%d", int(round(springConstant)));
            
            for (int i = 0; i < 8; i++) {
                springConstantInput.defaultValue[i] = defaultValText[i];
            }

            // Check if user has input a new value for the spring constant
            if (springConstantInput.checkForInput(mousePosition, isMouseDown)) {
                springConstant = stoi(springConstantInput.value);
            }

            springConstantInput.draw();

            char idText[256];
            snprintf(idText, sizeof(idText), "ID: %d", id);
            DrawText(idText, object1->position.x + 45.0f, object1->position.y + 60.0f, 12, GetColor(0xffffffff) );

            return;
        }

        void destroyJoint() {
            isActive = false;

            if (object1->connectedSpringIndex == id) object1->connectedSpringIndex = -1;
            if (object2->connectedSpringIndex == id) object2->connectedSpringIndex = -1;

            return;
        }

    private:
        float direction = 0.0f;
        float sinDirection = 0.0f;
        float cosDirection = 1.0f;
        float sinDirectionNegative = 0.0f;
        float cosDirectionNegative = 1.0f;

        float distBetweenObj = 0.0f;

        float springConstant = 30.0f;
        float unstretchedLength = 50.0f;

        float extension = 0.0f;
        float force = 0.0f;

        numberInput springConstantInput;

        circleCollider *object1;
        circleCollider *object2;
};

class objectBounder {
    public:
        Vector2 boundPosition = Vector2( { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f } );
        float radius = 500.0f;

        bool boundObject(circleCollider *obj) {

            float dist = distanceBetweenPoints(obj->position, boundPosition);

            Vector2 objectOffset = Vector2( {obj->position.x - boundPosition.x, obj->position.y - boundPosition.y} );

            if (dist > radius - obj->radius) {

                obj->position.x = boundPosition.x + (objectOffset.x / dist) * (radius - obj->radius);
                obj->position.y = boundPosition.y + (objectOffset.y / dist) * (radius - obj->radius);

                return true;

            }

            return false;
        }

        void checkToResizeBounder(float mouseDelta) {
            radius += mouseDelta * 10.0f;

            if (radius < 5.0f) radius = 5.0f;

            return;
        }

        void drawBounder() {
            // Draw bounds
            DrawCircle(boundPosition.x, boundPosition.y, radius, GetColor(0x11161fff) );

            return;
        }
};

// Main physics loop
int main()
{

    const int screenWidth = 1200;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Physics engine");

    Image windowIcon = LoadImage("images/icon.png");
    SetWindowIcon(windowIcon);

    SetTargetFPS(60);

    // Setup camera
    Camera2D cam = { 0 };

    cam.zoom = 1;
    cam.offset.x = 0.0f;
    cam.offset.y = 0.0f;

    // Setup basic monitor variables
    float systemTotalEnergy = 0.0f;

    bool simulationRunning = true;
    bool shouldShowInstructions = true;

    int subSteps = 8;

    objectBounder worldBounding;

    // Load sounds
    InitAudioDevice();

    Sound impactSound = LoadSound("sounds/impact.wav");
    SetSoundPitch(impactSound, 0.6f);

    // Storage
    const int sceneCircleCount = 256;
    const int sceneSpringCount = 256;

    int totalCircles = 3;
    int totalSprings = 2;

    circleCollider sceneCircleColliders[sceneCircleCount];

    SpringJoint sceneSpringJoints[sceneSpringCount];
    bool shouldDrawSpringInformation[sceneSpringCount];

    for (int i = 0; i < sceneSpringCount; i++) {
        shouldDrawSpringInformation[i] = false;
    }

    // Setup basic physics object
    sceneCircleColliders[0].radius = 15.0f;
    sceneCircleColliders[0].setPosition(float(screenWidth) / 2.0f, (float(screenHeight) / 2.0f) - 100.0f);
    sceneCircleColliders[0].setVelocity(0.0f, 0.0f);
    sceneCircleColliders[0].setAcceleration(0.0f, 0.0f);

    sceneCircleColliders[0].setMass(10.0f);
    sceneCircleColliders[0].setGravity(9.81f);
    sceneCircleColliders[0].connectedSpringIndex = 0;

    sceneCircleColliders[0].isKinematic = false;
    sceneCircleColliders[0].isActive = true;
    sceneCircleColliders[0].id = 0;

    // Dangling circles
    sceneCircleColliders[1].radius = 15.0f;
    sceneCircleColliders[1].setPosition((float(screenWidth) / 2.0f), (float(screenHeight) / 2.0f) + 20.0f);
    sceneCircleColliders[1].setVelocity(0.0f, 0.0f);
    sceneCircleColliders[1].setAcceleration(0.0f, 0.0f);
    sceneCircleColliders[1].connectedSpringIndex = 1;

    sceneCircleColliders[1].setMass(10.0f);
    sceneCircleColliders[1].setGravity(9.81f);

    sceneCircleColliders[1].isKinematic = true;
    sceneCircleColliders[1].isActive = true;
    sceneCircleColliders[1].id = 1;


    sceneCircleColliders[2].radius = 15.0f;
    sceneCircleColliders[2].setPosition((float(screenWidth) / 2.0f), (float(screenHeight) / 2.0f) + 140.0f);
    sceneCircleColliders[2].setVelocity(0.0f, 0.0f);
    sceneCircleColliders[2].setAcceleration(0.0f, 0.0f);

    sceneCircleColliders[2].setMass(10.0f);
    sceneCircleColliders[2].setGravity(9.81f);

    sceneCircleColliders[2].isKinematic = true;
    sceneCircleColliders[2].isActive = true;
    sceneCircleColliders[2].id = 2;

    // Spring joint
    sceneSpringJoints[0].setConnectedCircles(&sceneCircleColliders[0], &sceneCircleColliders[1]);
    sceneSpringJoints[0].setSpringConstant(400.0f);
    sceneSpringJoints[0].setUnstretchedLength(100.0f);
    sceneSpringJoints[0].isActive = true;
    sceneSpringJoints[0].id = 0;

    sceneSpringJoints[1].setConnectedCircles(&sceneCircleColliders[1], &sceneCircleColliders[2]);
    sceneSpringJoints[1].setSpringConstant(400.0f);
    sceneSpringJoints[1].setUnstretchedLength(100.0f);
    sceneSpringJoints[1].isActive = true;
    sceneSpringJoints[1].id = 1;

    // Setup mouse listeners
    Vector2 mousePosition = Vector2({ 0.0f, 0.0f });
    Vector2 globalMousePosition = Vector2({ 0.0f, 0.0f });

    bool isMouseDown = false;
    bool middleMouseButtonDown = false;
    bool rightClickDown = false;
    bool frontSideButtonDown = false;
    bool backSideButtonDown = false;

    circleCollider *pickedUpObject = 0;
    bool isHoldingObject = false;

    int lastRightClickedObject = -1;

    // Main game loop
    while (!WindowShouldClose())
    {

        Vector2 mousePositionDelta = Vector2({ GetMousePosition().x - mousePosition.x, GetMousePosition().y - mousePosition.y });

        mousePosition = GetMousePosition();
        globalMousePosition = Vector2( { mousePosition.x - cam.offset.x, mousePosition.y - cam.offset.y } );

        isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        middleMouseButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || IsKeyPressed(KEY_F);
        rightClickDown = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
        frontSideButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_EXTRA) || IsKeyPressed(KEY_Q);
        backSideButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_SIDE) || IsKeyPressed(KEY_E);

        // Check to resize the world bounder
        float scrollWheelDelta = GetMouseWheelMove();
        worldBounding.checkToResizeBounder(scrollWheelDelta);

        // Zoom in when user scrolls - currently doesn't work with picking up objects

        /*cam.zoom += scrollWheelDelta * 0.01f;

        if (cam.zoom < 0.1f) cam.zoom = 0.1f;*/

        // Default cursor
        SetMouseCursor(0);

        // Record the time taken to run the physics
        clock_t start = clock();

        // Check to pause/play the simulation
        if (IsKeyPressed(KEY_P)) {
            // Pause/Play simulation
            simulationRunning = !simulationRunning;
        }

        // Check to add another circle to the scene
        if (frontSideButtonDown) {

            int freeSlot = -1;

            // Find next free slot in springs array
            for (int c = 0; c < sceneCircleCount; c++) {
                if (!sceneCircleColliders[c].isActive) {
                    freeSlot = c;
                    c += sceneCircleCount;
                }
            }

            if (freeSlot >= 0) {
                // Add ball to scene
                sceneCircleColliders[freeSlot].radius = 15.0f;
                sceneCircleColliders[freeSlot].setPosition(globalMousePosition.x, globalMousePosition.y);
                sceneCircleColliders[freeSlot].setVelocity(0.0f, 0.0f);
                sceneCircleColliders[freeSlot].setAcceleration(0.0f, 0.0f);

                sceneCircleColliders[freeSlot].setMass(10.0f);
                sceneCircleColliders[freeSlot].setGravity(9.81f);

                sceneCircleColliders[freeSlot].isKinematic = true;
                sceneCircleColliders[freeSlot].isActive = true;
                sceneCircleColliders[freeSlot].connectedSpringIndex = -1;
                sceneCircleColliders[freeSlot].id = freeSlot;

                totalCircles++;
            }
        }

        if (simulationRunning) {

            for (int s = 0; s < subSteps; s++) {

                systemTotalEnergy = 0.0f;

                for (int i = 0; i < sceneSpringCount; i++) {
                    if (sceneSpringJoints[i].isActive) sceneSpringJoints[i].updateJoint( GetFrameTime() / float(subSteps) );
                }

                for (int i = 0; i < sceneCircleCount; i++) {
                    if (sceneCircleColliders[i].isActive) {

                        // Resolve any collisions with other colliders
                        for (int c = 0; c < sceneCircleCount; c++) {
                            if (sceneCircleColliders[c].isActive && c != i) {

                                double currentTime = double(clock()) / CLOCKS_PER_SEC;

                                // Check and fix any collisions
                                if (sceneCircleColliders[i].resolveCollision(&sceneCircleColliders[c])) {
                                    
                                    // Play collision sound if enough time has elapsed since the last collision of the object
                                    if (sceneCircleColliders[i].lastImpactSoundTime < currentTime - 0.2f) {
                                        StopSound(impactSound);
                                        PlaySound(impactSound);
                                    }

                                    sceneCircleColliders[i].lastImpactSoundTime = currentTime;
                                }
                            }
                        }

                        // Update the position of the collider
                        sceneCircleColliders[i].updateBody( GetFrameTime() / float(subSteps) );

                        systemTotalEnergy += sceneCircleColliders[i].systemEnergy;

                        // Keep the circles inside the world bounds
                        if (worldBounding.boundObject(&sceneCircleColliders[i])) {
                            double currentTime = double(clock()) / CLOCKS_PER_SEC;
                                    
                            // Play collision sound if enough time has elapsed since the last collision of the object
                            if (sceneCircleColliders[i].lastImpactSoundTimeForBorder < currentTime - 0.2f) {
                                StopSound(impactSound);
                                PlaySound(impactSound);
                            }

                            sceneCircleColliders[i].lastImpactSoundTimeForBorder = currentTime;
                        }

                    }
                }

            }

        }

        // Calulate the time to run the physics
        clock_t end = clock();
        double physicsTime = double(end - start) / CLOCKS_PER_SEC;

        // Record the time taken to draw the scene
        start = clock();

        BeginDrawing();

        ClearBackground( GetColor(0x21262fff) );

        BeginMode2D(cam);

            // Draw world bounds
            worldBounding.drawBounder();

            DrawText("Physics Engine", (float(screenWidth) / 2.0f) - 150.0f, (float(screenHeight) / 2.0f) - 20.0f, 40, GetColor(0x354157ff) );
            DrawText("By GameDev46", (float(screenWidth) / 2.0f) - 80.0f, (float(screenHeight) / 2.0f) + 25.0f, 20, GetColor(0x354157ff) );

            bool hasRightClickedObject = false;

            // Check for pickup
            for (int i = 0; i < sceneCircleCount; i++) {

                if (!sceneCircleColliders[i].isActive) continue;

                if (CheckCollisionPointCircle(globalMousePosition, sceneCircleColliders[i].position, sceneCircleColliders[i].radius)) {
                    // Pointing hand cursor
                    SetMouseCursor(4);

                    // Check to see if circle should be deleted
                    if (backSideButtonDown) {
                        sceneCircleColliders[i].isActive = false;

                        totalCircles--;

                        for (int s = 0; s < sceneSpringCount; s++) {
                            
                            if (!sceneSpringJoints[s].isActive) continue;

                            if (sceneSpringJoints[s].isConnectedTo(&sceneCircleColliders[i])) {
                                sceneSpringJoints[s].destroyJoint();

                                shouldDrawSpringInformation[s] = false;

                                totalSprings--;
                            }
                        }

                        continue;
                    }

                    // Draw circle id
                    sceneCircleColliders[i].drawInformation();

                    // Draw spring guide
                    if (sceneCircleColliders[i].connectedSpringIndex >= 0) {
                        if (middleMouseButtonDown) shouldDrawSpringInformation[sceneCircleColliders[i].connectedSpringIndex] = !shouldDrawSpringInformation[sceneCircleColliders[i].connectedSpringIndex];
                    }

                    // Check to see if object should be picked up
                    if (isMouseDown && !isHoldingObject) {

                        pickedUpObject = &sceneCircleColliders[i];
                        isHoldingObject = true;

                        lastRightClickedObject = -1;

                    } else if (rightClickDown && !isHoldingObject) {

                        hasRightClickedObject = true;

                        // Check to create joint
                        if (lastRightClickedObject >= 0 && lastRightClickedObject != i) {

                            int freeSlot = -1;

                            // Find next free slot in springs array
                            for (int s = 0; s < sceneSpringCount; s++) {
                                if (!sceneSpringJoints[s].isActive) {
                                    freeSlot = s;
                                    s += sceneSpringCount;
                                }
                            }

                            if (freeSlot >= 0) {
                                // Join together the circles
                                sceneSpringJoints[freeSlot].setConnectedCircles(&sceneCircleColliders[i], &sceneCircleColliders[lastRightClickedObject]);
                                sceneSpringJoints[freeSlot].setSpringConstant(400.0f);
                                sceneSpringJoints[freeSlot].setUnstretchedLength(distanceBetweenPoints(sceneCircleColliders[i].position, sceneCircleColliders[lastRightClickedObject].position));
                                sceneSpringJoints[freeSlot].isActive = true;
                                sceneSpringJoints[freeSlot].id = freeSlot;

                                totalSprings++;

                                if (sceneCircleColliders[lastRightClickedObject].connectedSpringIndex == -1) {

                                    sceneCircleColliders[lastRightClickedObject].connectedSpringIndex = freeSlot;
                                    shouldDrawSpringInformation[sceneCircleColliders[lastRightClickedObject].connectedSpringIndex] = false;
                                
                                } else if (sceneCircleColliders[i].connectedSpringIndex == -1) {
                                    
                                    sceneCircleColliders[i].connectedSpringIndex = freeSlot;
                                    shouldDrawSpringInformation[freeSlot] = false;
                                
                                } else {
                                    
                                    shouldDrawSpringInformation[sceneCircleColliders[i].connectedSpringIndex] = false;
                                    sceneCircleColliders[i].connectedSpringIndex = freeSlot;
                                    shouldDrawSpringInformation[freeSlot] = false;
                                
                                }

                            }

                            lastRightClickedObject = -1;

                        } else {

                            if (lastRightClickedObject == i) {
                                // Toggle whether the object is static or not
                                sceneCircleColliders[i].isKinematic = !sceneCircleColliders[i].isKinematic;
                                lastRightClickedObject = -1;
                            } else {
                                lastRightClickedObject = i;
                            }

                        }

                    }
                }

            }

            if (rightClickDown && !hasRightClickedObject) lastRightClickedObject = -1;

            if (isHoldingObject && isMouseDown) {

                pickedUpObject->setPosition(globalMousePosition.x, globalMousePosition.y);
                pickedUpObject->setVelocity(0.0f, 0.0f);

            } else {
                pickedUpObject = 0;
                isHoldingObject = false;
            }

            for (int i = 0; i < sceneSpringCount; i++) {
                if (!sceneSpringJoints[i].isActive) continue;

                sceneSpringJoints[i].draw();

                if (shouldDrawSpringInformation[i]) sceneSpringJoints[i].drawInformation(globalMousePosition, isMouseDown);
            }

            for (int i = 0; i < sceneCircleCount; i++) {

                if (!sceneCircleColliders[i].isActive) continue;

                if (lastRightClickedObject == i) {
                    if (sceneCircleColliders[i].isKinematic) DrawText("Right click again to freeze", sceneCircleColliders[i].position.x + 40.0f, sceneCircleColliders[i].position.y - 15.0f, 13, GetColor(0xffffffff));
                    if (!sceneCircleColliders[i].isKinematic) DrawText("Right click again to unfreeze", sceneCircleColliders[i].position.x + 40.0f, sceneCircleColliders[i].position.y - 15.0f, 13, GetColor(0xffffffff));

                    DrawText("Right click another circle to create joint", sceneCircleColliders[i].position.x + 40.0f, sceneCircleColliders[i].position.y, 13, GetColor(0xffffffff));

                    DrawCircle(sceneCircleColliders[i].position.x, sceneCircleColliders[i].position.y, sceneCircleColliders[i].radius + 4, GetColor(0xffffffff));
                } else {
                    DrawCircle(sceneCircleColliders[i].position.x, sceneCircleColliders[i].position.y, sceneCircleColliders[i].radius + 2, GetColor(0x131313ff));
                }

                DrawCircle(sceneCircleColliders[i].position.x, sceneCircleColliders[i].position.y, sceneCircleColliders[i].radius, GetColor(0xb8c7e3ff));
                DrawCircle(sceneCircleColliders[i].position.x, sceneCircleColliders[i].position.y, 4, GetColor(0x11161fff));

                if (!sceneCircleColliders[i].isKinematic) DrawRectangle(sceneCircleColliders[i].position.x - 4, sceneCircleColliders[i].position.y - 4, 8, 8, GetColor(0x11161fff));
            }

            // Check to see is user can pan camera
            if (!isHoldingObject && isMouseDown) {
                SetMouseCursor(9);
                cam.offset.x += mousePositionDelta.x;
                cam.offset.y += mousePositionDelta.y;
            }

        EndMode2D();

        // Calulate the time to draw the scene
        end = clock();
        double renderTime = double(end - start) / CLOCKS_PER_SEC;

        // UI

        char systemTotalEnergyText[256];
        snprintf(systemTotalEnergyText, sizeof(systemTotalEnergyText), "System Energy: %.4g KJ", systemTotalEnergy / 1000.0f);
        DrawText(systemTotalEnergyText, 10.0f, 10.0f, 15, GetColor(0xffffffff) );

        char hertzText[256];
        snprintf(hertzText, sizeof(hertzText), "Frequency: %d Hz", int( round( float(subSteps) / GetFrameTime() ) ));
        DrawText(hertzText, 10.0f, 30.0f, 15, GetColor(0xffffffff) );

        char fpsText[256];
        snprintf(fpsText, sizeof(fpsText), "FPS: %d ", int( round( 1.0f / GetFrameTime() ) ));
        DrawText(fpsText, 10.0f, 50.0f, 15, GetColor(0xffffffff) );

        char physicsTimeText[256];
        snprintf(physicsTimeText, sizeof(physicsTimeText), "Physics time: %.1f ms", float(physicsTime * 1000.0f));
        DrawText(physicsTimeText, 10.0f, 70.0f, 15, GetColor(0xffffffff) );

        char renderTimeText[256];
        snprintf(renderTimeText, sizeof(renderTimeText), "Render Time: %.1f ms", float(renderTime * 1000.0f));
        DrawText(renderTimeText, 10.0f, 90.0f, 15, GetColor(0xffffffff) );

        char frameTimeText[256];
        snprintf(frameTimeText, sizeof(frameTimeText), "Frame Time: %.1f ms", GetFrameTime() * 1000.0f );
        DrawText(frameTimeText, 10.0f, 110.0f, 15, GetColor(0xffffffff) );

        char totalCirclesText[256];
        snprintf(totalCirclesText, sizeof(totalCirclesText), "Circles: %d / %d", totalCircles, sceneCircleCount);
        DrawText(totalCirclesText, 10.0f, 150.0f, 15, GetColor(0xffffffff) );

        char totalSpringsText[256];
        snprintf(totalSpringsText, sizeof(totalSpringsText), "Springs: %d / %d", totalSprings, sceneSpringCount);
        DrawText(totalSpringsText, 10.0f, 170.0f, 15, GetColor(0xffffffff) );

        if (IsKeyPressed(KEY_H)) shouldShowInstructions = !shouldShowInstructions;

        // Controls
        if (shouldShowInstructions) {
            DrawText("H - Hide instructions", 10.0f, GetScreenHeight() - 140.0f, 13, GetColor(0xffffffff) );
            DrawText("P - Pause/Play the simulation", 10.0f, GetScreenHeight() - 120.0f, 13, GetColor(0xffffffff) );
            DrawText("LEFT CLICK - Move objects or pan camera", 10.0f, GetScreenHeight() - 100.0f, 13, GetColor(0xffffffff) );
            DrawText("RIGHT CLICK (over object) - To create joints or freeze objects", 10.0f, GetScreenHeight() - 80.0f, 13, GetColor(0xffffffff) );
            DrawText("MIDDLE MOUSE BUTTON / F (over object) - View the objects connected spring properties", 10.0f, GetScreenHeight() - 60.0f, 13, GetColor(0xffffffff) );
            DrawText("FRONT SIDE MOUSE BUTTON / Q - Create a new object", 10.0f, GetScreenHeight() - 40.0f, 13, GetColor(0xffffffff) );
            DrawText("BACK SIDE MOUSE BUTTON / E (over object) - Destroy object", 10.0f, GetScreenHeight() - 20.0f, 13, GetColor(0xffffffff) );
        }

        EndDrawing();

    }

    UnloadSound(impactSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
