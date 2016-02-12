/*
 *  arc.cpp
 *  TronDemo
 *
 *  Created by Kris Meeusen on 06/05/11.
 *  Copyright 2011 Lab101. All rights reserved.
 *
 */

#include "arc.h"


void arc::createMesh()
{
	float x,y;
	float angle;
	// Use smaller steps on big circles
	float angleSteps = 10 / innerRadius ;
	
	//mesh.setMode(ofPrimitive)
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	meshOutline.setMode(OF_PRIMITIVE_LINE_LOOP);

	//mesh.setMode(OF_TRIANGLE_STRIP_MODE);
	//meshOutline.setMode(OF_LINE_LOOP_MODE);

	int index = 0;
	float colorBlue = colorBlueStartFactor;
	float colorBlueSteps = (colorBlueEndFactor - colorBlueStartFactor) / ((endAngle-startAngle)/angleSteps);

	vector<ofVec3f> innerCircleMeshOutline;

	for (float angle = startAngle; angle <= endAngle; angle+=angleSteps){
		colorBlue += colorBlueSteps;
		
		x = outerRadius * cos(angle);
		y = outerRadius * sin(angle); 
		
		// inner circle fill
		mesh.addVertex(ofVec3f(x,y,0));
		// adding the points for the border upper part
		meshOutline.addVertex(ofVec3f(x,y,0));

		//mesh.addColor(ofColor(0,colorBlue ,colorBlue- colorGreenCorrection));
		mesh.addColor(ofFloatColor(0,colorBlue,colorBlue- colorGreenCorrection));
		x = innerRadius * cos(angle);
		y = innerRadius * sin(angle); 

		mesh.addVertex(ofVec3f(x,y,0));
		// adding the inner circle points to a vector because they need to be in reverse order.
		innerCircleMeshOutline.push_back(ofVec3f(x,y,0));
				
		mesh.addColor(ofFloatColor(0,colorBlue ,colorBlue- colorGreenCorrection));

	}
	
	std::reverse(innerCircleMeshOutline.begin(), innerCircleMeshOutline.end());	
	meshOutline.addVertices(innerCircleMeshOutline);
		
}


void arc::draw(float rotation)
{
	glPushMatrix();

	ofRotateZ(rotation * ((clockwise) ? 1 : -1));

	ofSetLineWidth(1);
	ofSetColor(0, 60, 60);
	meshOutline.drawFaces();	
	
	ofSetLineWidth(0);
	mesh.drawFaces();

	glPopMatrix();
}