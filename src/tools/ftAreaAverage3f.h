
#pragma once

#include "ofMain.h"
#include "ftFbo.h"
#include "ftAreaAverage.h"

namespace flowTools {
	
	class ftAreaAverage3f : public ftAreaAverage {
	public:
		ftAreaAverage3f(){ ; }
		virtual	~ftAreaAverage3f() { ; }
		
		void		setup(int _width, int _height, string _name = "") ;
		void		setSize(int _width, int _height) ;
		void		update();
		
		ofVec3f		getDirection()			{ return direction; }
		ofVec3f		getTotalVelocity()		{ return totalVelocity; }
		vector<ofVec3f>& getVelocities()	{ return velocities; }
		
	private:
		ofVec3f					direction;
		ofVec3f					totalVelocity;
		ofParameter<ofVec3f>	pDirection;
		vector<ofVec3f>			velocities;
		
		void pRoiXListener(float& _value)		{ ftAreaAverage::pRoiXListener(_value); }
		void pRoiYListener(float& _value)		{ ftAreaAverage::pRoiXListener(_value); }
		void pScaleFactorListener(float& _value){ ftAreaAverage::pScaleFactorListener(_value); }
	};
}