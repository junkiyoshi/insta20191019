#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();

	for (int i = 0; i < this->base_mesh.getVertices().size(); i++) {

		this->base_mesh.addColor(ofColor(0));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh = this->base_mesh;
	this->wireframe_mesh = this->base_mesh;

	for (int i = 0; i < this->base_mesh.getVertices().size(); i++) {

		auto vertex = this->base_mesh.getVertices()[i];
		int noise_value = (int)ofMap(ofNoise(vertex.x * 0.005, vertex.y * 0.005, vertex.z * 0.005, ofGetFrameNum() * 0.005), 0, 1, 5, 9);

		auto vertex_1 = glm::normalize(vertex) * ofMap(noise_value, 5, 9, 200, 350);
		auto vertex_2 = glm::normalize(vertex) * ofMap(noise_value, 5, 9, 201, 351);

		this->mesh.setVertex(i, vertex_1);
		this->mesh.setColor(i, ofColor(39));

		this->wireframe_mesh.setVertex(i, vertex_2);
		this->wireframe_mesh.setColor(i, ofColor(239));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.25);

	this->mesh.draw();
	this->wireframe_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}