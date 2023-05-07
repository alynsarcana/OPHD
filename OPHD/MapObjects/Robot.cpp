#include "Robot.h"

Robot::Robot(const std::string& name, const std::string& spritePath, Type t) :
	MapObject(name, spritePath, "running"),
	mType{t}
{}


Robot::Robot(const std::string& name, const std::string& spritePath, const std::string& initialAction, Type t) :
	MapObject(name, spritePath, initialAction),
	mType{t}
{}


void Robot::startTask(int turns)
{
	if (turns < 1) { throw std::runtime_error("Robot::startTask() called with a value less than 1."); }
	mTurnsToCompleteTask = turns;
}


NAS2D::Dictionary Robot::getDataDict() const
{
	return {{
		{"type", static_cast<int>(mType)},
		{"age", mFuelCellAge},
		{"production", mTurnsToCompleteTask},
	}};
}


void Robot::updateTask()
{
	if (mSelfDestruct)
	{
		die();
	}

	if (mCancelTask)
	{
		mTurnsToCompleteTask = 0;
		return;
	}

	mTurnsToCompleteTask--;

	if (mTurnsToCompleteTask == 0)
	{
		mTaskCompleteSignal(this);
	}

	mFuelCellAge++;

	if (mFuelCellAge == 200)
	{
		die();
	}
}
