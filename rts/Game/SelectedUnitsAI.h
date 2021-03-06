/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef SELECTED_UNITS_AI_H
#define SELECTED_UNITS_AI_H

#include "Sim/Units/CommandAI/Command.h"
#include "System/float3.h"

#include <vector>

class CUnit;


/// Handling commands given to the currently  selected group of units.
class CSelectedUnitsHandlerAI {
public:
	/* set<int> selUnits;

	void AddUnit(int unit); (And include update() in game.cpp to call every frame)
	void RemoveUnit(int unit);
	*/

	void GiveCommandNet(Command& c, int player);

private:
	void CalculateGroupData(int player, bool queueing);
	void MakeFormationFrontOrder(Command* c, int player);
	void CreateUnitOrder(std::vector< std::pair<float, int> >& out, int player);
	float3 MoveToPos(float3 nextCornerPos, float3 dir, const CUnit* unit, Command* command, std::vector<std::pair<int, Command> >* frontcmds, bool* newline);
	void AddUnitSetMaxSpeedCommandNet(CUnit* unit, unsigned char options);
	void AddGroupSetMaxSpeedCommandNet(CUnit* unit, unsigned char options);
	void SelectAttackNet(const Command& cmd, int player);
	void SelectCircleUnits(const float3& pos, float radius, int player, std::vector<int>& units);
	void SelectRectangleUnits(const float3& pos0, const float3& pos1, int player, std::vector<int>& units);
	float3 LastQueuePosition(const CUnit* unit);

private:
	float3 groupCenterCoor;
	float3 formationCenterPos;
	float3 formationRightPos;

	float groupSumLength = 0.0f;
	float groupAvgLength = 0.0f;
	float groupFrontLength = 0.0f;
	float groupAddedSpace = 0.0f;
	float groupMinMaxSpeed = 0.0f;
	float groupColumnDist = 64.0f;

	int formationNumColumns = 0;


	std::vector< std::pair<float, int> > sortedUnitPairs; // <priority, unitID>
	std::vector< std::pair<float, std::vector<int>> > sortedUnitGroups;
	std::vector< std::pair<int, Command> > frontMoveCommands;

	std::vector<size_t> mixedUnitIDs;
	std::vector<size_t> mixedGroupSizes;


	std::vector<int> targetUnitIDs;
};

extern CSelectedUnitsHandlerAI selectedUnitsAI;

#endif // SELECTED_UNITS_AI_H
