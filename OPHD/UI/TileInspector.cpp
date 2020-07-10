// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TileInspector.h"

#include "TextRender.h"
#include "../Constants.h"

#include <map>
#include <sstream>

using namespace NAS2D;


TileInspector::TileInspector() :
	btnClose{"Close"}
{
	text(constants::WINDOW_TILE_INSPECTOR);
	init();
}


TileInspector::~TileInspector()
{
}


void TileInspector::init()
{
	size({200, 88});

	add(&btnClose, 145, 63);
	btnClose.size({50, 20});
	btnClose.click().connect(this, &TileInspector::btnCloseClicked);
}


void TileInspector::update()
{
	if(!visible())
		return;

	if(!mTile)
		return;

	Window::update();

	const auto* mine = mTile->mine();

	auto position = mRect.startPoint() + NAS2D::Vector{5, 25};
	drawLabelAndValue(position, "Has Mine: ", (mine ? "Yes" : "No"));

	if(mine)
	{
		position.y += 10;
		drawLabelAndValue(position, "Active: ", (mine->active() ? "Yes" : "No"));

		position.y += 10;
		drawLabelAndValue(position, "Production Rate: ", MINE_YIELD_TRANSLATION[mTile->mine()->productionRate()]);
	}

	position = mRect.startPoint() + NAS2D::Vector{5, 62};
	const auto tilePosition = mTile->position();
	drawLabelAndValue(position, "Location: ", std::to_string(tilePosition.x) + ", " + std::to_string(tilePosition.y));

	position.y += 10;
	drawLabelAndValue(position, "Terrain: ", TILE_INDEX_TRANSLATION[mTile->index()]);
}


void TileInspector::btnCloseClicked()
{
	visible(false);
}

