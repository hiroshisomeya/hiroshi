
#pragma once

#include "ofMain.h"
#include "ftUtil.h"
#include "ftSwapFbo.h"
#include "ftAddMultipliedShader.h"
#include "ftDisplayScalarShader.h"
//#include "ftVelocityField.h"

namespace flowTools {
	
	class ftFlow {
	public:
		ftFlow() {
			ofAddListener(ofEvents().update, this, &ftFlow::internalUpdate);
		}

		virtual ~ftFlow() {;}

		void internalUpdate(ofEventArgs &_args) {
			;
		}

		void allocate(int _width, int _height, int _internalFormat) {
			width = _width;
			height = _height;
			internalFormat = _internalFormat;
//			numChannels = ofGetNumChannelsFromGLFormat(internalFormat);
			inputFbo.allocate(width, height, internalFormat);
			outputFbo.allocate(width, height, internalFormat);
			numChannels = ftUtil::getNumChannelsFromInternalFormat(internalFormat);
			isFloat = ftUtil::isFloat(internalFormat);
			bInputSet = false;
		}
		
		void reset() { resetInput(); resetOutput(); }
		void resetInput() { ftUtil::zero(inputFbo); bInputSet = false; }
		void resetOutput() { ftUtil::zero(outputFbo); }

		void setInput(ofTexture &_inputTex) {
			ftUtil::zero(inputFbo);
			ftUtil::stretch(inputFbo, _inputTex);
			bInputSet = true;
		}

		void addInput(ofTexture &_inputTex, float _strength = 1.0) {
			inputFbo.swap();
			AddMultipliedShader.update(inputFbo, inputFbo.getBackTexture(), _inputTex, 1.0, _strength);
			bInputSet = true;
		}
		
		void setOutput(ofTexture &_inputTex) {
			ftUtil::zero(outputFbo);
			ftUtil::stretch(outputFbo, _inputTex);
			bInputSet = true;
		}
		
		void addOutput(ofTexture &_inputTex, float _strength = 1.0) {
			outputFbo.swap();
			AddMultipliedShader.update(outputFbo, outputFbo.getBackTexture(), _inputTex, 1.0, _strength);
			bInputSet = true;
		}

		ofTexture&	getOutput()		{ return outputFbo.getTexture(); }
		bool		getInputSet() 	{ return bInputSet; }
		
		ofTexture&	getInput()		{ return inputFbo.getTexture(); }

		ofParameterGroup&	getParameters() 	{ return parameters; }
		
		void draw(int _x, int _y, int _w, int _h, ofBlendMode _blendMode = OF_BLENDMODE_ALPHA) {
			drawScalar(_x, _y, _w, _h, _blendMode);
		}
		void drawScalar(int _x, int _y, int _w, int _h, ofBlendMode _blendMode = OF_BLENDMODE_ALPHA) {
			ofPushStyle();
			ofEnableBlendMode(_blendMode);
			if (ftUtil::isFloat(internalFormat)) {
				displayScalar.update(outputFbo.getTexture(), _w, _h, 1.0);
			} else {
				outputFbo.draw(_x, _y, _w, _h);
			}
			ofPopStyle();
		}
		void drawField(int _x, int _y, int _w, int _h, ofBlendMode _blendMode = OF_BLENDMODE_ALPHA){
			
		}
		
	protected:
		ofParameterGroup	parameters;
		int			width;
		int			height;
		int 		internalFormat;
		int			numChannels;
		bool		isFloat;
		
		ftSwapFbo 	inputFbo;
		bool		bInputSet;
		
		ftSwapFbo	outputFbo;
		ftAddMultipliedShader	AddMultipliedShader;
		
		
		ftDisplayScalarShader		displayScalar;
//		ftVelocityField		displayField;
	};
	
}

