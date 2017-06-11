#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	camWidth = 1920;  // try to grab at this size.
	camHeight = 1080;

	//we can now get back a list of devices.
	vector<ofVideoDevice> devices = cam1.listDevices();

	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else {
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}

	cam1.setDeviceID(0);
	cam1.setDesiredFrameRate(60);
	cam1.initGrabber(camWidth, camHeight);
	

	cam2.setDeviceID(1);
	cam2.setDesiredFrameRate(60);
	cam2.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){

	cam1.update();

	cam2.update();

	//if (cam1.isFrameNew()) {
	//	ofPixels & pixels = vidGrabber.getPixels();
	//	for (int i = 0; i < pixels.size(); i++) {
	//		videoInverted[i] = 255 - pixels[i];
	//	}
	//	videoTexture.loadData(videoInverted);
	//}

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(100, 100, 100);
	cam2.draw(20, 20, 320, 240);
	cam1.draw(340, 20, 320, 240);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	ofHideCursor();
	ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	maskGenerator.drag_nearest_corner(ofVec2f(x, y));
	ofImage tmpImage;
	tmpImage.setFromPixels(maskGenerator.getMaskPixels(), camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
	//imageProcessing.setMaskImage(tmpImage);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::updateHomography()
{
	vector<cv::Point2f> srcPoints, dstPoints;
	ofVec2f* maskPoints = maskGenerator.getHomographyPoints();
	srcPoints.push_back(cv::Point2f(maskPoints[0].x, maskPoints[0].y));
	srcPoints.push_back(cv::Point2f(maskPoints[1].x, maskPoints[1].y));
	srcPoints.push_back(cv::Point2f(maskPoints[2].x, maskPoints[2].y));
	srcPoints.push_back(cv::Point2f(maskPoints[3].x, maskPoints[3].y));

	dstPoints.push_back(cv::Point2f(0, 0));
	dstPoints.push_back(cv::Point2f(1, 0));
	dstPoints.push_back(cv::Point2f(1, 1));
	dstPoints.push_back(cv::Point2f(0, 1));
	homography.calcHomography(srcPoints, dstPoints);
}