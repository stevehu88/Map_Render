/*
 * Edge.h
 *
 *  Created on: Sep 2, 2015
 *      Author: Steve Hu
 */

#ifndef EDGE_H_
#define EDGE_H_
#include <vector>
#include "Node.h"

class Edge {
public:
	Edge();
	Edge(const std::vector<Node>& node,const int& speedLevel);
	virtual ~Edge();
	bool appendNode(const Node &node);

	const std::vector<Node>& getNodes() const {
		return nodes;
	}

	int getSpeedLevel() const {
		return speedLevel;
	}

	void setSpeedLevel(int speedLevel) {
		this->speedLevel = speedLevel;
	}

private:
	std::vector<Node> nodes;
	int speedLevel;
};

#endif /* EDGE_H_ */
