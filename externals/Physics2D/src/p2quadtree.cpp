#include "../include/p2quadtree.h"

p2QuadTree::p2QuadTree(p2AABB bounds): m_Bounds(bounds)
{
}

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds): m_NodeLevel(nodeLevel), m_Bounds(bounds)
{
}

p2QuadTree::~p2QuadTree()
{
	Clear();
}

void p2QuadTree::Clear()
{
	m_Objects.clear();

	for (int i = 0; i < CHILD_TREE_NMB; i++) {
		if (nodes[i] != nullptr) {
			nodes[i]->Clear();
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}

void p2QuadTree::Split()
{
	p2Vec2 center = m_Bounds.GetCenter();
	int newNodeLevel = m_NodeLevel + 1;

	/*
	| 1 | 0 |
	| 2 | 3 |
	*/
	nodes[0] = new p2QuadTree(newNodeLevel, { center, m_Bounds.topRight });
	nodes[1] = new p2QuadTree(newNodeLevel, { p2Vec2(m_Bounds.bottomLeft.x, center.y), p2Vec2(center.x, m_Bounds.topRight.y) });
	nodes[2] = new p2QuadTree(newNodeLevel, { m_Bounds.bottomLeft, center });
	nodes[3] = new p2QuadTree(newNodeLevel, { p2Vec2(center.x, m_Bounds.bottomLeft.y), p2Vec2(m_Bounds.topRight.x, center.y)});
}

int p2QuadTree::GetIndex(p2Body * rect)
{
	int index = -1;
	float xMidPoint = m_Bounds.GetCenter().x;
	float yMidPoint = m_Bounds.GetCenter().y;

	p2AABB rectAabb;
	rect->GetFatAABB(&rectAabb);

	bool isInTopNodes = rectAabb.bottomLeft.y > yMidPoint;
	bool isInBottomNodes = rectAabb.bottomLeft.y < yMidPoint;

	// Object totally fits in right nodes
	if (rectAabb.topRight.x > xMidPoint) {
		if (isInTopNodes) {
			index = 0;
		}
		if (isInBottomNodes) {
			index = 3;
		}
	}

	// Object totally fits in left nodes
	if (rectAabb.topRight.x < xMidPoint) {
		if (isInTopNodes) {
			index = 1;
		}
		if (isInBottomNodes) {
			index = 2;
		}
	}

	return index;
}

void p2QuadTree::Insert(p2Body * obj)
{
	if (nodes[0] != nullptr) {
		int objIndex = GetIndex(obj);
		if (objIndex != 1) {
			nodes[objIndex]->Insert(obj);
			return;
		}
	}

	m_Objects.push_back(obj);

	if (m_Objects.size() > MAX_OBJECTS && m_NodeLevel < MAX_LEVELS) {
		Split();

		auto objItr = m_Objects.begin();
		while (objItr != m_Objects.end()) {
			int objIndex = GetIndex(*objItr);
			if (objIndex != 1) {
				nodes[objIndex]->Insert(*objItr);
				objItr = m_Objects.erase(objItr);
			}
			else {
				objItr++;
			}
		}
	}
}

std::list<p2Body*> p2QuadTree::GetChildObjects()
{
	std::list<p2Body*> allObjects = m_Objects;

	for (int i = 0; i < CHILD_TREE_NMB; i++) {
		if (nodes[i] != nullptr) {
			allObjects.merge(nodes[i]->GetChildObjects());
		}
	}

	return allObjects;
}

void p2QuadTree::Retrieve(std::list<std::pair<p2Body*, p2Body*>>* aabbContacts)
{
	auto objItr = m_Objects.begin();

	while (objItr != m_Objects.end()) {
		auto objItr2 = m_Objects.begin();
		std::list<p2Body*> possibleContacts = m_Objects;
		possibleContacts.erase(objItr);
		int objIndex = GetIndex((*objItr));

		if (objIndex != -1) {
			possibleContacts.merge(nodes[objIndex]->GetChildObjects());
		}
		else {
			for (int i = 0; i < CHILD_TREE_NMB; i++) {
				if (nodes[i] != nullptr) {
					possibleContacts.merge(nodes[i]->GetChildObjects());
				}
			}
		}

		auto contactItr = possibleContacts.begin();
		while (contactItr != possibleContacts.end()) {
			p2AABB obj1;
			p2AABB obj2;
			(*objItr)->GetFatAABB(&obj1);
			(*contactItr)->GetFatAABB(&obj2);

			if (obj1.Contains(obj2)) {
				aabbContacts->push_back(std::make_pair((*objItr), (*contactItr)));
			}

			contactItr = possibleContacts.erase(contactItr);
		}

		objItr = m_Objects.erase(objItr);
	}
}
