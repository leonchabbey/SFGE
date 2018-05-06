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

	bool isInTopNodes = rectAabb.topRight.y < yMidPoint && rectAabb.bottomLeft.y < yMidPoint;
	bool isInBottomNodes = rectAabb.topRight.y > yMidPoint && rectAabb.bottomLeft.y > yMidPoint;
	bool isInLeftNodes = rectAabb.topRight.x < xMidPoint && rectAabb.bottomLeft.x < xMidPoint;
	bool isInRightNodes = rectAabb.topRight.x > xMidPoint && rectAabb.bottomLeft.x > xMidPoint;

	// Object totally fits in right nodes
	if (isInRightNodes) {
		if (isInTopNodes) {
			index = 0;
		}
		if (isInBottomNodes) {
			index = 3;
		}
	}

	// Object totally fits in left nodes
	if (isInLeftNodes) {
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
		if (objIndex != -1) {
			nodes[objIndex]->Insert(obj);
			return;
		}
	}

	m_Objects.push_back(obj);

	if (m_Objects.size() > MAX_OBJECTS && m_NodeLevel < MAX_LEVELS) {
		if (nodes[0] == nullptr) {
			Split();
		}

		auto objItr = m_Objects.begin();
		while (objItr != m_Objects.end()) {
			int objIndex = GetIndex(*objItr);
			if (objIndex != -1) {
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
	std::list<p2Body*> allObjects(m_Objects);

	for (int i = 0; i < CHILD_TREE_NMB; i++) {
		if (nodes[i] != nullptr) {
			MergeChildBodies(i, allObjects);
		}
	}

	return allObjects;
}

void p2QuadTree::Retrieve(std::list<std::pair<p2Body*, p2Body*>>* aabbContacts)
{
	for (auto objItr = m_Objects.begin(); objItr != m_Objects.end();) {
		std::list<p2Body*> possibleContacts(m_Objects);
		int objIndex = GetIndex((*objItr));

		/*
		if (objIndex != -1) {
			if (nodes[objIndex] != nullptr) {
				MergeChildBodies(objIndex, possibleContacts);
			}
		}
		*/
		if (objIndex == -1) {
			for (int i = 0; i < CHILD_TREE_NMB; i++) {
				if (nodes[i] != nullptr) {
					MergeChildBodies(i, possibleContacts);
				}
			}
		}

		for (auto contactItr = possibleContacts.begin(); contactItr != possibleContacts.end(); ++contactItr) {
			if (*objItr == *contactItr) {
				continue;
			}
				
			p2AABB obj1;
			p2AABB obj2;
			(*objItr)->GetFatAABB(&obj1);
			(*contactItr)->GetFatAABB(&obj2);

			std::cout << "AABB test:" << "\n";
			obj1.bottomLeft.Show();
			obj1.topRight.Show();
			obj2.bottomLeft.Show();
			obj2.topRight.Show();
			obj1.GetCenter().Show();

			if (obj1.Contains(obj2)) {
				aabbContacts->push_back(std::make_pair((*objItr), (*contactItr)));
			}
		}

		objItr = m_Objects.erase(objItr);
	}

	for (int i = 0; i < CHILD_TREE_NMB; i++) {
		if (nodes[i] != nullptr) {
			nodes[i]->Retrieve(aabbContacts);
		}
	}
}

void p2QuadTree::MergeChildBodies(int index, std::list<p2Body*>& mainContacts)
{
	std::list<p2Body*> childPossibleContacts = nodes[index]->GetChildObjects();
	mainContacts.insert(mainContacts.end(), childPossibleContacts.begin(), childPossibleContacts.end());
}

const float TestpixelPerMeter = 100.0f;

float pixel2meter(float pixel)
{
	return pixel / TestpixelPerMeter;
}

float pixel2meter(int pixel)
{
	return pixel / TestpixelPerMeter;
}

p2Vec2 pixel2meter(sf::Vector2f pixel)
{
	return p2Vec2(pixel2meter(pixel.x), pixel2meter(pixel.y));
}

p2Vec2 pixel2meter(sf::Vector2i pixel)
{
	return p2Vec2(pixel2meter(pixel.x), pixel2meter(pixel.y));
}

float meter2pixel(float meter)
{
	return meter * TestpixelPerMeter;
}

sf::Vector2f meter2pixel(p2Vec2 meter)
{
	return sf::Vector2f(meter2pixel(meter.x), meter2pixel(meter.y));
}

void p2QuadTree::Update()
{
	position = m_Bounds.GetCenter();
	extents = m_Bounds.GetExtents();
	for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		if (nodes[i] != nullptr)
		{
			nodes[i]->Update();
		}
	}
}

void p2QuadTree::Draw(sf::RenderWindow& window)
{
	rectangle.setPosition(meter2pixel(position) - meter2pixel(extents));
	rectangle.setSize(meter2pixel(extents)*2.0f);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(1.0f);
	rectangle.setOutlineColor(sf::Color::Blue);
	window.draw(rectangle);
	for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		if (nodes[i] != nullptr)
		{
			nodes[i]->Draw(window);
		}
	}
}
