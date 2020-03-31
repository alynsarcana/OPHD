#pragma once

#include "NAS2D/State.h"
#include "NAS2D/EventHandler.h"
#include "NAS2D/Timer.h"
#include "NAS2D/Renderer/Point.h"
#include "NAS2D/Resources/Image.h"


#include "../Constants.h"


using namespace NAS2D;


class SplashState : public NAS2D::State
{
public:
	SplashState();
	virtual ~SplashState();

protected:

	void initialize();
	NAS2D::State* update();

private:
	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);
	void onMouseDown(NAS2D::EventHandler::MouseButton button, int x, int y);

	void skipSplash();

private:
	NAS2D::Image				mLogoLairworks;
	NAS2D::Image				mLogoNas2d;
	NAS2D::Image				mLogoOutpostHd;
	NAS2D::Image				mFlare;
	NAS2D::Image				mByline;

	NAS2D::Point_2d			mMousePosition;

	NAS2D::Timer				mTimer;

	NAS2D::State*				mReturnState = this;
};
