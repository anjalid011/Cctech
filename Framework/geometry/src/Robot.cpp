#include "Robot.h"
#include "Geometry.h"
#include "Shape.h"
#include "Plotter.h"
#include "Transformations.h"
#include <vector>

Robot::Robot() {
    // this->torsoHeight = torsoHeight;
    // this->torsoRadius = torsoRadius;
}

void Robot::buildAndPlot() {
    // Define torso dimensions
    double torsoHeight = 40, torsoRadius = 15;

    // Define dimensions for other parts relative to the torso
    double headRadius = torsoRadius * 0.6;
    double hatBaseRadius = headRadius * 0.8, hatHeight = headRadius * 0.5;
    double neckRadius = torsoRadius * 0.3, neckHeight = torsoHeight * 0.1;
    double armRadius = torsoRadius * 0.2, armLength = torsoHeight * 0.7;
    double legRadius = torsoRadius * 0.3, legLength = torsoHeight * 0.8;

    // Define positions for each part
    double torsoCenterX = 0, torsoCenterY = 0, torsoCenterZ = 0; // Torso at origin
    double headCenterZ = torsoCenterZ + torsoHeight / 2 + neckHeight + headRadius;
    double hatCenterZ = headCenterZ + headRadius + hatHeight / 2;
    double neckCenterZ = torsoCenterZ + torsoHeight / 2 + neckHeight / 2;
    double leftArmCenterX = torsoCenterX - torsoRadius - armRadius;
    double rightArmCenterX = torsoCenterX + torsoRadius + armRadius;
    double armCenterZ = torsoCenterZ + torsoHeight / 2;
    double leftLegCenterX = torsoCenterX - torsoRadius / 2;
    double rightLegCenterX = torsoCenterX + torsoRadius / 2;
    double legCenterZ = torsoCenterZ - torsoHeight / 2 - legLength / 2;

    // Create robot parts
    Sphere head(headRadius);
    Cone hat(hatBaseRadius, hatHeight);
    Cylinder neck(neckRadius, neckHeight);
    Cylinder torso(torsoRadius, torsoHeight);
    Cylinder leftArm(armRadius, armLength);
    Cylinder rightArm(armRadius, armLength);
    Cylinder leftLeg(legRadius, legLength);
    Cylinder rightLeg(legRadius, legLength);

    // Create a Transformations object
    Transformations t;

    // Apply transformations to position the parts
    // t.applyTranslation(head, torsoCenterX, torsoCenterY, headCenterZ);
    // t.applyTranslation(hat, torsoCenterX, torsoCenterY, hatCenterZ);
    // t.applyTranslation(neck, torsoCenterX, torsoCenterY, neckCenterZ);
    // t.applyTranslation(torso, torsoCenterX, torsoCenterY, torsoCenterZ);
    // t.applyTranslation(leftArm, leftArmCenterX, torsoCenterY, armCenterZ);
    // t.applyTranslation(rightArm, rightArmCenterX, torsoCenterY, armCenterZ);
    // t.applyTranslation(leftLeg, leftLegCenterX, torsoCenterY, legCenterZ);
    // t.applyTranslation(rightLeg, rightLegCenterX, torsoCenterY, legCenterZ);

    // Draw all parts
    head.draw();
    hat.draw();
    neck.draw();
    torso.draw();
    leftArm.draw();
    rightArm.draw();
    leftLeg.draw();
    rightLeg.draw();

    // Apply transformations and plot
    // t.performTransformation();

    Plotter::plot3D(".././geometry/scripts/shape.dat", "Robot");
}