//Class used to generate ground truth data for BeesBook
//CTRL + LCM --> Sets a new tag

#ifndef BeesBookTagMatcher_H
#define BeesBookTagMatcher_H

#include "cv.h"
#include "source/tracking/TrackingAlgorithm.h"
#include "source/tracking/algorithm/BeesBookTagMatcher/resources/myGrid.h"
#include "source/tracking/algorithm/BeesBookTagMatcher/resources/myNewGrid.h"
#include <math.h>
#define _USE_MATH_DEFINES

class BeesBookTagMatcher : public TrackingAlgorithm
{
	private:

		//////////////// TEST FLAGS!!!! ---------------------

		myNewGrid			g;				//active Grid
		myNewGrid			gtemp;			//auxiliar instance for drwaing grids already in vector

		std::vector<myNewGrid> _Grids;		//vector of set grids

		//------ NEW FLAGS
		bool _ready;						//Ready for a new tag --Ctrl + LCM--
		bool _setTag;						//a new set of points is being configured

		bool _activeTag;					//a new Tag has been set and can now be modified

		bool _setP0;						//Set P0 --Left Click and drag--
		bool _setP1;						//Set P1 --Left Click and drag--
		bool _setP2;						//Set P2 --Left Click and drag--

		//------- Test
		bool _setOrient;					//to modify exclusively the tag orientation.

		std::vector<cv::Point> orient;		//auxiliar variable for drawing the orientation while setting the Tag
		cv::Point diff;						//auxiliar variable
		cv::Point prevPosition;				//auxiliar variable



		// FUNCTIONS
		void drawSetTags(cv::Mat image);										//function that draws the Tags set so far calling instances of MyNewGrid.
		void drawOrientation(cv::Mat image, std::vector<cv::Point> orient);		//function that draws the orientation vector while being set.
		void drawActiveTag(cv::Mat image);										//function that draws an active tag calling an instance of MyNewGrid
		////
		void drawSettingTheta(cv::Mat &img);									//function that draws the tag while being rotated in space

		void setTag(cv::Point location);										//function called while setting the tag (it initializes orient vector)
		void setTheta(cv::Point location);										//function that allows P1 and P2 to be modified to calculate the tag's angle in space.

		void cancelTag(cv::Point2f location);									//function that cancels the active tag and activates the previous one.

		bool selectPoint(cv::Point location);									//function that checks if one of the set Points is selected, returns true when one of the points is selected
		void selectTag(cv::Point location);										//function that checks if one of the already set Tags is selected.
		//auxiliar function
		double dist(cv::Point p1, cv::Point p2);								//function that calculates the distance between two points

	public:

		//----- Color Settings
		static cv::Scalar COLOR_BLUE;
		static	cv::Scalar COLOR_RED;
		static	cv::Scalar COLOR_GREEN;
		static	cv::Scalar COLOR_YELLOW;

        BeesBookTagMatcher	( Settings &settings, std::string &serializationPathName, QWidget *parent );
		~BeesBookTagMatcher	( void );


		void track			( ulong frameNumber, cv::Mat & frame );
		void paint			( cv::Mat& image );
		void reset			( );


	public slots:
		//mouse click and move events
		void mouseMoveEvent		( QMouseEvent * e );
		void mousePressEvent	( QMouseEvent * e );
		void mouseReleaseEvent	( QMouseEvent * e );
		void mouseWheelEvent	( QWheelEvent * e );

};

#endif
