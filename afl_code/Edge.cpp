/*
 * Edge.cpp
 *
 *  Created on: Sep 2, 2015
 *      Author: Steve Hu
 */

#include "Edge.h"

Edge::Edge() {
	speedLevel = -1;
}

Edge::Edge(const std::vector<Node>& nodes, const int& speedLevel)
{
	this->nodes = nodes;
	this->speedLevel = speedLevel;
}

Edge::~Edge() {
}

bool Edge::appendNode(const Node& node)
{
	this->nodes.push_back(node);
	return true;
}

