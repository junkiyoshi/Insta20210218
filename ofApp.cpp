#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetColor(255);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);


	this->number_of_targets = 400;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->target_list.push_back(glm::vec2());
		this->color_list.push_back(glm::vec3(ofRandom(0.2, 0.8), ofRandom(0.2, 0.8), ofRandom(0.2, 0.8)));
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < this->number_of_targets; i++) {

		this->target_list[i] = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0002), 0, 1, -100, 820), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0002), 0, 1, -100, 820));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->target_list[0].x, this->number_of_targets);
	this->shader.setUniform3fv("colors", &this->color_list[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();

	ofSetColor(239);
	string word = "PCD 2021";
	this->font.drawStringAsShapes(word, 360 + this->font.stringWidth(word) * -0.5, 360 + this->font.stringHeight(word) * 0.5);

}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}