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

	replit: https://replit.com/@GameDev46
	youtube: https://www.youtube.com/@gamedev46
	twitter: https://twitter.com/GameDev46
	github: https://github.com/GameDev46
*/

// Include the raylib library
#include "include/raylib.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <time.h>
#include <fstream>

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

struct arr {
    float values[2];
};

struct arr solveQuadratic(float a, float b, float c) {
    arr solutions;

    solutions.values[0] = ( -b + sqrt( (b * b) - (4.0f * a * c)) ) / ( 2.0f * a );
    solutions.values[1] = ( -b - sqrt( (b * b) - (4.0f * a * c)) ) / ( 2.0f * a );

    return solutions;
}

float sign(float a) {
    return a / abs(a);
}

/* ---------------------- */
/* CLASSES */
/* ---------------------- */

// UI Textbox
class numberInput {
    public:
        Vector2 size = Vector2({20.0f, 20.0f});
        Vector2 position = Vector2({0.0f, 0.0f});

        char value[16];
        char defaultValue[16];

        bool checkForInput(Vector2 mousePosition, bool isMouseDown) {

           numberInputRectangle = { position.x, position.y, size.x, size.y };

           if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) SetMouseCursor(2);

            if (isMouseDown) {
                if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) {
                    isSelected = true;

                    for (int i = 0; i < 16; i++) {
                        textInput[i] = ' ';
                    }

                    charsInValue = 0;
                    arrayIndex = 0;

                } else if (isSelected) {
                    isSelected = false;

                    if (charsInValue <= 0) {
                        for (int i = 0; i < 16; i++) {
                            textInput[i] = defaultValue[i];
                        }
                    }

                    for (int i = 0; i < 16; i++) {
                        value[i] = textInput[i];
                    }

                    arrayIndex = 0;

                    return true;
                }
            }
            
            if (isSelected) {

                if (IsKeyPressed(KEY_ONE)) { textInput[arrayIndex++] = '1'; charsInValue++; }
                if (IsKeyPressed(KEY_TWO)) { textInput[arrayIndex++] = '2'; charsInValue++; }
                if (IsKeyPressed(KEY_THREE)) { textInput[arrayIndex++] = '3'; charsInValue++; }
                if (IsKeyPressed(KEY_FOUR)) { textInput[arrayIndex++] = '4'; charsInValue++; }
                if (IsKeyPressed(KEY_FIVE)) { textInput[arrayIndex++] = '5'; charsInValue++; }
                if (IsKeyPressed(KEY_SIX)) { textInput[arrayIndex++] = '6'; charsInValue++; }
                if (IsKeyPressed(KEY_SEVEN)) { textInput[arrayIndex++] = '7'; charsInValue++; }
                if (IsKeyPressed(KEY_EIGHT)) { textInput[arrayIndex++] = '8'; charsInValue++; }
                if (IsKeyPressed(KEY_NINE)) { textInput[arrayIndex++] = '9'; charsInValue++; }
                if (IsKeyPressed(KEY_ZERO)) { textInput[arrayIndex++] = '0'; charsInValue++; }

                if (IsKeyPressed(KEY_PERIOD)) textInput[arrayIndex++] = '.';

                if (IsKeyPressed(KEY_BACKSPACE) && arrayIndex > 0) { textInput[--arrayIndex] = ' '; charsInValue--; }

                if (arrayIndex >= 15 || IsKeyPressed(KEY_ENTER)) {
                    isSelected = false;

                    if (charsInValue <= 0) {
                        for (int i = 0; i < 16; i++) {
                            textInput[i] = defaultValue[i];
                        }
                    }

                    for (int i = 0; i < 16; i++) {
                        value[i] = textInput[i];
                    }

                    arrayIndex = 0;

                    return true;
                }

            }

            return false;
        }

        void draw() {

            DrawRectangle(position.x, position.y + size.y, size.x, 1.0f, GetColor(0xffffffff) );

            if (isSelected) {
                DrawText(textInput, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            } else {
                DrawText(defaultValue, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            }

            return;
        }

    private:
        int arrayIndex = 0;
        char textInput[16];

        bool isSelected = false;
        int charsInValue = 0;

        Rectangle numberInputRectangle;
};

class textboxInput {
    public:
        Vector2 size = Vector2({20.0f, 20.0f});
        Vector2 position = Vector2({0.0f, 0.0f});

        char value[16];
        char defaultValue[16];

        bool checkForInput(Vector2 mousePosition, bool isMouseDown) {

           numberInputRectangle = { position.x, position.y, size.x, size.y };

           if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) SetMouseCursor(2);

            if (isMouseDown) {
                if (CheckCollisionPointRec(mousePosition, numberInputRectangle)) {
                    isSelected = true;

                    for (int i = 0; i < 16; i++) {
                        textInput[i] = ' ';
                    }

                    charsInValue = 0;
                    arrayIndex = 0;

                } else if (isSelected) {
                    isSelected = false;

                    if (charsInValue <= 0) {
                        for (int i = 0; i < 16; i++) {
                            textInput[i] = defaultValue[i];
                        }
                    }

                    for (int i = 0; i < 16; i++) {
                        value[i] = textInput[i];
                    }

                    arrayIndex = 0;

                    return true;
                }
            }
            
            if (isSelected) {

                int key = GetCharPressed();

                if (key >= 32 && key <= 125) {
                    textInput[arrayIndex++] = char(key);
                    charsInValue++;
                }
                
                if (IsKeyPressed(KEY_BACKSPACE) && arrayIndex > 0) { textInput[--arrayIndex] = ' '; charsInValue--; }

                if (arrayIndex >= 15 || IsKeyPressed(KEY_ENTER)) {
                    isSelected = false;

                    if (charsInValue <= 0) {
                        for (int i = 0; i < 16; i++) {
                            textInput[i] = defaultValue[i];
                        }
                    }

                    for (int i = 0; i < 16; i++) {
                        value[i] = textInput[i];
                    }

                    arrayIndex = 0;

                    return true;
                }

            }

            return false;
        }

        bool selected() {
            return isSelected;
        }

        void draw() {

            DrawRectangle(position.x, position.y + size.y, size.x, 1.0f, GetColor(0xffffffff) );

            if (isSelected) {
                DrawText(textInput, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            } else {
                DrawText(defaultValue, position.x + 2.0f, position.y + 5.0f, 12, GetColor(0xffffffff) );
            }

            return;
        }

    private:
        int arrayIndex = 0;
        char textInput[16];

        bool isSelected = false;
        int charsInValue = 0;

        Rectangle numberInputRectangle;
};

class checkbox {
    public:
        Vector2 size = Vector2({10.0f, 10.0f});
        Vector2 position = Vector2({0.0f, 0.0f});

        bool isTicked = false;

        bool checkForInput(Vector2 mousePosition, bool isMouseDown) {

           inputRectangle = { position.x, position.y, size.x, size.y };

           if (CheckCollisionPointRec(mousePosition, inputRectangle)) {
                SetMouseCursor(4);

                if (isMouseDown) {
                    isTicked = !isTicked;
                    return true;
                }
           }
           
           return false;
        }

        void draw() {

            DrawRectangleLines(position.x, position.y, size.x, size.y, GetColor(0xffffffff));

            if (isTicked) DrawRectangle(position.x, position.y, size.x, size.y, GetColor(0xffffffff));

            return;
        }

    private:
        Rectangle inputRectangle;
};

class button {
    public:
        Vector2 position;
        Vector2 size;
        Color colour;
        Color hoverColour;

        char buttonText[256];

        bool isMouseOverButton(Vector2 mousePosition) {
            if (mousePosition.x > position.x && mousePosition.x < position.x + size.x) {
                if (mousePosition.y > position.y && mousePosition.y < position.y + size.y) {
                    return true;
                }
            }

            return false;
        }

        void draw(Vector2 mousePosition) {

            if (isMouseOverButton(mousePosition)) {
                DrawRectangle(position.x, position.y, size.x, size.y, hoverColour);

                // Pointing hand cursor
                SetMouseCursor(4);
            } else {
                DrawRectangle(position.x, position.y, size.x, size.y, colour);
            }

            DrawText(buttonText, position.x + 10.0f, position.y + (size.y / 2) - 7.0f, 12, WHITE);
        }
};

class Panel {
    public:

        Vector2 position = Vector2({ 0.0f, 0.0f });

        void checkToDrag(Vector2 mousePosition, Rectangle rect, bool isMouseDown, bool wasMouseDown) {

            hovered = CheckCollisionPointRec(mousePosition, rect) || isBeingDragged;

            if (CheckCollisionPointRec(mousePosition, rect)) {
                SetMouseCursor(4);
                if (!isBeingDragged && isMouseDown && !wasMouseDown) isBeingDragged = true;
            }

            if (isBeingDragged) {
                if (!isMouseDown) isBeingDragged = false;
                position = mousePosition;
            }

            // Check the bounds of the window
            float screenWidth = GetScreenWidth();
            float screenHeight = GetScreenHeight();

            // X Check
            if (position.x >= screenWidth - (rect.width * 0.5f)) position.x = screenWidth - (rect.width * 0.5f);
            if (position.x <= rect.width * 0.5f) position.x = (rect.width * 0.5f);

            // Y Check
            if (position.y >= screenHeight - rect.height) position.y = screenHeight - rect.height;
            if (position.y <= 0) position.y = 0;

            return;
        }

        bool isHovered() {
            if (hovered) return true;
            return false;
        }

        bool beingDragged() {
            if (isBeingDragged) return true;
            return false;
        }

    private:
        bool isBeingDragged = false;
        bool hovered = false;

};

// Create the circleCollider class
class circleCollider {
    public:
        Vector2 position = Vector2({ 0.0f, 0.0f });
        Vector2 oldPosition = Vector2({ 0.0f, 0.0f });
        Vector2 velocity = Vector2({ 0.0f, 0.0f });
        Vector2 acceleration = Vector2({ 0.0f, 0.0f });

        Vector2 velocityForNextFrame = Vector2({ 0.0f, 0.0f });
        bool shouldUseVelocityForNextFrame = false;

        bool canCollide = true;

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

        float getGravity() {
            return gravity;
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

        bool resolveCollision(circleCollider *otherObj, bool useMomentum) {

            if (!canCollide || !otherObj->canCollide) return false;

            float dist = distanceBetweenPoints(position, otherObj->position);

            float minDist = radius + otherObj->radius;

            if (dist - minDist < 0.0f) {

                // UPDATE: Use momentum in calculations so that nodes of different masses can be used!

                // Move circles apart
                float collisionAxisDirection = atan2(position.y - otherObj->position.y, position.x - otherObj->position.x);

                float overlap = dist - minDist;

                if (!useMomentum) {

                    // Move objects out of collision based on a ratio of their masses

                    float massRatio = 1 / (mass + otherObj->getMass());

                    position.x += cos(collisionAxisDirection) * -overlap * massRatio * otherObj->getMass();
                    position.y += sin(collisionAxisDirection) * -overlap * massRatio * otherObj->getMass();

                    otherObj->position.x += cos(collisionAxisDirection) * overlap * massRatio * mass;
                    otherObj->position.y += sin(collisionAxisDirection) * overlap * massRatio * mass;

                } else {

                    float totalMomentum = (otherObj->getMass() * lengthOfVector(otherObj->velocity)) + (mass * lengthOfVector(velocity));

                    float totalEnergy = (0.5f * otherObj->getMass() * lengthOfVector(otherObj->velocity) * lengthOfVector(otherObj->velocity)) + (0.5f * mass * lengthOfVector(velocity) * lengthOfVector(velocity));

                    float a = (otherObj->getMass() * otherObj->getMass()) + (mass * otherObj->getMass());
                    float b = -2.0f * totalMomentum * otherObj->getMass();
                    float c = (totalMomentum * totalMomentum) - (2.0f * mass * totalEnergy);

                    float appropriateValue = 0.0f;

                    float sol1 = solveQuadratic(a, b, c).values[0];
                    float sol2 = solveQuadratic(a, b, c).values[1];

                    if (sign(sol1) != sign(otherObj->velocity.x) && sign(sol2) == sign(otherObj->velocity.x)) {
                        appropriateValue = sol1;
                    }
                    else if (sign(sol2) != sign(otherObj->velocity.x) && sign(sol1) == sign(otherObj->velocity.x)) {
                        appropriateValue = sol2;
                    }
                    else if (abs(sol1) < abs(sol2)) {
                        appropriateValue = sol1;
                    }
                    else if (abs(sol1) >= abs(sol2)) {
                        appropriateValue = sol2;
                    }

                    //cout << sol1 << " " << sol2 << " " << appropriateValue << endl;

                    float otherObjVelocity = appropriateValue;
                    float objVelocity = ( totalMomentum - (otherObjVelocity * otherObj->getMass()) ) / mass;

                    position.x += cos(collisionAxisDirection) * -overlap * 0.5f;
                    position.y += sin(collisionAxisDirection) * -overlap * 0.5f;

                    otherObj->position.x += cos(collisionAxisDirection) * overlap * 0.5f;
                    otherObj->position.y += sin(collisionAxisDirection) * overlap * 0.5f;

                    velocityForNextFrame = Vector2({ objVelocity * cos(collisionAxisDirection), objVelocity * sin(collisionAxisDirection) });
                    shouldUseVelocityForNextFrame = true;

                    otherObj->velocityForNextFrame = Vector2({ otherObjVelocity * cos(collisionAxisDirection), otherObjVelocity * sin(collisionAxisDirection) });
                    otherObj->shouldUseVelocityForNextFrame = true;

                }

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

                if (shouldUseVelocityForNextFrame) {
                    velocity = velocityForNextFrame;
                    shouldUseVelocityForNextFrame = false;
                }

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
            systemEnergy += mass * gravity * 100.0f * (10000.0f - position.y);

            // Reset acceleration for next iteration
            acceleration.x = 0.0f;
            acceleration.y = 0.0f;

            return;
        }

        void drawInformation(Vector2 mousePosition, bool isMouseDown) {

            char idText[256];
            snprintf(idText, sizeof(idText), "ID: %d", id);
            DrawText(idText, position.x + 25.0f, position.y - 40.0f, 12, GetColor(0xffffffff) );

            char connectedSpringText[256];
            snprintf(connectedSpringText, sizeof(connectedSpringText), "Connected Spring: %d", connectedSpringIndex);
            DrawText(connectedSpringText, position.x + 25.0f, position.y - 60.0f, 12, GetColor(0xffffffff) );

            /*char massText[256];
            snprintf(massText, sizeof(massText), "Mass: %d g", int(round(mass)));
            DrawText(massText, position.x + 25.0f, position.y - 80.0f, 12, GetColor(0xffffffff) );*/

            DrawText("Mass: ", position.x + 25.0f, position.y - 80.0f, 12, GetColor(0xffffffff) );

            massInput.position = Vector2( { position.x + 60.0f, position.y - 85.0f } );
            massInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultSpringConstantValue[16];
            snprintf(defaultSpringConstantValue, sizeof(defaultSpringConstantValue), "%.2f", mass);

            for (int i = 0; i < 16; i++) {
                massInput.defaultValue[i] = defaultSpringConstantValue[i];
            }

            // Check if user has input a new value for the spring constant
            if (massInput.checkForInput(mousePosition, isMouseDown)) {
                // Convert the value from a char array to an integer
                string str(massInput.value);
                mass = stof(str);
            }

            massInput.draw();


            DrawText("Radius: ", position.x + 25.0f, position.y - 100.0f, 12, GetColor(0xffffffff) );

            radiusInput.position = Vector2( { position.x + 70.0f, position.y - 105.0f } );
            radiusInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultRadiusValue[16];
            snprintf(defaultRadiusValue, sizeof(defaultRadiusValue), "%.2f", radius);

            for (int i = 0; i < 16; i++) {
                radiusInput.defaultValue[i] = defaultRadiusValue[i];
            }

            // Check if user has input a new value for the spring constant
            if (radiusInput.checkForInput(mousePosition, isMouseDown)) {
                // Convert the value from a char array to an integer
                string str(radiusInput.value);
                radius = stof(str);
            }

            radiusInput.draw();

            char positionText[256];
            snprintf(positionText, sizeof(positionText), "Position: %d %d", int(round(position.x)), int(round(position.y)));
            DrawText(positionText, position.x + 25.0f, position.y - 120.0f, 12, GetColor(0xffffffff) );

            char velocityText[256];
            snprintf(velocityText, sizeof(velocityText), "Velocity: %d %d", int(round(velocity.x)), int(round(velocity.y)));
            DrawText(velocityText, position.x + 25.0f, position.y - 140.0f, 12, GetColor(0xffffffff) );

            return;
        }

    private:
        float mass = 1.0f;
        float gravity = 9.81f;

        numberInput massInput;
        numberInput radiusInput;

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

        float getSpringConstant() {
            return springConstant;
        }

        void setUnstretchedLength(float newUnstretchedLength) {
            unstretchedLength = newUnstretchedLength;
            return;
        }

        float getUnstretchedLength() {
            return unstretchedLength;
        }

        void setConnectedCircles(circleCollider *obj1, circleCollider *obj2) {
            object1 = obj1;
            object2 = obj2;
            return;
        }

        int getConnectedCircles(int num) {
            if (num == 1) {
                return object1->id;
            } else {
                return object2-> id;
            }
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

            float UIRad = atan2(object1->position.y - object2->position.y, object1->position.x - object2->position.x);

            float offsetX = sin(UIRad) * inverseDistance * 600.0f;
            float offsetY = cos(UIRad) * inverseDistance * 600.0f;

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

            float UIRad = atan2(object1->position.y - object2->position.y, object1->position.x - object2->position.x);

            float offsetX = (cos(UIRad) * -unstretchedLength) + (sin(-UIRad) * 25.0f);
            float offsetY = (sin(UIRad) * -unstretchedLength) + (cos(UIRad) * 25.0f);

            Vector2 startPoint = Vector2({ object1->position.x + (sin(-UIRad) * 25.0f), object1->position.y + (cos(UIRad) * 25.0f) });
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
            springConstantInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultSpringConstantValue[16];
            snprintf(defaultSpringConstantValue, sizeof(defaultSpringConstantValue), "%.2f", springConstant);
            
            for (int i = 0; i < 16; i++) {
                springConstantInput.defaultValue[i] = defaultSpringConstantValue[i];
            }

            // Check if user has input a new value for the spring constant
            if (springConstantInput.checkForInput(mousePosition, isMouseDown)) {
                // Convert the value from a char array to an integer
                string str(springConstantInput.value);
                springConstant = stof(str);
            }

            springConstantInput.draw();


            DrawText("Natural Length: ", object1->position.x + 45.0f, object1->position.y + 60.0f, 12, GetColor(0xffffffff) );

            // Allow user to edit spring constant
            naturalLengthInput.position = Vector2( { object1->position.x + 140.0f, object1->position.y + 55.0f } );
            naturalLengthInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultNaturalLengthValue[16];
            snprintf(defaultNaturalLengthValue, sizeof(defaultNaturalLengthValue), "%.2f", unstretchedLength);
            
            for (int i = 0; i < 16; i++) {
                naturalLengthInput.defaultValue[i] = defaultNaturalLengthValue[i];
            }

            // Check if user has input a new value for the spring constant
            if (naturalLengthInput.checkForInput(mousePosition, isMouseDown)) {
                // Convert the value from a char array to an integer
                string str(naturalLengthInput.value);
                unstretchedLength = stof(str);
            }

            naturalLengthInput.draw();

            char idText[256];
            snprintf(idText, sizeof(idText), "ID: %d", id);
            DrawText(idText, object1->position.x + 45.0f, object1->position.y + 80.0f, 12, GetColor(0xffffffff) );

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

        float distBetweenObj = 0.0f;

        float springConstant = 30.0f;
        float unstretchedLength = 50.0f;

        float extension = 0.0f;
        float force = 0.0f;

        numberInput springConstantInput;
        numberInput naturalLengthInput;

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

/* ---------------------- */
/* SAVING AND LOADING */
/* ---------------------- */

void saveFile(string fileName, circleCollider* circlesData, int maxCircles, SpringJoint* springsData, int maxSprings, objectBounder worldBound, float worldGravitySetting, bool useMoment) {

    string saveString = to_string(worldBound.radius) + "$";
    saveString = saveString + to_string(worldGravitySetting) + "$";
    saveString = saveString + ((useMoment == true) ? "1" : "0") + "$";

    for (int i = 0; i < maxCircles; i++) {

        if (!circlesData[i].isActive) continue;

        saveString = saveString + "Node" + "&";
        saveString = saveString + to_string(circlesData[i].id) + "&";

        saveString = saveString + to_string(circlesData[i].position.x) + "&";
        saveString = saveString + to_string(circlesData[i].position.y) + "&";

        saveString = saveString + to_string(circlesData[i].getMass()) + "&";
        saveString = saveString + to_string(circlesData[i].getGravity()) + "&";

        saveString = saveString + (circlesData[i].canCollide ? "1" : "0") + "&";

        saveString = saveString + to_string(circlesData[i].radius) + "&";

        saveString = saveString + (circlesData[i].isKinematic ? "1" : "0") + "&";

        saveString = saveString + to_string(circlesData[i].connectedSpringIndex) + "$";
    }

    for (int i = 0; i < maxSprings; i++) {

        if (!springsData[i].isActive) continue;

        saveString = saveString + "Spring" + "&";
        saveString = saveString + to_string(springsData[i].id) + "&";

        saveString = saveString + to_string(springsData[i].getSpringConstant()) + "&";
        saveString = saveString + to_string(springsData[i].getUnstretchedLength()) + "&";

        saveString = saveString + to_string(springsData[i].getConnectedCircles(1)) + "&";
        saveString = saveString + to_string(springsData[i].getConnectedCircles(2)) + "$";
    }

    ofstream file(fileName + ".txt");

    file << saveString;

    file.close();

    return;
}

void loadFile(string fileName, circleCollider* circlesData, int maxCircles, SpringJoint* springsData, int maxSprings, objectBounder worldBound, float *worldGravitySetting, bool *useMoment) {

    ifstream file(fileName + ".txt");

    string loadedText;
    getline(file, loadedText);

    file.close();

    char *loadString = new char[loadedText.length()]; 

    for (unsigned int i = 0; i < loadedText.length(); i++) {
        loadString[i] = loadedText[i];
    }

    for (int i = 0; i < maxCircles; i++) {
        circlesData[i].isActive = false;
    }

    for (int i = 0; i < maxSprings; i++) {
        springsData[i].isActive = false;
    }
 
    // Load the saved level stroke data
    char *token = strtok(loadString, "$");
    worldBound.radius = atof(token);

    token = strtok(NULL, "$");

    string tokenString(token);
    *worldGravitySetting = stof(tokenString);

    token = strtok(NULL, "$");

    *useMoment = (atoi(token) == 1) ? true : false;

    token = strtok(NULL, "$");

    int i = 0;
   
   // Loop over each object
    while (token != NULL)
    {

        char *objectData = strtok(token, "&");
        string objectType(objectData);

        objectData = strtok(NULL, "&");

        int objID = atoi(objectData);

        int obj1ID = 0; // For spring

        objectData = strtok(NULL, "&");
        int x = 0;

        // Set each property of the object
        while (objectData != NULL)
        {
            if (objectType == "Node") {

                circlesData[objID].isActive = true;

                if (x == 0) {
                    circlesData[objID].position.x = atof(objectData);
                    circlesData[objID].oldPosition.x = atof(objectData);
                }

                if (x == 1) {
                    circlesData[objID].position.y = atof(objectData);
                    circlesData[objID].oldPosition.y = atof(objectData);
                }

                if (x == 2) circlesData[objID].setMass(atof(objectData));
                if (x == 3) circlesData[objID].setGravity(atof(objectData));

                if (x == 4) circlesData[objID].canCollide = (atoi(objectData) == 1) ? true : false;

                if (x == 5) circlesData[objID].radius = atof(objectData);

                if (x == 6) circlesData[objID].isKinematic = (atoi(objectData) == 1) ? true : false;

                if (x == 7) circlesData[objID].connectedSpringIndex = atoi(objectData);

            }

            if (objectType == "Spring") {

                springsData[objID].isActive = true;

                if (x == 0) springsData[objID].setSpringConstant(atof(objectData));
                if (x == 1) springsData[objID].setUnstretchedLength(atof(objectData));

                if (x == 2) obj1ID = atoi(objectData);

                if (x == 3) {
                    int obj2ID = atoi(objectData);

                    springsData[objID].setConnectedCircles(&circlesData[obj1ID], &circlesData[obj2ID]);
                }

            }

            objectData = strtok(NULL, "&");

            x++;
        }

        // Reset token ready for next iteration (token is a destructive process)

        char *newLoadString = new char[loadedText.length()]; 

        for (unsigned int i = 0; i < loadedText.length(); i++) {
            newLoadString[i] = loadedText[i];
        }

        token = strtok(newLoadString, "$");

        for (int y = 0; y < i + 3; y++) {
            token = strtok(NULL, "$");
        }

        i++;
    }

    return;
}

// Main physics loop
int main()
{

    const int screenWidth = 1200;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Physics Engine");

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
    float startSystemEnergy = 0.0f;

    bool updateStartSystemEnergy = true;

    bool simulationRunning = true;
    bool shouldShowInstructions = true;

    int subSteps = 8;

    objectBounder worldBounding;

    // Basic options

    float worldDefaultSpringConstant = 400.0f;
    numberInput defaultSpringConstantInput;

    float worldGravity = 9.81f;
    numberInput worldGravityInput;

    float defaultObjectMass = 10.0f;
    numberInput spawnedObjectMassInput;

    float spawnedObjectRadius = 15.0f;
    numberInput spawnedObjectRadiusInput;

    numberInput positionXInput;
    numberInput positionYInput;
    numberInput velocityXInput;
    numberInput velocityYInput;

    numberInput inspectorMassInput;
    numberInput inspectorRadiusInput;

    checkbox hasCollisionsInput;

    char lastSaveFile[16] = "";
    textboxInput fileSaveName;

    bool useMomentum = false;
    checkbox useMomentumInput;

    button deleteAllObjectButton;
    deleteAllObjectButton.position = Vector2({ 0.0f, 0.0f });
    deleteAllObjectButton.size = Vector2({ 150.0f, 25.0f });
    deleteAllObjectButton.colour = GetColor(0xe85b4aff);
    deleteAllObjectButton.hoverColour = GetColor(0xcf4838ff);

    char destroyObjectsButtText[256] = "Destroy All Objects";
    for (int i = 0; i < 256; i++) {
        deleteAllObjectButton.buttonText[i] = destroyObjectsButtText[i];
    }

    button deleteAllJointsButton;
    deleteAllJointsButton.position = Vector2({ 0.0f, 0.0f });
    deleteAllJointsButton.size = Vector2({ 150.0f, 25.0f });
    deleteAllJointsButton.colour = GetColor(0xe85b4aff);
    deleteAllJointsButton.hoverColour = GetColor(0xcf4838ff);

    char destroyJointsButtText[256] = "Destroy All Joints";
    for (int i = 0; i < 256; i++) {
        deleteAllJointsButton.buttonText[i] = destroyJointsButtText[i];
    }

    button saveButton;
    saveButton.position = Vector2({ 0.0f, 0.0f });
    saveButton.size = Vector2({ 80.0f, 25.0f });
    saveButton.colour = GetColor(0x24a652ff);
    saveButton.hoverColour = GetColor(0x1bc457ff);

    char saveButtonText[256] = "Save";
    for (int i = 0; i < 256; i++) {
        saveButton.buttonText[i] = saveButtonText[i];
    }

    button loadButton;
    loadButton.position = Vector2({ 0.0f, 0.0f });
    loadButton.size = Vector2({ 80.0f, 25.0f });
    loadButton.colour = GetColor(0xffffff44);
    loadButton.hoverColour = GetColor(0xffffff66);

    char loadButtonText[256] = "Load";
    for (int i = 0; i < 256; i++) {
        loadButton.buttonText[i] = loadButtonText[i];
    }

    // Settings menu drag

    Panel worldSettingsPanel;
    worldSettingsPanel.position = Vector2({ 110.0f, 290.0f });

    Panel worldInfoPanel;
    worldInfoPanel.position = Vector2({ 153.0f, 20.0f });

    Panel objectCountPanel;
    objectCountPanel.position = Vector2({ 93.0f, 180.0f });

    Panel inspectorPanel;
    inspectorPanel.position = Vector2({ GetScreenWidth() + 100.0f, 20.0f });

    Panel savePanel;
    savePanel.position = Vector2({ GetScreenWidth() + 100.0f, 335.0f });

    // Icons

    Texture2D settingsIcon = LoadTexture("images/settings.png");
    Texture2D statsIcon = LoadTexture("images/stats.png");
    Texture2D circleIcon = LoadTexture("images/circle.png");
    Texture2D inspectIcon = LoadTexture("images/inspect.png");
    Texture2D saveIcon = LoadTexture("images/save.png");

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
    bool shouldDrawCircleInformation[sceneCircleCount];

    for (int i = 0; i < sceneCircleCount; i++) {
        shouldDrawCircleInformation[i] = false;
    }

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
    bool wasMouseDown = false;
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

        wasMouseDown = isMouseDown;
        isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        middleMouseButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || (IsKeyPressed(KEY_F) && !fileSaveName.selected());
        rightClickDown = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
        frontSideButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_EXTRA) || (IsKeyPressed(KEY_Q) && !fileSaveName.selected());
        backSideButtonDown = IsMouseButtonPressed(MOUSE_BUTTON_SIDE) || (IsKeyPressed(KEY_E) && !fileSaveName.selected());

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
        if (IsKeyPressed(KEY_P) && !fileSaveName.selected()) {
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
                sceneCircleColliders[freeSlot].radius = spawnedObjectRadius;
                sceneCircleColliders[freeSlot].setPosition(globalMousePosition.x, globalMousePosition.y);
                sceneCircleColliders[freeSlot].setVelocity(0.0f, 0.0f);
                sceneCircleColliders[freeSlot].setAcceleration(0.0f, 0.0f);

                sceneCircleColliders[freeSlot].setMass(defaultObjectMass);
                sceneCircleColliders[freeSlot].setGravity(worldGravity);

                sceneCircleColliders[freeSlot].isKinematic = true;
                sceneCircleColliders[freeSlot].isActive = true;
                sceneCircleColliders[freeSlot].connectedSpringIndex = -1;
                sceneCircleColliders[freeSlot].id = freeSlot;

                shouldDrawCircleInformation[freeSlot] = false;

                totalCircles++;

                updateStartSystemEnergy = true;
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
                                if (sceneCircleColliders[i].resolveCollision(&sceneCircleColliders[c], useMomentum)) {
                                    
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

        if (updateStartSystemEnergy) {
            startSystemEnergy = systemTotalEnergy;
            updateStartSystemEnergy = false;
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

                if (shouldDrawCircleInformation[i]) sceneCircleColliders[i].drawInformation(globalMousePosition, isMouseDown && !wasMouseDown);

                if (CheckCollisionPointCircle(globalMousePosition, sceneCircleColliders[i].position, sceneCircleColliders[i].radius)) {
                    // Pointing hand cursor
                    SetMouseCursor(4);

                    // Check to see if circle should be deleted
                    if (backSideButtonDown) {
                        sceneCircleColliders[i].isActive = false;
                        shouldDrawCircleInformation[i] = false;

                        totalCircles--;

                        updateStartSystemEnergy = true;

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

                    // Check to toggle the circle information
                    if (middleMouseButtonDown) shouldDrawCircleInformation[i] = !shouldDrawCircleInformation[i];

                    // Draw spring guide
                    if (sceneCircleColliders[i].connectedSpringIndex >= 0) {
                        if (middleMouseButtonDown) shouldDrawSpringInformation[sceneCircleColliders[i].connectedSpringIndex] = !shouldDrawSpringInformation[sceneCircleColliders[i].connectedSpringIndex];
                    }

                    // Check to see if object should be picked up
                    if (isMouseDown && !wasMouseDown && !isHoldingObject) {

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
                                sceneSpringJoints[freeSlot].setSpringConstant(worldDefaultSpringConstant);
                                sceneSpringJoints[freeSlot].setUnstretchedLength(distanceBetweenPoints(sceneCircleColliders[i].position, sceneCircleColliders[lastRightClickedObject].position));
                                sceneSpringJoints[freeSlot].isActive = true;
                                sceneSpringJoints[freeSlot].id = freeSlot;

                                totalSprings++;

                                updateStartSystemEnergy = true;

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

                if (shouldDrawSpringInformation[i]) sceneSpringJoints[i].drawInformation(globalMousePosition, isMouseDown && !wasMouseDown);
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
            if (!isHoldingObject && isMouseDown && !worldSettingsPanel.isHovered() && !objectCountPanel.isHovered() && !worldInfoPanel.isHovered() && !inspectorPanel.isHovered() && !savePanel.isHovered()) {
                SetMouseCursor(9);
                cam.offset.x += mousePositionDelta.x;
                cam.offset.y += mousePositionDelta.y;
            }

        EndMode2D();

        // Calulate the time to draw the scene
        end = clock();
        double renderTime = double(end - start) / CLOCKS_PER_SEC;

        // UI ----------------

        // World Info ---------------

        Rectangle rect = { worldInfoPanel.position.x - 148.0f, worldInfoPanel.position.y - 14.0f, 300.0f, 30.0f };
        worldInfoPanel.checkToDrag(mousePosition, rect, isMouseDown, wasMouseDown);

        // Panel outline
        rect = { worldInfoPanel.position.x - 150.0f, worldInfoPanel.position.y - 16.0f, 304.0f, 154.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Panel backing
        rect = { worldInfoPanel.position.x - 148.0f, worldInfoPanel.position.y - 14.0f, 300.0f, 150.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1b202dff));

        // Title outline
        rect = { worldInfoPanel.position.x - 148.0f, worldInfoPanel.position.y - 14.0f, 300.0f, 32.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Title backing
        rect = { worldInfoPanel.position.x - 148.0f, worldInfoPanel.position.y - 14.0f, 300.0f, 30.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1f2432ff));

        // Panel title
        DrawText("World Info", worldInfoPanel.position.x - 113.0f, worldInfoPanel.position.y, 12, GetColor(0xffffffff) );

        DrawTextureEx(statsIcon, Vector2({ worldInfoPanel.position.x - 140.0f, worldInfoPanel.position.y - 5.0f }), 0.0f, 0.03f, GetColor(0xff88ffff));

        // System information

        char systemTotalEnergyText[256];
        snprintf(systemTotalEnergyText, sizeof(systemTotalEnergyText), "System Energy: %d KJ", int(round(systemTotalEnergy / 1000.0f)) );
        DrawText(systemTotalEnergyText, worldInfoPanel.position.x - 133.0f, worldInfoPanel.position.y + 40.0f, 15, GetColor(0xffffffff) );

        char systemTotalEnergyLoss[256];
        snprintf(systemTotalEnergyLoss, sizeof(systemTotalEnergyLoss), "%.2f %%", ((startSystemEnergy - systemTotalEnergy) / (systemTotalEnergy)) * 100.0f );
        DrawText(systemTotalEnergyLoss, worldInfoPanel.position.x + 90.0f, worldInfoPanel.position.y + 40.0f, 12, GetColor(0xffffff88) );

        char hertzText[256];
        snprintf(hertzText, sizeof(hertzText), "Frequency: %d Hz", int( round( float(subSteps) / GetFrameTime() ) ));
        DrawText(hertzText, worldInfoPanel.position.x - 133.0f, worldInfoPanel.position.y + 70.0f, 12, GetColor(0xffffffff) );

        char fpsText[256];
        snprintf(fpsText, sizeof(fpsText), "FPS: %d ", int( round( 1.0f / GetFrameTime() ) ));
        DrawText(fpsText, worldInfoPanel.position.x - 133.0f, worldInfoPanel.position.y + 90.0f, 12, GetColor(0xffffffff) );

        char playStateText[256] = "";
        strcat(playStateText, "State: ");
        strcat(playStateText, (simulationRunning) ? "Playing" : "Paused");
        DrawText(playStateText, worldInfoPanel.position.x - 133.0f, worldInfoPanel.position.y + 110.0f, 12, GetColor(0xffffffff) );

        char physicsTimeText[256];
        snprintf(physicsTimeText, sizeof(physicsTimeText), "Physics time: %.1f ms", float(physicsTime * 1000.0f));
        DrawText(physicsTimeText, worldInfoPanel.position.x + 7.0f, worldInfoPanel.position.y + 70.0f, 12, GetColor(0xffffffff) );

        char renderTimeText[256];
        snprintf(renderTimeText, sizeof(renderTimeText), "Render Time: %.1f ms", float(renderTime * 1000.0f));
        DrawText(renderTimeText, worldInfoPanel.position.x + 7.0f, worldInfoPanel.position.y + 90.0f, 12, GetColor(0xffffffff) );

        char frameTimeText[256];
        snprintf(frameTimeText, sizeof(frameTimeText), "Frame Time: %.1f ms", GetFrameTime() * 1000.0f );
        DrawText(frameTimeText, worldInfoPanel.position.x + 7.0f, worldInfoPanel.position.y + 110.0f, 12, GetColor(0xffffffff) );


        // Object counters ---------------

        rect = { objectCountPanel.position.x - 87.5f, objectCountPanel.position.y - 12.0f, 170.0f, 30.0f };
        objectCountPanel.checkToDrag(mousePosition, rect, isMouseDown, wasMouseDown);

        // Background

        // Panel outline
        rect = { objectCountPanel.position.x - 89.5f, objectCountPanel.position.y - 14.0f, 174.0f, 98.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Panel backing
        rect = { objectCountPanel.position.x - 87.5f, objectCountPanel.position.y - 12.0f, 170.0f, 94.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1b202dff));

        // Title outline
        rect = { objectCountPanel.position.x - 87.5f, objectCountPanel.position.y - 12.0f, 170.0f, 32.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Title backing
        rect = { objectCountPanel.position.x - 87.5f, objectCountPanel.position.y - 12.0f, 170.0f, 30.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1f2432ff));

        // Panel title
        DrawText("Object Count", objectCountPanel.position.x - 52.5f, objectCountPanel.position.y, 12, GetColor(0xffffffff) );

        DrawTextureEx(circleIcon, Vector2({ objectCountPanel.position.x - 75.0f, objectCountPanel.position.y - 3.0f }), 0.0f, 0.026f, GetColor(0xffffffff));

        char totalCirclesText[256];
        snprintf(totalCirclesText, sizeof(totalCirclesText), "Circles: %d / %d", totalCircles, sceneCircleCount);
        DrawText(totalCirclesText, objectCountPanel.position.x - 72.5f, objectCountPanel.position.y + 30.0f, 12, GetColor(0xffffffff) );

        char totalSpringsText[256];
        snprintf(totalSpringsText, sizeof(totalSpringsText), "Springs: %d / %d", totalSprings, sceneSpringCount);
        DrawText(totalSpringsText, objectCountPanel.position.x - 72.5f, objectCountPanel.position.y + 55.0f, 12, GetColor(0xffffffff) );

        // World settings ---------------

        // Check to drag panel
        rect = { worldSettingsPanel.position.x - 106.0f, worldSettingsPanel.position.y - 12.0f, 200.0f, 30.0f };
        worldSettingsPanel.checkToDrag(mousePosition, rect, isMouseDown, wasMouseDown);

        // Background

        // Outline
        rect = { worldSettingsPanel.position.x - 108.0f, worldSettingsPanel.position.y - 14.0f, 204.0f, 361.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Panel Backing
        rect = { worldSettingsPanel.position.x - 106.0f, worldSettingsPanel.position.y - 12.0f, 200.0f, 357.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1b202dff));

        // Title outline
        rect = { worldSettingsPanel.position.x - 108.0f, worldSettingsPanel.position.y - 12.0f, 202.0f, 32.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Title backing
        rect = { worldSettingsPanel.position.x - 106.0f, worldSettingsPanel.position.y - 12.0f, 200.0f, 30.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1f2432ff));

        // Panel title
        DrawText("World Settings", worldSettingsPanel.position.x - 66.0f, worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        DrawTextureEx(settingsIcon, Vector2({ worldSettingsPanel.position.x - 90.0f, worldSettingsPanel.position.y - 3.0f }), 0.0f, 0.026f, GetColor(0xff9a52ff));

        // Inputs

        DrawText("Use Momentum (unstable): ", worldSettingsPanel.position.x - 86.0f, 40.0f + worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        useMomentumInput.position = Vector2( { worldSettingsPanel.position.x - 86.0f, 55.0f + worldSettingsPanel.position.y } );
        useMomentumInput.size = Vector2( { 15.0f, 15.0f } );

        // Check if user has input a new value for the spring constant
        if (useMomentumInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
            useMomentum = useMomentumInput.isTicked;
        }

        useMomentumInput.draw();


        DrawText("Spawned Spring Constant: ", worldSettingsPanel.position.x - 86.0f, 85.0f + worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        defaultSpringConstantInput.position = Vector2( { worldSettingsPanel.position.x - 86.0f, 100.0f + worldSettingsPanel.position.y } );
        defaultSpringConstantInput.size = Vector2( { 60.0f, 18.0f } );

        char defaultSpringConstantValue[16];
        snprintf(defaultSpringConstantValue, sizeof(defaultSpringConstantValue), "%.2f", worldDefaultSpringConstant);

        for (int i = 0; i < 16; i++) {
            defaultSpringConstantInput.defaultValue[i] = defaultSpringConstantValue[i];
        }

        // Check if user has input a new value for the spring constant
        if (defaultSpringConstantInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
            // Convert the value from a char array to an integer
            string str(defaultSpringConstantInput.value);
            worldDefaultSpringConstant = stof(str);
        }

        defaultSpringConstantInput.draw();


        DrawText("World Gravity: ", worldSettingsPanel.position.x - 86.0f, 130.0f + worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        worldGravityInput.position = Vector2( { worldSettingsPanel.position.x - 86.0f, 145.0f + worldSettingsPanel.position.y } );
        worldGravityInput.size = Vector2( { 60.0f, 18.0f } );

        char defaultWorldGravityInput[16];
        snprintf(defaultWorldGravityInput, sizeof(defaultWorldGravityInput), "%.2f", worldGravity);

        for (int i = 0; i < 16; i++) {
            worldGravityInput.defaultValue[i] = defaultWorldGravityInput[i];
        }

        // Check if user has input a new value for the spring constant
        if (worldGravityInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
            // Convert the value from a char array to an integer
            string str(worldGravityInput.value);
            worldGravity = stof(str);

            // Update all objects gravity
            for (int i = 0; i < sceneCircleCount; i++) {
                sceneCircleColliders[i].setGravity(worldGravity);
            }

            updateStartSystemEnergy = true;
        }

        worldGravityInput.draw();


        DrawText("Spawned Object Mass: ", worldSettingsPanel.position.x - 86.0f, 175.0f + worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        spawnedObjectMassInput.position = Vector2( { worldSettingsPanel.position.x - 86.0f, 190.0f + worldSettingsPanel.position.y } );
        spawnedObjectMassInput.size = Vector2( { 60.0f, 18.0f } );

        char defaultObjectMassValue[16];
        snprintf(defaultObjectMassValue, sizeof(defaultObjectMassValue), "%.2f", defaultObjectMass);

        for (int i = 0; i < 16; i++) {
            spawnedObjectMassInput.defaultValue[i] = defaultObjectMassValue[i];
        }

        // Check if user has input a new value for the spring constant
        if (spawnedObjectMassInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
            // Convert the value from a char array to an integer
            string str(spawnedObjectMassInput.value);
            defaultObjectMass = stof(str);
        }

        spawnedObjectMassInput.draw();


        DrawText("Spawned Object Radius: ", worldSettingsPanel.position.x - 86.0f, 220.0f + worldSettingsPanel.position.y, 12, GetColor(0xffffffff) );

        spawnedObjectRadiusInput.position = Vector2( { worldSettingsPanel.position.x - 86.0f, 235.0f + worldSettingsPanel.position.y } );
        spawnedObjectRadiusInput.size = Vector2( { 60.0f, 18.0f } );

        char defaultSpawnedObjectRadiusValue[16];
        snprintf(defaultSpawnedObjectRadiusValue, sizeof(defaultSpawnedObjectRadiusValue), "%.2f", spawnedObjectRadius);

        for (int i = 0; i < 16; i++) {
            spawnedObjectRadiusInput.defaultValue[i] = defaultSpawnedObjectRadiusValue[i];
        }

        // Check if user has input a new value for the spring constant
        if (spawnedObjectRadiusInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
            // Convert the value from a char array to an integer
            string str(spawnedObjectRadiusInput.value);
            spawnedObjectRadius = stof(str);
        }

        spawnedObjectRadiusInput.draw();


        deleteAllObjectButton.position = Vector2({ worldSettingsPanel.position.x - 86.0f, 275.0f + worldSettingsPanel.position.y });

        if (deleteAllObjectButton.isMouseOverButton(mousePosition) && isMouseDown && !wasMouseDown) {
            // Remove all objects and connections

            for (int i = 0; i < sceneCircleCount; i++) {

                if (!sceneCircleColliders[i].isActive) continue;

                sceneCircleColliders[i].isActive = false;
                shouldDrawCircleInformation[i] = false;

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

            updateStartSystemEnergy = true;
        }

        deleteAllObjectButton.draw(mousePosition);


        deleteAllJointsButton.position = Vector2({ worldSettingsPanel.position.x - 86.0f, 310.0f + worldSettingsPanel.position.y });

        if (deleteAllJointsButton.isMouseOverButton(mousePosition) && isMouseDown && !wasMouseDown) {
            // Remove all objects and connections

            for (int i = 0; i < sceneCircleCount; i++) {

                if (!sceneCircleColliders[i].isActive) continue;

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

            updateStartSystemEnergy = true;
        }

        deleteAllJointsButton.draw(mousePosition);


        // Inspector Panel ---------------

        // Check to drag panel
        rect = { inspectorPanel.position.x - 106.0f, inspectorPanel.position.y - 12.0f, 200.0f, 30.0f };
        inspectorPanel.checkToDrag(mousePosition, rect, isMouseDown, wasMouseDown);

        // Background

        // Outline
        rect = { inspectorPanel.position.x - 108.0f, inspectorPanel.position.y - 14.0f, 204.0f, 311.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Panel Backing
        rect = { inspectorPanel.position.x - 106.0f, inspectorPanel.position.y - 12.0f, 200.0f, 307.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1b202dff));

        // Title outline
        rect = { inspectorPanel.position.x - 108.0f, inspectorPanel.position.y - 12.0f, 202.0f, 32.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Title backing
        rect = { inspectorPanel.position.x - 106.0f, inspectorPanel.position.y - 12.0f, 200.0f, 30.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1f2432ff));

        // Panel title
        DrawText("Inspector", inspectorPanel.position.x - 66.0f, inspectorPanel.position.y, 12, GetColor(0xffffffff) );

        DrawTextureEx(inspectIcon, Vector2({ inspectorPanel.position.x - 90.0f, inspectorPanel.position.y - 3.0f }), 0.0f, 0.026f, GetColor(0xff5c5cff));

        // Inputs

        if (lastRightClickedObject != -1) {

            DrawText("Pos X: ", inspectorPanel.position.x - 86.0f, 45.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            positionXInput.position = Vector2( { inspectorPanel.position.x - 86.0f, 57.0f + inspectorPanel.position.y } );
            positionXInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultPosX[16];
            snprintf(defaultPosX, sizeof(defaultPosX), "%.2f", sceneCircleColliders[lastRightClickedObject].position.x);

            for (int i = 0; i < 16; i++) {
                positionXInput.defaultValue[i] = defaultPosX[i];
            }

            // Check if user has input a new value for the spring constant
            if (positionXInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(positionXInput.value);
                sceneCircleColliders[lastRightClickedObject].position.x = stof(str);

                updateStartSystemEnergy = true;
            }

            positionXInput.draw();


            DrawText("Pos Y: ", inspectorPanel.position.x - 86.0f, 90.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            positionYInput.position = Vector2( { inspectorPanel.position.x - 86.0f, 102.0f + inspectorPanel.position.y } );
            positionYInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultPosY[16];
            snprintf(defaultPosY, sizeof(defaultPosY), "%.2f", sceneCircleColliders[lastRightClickedObject].position.y);

            for (int i = 0; i < 16; i++) {
                positionYInput.defaultValue[i] = defaultPosY[i];
            }

            // Check if user has input a new value for the spring constant
            if (positionYInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(positionYInput.value);
                sceneCircleColliders[lastRightClickedObject].position.y = stof(str);

                updateStartSystemEnergy = true;
            }

            positionYInput.draw();


            DrawText("Vel X: ", inspectorPanel.position.x + 10.0f, 45.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            velocityXInput.position = Vector2( { inspectorPanel.position.x + 10.0f, 57.0f + inspectorPanel.position.y } );
            velocityXInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultVelX[16];
            snprintf(defaultVelX, sizeof(defaultVelX), "%.2f", sceneCircleColliders[lastRightClickedObject].velocity.x);

            for (int i = 0; i < 16; i++) {
                velocityXInput.defaultValue[i] = defaultVelX[i];
            }

            // Check if user has input a new value for the spring constant
            if (velocityXInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(velocityXInput.value);
                sceneCircleColliders[lastRightClickedObject].velocityForNextFrame.y = sceneCircleColliders[lastRightClickedObject].velocity.y;
                sceneCircleColliders[lastRightClickedObject].velocityForNextFrame.x = stof(str);

                sceneCircleColliders[lastRightClickedObject].shouldUseVelocityForNextFrame = true;

                updateStartSystemEnergy = true;
            }

            velocityXInput.draw();


            DrawText("Vel Y: ", inspectorPanel.position.x + 10.0f, 90.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            velocityYInput.position = Vector2( { inspectorPanel.position.x + 10.0f, 102.0f + inspectorPanel.position.y } );
            velocityYInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultVelY[16];
            snprintf(defaultVelY, sizeof(defaultVelY), "%.2f", sceneCircleColliders[lastRightClickedObject].velocity.y);

            for (int i = 0; i < 16; i++) {
                velocityYInput.defaultValue[i] = defaultVelY[i];
            }

            // Check if user has input a new value for the spring constant
            if (velocityYInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(velocityYInput.value);
                sceneCircleColliders[lastRightClickedObject].velocityForNextFrame.x = sceneCircleColliders[lastRightClickedObject].velocity.x;
                sceneCircleColliders[lastRightClickedObject].velocityForNextFrame.y = stof(str);

                sceneCircleColliders[lastRightClickedObject].shouldUseVelocityForNextFrame = true;

                updateStartSystemEnergy = true;
            }

            velocityYInput.draw();


            DrawText("Collisions: ", inspectorPanel.position.x - 86.0f, 145.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            hasCollisionsInput.position = Vector2( { inspectorPanel.position.x - 86.0f, 160.0f + inspectorPanel.position.y } );
            hasCollisionsInput.size = Vector2( { 15.0f, 15.0f } );

            hasCollisionsInput.isTicked = sceneCircleColliders[lastRightClickedObject].canCollide;

            // Check if user has input a new value for the spring constant
            if (hasCollisionsInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {
                sceneCircleColliders[lastRightClickedObject].canCollide = hasCollisionsInput.isTicked;
            }

            hasCollisionsInput.draw();

            DrawText("Mass: ", inspectorPanel.position.x - 86.0f, 190.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            inspectorMassInput.position = Vector2( { inspectorPanel.position.x - 86.0f, 202.0f + inspectorPanel.position.y } );
            inspectorMassInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultMassString[16];
            snprintf(defaultMassString, sizeof(defaultMassString), "%.2f", sceneCircleColliders[lastRightClickedObject].getMass());

            for (int i = 0; i < 16; i++) {
                inspectorMassInput.defaultValue[i] = defaultMassString[i];
            }

            // Check if user has input a new value for the spring constant
            if (inspectorMassInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(inspectorMassInput.value);
                sceneCircleColliders[lastRightClickedObject].setMass(stof(str));

                updateStartSystemEnergy = true;
            }

            inspectorMassInput.draw();


            DrawText("Radius: ", inspectorPanel.position.x - 86.0f, 235.0f + inspectorPanel.position.y, 12, GetColor(0xffffffff) );

            inspectorRadiusInput.position = Vector2( { inspectorPanel.position.x - 86.0f, 247.0f + inspectorPanel.position.y } );
            inspectorRadiusInput.size = Vector2( { 60.0f, 18.0f } );

            char defaultRadiusString[16];
            snprintf(defaultRadiusString, sizeof(defaultRadiusString), "%.2f", sceneCircleColliders[lastRightClickedObject].radius);

            for (int i = 0; i < 16; i++) {
                inspectorRadiusInput.defaultValue[i] = defaultRadiusString[i];
            }

            // Check if user has input a new value for the spring constant
            if (inspectorRadiusInput.checkForInput(mousePosition, isMouseDown && !wasMouseDown) && lastRightClickedObject != -1) {
                // Convert the value from a char array to an integer
                string str(inspectorRadiusInput.value);
                sceneCircleColliders[lastRightClickedObject].radius = stof(str);
            }

            inspectorRadiusInput.draw();

        } else {

            DrawText("Please select an object\n to edit its properties", inspectorPanel.position.x - 80.0f, 45.0f + inspectorPanel.position.y, 12, GetColor(0xffffff55) );

        }


        // Save and Load Panel ---------------

        // Check to drag panel
        rect = { savePanel.position.x - 106.0f, savePanel.position.y - 12.0f, 200.0f, 30.0f };
        savePanel.checkToDrag(mousePosition, rect, isMouseDown, wasMouseDown);

        // Background

        // Outline
        rect = { savePanel.position.x - 108.0f, savePanel.position.y - 14.0f, 204.0f, 154.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Panel Backing
        rect = { savePanel.position.x - 106.0f, savePanel.position.y - 12.0f, 200.0f, 150.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1b202dff));

        // Title outline
        rect = { savePanel.position.x - 108.0f, savePanel.position.y - 12.0f, 202.0f, 32.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x0b101dff));

        // Title backing
        rect = { savePanel.position.x - 106.0f, savePanel.position.y - 12.0f, 200.0f, 30.0f };
        DrawRectangleRounded(rect, 0.05f, 10, GetColor(0x1f2432ff));

        // Panel title
        DrawText("Save and Load", savePanel.position.x - 66.0f, savePanel.position.y, 12, GetColor(0xffffffff) );

        DrawTextureEx(saveIcon, Vector2({ savePanel.position.x - 90.0f, savePanel.position.y - 3.0f }), 0.0f, 0.026f, GetColor(0xffffffff));

        // Inputs

        DrawText("File Name: ", savePanel.position.x - 86.0f, 45.0f + savePanel.position.y, 12, GetColor(0xffffffff) );

        fileSaveName.position = Vector2( { savePanel.position.x - 86.0f, 60.0f + savePanel.position.y } );
        fileSaveName.size = Vector2( { 130.0f, 18.0f } );

        for (int i = 0; i < 16; i++) {
            fileSaveName.defaultValue[i] = lastSaveFile[i];
        }

        // Check if user has input a new value for the spring constant
        if (fileSaveName.checkForInput(mousePosition, isMouseDown && !wasMouseDown)) {      
            
            for (int i = 0; i < 16; i++) {
                lastSaveFile[i] = fileSaveName.value[i];
            }

        }

        fileSaveName.draw();


        saveButton.position = Vector2({ savePanel.position.x - 86.0f, 90.0f + savePanel.position.y });

        if (saveButton.isMouseOverButton(mousePosition) && isMouseDown && !wasMouseDown) {
            
            string str(lastSaveFile);

            // Save simulation
            saveFile(str, sceneCircleColliders, sceneCircleCount, sceneSpringJoints, sceneSpringCount, worldBounding, worldGravity, useMomentum);

        }

        saveButton.draw(mousePosition);


        loadButton.position = Vector2({ savePanel.position.x + 0.0f, 90.0f + savePanel.position.y });

        if (loadButton.isMouseOverButton(mousePosition) && isMouseDown && !wasMouseDown) {

            string str(lastSaveFile);

            // Load Simulation
            loadFile(str, sceneCircleColliders, sceneCircleCount, sceneSpringJoints, sceneSpringCount, worldBounding, &worldGravity, &useMomentum);

            useMomentumInput.isTicked = useMomentum;

            updateStartSystemEnergy = true;
        }

        loadButton.draw(mousePosition);



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
