#include "CrimeRateUpdate.h"
#include "../UI/PopulationPanel.h"
#include "../Things/Structures/Structure.h"
#include "../StructureManager.h"
#include <NAS2D/Utility.h>
#include <random>
#include <functional>


namespace {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int> distribution(0, 1000);
	auto random = std::bind(distribution, std::ref(generator));
}


CrimeRateUpdate::CrimeRateUpdate(PopulationPanel& populationPanel) : mPopulationPanel(populationPanel) { }


void CrimeRateUpdate::update(const std::vector<TileList>& policeOverlays)
{
	mStructuresCommittingCrimes.clear();
	mMoraleChange = 0;

	const auto& structuresWithCrime = NAS2D::Utility<StructureManager>::get().structuresWithCrime();

	// Colony will not have a crime rate until at least one structure that supports crime is built
	if (structuresWithCrime.empty()) {
		setPopulationPanel(0, 0);
		return;
	}

	double accumulatedCrime = 0;

	for (auto structure : structuresWithCrime)
	{
		int crimeRateChange = isProtectedByPolice(policeOverlays, structure) ? -1 : 1;
		structure->increaseCrimeRate(crimeRateChange);

		// Crime Rate of 0% means no crime
		// Crime Rate of 100% means crime occurs 10% of the time
		if (structure->crimeRate() + random() > 1000)
		{
			mStructuresCommittingCrimes.push_back(structure);
		}

		accumulatedCrime += structure->crimeRate();
	}

	int meanCrimeRate = static_cast<int>(accumulatedCrime / structuresWithCrime.size());
	mMoraleChange = calculateMoraleChange(meanCrimeRate);

	setPopulationPanel(mMoraleChange, meanCrimeRate);
}


bool CrimeRateUpdate::isProtectedByPolice(const std::vector<TileList>& policeOverlays, Structure* structure)
{
	const auto& structureTile = NAS2D::Utility<StructureManager>::get().tileFromStructure(structure);

	for (const auto& tile : policeOverlays[structureTile.depth()])
	{
		if (tile->position() == structureTile.position())
		{
			return true;
		}
	}

	return false;
}


int CrimeRateUpdate::calculateMoraleChange(int meanCrimeRate)
{
	if (meanCrimeRate > 50)
	{
		// Reduce morale by 1 for every 10% above 50%
		return -1 * (meanCrimeRate / 10 - 4);
	}
	else if (meanCrimeRate < 10)
	{
		return 1;
	}

	return 0;
}


void CrimeRateUpdate::setPopulationPanel(int moraleChange, int meanCrimeRate)
{
	mPopulationPanel.crimeRate(meanCrimeRate);

	if (moraleChange > 0)
	{
		mPopulationPanel.addMoraleReason("Low Crime Rate", moraleChange);
	}
	else if (moraleChange < 0)
	{
		mPopulationPanel.addMoraleReason("High Crime Rate", moraleChange);
	}
}
